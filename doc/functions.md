
[TOC]

#1. image
##1.1 header file
###1.1.1 c cpp
      #include <cv.h>
      #include <highgui.h>
###1.1.2 python
      import cv2
##1.2 open image
###1.2.1 c
####define
    IplImage* cvLoadImage( const char* filename, int iscolor CV_DEFAULT(CV_LOAD_IMAGE_COLOR));

    CvMat* cvLoadImageM( const char* filename, int iscolor CV_DEFAULT(CV_LOAD_IMAGE_COLOR));

    #define cvvLoadImage(name) cvLoadImage((name),1)

        filename: name of file to load
        iscolor: the color type of image, default is CV_LOAD_IMAGE_COLOR
####usage
    IplImage *img = cvLoadImage("test.jpg", CV_LOAD_IMAGE_COLOR);
    CvMat *img_mat = cvLoadImageM("test.jpg", CV_LOAD_IMAGE_COLOR);
###1.2.2 cpp
####define
    Mat imread( const string& filename, int flags=1 );

        filename: name of file to read
        flags: color of image, default is IMREAD_COLOR = 1
####usage
    Mat img = imread("test.jpg", IMREAD_COLOR);
###1.2.3 python
####define
    cv2.imread(filename, flags)

        filename: path of file to read
        flags: the color type of image
####usage
    img = cv2.imread("test.jpg", cv2.IMREAD_COLOR)

##1.3 create image
###1.3.1 c
####define
    IplImage* cvCreateImage( CvSize size, int depth, int channels );

        size: cvSize(width, height)
        depth: color depth by bits per channel
        channels: channels of color
####usage
    //create 24 bits depth color, 8 bits depth per channel of 3 channels
    IplImage *img = cvCreateImagte(cvSize(100, 100), 8, 3);
###1.3.2 cpp
####define
    //see the define of Mat Class in opencv2/core/core.hpp
    cv::Mat(int rows, int cols, int type);
####usage
    Mat img(100, 100, CV_8UC3);
###1.3.3 python
####define
    numpy.zero((width, height, channels), type)
####usage
    numpy.zero((100, 100, 3), dtype="uint8")

##1.4 show image
###1.4.1 c
####define
    void cvShowImage( const char* name, const CvArr* image );

        name: name of the window to show image
        image: image to show
####usage
    IplImage *img = cvLoadImage("test.jpg", CV_LOAD_IMAGE_COLOR);
    cvShowImage("test window", image);
###1.4.2 cpp
####define
    void imshow(const string& winname, InputArray mat);

        winname: name of the window to show image
        mat: image to show
####usage
    Mat img = imread("test.jpg");
    namedWindow("test window");
    imshow("test window", img);
###1.4.3 python
####define
    cv2.imshow(winname, image)

        winname: name of the window to show image
        image: image to show
####usage
    img = cv2.imread("test.jpg", cv2.IMREAD_COLOR)
    cv2.namedWindow("test window")
    cv2.imshow("test window", img)

##1.5 release image
###1.5.1 c
####define
    void cvReleaseImage( IplImage** image );
      image: the pointer of image to release
####usage
    cvReleaseImage(&image);
###1.5.2 cpp
  no such function
  if use Mat *img = new Mat(), then use delete img
###1.5.3 python
  no such function

##1.6 down scale and smooth image
###1.6.1 c
####define
    void cvPyrDown(const CvArr* src, CvArr* dst, int filter CV_DEFAULT(CV_GAUSSIAN_5x5));
####usage
    IplImage *img_src = cvLoadImage("test.jpg", CV_LOAD_IMAGE_COLOR);
    IplImage *img_dst = cvCreateImage(cvSize(img_src->width/2, img_src->height/2), img_src->depth, img_src->nChannels);
    cvPyrDown(img_src, img_dst, CV_GAUSSIAN_5x5);
###1.6.2 cpp
####define
    void pyrDown( InputArray src, OutputArray dst, const Size& dstsize=Size(), int borderType=BORDER_DEFAULT );
####usage
    Mat img_src = rmread("test.jpg", IMREAD_COLOR);
    Size size_src = (Size)img_src.size();
    Mat img_dst;
    pyrDown(img_src, img_dst, Size(size_src.width/2, size_src.height/2));
###1.6.3 python
  img_downscale = cv2.pyrDown(img)

##1.7 smooth image
###1.7.1 c
####define
    void cvSmooth( const CvArr* src, CvArr* dst, int smoothtype CV_DEFAULT(CV_GAUSSIAN),
                        int size1 CV_DEFAULT(3), int size2 CV_DEFAULT(0),
                        double sigma1 CV_DEFAULT(0), double sigma2 CV_DEFAULT(0));
####usage
    cvSmooth(img, img_smooth, CV_GAUSSIAN, 3, 3, 1.0, 1.5);
###1.7.2 cpp
####define
    //see imgproc.hpp
    void GaussianBlur( InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT );
####usage
    GaussianBlur(img, img_smooth, Size(3, 3), 1.0, 1.0, 0);
###1.7.3 python
    img_smooth = cv2.GaussianBlur(img, (3, 3), 0)

##1.7 get edge of image (canny)
###1.7.1 c
####define
    void cvCanny(const CvArr* image, CvArr* edges, double threshold1, double threshold2, int aperture_size CV_DEFAULT(3));
####usage
    IplImage *img = cvLoadImage("test.jpg", CV_LOAD_IMAGE_COLOR);
    IplImage *img_canny = cvCreateImage(cvSize(img->width, img->height), CV_8UC1, 1);
    cvCanny(img, img_canny, 100, 150, 3);
###1.7.2 cpp
####define
    void Canny( InputArray image, OutputArray edges, double threshold1, double threshold2, int apertureSize=3, bool L2gradient=false );
####usage
    Mat img_canny((Size)img.size(), CV_8UC1);
    Canny(img, img_canny, 100, 150);
###1.7.3 python
    img_gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
    img_canny = cv2.Canny(img_gray, 100, 150)

#2. window
##2.1 create named window
###2.1.1 c
####define
    int cvNamedWindow( const char* name, int flags CV_DEFAULT(CV_WINDOW_AUTOSIZE) );
        name: name of the window to create
        flags: window size flags
####usage
    cvNamedWindow("test window", CV_WINDOW_AUTOSIZE);
###2.1.2 cpp
####define
    void namedWindow(const string& winname, int flags = WINDOW_AUTOSIZE);
        winname: name of the window to create
        flags: window size flags, default is WINDOW_AUTOSIZE
####usage
    namedWindow("test window");
###2.1.3 python
####define
    cv2.namedWindow(winname, flags)
        winname: name of the window to create
        flags: window flags
####usage
    cv2.namedWindow("test window", cv2.WINDOW_AUTOSIZE)
##2.2 destroy window
###2.2.1 c
####define
    void cvDestroyWindow( const char* name );
		name: name of window to destroy
    void cvDestroyAllWindows(void);
####usage
    cvDestroyWindow("test window");
###2.2.2 cpp
####define
    void destroyWindow(const string& winname);
		winname: name of window to destroy
    void destroyAllWindows(void);
####usage
    destroyWindow("test window");
###2.2.3 python
####define
    cv2.destroyWindow(winname)
		winname: name of window to destroy
    cv2.destroyAllWindows()
####usage
    cv2.destroyWindow("test window")
