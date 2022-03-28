import socket
import os
import sys
import struct
import threading
import optparse
import time

def socket_client(client_name,times):
    try:
        client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        port = 2680
        client_sock.connect(('10.0.0.1', port))
    except socket.error as msg:
        print(msg)
        sys.exit(1)
    
    start_time = time.time()
    filename = ('./%s/load_data%d.txt' % (client_name, times))
    fp = open(filename, 'wb')

    max_data = 500
    while True:
        datareceived = client_sock.recv(max_data)
        if not datareceived:
            break
        fp.write(datareceived)

    fp.close()
    client_sock.close()
    end_time = time.time()
    print('File download successfully! It spend {} seconds to transfer to {}\n'.format(end_time - start_time, client_name))


if __name__ == '__main__':
    parser = optparse.OptionParser()
    parser.add_option('-n', dest='name', type=str)
    parser.add_option('-t', dest='times', type=int)
    (opt, args) = parser.parse_args()
    socket_client(opt.name, opt.times)