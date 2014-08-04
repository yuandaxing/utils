import socket
import sys

server = socket.socket(socket.AF_INET,
                       socket.SOCK_STREAM)

server.setsockopt(socket.SOL_SOCKET, 
                  socket.SO_REUSEADDR, 1)
server_address = ('localhost', 8081)

print 'starting up on %s port %s' % server_address
server.bind(server_address)
server.listen(5)

connection , client_address = server.accept()

print 'connection from', connection.getpeername()

data = connection.recv(4096)
if data :
    print 'receive', repr(data)
    data = data.rstrip()
    connection.send('%s\n%s\n%s\n' %
                    ('-'*80, 
                     data.center(80),
                     '-'*80))

connection.shutdown(socket.SHUT_UP | 
                    socket.SHUT_WR)
connection.close()
print 'connection closed.'
server.close()

