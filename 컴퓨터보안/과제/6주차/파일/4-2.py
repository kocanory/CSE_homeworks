if fbuf[0:3] == b'X5O':      #[0:3]의 내용이 X5O인지 판별                             
    print("Virus")           #바이러스 임을 출력
else:
    print("No Virus")        #바이러스가 아님을 출력