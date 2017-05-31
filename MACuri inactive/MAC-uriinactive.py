import os
import re
import sys
import time

try:
	#f=open(str(sys.argv[1]),'r') # dau fisierul in1.txt ca argument
	print("Introduceti de cate ori doriti sa afisati MAC-urile inactive")
	n=input()
	print("Introduceti numarul de secunde dupa care doriti sa se repete procesul")
	t=input()

	data=dict()
	with open(str(sys.argv[1]),'r') as f:
		for line in f:
			data.update({line:0}) #marchez toate MAC-urile initiale ca fiind inactive

	def GetMac(data,nr):
		for x in data:
			if data[x]==1: #daca MAC-urile au fost active le fac inactive
				data[x]=0

		s=os.popen("sudo arp-scan -l").read() #aflu si prelucrez MAC-urile active,dupa care le pun intr-o lista
		s=re.split("\n",s)
		s=[re.split("\t+" ,entry,4) for entry in s]
		lista=[]
		for entry in s:
			for x in entry:
				if len(str(x))==17 and x[2]==':':
					lista.append(x)

		for x in lista:
			data[x]=1; #daca MAC-ul exista il modific ca activ,daca nu exista il adaug in dictionar ca fiind activ

		print("MAC-uri inactive dupa "+str(t*nr)+" secunde: \n")
		for x in data:
			if data[x]==0:
				print x
	
		print('\n')
		time.sleep(t)
	

	for nr in range(n):
		GetMac(data,nr)

	f=open(str(sys.argv[1]),'w')
	for x in data:
		f.write(x+"\n")

	f.close()
except:
	print("Fisierul dat nu exita\n")
	


