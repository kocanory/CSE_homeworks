#-*- coding:utf-8 -*-
import hashlib
import os
import sys

VirusDB = ['44d88612fea8a8f36de82e1278abb02f:EICAR Test', 
           '77bff0b143e4840ae73d4582a8914a43:Dummy Test'] #악성코드 DB 저장


vdb = []

def MakeVirusDB():
    for pattern in VirusDB:
        t = []
        v = pattern.split(':') #':'를 delimeter로 하여 분리
        t.append(v[0])         # 해시 값 저장
        t.append(v[1])         # 악성코드 이름 저장
        vdb.append(t)          # vdb에 최종적으로 저장

def SearchVDB(fmd5):
    for t in vdb:
        if t[0] == fmd5:      #vdb에서 해시를 검색해서 존재여부 확인
            return True, t[1] #존재하면 True와 함께 악성코드 이름 반환
    return False, ' '         #존재하지 않으면 False와 함께 빈 string 반환

if __name__ == '__main__':
    MakeVirusDB()            #vdb 구성

    if len(sys.argv) != 2 : #파일을 입력하지 않았다면 메시지 출력 및 종료
        print('Usage : antivirus.py [file]')
        exit(0)

    fname = sys.argv[1] #파일 이름 저장

    fp = open(fname, 'rb')  #파일을 이진 파일로 불러옴
    fbuf = fp.read() #파일 내용 저장
    fp.close()  #파일 닫음

    m = hashlib.md5()   #해싱함수 불러옴
    m.update(fbuf)      #해싱 진행
    fmd5 = m.hexdigest()#해싱값 저장

    ret, vname = SearchVDB(fmd5)   #vdb에서 악성코드 검색
    if ret == True: #악성코드 존재하면 파일 이름과 악성코드 이름 출력
        print("%s : %s" % (fname, vname))   
        os.remove(fname) #악성코드 파일 삭제
    else:
        print("%s : ok" % (fname)) #파일 이름 출력하며 안전함을 출력
