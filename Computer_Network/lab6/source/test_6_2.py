# Copyright (C) 2011 Nippon Telegraph and Telephone Corporation.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
# implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from ryu.base import app_manager
from ryu.controller import ofp_event
from ryu.controller.handler import CONFIG_DISPATCHER, MAIN_DISPATCHER
from ryu.controller.handler import set_ev_cls
from ryu.ofproto import ofproto_v1_3
from ryu.lib.packet import packet, ethernet, arp, ipv6, ipv4
from ryu.lib import mac
from ryu.lib.packet import ether_types
import time

global hard_timeout
hard_timeout = 5
global up_path
up_path = 1


class ARP_PROXY_13(app_manager.RyuApp):
    OFP_VERSIONS = [ofproto_v1_3.OFP_VERSION]

    def __init__(self, *args, **kwargs):
        super(ARP_PROXY_13, self).__init__(*args, **kwargs)
        self.mac_to_port = {} # out_port = self.mac_to_port[dpid][dst]
        self.arp_table = {} # arp_dst_ip in self.arp_table ---- store the mac address of dst ip
        self.sw = {} # (datapath.id, arp_src_ip, arp_dst_ip) in self.sw
        self.dp = {} # switch id : datapath

    @set_ev_cls(ofp_event.EventOFPSwitchFeatures, CONFIG_DISPATCHER)
    def switch_features_handler(self, ev):
        datapath = ev.msg.datapath
        if datapath.id not in self.dp:
            self.dp[datapath.id] = datapath
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser

        # install table-miss flow entry
        #
        # we specify NO BUFFER to mac_len of the output action due to
        # OVS bug. At this moment, if we specify a lesser number, e.g.,
        # 128, OVS will send Packet-In with invalid buffer_id and truncated packet data.
        # In that case, we cannot output packets correctly.
        match = parser.OFPMatch()
        actions = [parser.OFPActionOutput(ofproto.OFPP_CONTROLLER,
                                          ofproto.OFPCML_NO_BUFFER)]
        self.add_flow(datapath, 0, match, actions)
        self.logger.info("switch: %s connected", datapath.id) # datapath includes the id and other information of switch

    def add_flow(self, datapath, priority, match, actions, hard_timeout = 0):
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser

        inst = [parser.OFPInstructionActions(ofproto.OFPIT_APPLY_ACTIONS, actions)]

        if hard_timeout:
            mod = parser.OFPFlowMod(datapath=datapath,
                                    priority=priority, match=match, hard_timeout = hard_timeout,
                                    instructions=inst)
        else:
            mod = parser.OFPFlowMod(datapath=datapath, priority=priority,
                                    match=match, instructions=inst)
        datapath.send_msg(mod)

    @set_ev_cls(ofp_event.EventOFPPacketIn, MAIN_DISPATCHER)
    def _packet_in_handler(self, ev):
        global hard_timeout
        global up_path

        hard_timeout = 0

        # If you hit this you might want to increase
        # the "miss_send_length" of your switch
        if ev.msg.msg_len < ev.msg.total_len:
            self.logger.debug("packet truncated: only %s of %s bytes",
                              ev.msg.msg_len, ev.msg.total_len)

        msg = ev.msg
        datapath = msg.datapath
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser
        in_port = msg.match['in_port']

        pkt = packet.Packet(msg.data)
        eth = pkt.get_protocols(ethernet.ethernet)[0]

        dst = eth.dst
        src = eth.src

        dpid = datapath.id

        if eth.ethertype == ether_types.ETH_TYPE_LLDP:
            # ignore lldp packet
            return

        if pkt.get_protocol(ipv6.ipv6):  # drop the ipv6 packets
            match = parser.OFPMatch(eth_type=eth.ethertype)
            actions = []
            self.add_flow(datapath, 1, match, actions)
            return None

        # if there is a arp packet
        arp_pkt = pkt.get_protocol(arp.arp) # when arp request happens, avoid arp storm

        if arp_pkt:
            self.arp_table[arp_pkt.src_ip] = src        #ARP learning
            #self.logger.info(" ARP: %s -> %s", arp_pkt.src_ip, arp_pkt.dst_ip)
            if self.arp_handler(msg):               #answer or drop
                return None


        # the following steps are about handling ususal packet

        self.mac_to_port.setdefault(dpid, {})
        self.logger.info("packet in: switch:%s source:%s destination:%s in port:%s", dpid, src, dst, in_port)

        # learn a mac address to avoid FLOOD next time.
        if src not in self.mac_to_port[dpid]:
            self.mac_to_port[dpid][src] = in_port
        # print self.mac_to_port
        if dst in self.mac_to_port[dpid]:
            out_port = self.mac_to_port[dpid][dst]
        else:
            #print(self.mac_to_port[dpid])
            out_port = ofproto.OFPP_FLOOD
            #print("Flood")
        
        ipv_4 = pkt.get_protocol(ipv4.ipv4)
        if ipv_4:
            if dpid == 3 or dpid == 4:
                out_port = 3 - in_port

            if dpid == 2:
                if in_port == 1:
                    hard_timeout = 5
                    if up_path:
                        out_port = 2
                        up_path = 0
                        self.add_flow(self.dp[1], 1, parser.OFPMatch(in_port=in_port, eth_dst=src), [parser.OFPActionOutput(out_port)], hard_timeout)
                        self.logger.info("install flow_mod in datapath %s in switch %s: %s -> %s",self.dp[1], 1, in_port, out_port)
                    else:
                        out_port = 3
                        up_path = 1
                        self.add_flow(self.dp[1], 1, parser.OFPMatch(in_port=in_port, eth_dst=src), [parser.OFPActionOutput(out_port)], hard_timeout)
                        self.logger.info("install flow_mod in datapath %s in switch %s: %s -> %s",self.dp[1], 1, in_port, out_port)
                else:
                    out_port = 1

            if dpid == 1:
                if in_port == 1:
                    hard_timeout = 5
                    if up_path:
                        out_port = 2
                        up_path = 0
                        self.add_flow(self.dp[2], 1, parser.OFPMatch(in_port=in_port, eth_dst=src), [parser.OFPActionOutput(out_port)], hard_timeout)
                        self.logger.info("install flow_mod in datapath %s in switch %s: %s -> %s",self.dp[2], 2, in_port, out_port)
                    else:
                        out_port = 3
                        up_path = 1
                        self.add_flow(self.dp[2], 1, parser.OFPMatch(in_port=in_port, eth_dst=src), [parser.OFPActionOutput(out_port)], hard_timeout)
                        self.logger.info("install flow_mod in datapath %s in switch %s: %s -> %s",self.dp[2], 2, in_port, out_port)
                else:
                    out_port = 1

        actions = [parser.OFPActionOutput(out_port)]

        # install a flow to avoid packet_in next time.
        if out_port != ofproto.OFPP_FLOOD:
            self.logger.info("install flow_mod in datapath %s in switch %s: %s -> %s",datapath, dpid, in_port, out_port)
            match = parser.OFPMatch(in_port=in_port, eth_dst=dst)
            self.add_flow(datapath, 1, match, actions, hard_timeout)

        data = None
        if msg.buffer_id == ofproto.OFP_NO_BUFFER:
            data = msg.data
        out = parser.OFPPacketOut(datapath=datapath, buffer_id=msg.buffer_id,
                                    in_port=in_port, actions=actions, data=data)

        datapath.send_msg(out)

    def arp_handler(self, msg):
        datapath = msg.datapath
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser
        in_port = msg.match['in_port']

        pkt = packet.Packet(msg.data)
        eth = pkt.get_protocols(ethernet.ethernet)[0]
        arp_pkt = pkt.get_protocol(arp.arp)

        if eth:
            eth_dst = eth.dst
            eth_src = eth.src

        # to handle with arp storm, every switch only allows one in port to ask mac address

        # sw[(datapath.id, eth_src, arp_dst_ip)] = in_port

        # Break the loop for avoiding ARP broadcast storm
        if eth_dst == mac.BROADCAST_STR:            # and arp_pkt
            arp_dst_ip = arp_pkt.dst_ip
            arp_src_ip = arp_pkt.src_ip

            if (datapath.id, arp_src_ip, arp_dst_ip) in self.sw:
                # packet come back at different port.
                if self.sw[(datapath.id, arp_src_ip, arp_dst_ip)] != in_port: # don't match the asking in port, drop
                    if arp_dst_ip in self.arp_table:    # arp reply
                        #actions = [parser.OFPActionOutput(ofproto.OFPP_FLOOD)]
                        actions = [parser.OFPActionOutput(in_port)]
                        ARP_Reply = packet.Packet()

                        ARP_Reply.add_protocol(ethernet.ethernet(ethertype=eth.ethertype,
                                                                dst=eth.src,
                                                                src=self.arp_table[arp_dst_ip]))
                        ARP_Reply.add_protocol(arp.arp(opcode=arp.ARP_REPLY,
                                                    src_mac=self.arp_table[arp_dst_ip],
                                                    src_ip=arp_dst_ip,
                                                    dst_mac=eth_src, dst_ip=arp_src_ip))

                        ARP_Reply.serialize()
                        
                        out = datapath.ofproto_parser.OFPPacketOut(datapath=datapath,
                                                                buffer_id=datapath.ofproto.OFP_NO_BUFFER,
                                                                in_port=datapath.ofproto.OFPP_CONTROLLER,
                                                                actions=actions, data=ARP_Reply.data)
                        datapath.send_msg(out)
                        #print("ARP Reply")
                    datapath.send_packet_out(in_port=in_port, actions=[])
                    return True
            else:
                self.sw[(datapath.id, arp_src_ip, arp_dst_ip)] = in_port
                #print(self.sw)
                self.mac_to_port.setdefault(datapath.id, {})
                self.mac_to_port[datapath.id][eth_src] = in_port

        if arp_pkt:

            opcode = arp_pkt.opcode

            if opcode == arp.ARP_REQUEST:
                hwtype = arp_pkt.hwtype
                proto = arp_pkt.proto
                hlen = arp_pkt.hlen
                plen = arp_pkt.plen

                arp_src_ip = arp_pkt.src_ip
                arp_dst_ip = arp_pkt.dst_ip

                if arp_dst_ip in self.arp_table:    # arp reply
                    #actions = [parser.OFPActionOutput(ofproto.OFPP_FLOOD)]
                    actions = [parser.OFPActionOutput(in_port)]
                    ARP_Reply = packet.Packet()

                    ARP_Reply.add_protocol(ethernet.ethernet(ethertype=eth.ethertype,
                                                             dst=eth.src,
                                                             src=self.arp_table[arp_dst_ip]))
                    ARP_Reply.add_protocol(arp.arp(opcode=arp.ARP_REPLY,
                                                   src_mac=self.arp_table[arp_dst_ip],
                                                   src_ip=arp_dst_ip,
                                                   dst_mac=eth_src, dst_ip=arp_src_ip))

                    ARP_Reply.serialize()

                    
                    out = datapath.ofproto_parser.OFPPacketOut(datapath=datapath,
                                                               buffer_id=datapath.ofproto.OFP_NO_BUFFER,
                                                               in_port=datapath.ofproto.OFPP_CONTROLLER,
                                                               actions=actions, data=ARP_Reply.data)
                    datapath.send_msg(out)

                    return True
        return False
