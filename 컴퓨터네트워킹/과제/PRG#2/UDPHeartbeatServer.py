from socket import *
import time
import random

serverSocket = socket(AF_INET, SOCK_DGRAM) #socket을 생성한다.
serverSocket.bind(("127.0.0.1", 12000)) #host name과 port name을 이용해 bind 한다

sequence_number = 1 #sequence 횟수를 저장한 변수를 선언한다.

while True:
    serverSocket.settimeout(15)   #socket의 timeout 시간을 15초로 설정한다,
    rand = random.randint(0, 10) 
    try:
        message, address = serverSocket.recvfrom(1024)
    except timeout:
        print ("\n\nthe client application has stopped\n")
        serverSocket.close() #timeout이 된 경우 client가 정지되었다고 간주하고 socket을 close한다.
        break

    serverSocket.settimeout(None)

    if rand < 4:
        continue
    print ("\nHeartbeat " + str(sequence_number)) #sequence_number를 화면에 출력한다.
    message = message.decode() #받은 메세지를 decoding한다.
    message = message.split(" ") #메세지를 띄어쓰기 단위로 나눈다.

    sent = float(message[2]) #client가 보낸 packet의 시간을 저장한다.

    received = time.time()
    received = float("{0:.5f}".format(received))
    print ("\tReceived time = " + str(received)) #server가 받은 시간을 저장한다.

    difference = received - sent
    difference = float("{0:.5f}".format(difference))
    print ("\tTime Difference = " + str(abs(difference)) + " seconds") #client가 server로 packet을 보내고 받는데 걸린 시간을 출력한다.

    lost = int(message[1]) - sequence_number
    print ("\tNumber of packets lost = " + str(lost)) #packet lost 수를 출력한다.
    sequence_number += 1