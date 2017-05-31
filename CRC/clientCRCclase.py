import socket,sys,unittest

poli="10011" 
lpoli=len(poli)
zero=''
for i in range(1,lpoli):    #pun gradul polinomului zerouri la finalul pachetului
	zero+='0'

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
					#print j,pachet[j]
	return pachet # in pachet mai avem doar restul


lista=[]
nr=0
with open("pachete.in",'r') as f:
	for line in f:
		nr=nr+1  #numarul de pachete
		lista.append(line[0:len(line)-1]+zero) #citesc toate pachetele din fisier si adaug zero la final  



class Client:
	def __init__(self):
		self.s = socket.socket()         # Create a socket object
		self.host = socket.gethostname() # Get local machine name
		self.port = int(sys.argv[1])               # Reserve a port for your service.
		self.s.connect((self.host,self.port))
	def __del__(self):
		self.s.close() #Close the socket when done

	def trimite(self):
		self.s.send(str(nr)) #trimit numarul de pachete

		for x in range(nr):
			rest=CRC(lista[x],poli,lpoli)
			#print "Restul la impartirea pachetului "+lista[x]+" la "+poli+" este "+str(rest)
			#print '\n'
	
			lpachet=len(lista[x])
			lista[x]=list(lista[x])
	
			for i in range(lpachet-lpoli+1,lpachet):
				lista[x][i]=rest[i]      #inlocuiesc in pachet bitii de 0 de la final cu restul


		for x in range(nr):
			while True:
				print "Am trimis "+str(lista[x])
				self.s.send(str(lista[x]))
				v=self.s.recv(5)
				print "Am primit "+v
				print '\n'
		
				if v=="DA":
					break   #am primit pachetul cum trebuie,merg la urmatorul,altfel retrimit
ob=Client()
ob.trimite()
