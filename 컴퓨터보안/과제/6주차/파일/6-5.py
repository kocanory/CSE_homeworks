#-*- coding:utf-8 -*-
import sys
import zlib
import hashlib
import os

def main():
    if  len(sys.argv) != 2: #파일 입력이 없는 경우 메세지 출력 및 함수 종료
        print("Usage : kmake.py [file]")
        return
    
    fname = sys.argv[1] #파일 이름 저장
    tname = fname

    fp = open(tname, 'rb') #파일을 이진 파일로 불러옴
    buf = fp.read() #파일 내용 저장
    fp.close()  #파일 닫음

    buf2 = zlib.compress(buf) #파일 내용 압축

    buf3 = ''
    for c in buf2:
        buf3 += chr(ord(c) ^ 0xFF) #압축된 내용을 0xFF로 xor

    buf4 = 'KAVM' + buf3 #헤더 생성
    f = buf4 

    for i in range(3):
        md5 = hashlib.md5() #해싱함수 불러옴
        md5.update(f) #해시값 구함
        f = md5.hexdigest() #해시값 저장

    buf4 += f #암호화된 내용에 해시값 저장

    kmd_name = fname.split('.')[0] + '.kmd'#파일 이름에 .kmd 확장자 추가
    fp = open(kmd_name, 'wb') #kmd 확장자로 암호 파일 생성
    fp.write(buf4) #파일 출력
    fp.close() #파일 닫음

    print("%s -> %s" % (fname, kmd_name)) #파일 이름과 암호화된 파일 이름 출력

if __name__ == '__main__':
    main()