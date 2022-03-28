#!/usr/bin/env python

import time
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

    info( '*** Add hosts\n')
    server = net.addHost('server', cls=Host, ip='10.0.0.1', defaultRoute=None)
    client1 = net.addHost('client1', cls=Host, ip='10.0.0.2', defaultRoute=None)
    client2 = net.addHost('client2', cls=Host, ip='10.0.0.3', defaultRoute=None)
    client3 = net.addHost('client3', cls=Host, ip='10.0.0.4', defaultRoute=None)
    client4 = net.addHost('client4', cls=Host, ip='10.0.0.5', defaultRoute=None)
    client5 = net.addHost('client5', cls=Host, ip='10.0.0.6', defaultRoute=None)
    client6 = net.addHost('client6', cls=Host, ip='10.0.0.7', defaultRoute=None)

    info( '*** Add links\n')
    net.addLink(s1, server)
    net.addLink(s1, client1)
    net.addLink(s1, client2)
    net.addLink(s1, client3)
    net.addLink(s1, client4)
    net.addLink(s1, client5)
    net.addLink(s1, client6)

    info( '*** Starting network\n')
    net.build()
    info( '*** Starting controllers\n')
    for controller in net.controllers:
        controller.start()

    info( '*** Starting switches\n')
    net.get('s1').start([])

    info( '*** Post configure switches and hosts\n')

    '''
    server.cmdPrint('python3 -u s.py > server.log &')
    time.sleep(1)
    client1.cmdPrint('python3 c.py -n h1 -i 10.0.0.1')
    '''

    
    server.cmd('python3 -u server.py > server.log &')
    time.sleep(3)

    i = 5
    while i > 0:
        client1.cmdPrint('python3 client.py -n client1 -t %d &' % i)
        client2.cmdPrint('python3 client.py -n client2 -t %d &' % i)
        client3.cmdPrint('python3 client.py -n client3 -t %d &' % i)
        client4.cmdPrint('python3 client.py -n client4 -t %d &' % i)
        client4.cmdPrint('python3 client.py -n client5 -t %d &' % i)
        client6.cmdPrint('python3 client.py -n client6 -t %d &' % i)
        i = i - 1
    

    CLI(net)
    net.stop()

if __name__ == '__main__':
    setLogLevel( 'info' )
    myNetwork()

