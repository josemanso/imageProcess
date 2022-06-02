#include "opencv2/opencv.hpp"

#include <iostream>

using namespace std;
using namespace cv;

class WatershedSegmenter {
  private: Mat markers;
  public: void setMarkers( const Mat& markeeImage){
    markeeImage.convertTo( markers, CV_32S);
  }

  Mat process( const Mat &image) {
    watershed(image, markers);
    markers.convertTo(markers, CV_8U);
    return markers;
  }
};

int main()
{
  Mat image = imread("/home/josemo/Documentos/imagenes/objects.jpg");

  Mat binary;
  cvtColor(image, binary, COLOR_BGR2GRAY);
  threshold(binary, binary, 100, 255, THRESH_BINARY);

  imshow( "Original Image", image);
  imshow( "Original Binary", binary);

  // Eliminate noise and smaller objects
  Mat fg;
  erode(binary, fg, Mat(), Point(-1, -1), 2);
  imshow("fg", fg);

  // Identify image pixels without objects
  Mat bg;
  //dilate(binary, bg, Mat(), Point(-1, -1), 3);
  dilate( binary, bg, Mat::ones(3, 3, CV_8U));  // Kernel 3x3
  threshold(bg, bg, 1, 128, THRESH_BINARY_INV);
  imshow("bg", bg);

  // create  markers image
  Mat markers(binary.size(), CV_8U, Scalar(0));
  markers = fg + bg;
  imshow("markers", markers);

  // create watershed segmentation object
  WatershedSegmenter segmenter;
  segmenter.setMarkers(markers);

  Mat result = segmenter.process(image);
  result.convertTo(result, CV_8U);
  imshow(" Final Result", result);

  waitKey(0);
  return 0;
}
