import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('localhost', 8081))
s.send('happy hacking')
data = s.recv(1024)
s.close()
print data
