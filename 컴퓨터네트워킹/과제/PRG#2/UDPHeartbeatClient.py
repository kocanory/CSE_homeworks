import socket
from socket import AF_INET, SOCK_DGRAM
import time

clientSocket = socket.socket(AF_INET, SOCK_DGRAM) #socket을 생성한다.

serverName = "127.0.0.1" #테스트를 위해 local host의 ip를 사용한다.

sequence_number = 1 #sequence 횟수를 저장한 변수를 선언한다.

while True:
    start=time.time()
    start = float("{0:.5f}".format(start))
    message = "Ping " + str(sequence_number) + " " + str(start) #server에게 전송할 메시지를 저장한다.

    clientSocket.sendto(message.encode(), (serverName, 12000)) #server 에게 메시지를 보낸다.
    print ("\n" + message) #메세지를 화면에 출력한다.
    sequence_number += 1 #sequence 횟수를 1 증가시킨다.

    time.sleep(5) #10초마다 서버에게 메세지를 보내도록 한다.