#-*- coding:utf-8 -*-
import hashlib
import os

fp = open('eicar.txt', 'rb') #eicar.txt를 이진 파일로 open
fbuf = fp.read()             #eicar.txt 파일의 내용을 저장
fp.close()                   #파일 close

m = hashlib.md5()            #md5 해시함수 불러옴
m.update(fbuf)               #문자열 hello 해싱
fmd5 = m.hexdigest()         #해싱된 문자열 저장

if fmd5 == '44d88612fea8a8f36de82e1278abb02f': #해시값 비교
    print("Virus")          #같으면 바이러스
    os.remove('eicar.txt')  #바이러스 파일 삭제
else:
    print("No Virus")       #바이러스 아님