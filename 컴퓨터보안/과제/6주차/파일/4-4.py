#-*- coding:utf-8 -*-
import hashlib

m = hashlib.md5()                   #md5 해시함수 불러옴
m.update('hello'.encode('utf-8'))   #문자열 hello 해싱
fmd5 = m.hexdigest()                #해싱된 문자열 저장
print(fmd5)                           