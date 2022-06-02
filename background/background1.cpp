//background1.cpp
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <math.h>
//#include <Windows.h>
#include "opencv2/video/background_segm.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

int main( int argc, char** argv)
{
  // Init background sunstractor
  Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2(500, 16.0, true);
  // Create empty input img, foreground and background image and foreground mask
  Mat img, foregroundMask, backgroundImage, foregroundImg;
  // capture video  from surce 0, which is web camera,  If you want capture
  // video file, yus replace  by VideoCapture cap("videoFile,mov")
  VideoCapture cap(0);

  //
  if (!cap.isOpened()){
      cout << "Video Capture Fail" << endl;
      return -1;
  }

  //MAt frame;

  // main loop to grab sequences of imput files
  for (;;) {
    /** bool ok = cap.grab();
    if (ok == false) {
      cout << "Video Capture Fail" << endl;
    }
    else{
      // obtain input image from source
      cap.retrieve(img, CAP_OPENNI_BGR_IMAGE);
      **/
      if (!cap.read(img)) {
        break;
      }
      else{


      // Just resize input image if you want

      resize(img, img, Size(640, 480));
      // create a foreground mask of proper size
      if (foregroundMask.empty()) {
        foregroundMask.create(img.size(), img.type());
      }
      // compute foreground mask 8 bits image
      // -1 is parameter that chose automatically your learning rate
      bg_model->apply(img, foregroundMask, true ? -1 : 0);
      // smooth the mask to reducenoise in image
      GaussianBlur(foregroundMask, foregroundMask, Size(11, 11), 3.5, 3.5 );
      // threshold mask to saturate at black and white values
      threshold(foregroundMask, foregroundMask, 10, 255, THRESH_BINARY );
      // create black foreground image
      foregroundImg = Scalar::all(0);
      // Copy source image to foregroung image only in area with white mask
      img.copyTo(foregroundImg, foregroundMask);
      // Get background image
      bg_model->getBackgroundImage(backgroundImage);
      // Show the results
      imshow("Foreground Mask", foregroundMask);

      imshow("Foreground Image", foregroundImg);
      int key6 = waitKey(10);
      if (!backgroundImage.empty()) {
        imshow("Mean Background Image", backgroundImage);
        int key5 = waitKey(10);

      }
    }

  }
  return EXIT_SUCCESS;
}
