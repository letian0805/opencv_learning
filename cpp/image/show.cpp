#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace cv; 

int main(int argc, char *argv[])
{
    Mat image; 
    image=imread(argv[1]); 
    namedWindow("test"); 
    imshow("test", image); 
    waitKey(5000); 
    return 0; 
}
