#-*- coding:utf-8 -*-
import os

fp = open('eicar.txt', 'rb') #eicar.txt를 이진 파일로 open
fbuf = fp.read()             #eicar.txt 파일의 내용을 저장
fp.close()                   #파일 close

if fbuf[0:3] == b'X5O':      #[0:3]의 내용이 X5O인지 판별                             
    print("Virus")           #바이러스 임을 출력
    os.remove('eicar.txt')   #eicar.txt 파일 삭제
else:
    print("No Virus")        #바이러스가 아님을 출력