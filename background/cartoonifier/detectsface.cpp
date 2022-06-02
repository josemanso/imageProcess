//Include required header files from OpenCV directory
#include "opencv2/objdetect.hpp"
//#include "/usr/local/include/opencv2/highgui.hpp"

//#include "/usr/local/include/opencv2/imgproc.hpp"

#include "opencv2/core/core.hpp"
//#include <opencv2/core/types_c.h>
//#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// Function for Face Detection
void detectionAndDraw( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade, double scale);

//// 1. Load Haar feature-based cascade classifiers
string cacadeName, nestedCascadeName;
String faceCascade { "/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml" } ;
String eyesCascade { "/usr/share/opencv4/haarcascades/haarcascade_eye_tree_eyeglasses.xml" } ;
String face_cascade_name = "haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";// /usr/share/opencv4
String face_cascade_name1 = "haarcascade_frontalcatface.xml";  //usr/share/opencv4
String eyes_cascade_name1 = "haarcascade_eye_tree_eyeglasses.xml";
String face_cascade_name2 = "haarcascade_frontalface_default.xml";
String eyes_cascade_name2 = "haarcascade_eye_tree_eyeglasses.xml";
String face_cascade_name3 = "/usr/share/opencv4/haarcascades/haarcascade_frontalcatface.xml";
String eyes_cascade_name3 = "/usr/share/opencv4/haarcascades/haarcascade_eye_tree_eyeglasses.xml";


/** function main **/
int main( int argc, const char** argv)
{
  // VideoCapture class for playing video
  VideoCapture capture;
  Mat frame, image;

  // PreDefined trained XML classifiers with facial features
  CascadeClassifier cascade, nestedCascade;
  double scale=1;

  // Load classifiers from "opencv/data/haarcascades" directory
  if (!cascade.load(face_cascade_name3)) { printf("--(!)Error loading faces\n"); return -1; };
  if (!nestedCascade.load(eyes_cascade_name3)) { printf("--(!)Error loading eyes\n"); return -1; };
  //nestedCascade.load( "../../haarcascade_eye_tree_eyeglasses.xml" ) ;
  //if( !nestedCascade.load( "haarcascade_eye_tree_eyeglasses.xml" )) {
    //print("--(!)Error loading eyes\n"); return -1;} ;
  /**
  if (!nestedCascade) {
    cerr << "Error loading haarcascade_eye_tree_eyeglasses" << '\n';
    return -1;
  }
  **/
  //CascadeClassifier(nestedCascade&  "../../haarcascade_eye_tree_eyeglasses.xml" );
  // Change path before execution
  //cascade.load( "../../haarcascade_frontalcatface.xml" ) ;
  //if (!cascade.load( "haarcascade_frontalcatface.xml" )){
  //  print("--(!)Error loading faces\n"); return -1;
  //} ;

  /**
  if (!cascade) {
    cerr << "Error loading haarcascade_frontalcatface" << '\n';
    return -1;
  }
  **/
  //CascadeClassifier(cascade&  "../../haarcascade_frontalcatface.xml");

  // Checks whether the classifier has been loaded.
  //bool CascadeClassifier::empty()

  /// 1. Load Haar feature-based cascade classifiers
  //if (!cascade.load(face_cascade)) { printf("--(!)Error loading faces\n"); return -1; };
  //if (!nestedCascade.load(eyes_cascade)) { printf("--(!)Error loading eyes\n"); return

  // Start Video
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
      detectionAndDraw( frame1, cascade, nestedCascade, scale);
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

void detectionAndDraw(
  Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
  double scale
)
{

  vector<Rect> faces, faces2;
  Mat gray, smallImg;

  cvtColor( img, gray, COLOR_BGR2GRAY); // Conver to gray
  double fx = 1/scale;

  // Resize the Grayscale Image
  resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR);
  equalizeHist( smallImg, smallImg);

  // Detect faces of different sizes using cascade classifier.
  cascade.detectMultiScale( smallImg, faces, 1.1, 2,
    0|CASCADE_SCALE_IMAGE,Size(30, 30));

  // Draw circles around the faces
  for( size_t i = 0; i < faces.size(); i++){
    Rect r = faces[i];
    Mat smallImgROI;
    vector<Rect> nestedObjects;
    Point center;
    Scalar color = Scalar(255, 0,0);  // Color for Drawing tool; blue
    int radius;

    double aspect_ratio = (double)r.width/r.height;
    if( 0.75 < aspect_ratio && aspect_ratio < 1.3 )
    {
      center.x = cvRound((r.x + r.width*0.5)*scale);
      center.y = cvRound((r.y + r.height*0.5)*scale);
      radius = cvRound((r.width + r.height)*0.25*scale);
      circle( img, center, radius, color, 3, 8, 0 );
    }
    else{
      rectangle( img,
        Point(cvRound(r.x*scale), cvRound(r.y*scale)),
                    Point(cvRound((r.x + r.width-1)*scale),
                    cvRound((r.y + r.height-1)*scale)), color, 3, 8, 0);
    }
    //rectangle( img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
                    //cvPoint(cvRound((r.x + r.width-1)*scale),
                    //cvRound((r.y + r.height-1)*scale)), color, 3, 8, 0);
      rectangle( img, Point(cvRound(r.x*scale), cvRound(r.y*scale)),
        Point(cvRound((r.x + r.width-1)*scale),
        cvRound((r.y + r.height-1)*scale)), color, 3, 8, 0);
    if(nestedCascade.empty()) continue;
    smallImgROI = smallImg( r );

    // Detection of eyes int the input image
    nestedCascade.detectMultiScale( smallImgROI, nestedObjects,
          1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
          printf("Supongo que está aqui...ojos.\n" );
    // Draw circles around eyes
    printf("Supongo que está aqui..no  eyes ..\n" );
    for( size_t j = 0; j < nestedObjects.size(); j++)
    {
      Rect nr = nestedObjects[j];
      center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale);
      center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale);
      radius = cvRound((nr.width + nr.height)*0.25*scale);
      circle( img, center, radius, color, 3, 8, 0);
    }
}
//
 // shoe proeccessed image with detected faces
 imshow("Faces Detection", img);
}
