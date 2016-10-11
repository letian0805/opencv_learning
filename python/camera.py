# http://www.pyimagesearch.com/2015/05/25/basic-motion-detection-and-tracking-with-python-and-opencv/
# http://python.jobbole.com/81593/
# import the necessary packages
import argparse
import datetime
import time
import cv2
import cv2.cv as cv
import numpy as np
# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-v", "--video", help="path to the video file")
ap.add_argument("-a", "--min-area", type=int, default=300, help="minimum area size")
ap.add_argument("-w", "--min-width", type=int, default=100, help="minimum area width")
args = vars(ap.parse_args())
# if the video argument is None, then we are reading from webcam
if args.get("video", None) is None:
  camera = cv2.VideoCapture(0)
  time.sleep(0.25)
# otherwise, we are reading from a video file
else:
  camera = cv2.VideoCapture(args["video"])
# initialize the first frame in the video stream
firstFrame = None
lastCnts = None
frame_flag = 0
cnts_flag = 0
# Define the codec
fourcc = cv.CV_FOURCC('X', 'V', 'I', 'D')
framecount = 0
frame = np.zeros((640,480))
##out = cv2.VideoWriter('calm_down_video_'+datetime.datetime.now().strftime("%A_%d_%B_%Y_%I_%M_%S%p")+'.avi',fourcc, 5.0, np.shape(frame))
# to begin with, the light is not stable, calm it down
tc = 40
while tc:
  ret, frame = camera.read()
  ##out.write(frame)
  #cv2.imshow("vw",frame)
  cv2.waitKey(10)
  tc -= 1
totalc = 3
tc = totalc
frames = []

def removeSmallRect(cnts):
  ret = []
  for c in cnts:
    contour = cv2.contourArea(c)
    (x, y, w, h) = cv2.boundingRect(c)
    if contour < args["min_area"] or w < args["min_width"] or h < args["min_width"]:
      continue
    ret.extend([c])
  return ret

class Rect:
  def __init__(self, x, y, w, h):
    self.x = x
    self.y = y
    self.w = w
    self.h = h

def rectCanMerge(r1, r2):
  delta_x = abs((r1.x + r1.w / 2) - (r2.x + r2.w / 2))
  delta_y = abs((r1.y + r1.h / 2) - (r2.y + r2.h / 2))
  return delta_y <= (r1.h + r2.h)/2 and delta_x <= (r1.w + r2.w)/2

def mergeRect(r1, r2):
    x = min(r1.x, r2.x)
    y = min(r1.y, r2.y)
    w = max(r1.x + r1.w, r2.x + r2.w) - x
    h = max(r1.y + r1.h, r2.y + r2.h) - y
    return Rect(x, y, w, h)

def cntsToRects(cnts):
  ret = []
  for c in cnts:
    (x, y, w, h) = cv2.boundingRect(c)
    r = Rect(x, y, w, h)
    ret.extend([r])
  return ret

def mergeAllRect(rects):
  ret = []
  while(len(rects) > 1):
    r = rects.pop()
    can_merge = False
    for i in xrange(0, len(rects) - 1):
      ri = rects[i]
      can_merge = rectCanMerge(ri, r)
      if can_merge:
        rects[i] = mergeRect(r, ri)
        break
    if not can_merge:
      ret.extend([r])
  return ret

##out.release()
# loop over the frames of the video
while True:
  # grab the current frame and initialize the occupied/unoccupied
  # text
  (grabbed, frame) = camera.read()
  text = "Unoccupied"
  # if the frame could not be grabbed, then we have reached the end
  # of the video
  if not grabbed:
    #time.sleep(0.01)
    continue
  # resize the frame, convert it to grayscale, and blur it
  gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
  gray = cv2.GaussianBlur(gray, (21, 21), 0)
  # update firstFrame for every while
  if frame_flag == 0:
    firstFrame = gray
    frame_flag = 1
  #print tc
  # compute the absolute difference between the current frame and
  # first frame
  frameDelta = cv2.absdiff(firstFrame, gray)
  thresh = cv2.threshold(frameDelta, 25, 255, cv2.THRESH_BINARY)[1]
  # dilate the thresholded image to fill in holes, then find contours
  # on thresholded image
  thresh = cv2.dilate(thresh, None, iterations=2)
  (cnts, _) = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
  cnts = removeSmallRect(cnts)
  rects = cntsToRects(cnts)
  ret = mergeAllRect(rects)
  rects = ret
  if cnts_flag == 0:
    lastCnts = rects
    cnts_flag = 1
  if len(rects) == 0:
    rects = lastCnts
  # loop over the contours
  for r in rects:
    # compute the bounding box for the contour, draw it on the frame,
    # and update the text
    cv2.rectangle(frame, (r.x, r.y), (r.x + r.w, r.y + r.h), (0, 255, 0), 2)
    text = "Occupied"
  lastCnts = rects
  # draw the text and timestamp on the frame
  cv2.putText(frame, "Room Status: {}".format(text), (10, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)
  cv2.putText(frame, datetime.datetime.now().strftime("%A %d %B %Y %I:%M:%S%p"), (10, frame.shape[0] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.35, (0, 0, 255), 1)
  # show the frame and record if the user presses a key
  cv2.imshow("Security Feed", frame)
  cv2.imshow("Thresh", thresh)
  cv2.imshow("Frame Delta", frameDelta)
  # save the detection result
  if text == "Occupied":
    if framecount == 0:
      # create VideoWriter object
      ##out = cv2.VideoWriter(datetime.datetime.now().strftime("%A_%d_%B_%Y_%I_%M_%S%p")+'.avi',fourcc, 10.0, np.shape(gray)[::-1])
      ##cv2.imwrite(datetime.datetime.now().strftime("%A_%d_%B_%Y_%I_%M_%S%p")+'.jpg',frame)
      # write the flipped frame
      ##out.write(frame)
      framecount += 1
    else:
      # write the flipped frame
      ##out.write(frame)
      framecount += 1
  elif framecount > 20 or framecount<2:
    ##out.release()
    framecount = 0
  frames.insert(0, gray)
  if len(frames) > totalc:
    firstFrame = frames.pop()
  key = cv2.waitKey(10) & 0xFF
  # if the `ESC` key is pressed, break from the lop
  if key == 27:
    break
# cleanup the camera and close any open windows
camera.release()
cv2.destroyAllWindows()
