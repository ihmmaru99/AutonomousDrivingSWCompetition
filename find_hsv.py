import cv2
import numpy as np


hsv = 0
lower_blue1 = 0
upper_blue1 = 0
lower_blue2 = 0
upper_blue2 = 0
lower_blue3 = 0
upper_blue3 = 0


def mouse_callback(event, x, y, flags, param):
    global hsv, lower_blue1, upper_blue1, lower_blue2, upper_blue2, lower_blue3, upper_blue3

    # 마우스 왼쪽 버튼 누를시 위치에 있는 픽셀값을 읽어와서 HSV로 변환 (x, y 값으로 저장)
    if event == cv2.EVENT_LBUTTONDOWN:
        print(img_color[y, x])
        color = img_color[y, x]

        one_pixel = np.uint8([[color]])
        hsv = cv2.cvtColor(one_pixel, cv2.COLOR_BGR2HSV)
        hsv = hsv[0][0]

        # HSV 색공간에서 마우스 클릭으로 얻은 픽셀값과 유사한 픽셀값의 범위를 정함
        if hsv[0] < 10:
            print("case1")
            lower_blue1 = np.array([hsv[0]-10+180, 30, 30]) # 색상만 조절
            upper_blue1 = np.array


def mouse_callback(event, x, y, flags, param):
    global hsv, lower_blue1, upper_blue1, lower_blue2, upper_blue2, lower_blue3, upper_blue3

    # 마우스 왼쪽 버튼 누를시 위치에 있는 픽셀값을 읽어와서 HSV로 변환 (x, y 값으로 저장)
    if event == cv2.EVENT_LBUTTONDOWN:
        print(img_color[y, x])
        color = img_color[y, x]

        one_pixel = np.uint8([[color]])
        hsv = cv2.cvtColor(one_pixel([180, 255, 255]))
        lower_blue2 = np.array([0, 30, 30])
        upper_blue2 = np.array([hsv[0], 255, 255])
        lower_blue3 = np.array([hsv[0], 30, 30])
        upper_blue3 = np.array([hsv[0]+10, 255, 255])
            #     print(i-10+180, 180, 0, i)
            #     print(i, i+10)

    elif hsv[0] > 170:
        print("case2")
        lower_blue1 = np.array([hsv[0], 30, 30])
        upper_blue1 = np.array([180, 255, 255])
        lower_blue2 = np.array([0, 30, 30])
        upper_blue2 = np.array([hsv[0]+10-180, 255, 255])
        lower_blue3 = np.array([hsv[0]-10, 30, 30])
        upper_blue3 = np.array([hsv[0], 255, 255])
            #     print(i, 180, 0, i+10-180)
            #     print(i-10, i)
    else:
        print("case3")
        lower_blue1 = np.array([hsv[0], 30, 30])
        upper_blue1 = np.array([hsv[0]+10, 255, 255])
        lower_blue2 = np.array([hsv[0]-10, 30, 30])
        upper_blue2 = np.array([hsv[0], 255, 255])
        lower_blue3 = np.array([hsv[0]-10, 30, 30])
        upper_blue3 = np.array([hsv[0], 255, 255])
            #     print(i, i+10)
            #     print(i-10, i)

        print(hsv[0])
        print("@1", lower_blue1, "~", upper_blue1)
        print("@2", lower_blue2, "~", upper_blue2)
        print("@3", lower_blue3, "~", upper_blue3)


cv2.namedWindow('img_color')
cv2.setMouseCallback('img_color', mouse_callback)

while(True):
    img_color = cv2.imread('red.png')
    img_hsv = cv2.cvtColor(img_color, cv2.COLOR_BGR2HSV)

    img_mask1 = cv2.inRange(img_hsv, lower_blue1, upper_blue1)
    img_mask2 = cv2.inRange(img_hsv, lower_blue2, upper_blue2)
    img_mask3 = cv2.inRange(img_hsv, lower_blue3, upper_blue3)
    img_mask = img_mask1 | img_mask2 | img_mask3

    img_result = cv2.bitwise_and(img_color, img_color, mask=img_mask)


    cv2.imshow('img_color', img_color)
    cv2.imshow('img_mask', img_mask)
    cv2.imshow('img_result', img_result)


    if cv2.waitKey(1) & 0xFF == 'q':
        break

cv2.destroyAllWindows()