#include <cv.h>
#include <highgui.h>

int main(int argc, char *argv[])
{
  int filter = IPL_GAUSSIAN_5x5;
  IplImage *img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
  IplImage *out = cvCreateImage(cvSize(img->width/2, img->height/2), img->depth, img->nChannels);
  cvPyrDown(img, out, CV_GAUSSIAN_5x5);
  cvNamedWindow("in", CV_WINDOW_AUTOSIZE);
  cvNamedWindow("out", CV_WINDOW_AUTOSIZE);
  cvShowImage("in", img);
  cvShowImage("out", out);
  cvWaitKey(10000);
  cvReleaseImage(&img);
  cvReleaseImage(&out);
  cvDestroyAllWindows();
  return 0;
}
