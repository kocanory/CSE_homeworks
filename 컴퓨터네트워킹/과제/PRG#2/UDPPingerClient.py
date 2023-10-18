import socket
from socket import AF_INET, SOCK_DGRAM
import time

print ("        Response ping") #Statement to let me know the program started correctly
print ("===============================")
serverName = "127.0.0.1" #테스트를 위해 local host의 ip를 사용한다.
clientSocket = socket.socket(AF_INET, SOCK_DGRAM) #socket을 생성한다.
min_time = 1.0 #RTTs의 min 값을 저장하기 위한 변수를 선언한다.
max_time = 0.0 #RTTs의 max 값을 저장하기 위한 변수를 선언한다.
sum_time = 0.0 #RTTs의 average를 구하기 위해 RTT들의 sum을 저장하는 변수를 선언한다.
count = 0 #reponse 횟수를 저장하기 위한 변수를 선언한다.
sequence_number = 1 #sequence 횟수를 저장한 변수를 선언한다.
while sequence_number<=10:
        message = "Ping" #server에게 전송할 메시지를 저장한다.
        start=time.time() #RTT를 구하기 위해, packet을 전송할 때의 시간을 저장한다.
        clientSocket.sendto(message.encode(), (serverName, 12000))#server 에게 메시지를 보낸다.
        
        try:
                clientSocket.settimeout(1) #socket의 timeout 시간을 1초로 설정한다,
                message, address = clientSocket.recvfrom(1024) #server에게 메시지를 수신한다.
                elapsed = (time.time()-start) # RTT를 계산한다.
                elapsed = float("{0:.5f}".format(elapsed)) #소수점 5자리 이하의 숫자는 출력이 안되도록 한다.
                min_time = min(min_time, elapsed) #현재 packet의 RTT와 minimum 값을 비교하여 변수에 더 작은 값을 저장한다.
                max_time = max(max_time, elapsed) #현재 packet의 RTT와 maximum 값을 비교하여 변수에 더 큰 값을 저장한다.
                sum_time+=elapsed #average를 구하기 위해 RTT 값을 저장한다.
                count+=1 #response를 성공한 횟수 1 증가시킨다.
                print ("    " + message.decode() + "    " + str(sequence_number) +  "    " + str(elapsed) + " sec") #메시지와 sequence_number, RTT를 출력한다.
                clientSocket.settimeout(None) #socket의 timeout 초기화한다,               

        except socket.timeout: #socket이 1초 이내로 response를 받지 못할경우 출력한다.
                print (str(sequence_number) + " : Request timed out")

        print ("")
        sequence_number+=1 #sequence 횟수를 1 증가시킨다.
        if sequence_number > 10: #sequence 횟수가 10을 넘어갔을 경우 socket을 close한다.
            clientSocket.close()

average_time = sum_time / count #RTTs의 average 시간을 구한다.
rate = (sequence_number - 1 - count) / (sequence_number - 1)  * 100 #packet loss rate를 구한다.
min_time = float("{0:.5f}".format(min_time)) #소수점 5자리 이하의 숫자는 출력이 안되도록 한다.
max_time = float("{0:.5f}".format(max_time)) #소수점 5자리 이하의 숫자는 출력이 안되도록 한다.
average_time = float("{0:.5f}".format(average_time)) #소수점 5자리 이하의 숫자는 출력이 안되도록 한다.

print("Minimum RTT = " + str(min_time) + " sec") #RTTs의 minimum 시간을 출력한다.
print("Maximum RTT = " + str(max_time) + " sec") #RTTs의 maximum 시간을 출력한다.
print("Average RTTs = " + str(average_time) + " sec") #RTTs의 average 시간을 출력한다.
print("Packet loss rate = " + str(rate) + "%") #packet loss rate을 출력한다.
print("")