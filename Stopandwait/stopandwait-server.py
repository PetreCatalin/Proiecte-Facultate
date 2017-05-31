import socket,sys,time              

s = socket.socket()          # Create a socket object
host = socket.gethostname()  # Get local machine name
port = int(sys.argv[1])      # Reserve a port for your service.
Ts = int(sys.argv[2])     
s.bind((host, port))         # Bind to the port

s.listen(5)                  # Now wait for client connection.

c, addr = s.accept()      # Establish connection with client.
print 'Got connection from', addr

while True:
	x=c.recv(9)
	if x=="final":
		break
	time.sleep(Ts)
	c.send(x[0]+'ACK')

c.close()               #Close the connection              
	
