import random
from socket import *

serverSocket = socket(AF_INET, SOCK_DGRAM)#socket을 생성한다.
serverSocket.bind(('127.0.0.1', 12000)) #host name과 port name을 이용해 bind 한다

while True:

	rand = random.randint(0, 10) #0에서 10까지 무작위로 수를 생성한다. 
	message, address = serverSocket.recvfrom(1024) #client로부터 메세지를 받는다.
	message = message.upper() #메세지의 내용을 대문자로 바꾼다.
	
	if rand < 4:
		continue #무작위로 생성한 수가 4보다 작은 경우 client로 메세지를 전달하지 않는다. -> 40% 확률로 packet lost
	serverSocket.sendto(message, address) #그렇지 않으면 client로 메세지를 전달한다.

