fp = open('eicar.txt', 'rb') #eicar.txt를 이진 파일로 open
fbuf = fp.read()             #eicar.txt 파일의 내용을 저장
fp.close()                   #파일 close