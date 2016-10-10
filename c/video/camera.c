#include "highgui.h"
#include <string.h>

CvCapture *g_capture = NULL;

int main(int argc, char *argv[])
{
  char *window_name = "my test video";
  cvNamedWindow(window_name, CV_WINDOW_AUTOSIZE);
  g_capture = cvCreateCameraCapture(atoi(argv[1]));
  IplImage *frame;
  while(1){
    frame = cvQueryFrame(g_capture);
    if(!frame) continue;
    cvShowImage(window_name, frame);
    char c = cvWaitKey(8);
    if (c==27) break;
  }
  cvReleaseCapture(&g_capture);
  cvDestroyWindow(window_name);
  return 0;
}
