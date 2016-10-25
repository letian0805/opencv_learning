#include <cv.h>
#include <highgui.h>

using namespace cv;

int main(int argc, char *argv[])
{
  if (argc < 2){
    return -1;
  }
  Mat img = imread(argv[1]);
  Mat img_canny((Size)img.size(), CV_8UC1);
  Canny(img, img_canny, 100, 150);
  namedWindow("before canny", CV_WINDOW_AUTOSIZE);
  namedWindow("after canny", CV_WINDOW_AUTOSIZE);
  imshow("before canny", img);
  imshow("after canny", img_canny);
  waitKey(5000);
  destroyAllWindows();
  return 0;
}
