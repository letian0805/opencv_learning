# coding:utf-8  
import cv2, sys
import numpy as np
if len(sys.argv) < 2:
    exit(-1)
img = cv2.imread(sys.argv[1], cv2.IMREAD_COLOR)
img_smooth = cv2.GaussianBlur(img, (3, 3), 0)
cv2.namedWindow("before smooth")
cv2.namedWindow("after smooth")
cv2.imshow("before smooth", img)
cv2.imshow("after smooth", img_smooth)
cv2.waitKey(5000)
cv2.destroyAllWindows()
