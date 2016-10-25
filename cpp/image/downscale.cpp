#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 2){
    return -1;
  }
  Mat image = imread(argv[1]);
  Size size = (Size)image.size();
  Mat dst;
  pyrDown(image, dst, Size(size.width/2, size.height/2));
  namedWindow("in");
  namedWindow("out");
  imshow("in", image);
  imshow("out", dst);
  waitKey(10000); 
  destroyAllWindows();
  return 0;
}
