#-*- coding:utf-8 -*-
import sys
import zlib
import hashlib
import os
import StringIO

VirusDB = []
vdb = []
vsize = []

def DecodeKMD(fname):
    try :
        fp = open(fname, 'rb') #파일을 이진 파일로 불러옴
        buf = fp.read() #파일 내용 저장
        fp.close() #파일 닫음

        buf2 = buf[:-32] #암호화 내용 분리
        fmd5 = buf[-32:] #MD5 분리

        f = buf2
        for i in range(3):
            md5 = hashlib.md5() #해싱함수 불러옴
            md5.update(f) #해시값 구함
            f = md5.hexdigest() #해시값 저장

        if f != fmd5: #분리한 MD5 값과 같은지 확인
            raise SystemError
        
        buf3 = ''
        for c in buf2[4:]:
            buf3 += chr(ord(c) ^ 0xFF) #0xFF로 xor 한다
        buf4 = zlib.decompress(buf3) #압축을 해제한다
        return buf4 #복호화된 내용 반환
    except :
        pass

    return None #오류가 있으면 None 반환

def LoadVirusDB():
    buf = DecodeKMD('virus.kmd') #virus.kmd를 복호화
    fp = StringIO.StringIO(buf) #복호화한 파일을 불러옴

    while True:
        line = fp.readline()    #라인 별로 저장
        if not line : break     #읽을 라인 없을 경우 while 탈출

        line = line.strip()     #선행과 후행 문자 제거
        VirusDB.append(line)    #VirusDB에 저장
    fp.close() #파일 종료

def MakeVirusDB():
    for pattern in VirusDB:
        t = []
        v = pattern.split(':')  #':'를 delimeter로 하여 분리
        t.append(v[1])          #해시 값 저장
        t.append(v[2])          #악성코드 이름 저장
        vdb.append(t)           #vdb에 최종적으로 저장

        size = int(v[0])        #파일 크기 저장
        if vsize.count(size) == 0: #vsize에 해당 파일 크기가 없으면 추가
            vsize.append(size);

def SearchVDB(fmd5):
    for t in vdb:
        if t[0] == fmd5:      #vdb에서 해시를 검색해서 존재여부 확인
            return True, t[1] #존재하면 True와 함께 악성코드 이름 반환
    return False, ' '         #존재하지 않으면 False와 함께 빈 string 반환

def ScanMD5(fname):
    ret = False
    vname = ''

    size = os.path.getsize(fname) #파일의 사이즈 저장
    if vsize.count(size):   #파일의 사이즈가 vsize에 존재한다면
        fp = open(fname, 'rb') #파일 불러옴
        fbuf = fp.read() #파일의 내용 저장
        fp.close() #파일 닫음

        m = hashlib.md5() #해싱함수 불러옴
        m.update(fbuf) #해시값 계산
        fmd5 = m.hexdigest() #해시값 저장

        ret, vname = SearchVDB(fmd5) #해시값 검색
    return ret, vname

if __name__ == '__main__':
    LoadVirusDB()   #바이러스 DB 불러옴
    MakeVirusDB()   #vdb 구성

    if len(sys.argv) != 2 : #파일을 입력하지 않았다면 메시지 출력 및 종료
        print('Usage : antivirus.py [file]')
        exit(0)

    fname = sys.argv[1] #파일 이름 저장

    ret, vname = ScanMD5(fname) #MD5 해시로 바이러스 스캔

    if ret == True: #악성코드 존재하면 파일 이름과 악성코드 이름 출력
        print("%s : %s" % (fname, vname))   
        os.remove(fname) #악성코드 파일 삭제
    else:
        print("%s : ok" % (fname)) #파일 이름 출력하며 안전함을 출력

