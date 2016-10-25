#include <cv.h>
#include <highgui.h>

using namespace cv;

int main(int argc, char *argv[])
{
    if (argc < 2){
        return -1;
    }
    Mat img = imread(argv[1], IMREAD_COLOR);
    namedWindow("before smooth", WINDOW_AUTOSIZE);
    namedWindow("after smooth", WINDOW_AUTOSIZE);
    Mat img_smooth((Size)img.size(), img.depth(), img.type());
    GaussianBlur(img, img_smooth, Size(9, 9), 1.0, 1.0, 0);
    imshow("before smooth", img);
    imshow("after smooth", img_smooth);
    waitKey(5000);
    destroyAllWindows();
    return 0;
}
