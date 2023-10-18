#-*- coding:utf-8 -*-
import os
import hashlib

def SearchVDB(vdb, fmd5):
    for t in vdb:
        if t[0] == fmd5:      #vdb에서 해시를 검색해서 존재여부 확인
            return True, t[1] #존재하면 True와 함께 악성코드 이름 반환
    return False, ' '         #존재하지 않으면 False와 함께 빈 string 반환

def ScanMD5(vdb, vsize, fname):
    ret = False
    vname = ''

    size = os.path.getsize(fname) #입력받은 파일의 크기 저장
    if vsize.count(size):   #vsize에 입력 받은 파일의 크기가 저장되어 있다면
        fp = open(fname, 'rb')  #파일을 이진 파일로 불러옴
        fbuf = fp.read() #파일 내용 저장
        fp.close()  #파일 닫음

        m = hashlib.md5()   #해싱함수 불러옴
        m.update(fbuf)      #해싱 진행
        fmd5 = m.hexdigest()#해싱값 저장

        ret, vname = SearchVDB(vdb, fmd5) #vdb에서 악성코드 검색
    return ret, vname #검사 결과와 악성코드 이름 반환

def ScanStr(fp, offset, mal_str):
    size = len(mal_str) #악성코드 진단 문자열의 길이 저장

    fp.seek(offset) #문자열이 존재할 것으로 예상되는 위치로 이동
    buf = fp.read(size) #길이만큼 읽기
    if buf == mal_str: 
        return True #악성코드 발견
    else:
        return False #악성코드 미발견

   
def ScanVirus(vdb, vsize, sdb, fname):
    ret, vname = ScanMD5(vdb, vsize, fname) #vdb에서 MD5해싱을 이용하여 악성코드 존재하는지 확인
    if ret == True : #존재하면 존재 여부와 악성코드 이름 반환 
        return ret, vname
    
    fp = open(fname, 'rb') #파일을 이진파일로 불러옴
    for t in sdb :
        if ScanStr(fp, t[0], t[1]) == True: #특정 위치 검색법을 이용해서 찾은 경우
            ret = True #True 저장
            vname = t[2] #악성코드 이름 저장
            break #for문 탈출
    fp.close() #파일 닫음

    return ret, vname #악성코드 존재 여부와 이름 반환
'''

def ScanVirus(vdb, vsize, sdb, fname):
    print("[*] New ScanVirus") #새로운 스캔 함수임을 출력
    ret, vname = ScanMD5(vdb, vsize, fname) #vdb에서 MD5해싱을 이용하여 악성코드 존재하는지 확인
    if ret == True : #존재하면 존재 여부와 악성코드 이름 반환 
        return ret, vname
    
    fp = open(fname, 'rb') #파일을 이진파일로 불러옴
    for t in sdb :
        if ScanStr(fp, t[0], t[1]) == True: #특정 위치 검색법을 이용해서 찾은 경우
            ret = True #True 저장
            vname = t[2] #악성코드 이름 저장
            break #for문 탈출
    fp.close() #파일 닫음

    return ret, vname #악성코드 존재 여부와 이름 반환
'''