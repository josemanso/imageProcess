// resizing image
#include<opencv2/opencv.hpp>
#include<iostream>


using namespace std;
using namespace cv;

int main()
{
  Mat image1, image2, image3;
  // Read image
  Mat img = imread("/home/josemo/Camera/IMG_20190721_112024144_HDR.jpg");
  cout << "Width : " << img.size().width << endl;
  cout << "Heigth : " << img.size().height << endl;
  cout << "Chanels : :" << img.channels() << endl;
  // Show
  imshow("Original Image", img);

  // let's downscale the image using new  width and height
  int down_width = 300;
  int down_height = 200;
  //Mat resized_down;
  // resize 1, using new  width and height
  resize(img, image1, Size(down_width, down_height));
  imshow("Resized Down", image1);
  //
  resize(img, image2, Size(down_width, down_height), INTER_LINEAR);
  imshow("Resized Down inter linear", image2);

  resize(img, image3, Size(1151,181), 0, 0, INTER_AREA);
  imshow("Resized inter area", image3);

  waitKey();
  destroyAllWindows();
  return 0;
}
