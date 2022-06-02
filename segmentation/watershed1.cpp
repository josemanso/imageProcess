#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"


using namespace std;
using namespace cv;

//  show image
void showImg(const string& windowName,const Mat& img){
	imshow(windowName,img);
}
// background
void getBackground( const Mat& source, Mat& dst) {
  dilate( source, dst, Mat::ones(3, 3, CV_8U));  // Kernel 3x3
}
// Foreground
void getForeground( const Mat& source, Mat& dst) {
  distanceTransform( source, dst, DIST_L2, 3, CV_32F);
  normalize( dst, dst, 0, 1, NORM_MINMAX);
}

//Finding Marker
void findMarker( const Mat& sureBg, Mat& markers, vector<vector<Point>>& contours) {
  findContours( sureBg, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
  // Draw the foreground markers
  for (size_t i = 0, size = contours.size(); i < size; i++) {
    drawContours( markers, contours, static_cast<int>(i), Scalar(static_cast<int>(i)+1), -1);
  }
}
void getRandomColor(vector<Vec3b>& colors,size_t size)
{
	for (int i = 0; i < size ; ++i)
	{
			int b = theRNG().uniform(0, 256);
			int g = theRNG().uniform(0, 256);
			int r = theRNG().uniform(0, 256);
			colors.emplace_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
	}
}

// main
int main (int argc, char** argv)
{
  // read image
  Mat original_img = imread("/home/josemo/Documentos/imagenes/objects.jpg");
  if (original_img.empty()){
    std::cerr << "Error; Cannnot read image" << '\n';
  }
  // Convert the origina image yo grayscale
  Mat gray_img;
  cvtColor( original_img, gray_img, COLOR_BGR2GRAY);
  showImg("Gray Image", gray_img);
  // bimary escale
  Mat bin_img;
  threshold( gray_img, bin_img, 0, 255, THRESH_BINARY | THRESH_OTSU);
  showImg( "Threshold Image", bin_img);

  Mat sure_bg;
  getBackground(bin_img, sure_bg);
  showImg("Sure Background", sure_bg);

  Mat sure_fg;
  getForeground(bin_img, sure_fg);

  //Finding Marker
  Mat markers = Mat::zeros(sure_bg.size(), CV_32S);
  vector<vector<Point>> contours;
  findMarker( sure_bg, markers, contours);
  circle( markers, Point(5, 5), 3, Scalar(255), -1); //Drawing Circle around the marker

  // Applayin Watershed algorith,
  watershed( original_img, markers);

  Mat mark;
  markers.convertTo(mark, CV_8U);
  bitwise_not( mark, mark); // Convert white to black and black to white
  showImg("Marker", mark);

  /* Highliting Markers in the image */
  vector<Vec3b> colors;
  getRandomColor( colors, contours.size());

  // Create the result image
  Mat dst = Mat::zeros(markers.size(), CV_8UC3);
  // Fill labeled objects with random colors
  for (int i = 0; i < markers.rows; i++) {
    for (int j = 0; j< markers.cols; j++) {
      int index = markers.at<int>(i,j);
      if (index >0 && index <= static_cast<int>(contours.size())){
        dst.at<cv::Vec3b>(i,j) = colors[index-1];
      }
    }
  }

  showImg("Final Result", dst);
  waitKey(0);
  return 0;
}
