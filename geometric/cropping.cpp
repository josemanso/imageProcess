// cropping an imahe
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
  // Read image
  Mat img = imread("/home/josemo/Camera/IMG_20190721_112024144_HDR.jpg");
  cout << "Width : " << img.size().width << endl;
  cout << "Heigth : " << img.size().height << endl;
  cout << "Chanels : :" << img.channels() << endl;

  // Crop image
  Mat cropped_image = img(Range(1180, 1280), Range(1250, 1330));

  // display image
  imshow("Original image", img);
  imshow("Cropped image", cropped_image);

  // Save the croped image
  //imwrite("imagex.jpg", cropped_image);

  // 0 means loop infinitely
  waitKey(0);
  return(0);
}
