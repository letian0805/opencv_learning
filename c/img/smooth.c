#include "cv.h"
#include "highgui.h"

int main(int argc, char *argv[])
{
    IplImage *img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
    char *in_window = "Window in";
    char *out_window = "Window out";
    cvNamedWindow(in_window, CV_WINDOW_AUTOSIZE);
    cvNamedWindow(out_window, CV_WINDOW_AUTOSIZE);
    cvShowImage(in_window, img);
    IplImage *out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
    cvSmooth(img, out, CV_GAUSSIAN, 3, 3, 0, 1.0);
    cvShowImage(out_window, out);
    cvWaitKey(0);
    cvReleaseImage(&img);
    cvReleaseImage(&out);
    cvDestroyWindow(in_window);
    cvDestroyWindow(out_window);
    return 0;
}
