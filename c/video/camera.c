#include <cv.h>
#include <highgui.h>
#include <string.h>

CvCapture *g_capture = NULL;

int main(int argc, char *argv[])
{
  char *window_name = "my test video";
  cvNamedWindow(window_name, CV_WINDOW_AUTOSIZE);
  int cam_index = 0;
  if(argc > 1) {
      cam_index = atoi(argv[1]); 
  }
  g_capture = cvCreateCameraCapture(cam_index);
  IplImage *frame;
  while(1){
    frame = cvQueryFrame(g_capture);
    if(!frame) continue;
    cvShowImage(window_name, frame);
    char c = cvWaitKey(33);
    if (c==27) break;
  }
  cvReleaseCapture(&g_capture);
  cvDestroyWindow(window_name);
  return 0;
}
