#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import cv2, math, time

def traffic_recognition(frame):
    
    # 잠깐 640, 480으로 설정해둠 / 0:240(or 200), 80:560으로 재설정 필요
    roi1 = frame[0:800, 0:800]
    roi2 = frame[0:800, 0:800]      # 관심 영역 설정
    # 조정 필요
    # cv2.imshow('roi1', roi1)
    # cv2.imshow('roi2', roi2)

    hsv1 = cv2.cvtColor(roi1, cv2.COLOR_BGR2HSV)
    hsv2 = cv2.cvtColor(roi2, cv2.COLOR_BGR2HSV)  # hsv 변환
    # cv2.imshow('hsv', hsv)
    
    # 빨간색 색상 검출 영역 설정
    lower_red = np.array([155, 0, 230])
    upper_red = np.array([179, 20, 255])

    # 초록색 색상 검출 영역 설정
    lower_green = np.array([125, 0, 245])
    upper_green = np.array([160, 15, 255])
    
    # 초록색 영역 기준으로 색상 검출
    mask_green = cv2.inRange(hsv2, lower_green, upper_green)

    # 빨간색 영역 기준으로 색상 검출
    mask_red = cv2.inRange(hsv1, lower_red, upper_red)

    # 검출되는 각 색상을 ROI 영역에서 확인
    green = cv2.bitwise_and(roi2, roi2, mask=mask_green)
    red = cv2.bitwise_and(roi1, roi1, mask=mask_red)

    # cv2.imshow('ROI1', roi1)
    # cv2.imshow('ROI2', roi2)
 
    cv2.imshow('GREEN', green)
    cv2.imshow('RED', red)
    cv2.waitKey(0)

    blur_green = cv2.medianBlur(green, 5)
    blur_red = cv2.medianBlur(red, 5)
    # cv2.imshow('blur_green', blur_green)
    # cv2.imshow('blur_red', blur_red)

    bgr_green = cv2.cvtColor(blur_green, cv2.COLOR_HSV2BGR)
    bgr_red = cv2.cvtColor(blur_red, cv2.COLOR_HSV2BGR)
    # cv2.imshow('bgr_green', bgr_green)
    # cv2.imshow('bgr_red', bgr_red)

    gray_green = cv2.cvtColor(bgr_green, cv2.COLOR_BGR2GRAY)
    gray_red = cv2.cvtColor(bgr_red, cv2.COLOR_BGR2GRAY)
    # cv2.imshow('gray_green', gray_green)
    # cv2.imshow('gray_red', gray_red)

    # 파라미터 값 설정 필요
    circle_green = cv2.HoughCircles(gray_green, cv2.HOUGH_GRADIENT, 1, 20, param1= 40, param2= 15, minRadius= 30, maxRadius= 60)
    circle_red = cv2.HoughCircles(gray_red, cv2.HOUGH_GRADIENT, 1, 20, param1= 40, param2= 15, minRadius= 30, maxRadius= 60)

    if circle_red is not None:
        for i in range(circle_red.shape[1]):
            x, y, r = circle_red[0][i]
            print([x, y, r], 'RED')
            cv2.circle(red, (int(x), int(y)), int(r), (255, 0, 0), 3)
            cv2.imshow('RED', red)
            return 'RED'
    elif circle_green is not None:
        for i in range(circle_green.shape[1]):
            x, y, r = circle_green[0][i]
            print([x, y, r], 'GREEN')
            cv2.circle(green, (int(x), int(y)), int(r), (255, 0, 0), 3)
            cv2.imshow('GREEN', green)
            return 'GREEN'


# 2 hsv

# img = cv2.imread('green.png')
img = cv2.imread('red.png')

cv2.waitKey(0)
traffic_recognition(img)




# capture = cv2.VideoCapture(4)
# w, h = 640, 480
# capture.set(h, cv2.CAP_PROP_FRAME_HEIGHT)
# capture.set(w, cv2.CAP_PROP_FRAME_WIDTH)

# while capture.isOpened():
#     ret, frame = capture.read()
    
#     traffic_recognition(frame)

#     if cv2.waitKey(1) & 0xFF == ord('q'):
#         break

# capture.release()
# cv2.destroyAllWindows()

