#include <cv.h>
#include <highgui.h>

int main(int argc, char *argv[])
{
    if (argc < 2){
        return -1;
    }
    IplImage *img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
    CvSize size = cvSize(img->width, img->height);
    IplImage *img_canny = cvCreateImage(cvSize(img->width, img->height), 8, 1);
    IplImage *img_smooth = cvCreateImage(size, 8, 1);
    cvCanny(img, img_canny, 120, 150, 3);
    cvSmooth(img_canny, img_smooth, CV_GAUSSIAN, 9, 9, 0, 1.5);
    cvCanny(img_smooth, img_canny, 120, 150, 3);
    cvNamedWindow("before canny", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("after canny", CV_WINDOW_AUTOSIZE);
    cvShowImage("before canny", img);
    cvShowImage("after canny", img_canny);
    cvWaitKey(10000);
    cvReleaseImage(&img);
    cvReleaseImage(&img_canny);
    cvDestroyAllWindows();
    return 0;
}
