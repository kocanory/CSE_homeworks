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