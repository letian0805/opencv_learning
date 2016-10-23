#include "highgui.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    IplImage *img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
    cvNamedWindow("my test window", CV_WINDOW_AUTOSIZE);
    cvShowImage("my test window", img);
    printf("---image depth: %d\n", img->depth);
    cvWaitKey(0);
    cvReleaseImage(&img);
    cvDestroyWindow("my test window");
    return 0;
}
