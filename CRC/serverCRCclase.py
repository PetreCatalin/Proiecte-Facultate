import socket,sys,unittest    

poli="10011"  #polinomul la care impartim
lpoli=len(poli)
 
def CRC(pachet,poli,lpoli):
    lpachet=len(pachet)
    pachet=list(pachet)
     
    for i in range(lpachet-lpoli+1):
        if (pachet[i]=='1'):
            for j in range(i,i+lpoli):
                    if pachet[j]==poli[j-i]:
                         pachet[j]='0'
                    else:
                        pachet[j]='1'
    return pachet # in pachet mai avem doar restul


class Server:
	def __init__(self):
		self.s = socket.socket()          # Create a socket object
		self.host = socket.gethostname()  # Get local machine name
		self.port = int(sys.argv[1])      # Reserve a port for your service.
		self.s.bind((self.host,self.port))         # Bind to the port
		self.s.listen(5)                  # Now wait for client connection.
		self.c, self.addr = self.s.accept()      # Establish connection with client.
		print 'Got connection from', self.addr
	def __del__(self):
		self.c.close() #Close the connection
	def prim_trim(self):

		x=self.c.recv(10) #primesc numarul de pachete
		numar=int(x)
		#print numar

		ind=0
		while True:
			ind+=1
			print '\n'
			x=self.c.recv(300)
			print "Am primit "+x
	
			lpachet=len(x)
			restprimit=''
			nr=lpachet-((lpoli-1)*5)+1  
			while nr<=lpachet-1:
				if x[nr]=='0' or x[nr]=='1':
					restprimit+=x[nr]         #pastrez restul primit
				nr+=1
	
			print "Restul primit este "+ restprimit

			trim='' #creez in trim noul mesaj de trimis catre CRC
			for i in range(0,lpachet-(lpoli-1)*5):
				if x[i]=='0' or x[i]=='1':
					  trim+=x[i]

			for i in range(lpoli-1):
				trim+='0'    #pun 0 pe ultimele pozitii in locul restului
	
			print "Trimit in CRC "+trim
			x=CRC(trim,poli,lpoli)
			x=str(x)
	
			lx=len(x)
			rest=''
			nr=lx-((lpoli-1)*5)+1  
			while nr<=lx-1:
				if x[nr]=='0' or x[nr]=='1':
					rest+=x[nr]         #pastrez restul venit din CRC
				nr+=1

			print "Restul venit din CRC este " +rest

			if rest==restprimit:
				print "Cele doua resturi coincid"
				self.c.send("DA")
			else:
				print "Cele doua resturi nu coincid"
				self.c.send("NU")
				ind-=1    #astept retrimiterea pachetului

	
			if ind==numar:     #cand am trimis toate cele nr pachete corect inapoi dau break
				break 
ob=Server()
ob.prim_trim()           
	
