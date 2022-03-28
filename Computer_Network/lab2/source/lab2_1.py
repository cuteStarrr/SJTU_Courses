#!/usr/bin/env python

from mininet.net import Mininet
from mininet.node import Controller, RemoteController, OVSController
from mininet.node import CPULimitedHost, Host, Node
from mininet.node import OVSKernelSwitch, UserSwitch
from mininet.node import IVSSwitch
from mininet.cli import CLI
from mininet.log import setLogLevel, info
from mininet.link import TCLink, Intf
from subprocess import call

def myNetwork():

    net = Mininet( topo=None,
                   build=False,
                   ipBase='10.0.0.0/8')

    info( '*** Adding controller\n' )
    info( '*** Add switches\n')
    s1 = net.addSwitch('s1', cls=OVSKernelSwitch, failMode='standalone')
    s2 = net.addSwitch('s2', cls=OVSKernelSwitch, failMode='standalone')
    s3 = net.addSwitch('s3', cls=OVSKernelSwitch, failMode='standalone')

    info( '*** Add hosts\n')
    h1 = net.addHost('h1', cls=Host, ip='10.0.0.1', defaultRoute=None)
    h2 = net.addHost('h2', cls=Host, ip='10.0.0.2', defaultRoute=None)
    h3 = net.addHost('h3', cls=Host, ip='10.0.0.3', defaultRoute=None)

    info( '*** Add links\n')
    net.addLink(h1, s1)
    net.addLink(s2, h2)
    net.addLink(s3, h3)
    s1s2 = {'bw':10,'loss':5}
    net.addLink(s1, s2, cls=TCLink , **s1s2)
    s1s3 = {'bw':10,'loss':5}
    net.addLink(s1, s3, cls=TCLink , **s1s3)
    net.addLink(s2, s3)

    info( '*** Starting network\n')
    net.build()
    info( '*** Starting controllers\n')
    for controller in net.controllers:
        controller.start()

    info( '*** Starting switches\n')
    net.get('s1').start([])
    net.get('s2').start([])
    net.get('s3').start([])

    info( '*** Post configure switches and hosts\n')

    s1.cmd('ovs-ofctl add-flow s1 in_port=2,actions=output:1')
    s1.cmd('ovs-ofctl add-flow s1 in_port=3,actions=output:1')
    s2.cmd('ovs-ofctl add-flow s2 in_port=3,actions=output:1')
    s2.cmd('ovs-ofctl add-flow s2 in_port=2,actions=output:1')
    s3.cmd('ovs-ofctl add-flow s3 in_port=2,actions=output:1')
    s3.cmd('ovs-ofctl add-flow s3 in_port=3,actions=output:1')
    
    s3.cmd('ovs-ofctl add-flow s3 in_port=1,actions=all')
    s2.cmd('ovs-ofctl add-flow s2 in_port=1,actions=all')
    s1.cmd('ovs-ofctl add-flow s1 in_port=1,actions=all')

    CLI(net)
    net.stop()

if __name__ == '__main__':
    setLogLevel( 'info' )
    myNetwork()

