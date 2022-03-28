import socket
import os
import sys
import struct
import threading
import time

def file_transfer(ans_sock, addr):
    start_time = time.time()
    max_data = 500
    fp = open('data.txt', 'rb')
    while True:
        datasending = fp.read(max_data)
        #print(datasending)
        if not datasending:
            break
        ans_sock.send(datasending)

    fp.close()
    ans_sock.close()
    end_time = time.time()
    print('File transfer successfully! It spend {} seconds to transfer to client {}\n'.format(end_time - start_time, addr))


def socket_server():
    try:
        welcome_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        port = 2680
        welcome_sock.bind(('10.0.0.1', port))
        max_queue = 5
        welcome_sock.listen(max_queue)
        print('server ready\n')
        time.sleep(1)
    except socket.error as msg:
        print(msg)
        sys.exit(1)

    while True:
        answer_sock, client_addr = welcome_sock.accept()
        print('accept a client with ip address of {}!'.format(client_addr))

        thread_server = threading.Thread(target= file_transfer, args=(answer_sock,client_addr))
        thread_server.setDaemon(True)
        thread_server.start()

if __name__ == '__main__':
    socket_server()