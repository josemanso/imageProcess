
/** Face Detection from Video
**  (using Haar feature-based cascade classifiers)
**/

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

// Function for Face Detection
void detectionAndDraw( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade);

int main()
{
  //// 1. Load Haar feature-based cascade classifiers
  String faceCascade_name { "/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml" } ;
  String eyesCascade_name { "/usr/share/opencv4/haarcascades/haarcascade_eye_tree_eyeglasses.xml" } ;
  CascadeClassifier faceCascade;// { "/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml" } ;
  CascadeClassifier eyesCascade;// { "/usr/share/opencv4/haarcascades/haarcascade_eye_tree_eyeglasses.xml" } ;

  // Load classifiers from "opencv/data/haarcascades" directory
  if (!faceCascade.load(faceCascade_name)) { printf("--(!)Error loading faces\n"); return -1; };
  if (!eyesCascade.load(eyesCascade_name)) { printf("--(!)Error loading eyes\n"); return -1; };


  // Start Video
  VideoCapture capture;
  Mat frame;

  capture.open(0);
  if (capture.isOpened())
  {
    // Capture frames
    cout << "Face Detection Started....." << endl;
    while(1)
    {
      capture >> frame;
      if (frame.empty()){
        cerr << "There is not image" << '\n';
        break;
      }

      Mat frame1 = frame.clone();
      detectionAndDraw( frame1, faceCascade, eyesCascade);
      char c = (char)waitKey(10);

      // press q to exit from Window.
      if (c == 27 || c == 'q' || c == 'Q'){
        break;
      }
    }// while
  }// if capture open.
  else{
    cerr << "Could not open camera" << '\n';
  }
  return 0;
}

// Function for Face Detection
void detectionAndDraw( Mat& inputFrame, CascadeClassifier& faceCascade,
                    CascadeClassifier& eyesCascade)
{
  Mat inputFrameGray;
  cvtColor(inputFrame, inputFrameGray, cv::COLOR_BGR2GRAY); // Conver to gray
  //// 3. Find areas with faces using Haar cascade classifier
  vector<Rect> faces;
  faceCascade.detectMultiScale(inputFrameGray, faces);

  for (size_t i = 0; i < faces.size(); i++) {
    Point faceCenter { faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2};
    Size halfFace { faces[i].width/2, faces[i].height/2 };
    // input center, axes, angle= 0, startAngle= 360, colo, thichness=2
    ellipse( inputFrame, faceCenter, halfFace, 0, 0, 360, Scalar(255, 0, 255), 2);
    // Get the region of interes: facerectangle sub-frame in gray and colored
    Mat faceROIGray {inputFrameGray(faces[i])};

    // Find areas with eyes in faces usin Haar cascade classifiers
    vector<Rect> eyes;
    eyesCascade.detectMultiScale( faceROIGray, eyes);
    for (size_t j = 0; j < eyes.size(); j++) {
      Point eyeCenter {faces[i].x + eyes[j].x + eyes[j].width/2,
                     faces[i].y + eyes[j].y + eyes[j].height/2};
      int radius { cvRound((eyes[j].width + eyes[j].height)*0.25)};
      // input center radius color, thichness
      circle( inputFrame, eyeCenter, radius, Scalar(255, 0, 0), 2);
    }
  }
  // Shou the output video
  imshow("Face Detection", inputFrame);
  //if (waitKey(20) == 27) desbreak; // Wait Esc key to end program
}
