//sktech.cpp
#include <iostream>
#include <opencv2/opencv.hpp>
//#include <opencv2/videoio.hpp>
//#include "opencv2/highgui.hpp"

#include "cartoon.cpp"

using namespace cv;
using namespace std;

int main (int argc, char** argv)
{
  int cameraNumber = 0;
  // Get access to the camera.
  VideoCapture camera;
  camera.open(cameraNumber);
  if (!camera.isOpened()) {
    cerr << "ERROR: Could not access the camera or video!" <<
    endl;
    exit(1);
  }
  // Try to set the camera resolution.
  //camera.set(CV_CAP_PROP_FRAME_WIDTH, 640);
  //camera.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

  // Loop; basic real-time camera
  while (true){
    // Grab the nwxt camera frame.
    Mat cameraFrame;
    camera >> cameraFrame;
    if (cameraFrame.empty()){
      cerr << "Error: Couldn't grab a camera frame."<<endl;
      exit(1);
    }
    // Create a blank output image, that we will draw onto.
    Mat displayedFrame(cameraFrame.size(), CV_8UC3);

    // Run the cartooniier filter on the camear frame.
    cartoonifyImage(cameraFrame, displayedFrame);

    // Display the processed image onto the screen,
    imshow("Cartoonifier", displayedFrame);

    //  Wait for at least 20 millisecons,
    // so that the image can be displayed on the screen.
    // Checks if a key was pressed
    char keypress = waitKey(20); // Need this to see anything!
    if (keypress == 27) {  // Escape Key
      break;
    }
  } // end while
}
