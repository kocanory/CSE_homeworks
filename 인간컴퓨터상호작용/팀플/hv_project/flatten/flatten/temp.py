
import cv2
import numpy as np

fgbg = cv2.createBackgroundSubtractorKNN(detectShadows=False)

cam = cv2.VideoCapture(0, cv2.CAP_DSHOW)
width = int(cam.get(cv2.CAP_PROP_FRAME_WIDTH))
height = int(cam.get(cv2.CAP_PROP_FRAME_HEIGHT))
kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(7,7))
result = np.ones((height, width, 3))

while(True):
    ret, frame = cam.read()

    if ret:
        pass
    else : 
        print('비디오가 끝났거나 오류가 있습니다')
        break

    if result is NULL:
        result = frame
    

    original = frame.copy()

    background_extraction_mask = fgbg.apply(frame)
    background_extraction_mask = cv2.dilate(background_extraction_mask,kernel,iterations=1)
    background_extraction_mask = np.stack((background_extraction_mask,)*3, axis=-1)
    bitwise_image = cv2.bitwise_and(frame, background_extraction_mask)

    result = result.astype("uint8")
    print(result)
    temp = cv2.bitwise_and(result, background_extraction_mask)

    result = background_extraction_mask + temp
    cv2.imshow('image', result)
        
    #cv2.imshow('image', sub)
    if cv2.waitKey(25) == 27:
            break
