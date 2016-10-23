import cv2, sys

img = cv2.imread(sys.argv[1], cv2.IMREAD_COLOR)
cv2.namedWindow("test", cv2.WINDOW_AUTOSIZE)
cv2.imshow("test", img)
cv2.waitKey(5000)
#cv2.destroyWindow("test")
cv2.destroyAllWindows()
