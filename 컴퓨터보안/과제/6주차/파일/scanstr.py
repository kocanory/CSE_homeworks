#-*- coding:utf-8 -*-
def ScanStr(fp, offset, mal_str):
    size = len(mal_str) #악성코드 진단 문자열의 길이 저장

    fp.seek(offset) #문자열이 존재할 것으로 예상되는 위치로 이동
    buf = fp.read(size) #길이만큼 읽기

    if buf == mal_str: 
        return True #악성코드 발견
    else:
        return False #악성코드 미발견
    
fp = open('eicar.txt', 'rb') #파일을 이진파일로 불러옴
print(ScanStr(fp, 0, b'X5O')) #0번째 위치에 X5O가 존재하는지 확인
fp.close() #파일 닫음