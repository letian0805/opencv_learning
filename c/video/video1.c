#include "highgui.h"

int g_slider_position = 0;
CvCapture *g_capture = NULL;
int g_current_pos = 0;

void onTrackbarSlide(int pos)
{
  if (pos == g_current_pos) return;
  cvSetCaptureProperty(
    g_capture,
    CV_CAP_PROP_POS_FRAMES,
    pos);
  g_current_pos = pos;
}

int main(int argc, char *argv[])
{
  char *window_name = "my test video";
  cvNamedWindow(window_name, CV_WINDOW_AUTOSIZE);
  g_capture = cvCreateFileCapture(argv[1]);
  int frames = (int)cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_COUNT);
  if( frames != 0 ){
    cvCreateTrackbar(
      "Position",
      window_name,
      &g_slider_position,
      frames,
      onTrackbarSlide);
  }
  IplImage *frame;
  while(1){
    frame = cvQueryFrame(g_capture);
    if(!frame) break;
    cvShowImage(window_name, frame);
    int pos = cvGetTrackbarPos("Position", window_name);
    g_current_pos = pos + 1;
    cvSetTrackbarPos("Position", window_name, g_current_pos);
    char c = cvWaitKey(33);
    if (c==27) break;
  }
  cvReleaseCapture(&g_capture);
  cvDestroyWindow(window_name);
  return 0;
}
