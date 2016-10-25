# coding:utf-8

import cv2, sys
import numpy as np

if len(sys.argv) < 2:
    exit(-1)
img = cv2.imread(sys.argv[1], cv2.IMREAD_COLOR)
img_downscale = cv2.pyrDown(img)
cv2.namedWindow("before downscale", cv2.WINDOW_AUTOSIZE)
cv2.namedWindow("after downscale", cv2.WINDOW_AUTOSIZE)
cv2.imshow("before downscale", img)
cv2.imshow("after downscale", img_downscale)
cv2.waitKey(5000)
cv2.destroyAllWindows()
