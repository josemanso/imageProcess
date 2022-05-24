// contorno; Finding and Drawing Contours using OpenCV
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main( int argc, char** argv)
{
  //read the image
  Mat image = imread("/home/josemo/Documentos/imagenes/people.jpg");

  // Convert the image to grayscale transformat
  Mat img_gray;
  cvtColor(image, img_gray, COLOR_BGR2GRAY);
  // Apply binary theresholding
  Mat thresh;
  threshold(img_gray, thresh, 150, 255, THRESH_BINARY);
  imshow("Binary Image", thresh);
  waitKey(0);

  // detect the contours on the binary image
  vector<vector<Point> >contours;
  vector<Vec4i> hierarchy;
  findContours(thresh, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
  // draw the contours on the original image
  Mat image_copy = image.clone();
  drawContours(image_copy, contours, -1, Scalar(0, 255, 0), 2);
  imshow("None approximation", image_copy);
  waitKey(0);
  destroyAllWindows();
  return 0;
}
