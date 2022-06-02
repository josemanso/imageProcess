//cartoon
// Include OpenCV's C++ Interface
#include "opencv2/opencv.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"


using namespace cv;
using namespace std;

// cartoonifyImage(cameraFrame, displayedFrame)
void cartoonifyImage(Mat srcColor, Mat dst){

  // Conver to gray scale.
  Mat gray;
  cvtColor(srcColor, gray, COLOR_BGR2GRAY);
  // Applay gaussian blur.
  const int MEDIAN_BLUR_FILTER_SIZE = 7;
  medianBlur(gray, gray, MEDIAN_BLUR_FILTER_SIZE);
  // Find edges,
  Mat edges, edges2;
  Scharr(gray, edges, CV_8U, 1, 0);
  Scharr(gray, edges2, CV_8U, 1, 0, -1);
  edges += edges2; // Combine the c & y edges together
  const int EVIL_EDGE_THRESHOLD = 12;
  //const int LAPLACIAN_FILTER_SIZE = 5;
  //Laplacian(gray, edges, CV_8U, LAPLACIAN_FILTER_SIZE);
  // The Laplacian filter produces edges with varying brightness

  Mat mask;
  //const int EDGES_THRESHOLD = 80;
  // aplay thresholdS
  //threshold(edges, mask, EDGES_THRESHOLD, 255, THRESH_BINARY_INV);
  threshold(edges, mask, EVIL_EDGE_THRESHOLD, 255, THRESH_BINARY_INV);
  medianBlur(mask, mask, 3);

  // Let's reduce the total number of pixels by a
  // factor of four (for example, half width and half height)
  Size size = srcColor.size();
  Size smallSize;
  smallSize.width = size.width/2;
  smallSize.height = size.height/2;
  Mat smallImg = Mat(smallSize, CV_8UC3);//  Filter color strength
  resize(srcColor, smallImg, smallSize, 0, 0, INTER_LINEAR);

  Mat tmp = Mat (smallSize, CV_8UC3);
  int repetition = 7; // repetition for strong cartoon effect.
  for (int i=0; i<repetition; i++){
    int ksize = 9; //  Filter size. Has a large effect on speed
    double sigmaColor = 9; //  Filter color strength
    double sigmaSpace = 7; // Spatial strength. Affects speed.
    bilateralFilter(smallImg, tmp, ksize, sigmaColor, sigmaSpace);
    bilateralFilter(tmp, smallImg, ksize, sigmaColor, sigmaSpace);
  }

  Mat bigImg;
  resize(smallImg, bigImg, size, 0, 0, INTER_LINEAR);
  dst.setTo(0);
  bigImg.copyTo(dst, mask);


}// end cartoonifyImage()
