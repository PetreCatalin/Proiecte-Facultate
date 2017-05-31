import socket,sys,time            # Import socket module

s = socket.socket()         # Create a socket object
host = socket.gethostname() # Get local machine name
port = int(sys.argv[1])               # Reserve a port for your service.
Tc = int(sys.argv[2])

print("Inroduceti numarul de pachete pe care doriti sa le trimiteti");
nr=input()
lista=[]
for i in range(nr):
	lista.append("pachet "+str(i+1))

s.connect((host, port))

cb=0
for x in range(nr):
	while True:
		try:
			print "Am trimis "+str(cb)+lista[x]
			s.send(str(cb)+lista[x])    #trimit fiecare pachet si vad ce am primit pentru el
			s.settimeout(Tc)
			v=s.recv(5)
			if v[0]==str(cb):
				print "Am primit " +v +" pentru "+str(cb)+lista[x]
				cb=(cb+1)%2
				break #merg la urmatorul pachet
			else:
				print "Checkbitul nu corespunde"
			cb=(cb+1)%2
		except socket.timeout,eroare:
			print ("A expirat timpul,retrimit pachetul")
			cb=(cb+1)%2
	print '\n'
s.send("final")
s.close()                     # Close the socket when done
