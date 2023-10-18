#-*- coding:utf-8 -*-
import sys
import zlib
import hashlib
import os
import StringIO
import scanmod #
import curemod #
import imp

VirusDB = []
vdb = []
sdb = []
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
        v = pattern.split(':') #':'를 delimeter로 하여 분리

        scan_func = v[0] #악성코드 검사 함수
        #cure_func = v[1] #악성코드 치료 함수

        if scan_func == "ScanMD5" : #검사 함수가 MD5라면
            t.append(v[3]) #해시값 저장
            t.append(v[4]) #악성코드 이름값 저장
            vdb.append(t)  #vdb에 최종적으로 저장

            size = int(v[2]) #파일 크기 저장
            if vsize.count(size) == 0: #vsize에 해당 파일 크기가 없으면 추가
                vsize.append(size);

        elif scan_func == 'ScanStr': #검사 함수가 특정 위치 검색법이라면
            t.append(int(v[2])) #문자열의 위치 저장
            t.append(v[3]) #진단 문자열 저장
            t.append(v[4]) #악성코드 이름 저장
            sdb.append(t)  #sdb에 최종적으로 저장

if __name__ == '__main__':
    LoadVirusDB()   #바이러스 DB 불러옴
    MakeVirusDB()   #vdb 구성

    if len(sys.argv) != 2 : #파일을 입력하지 않았다면 메시지 출력 및 종료
        print('Usage : antivirus.py [file]')
        sys.exit(0) #실행파일로 변환했을때 오류 방지하기 위해 sys 명시

    fname = sys.argv[1] #파일 이름 저장

    try :
        m = 'scanmod'
        f, filename, desc = imp.find_module(m, ['']) #현재 폴더에서 모듈 탐색
        module = imp.load_module(m, f, filename, desc) #모듈 로드
        cmd = 'ret, vname = module.ScanVirus(vdb, vsize, sdb, fname)' #진단 함수 호출 명령어 구성작업
        exec(cmd) #명령어 실행
    except ImportError:
        ret, vname = scanmod.ScanVirus(vdb, vsize, sdb, fname) #동적 import에 실패하면 실행

    if ret == True:
        print("%s : %s" % (fname, vname)) #파일의 이름과 악성코드 이름 출력
        curemod.CureDelete(fname) #curemod의 CureDelete 함수 실행
    else:
        print("%s : ok" % (fname)) #파일이 안전함을 출력

