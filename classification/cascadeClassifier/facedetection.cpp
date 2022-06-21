//  - Load training data Cascade Classifiers
//  - Test Detection  with camera images
//
#include <iostream>	// c++ standar input/output

#include <opencv2/opencv.hpp>  // OpenCV library headers

// C++ namespaces C++ (avoid using prefix for standard classes)
// for OpenCV we will use  cv::  prefix
using namespace std;

//*************************************************************************
// Function prototypes
//*************************************************************************



//*************************************************************************
// Constants
//*************************************************************************
const char  * WINDOW_CAMERA1  = "(W1) Camera 1";	// windows id

//*************************************************************************
// Variables Globales
//*************************************************************************
int CAMERA_ID = 0;	//  default camera 0

string CASCADE_FACE_FILE = "/home/josemo/opencv/data_trained/data/haarcascades/haarcascade_frontalface_alt2.xml";
string CASCADE_EYES_FILE = "/home/josemo/opencv/data_trained/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";

//string CASCADE_FACE_FILE = ("/usr/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml");
//string CASCADE_EYES_FILE = "/usr/share/opencv4/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
//String CASCADE_FACE_FILE { "/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml" } ;
//String CASCADE_EYES_FILE { "/usr/share/opencv4/haarcascades/haarcascade_eye_tree_eyeglasses.xml" } ;

//*************************************************************************
// Funciones
//*************************************************************************

int main (int argc, char** argv)
{
    int key;
    cv::VideoCapture camera;  // Cameras
    cv::Mat capture; // Images
    cv::Mat gray_image;
    cv::Size camSize; // Camera resolution

    // check command line parameters (camera id)
    if(argc>2 && string(argv[1])=="-c")
        CAMERA_ID = atoi(argv[2]);

    // Load cascade trained classifiers
    cv::CascadeClassifier face_cascade, eyes_cascade;
    //String CASCADE_FACE_FILE { "/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml" } ;
    //String CASCADE_EYES_FILE { "/usr/share/opencv4/haarcascades/haarcascade_eye_tree_eyeglasses.xml" } ;
    
    // Load classifiers from "opencv/data/haarcascades" directory
    if (!face_cascade.load(CASCADE_FACE_FILE)) { printf("--(!)Error loading faces\n"); return -1; };
    if (!eyes_cascade.load(CASCADE_EYES_FILE)) { printf("--(!)Error loading eyes\n"); return -1; };


    cv::HOGDescriptor pederastian_detector;
    pederastian_detector.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());


    // Configuring cameras
    camera.open(CAMERA_ID);  // open camera
    if (!camera.isOpened()) {
        cerr << "You need to connect a camer, sorry" << endl;
        getchar(); // wait for a keystroke and exits
        return -1;
    }
    // Getting camera resolution
    camSize.width = (int)camera.get(cv::CAP_PROP_FRAME_WIDTH);
    camSize.height = (int)camera.get(cv::CAP_PROP_FRAME_HEIGHT);

    // Creating visualization windows
    cv::namedWindow(WINDOW_CAMERA1, cv::WINDOW_AUTOSIZE);

    cout << "Capturing images.\n Hit q/Q to exit." << endl;

    //-------------------------------------------
	// Main processing loop
	//-------------------------------------------
	// while there are images ...
    while(camera.read(capture)) {
        if (capture.empty()) {
            continue;// capture hast failled, continue
        }

        //-------------------------------------------
		// Put your image processing code here
		//-------------------------------------------
        cv::cvtColor(capture, gray_image, cv::COLOR_BGR2GRAY); // transforms to gray level
        cv::equalizeHist( gray_image, gray_image); // Normalize gray levels

        // Detect faces
        vector<cv::Rect> faces;
        face_cascade.detectMultiScale(gray_image, faces);

        for (size_t i = 0; i <faces.size(); i++) {
            cv::Point center(faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2);
          cv::ellipse(capture, center, cv::Size(faces[i].width/2, faces[i].height/2),
            0,0,360,cv::Scalar(255,0,255),4);

            cv::Mat faceROI = gray_image(faces[i]);  // region of interes
            //  -- in each faces, detect eyes
            vector<cv::Rect> eyes;
            eyes_cascade.detectMultiScale(faceROI, eyes);
            for (size_t j = 0; j < eyes.size(); j++) {
                cv::Point eye_center(faces[i].x+eyes[j].x+eyes[j].width/2,
                faces[i].y+eyes[j].y+eyes[j].height/2);
                int radius = cvRound((eyes[j].width+eyes[j].height)*0.25);
                cv:circle(capture, eye_center, radius, cv::Scalar(255,0,0),4);
            }

        }

        // Detected pederastians
        vector<cv::Rect> foundLocations;
        vector<double> foundWeigths;
        pederastian_detector.detectMultiScale(gray_image, foundLocations, foundWeigths);

        for(size_t i = 0; i <foundLocations.size(); i++) {
            int x,y,w,h;
            x = foundLocations[i].x; y = foundLocations[i].y;
            w = foundLocations[i].width; h =foundLocations[i].height;
            cv::rectangle(capture,cv::Point(x,y), cv::Point(x+w, y+h),cv::Scalar(0,0,200),2);

            ostringstream text;
            text << setprecision(2) << foundWeigths[i];

            cv::Size textSize; int baseline;
            textSize = cv::getTextSize(text.str(), cv::FONT_HERSHEY_DUPLEX, 0.3,1, &baseline);
            cv::rectangle(capture, cv::Point(x,y), cv::Point(x+10+textSize.width, y-10-textSize.height),
            cv::Scalar(0,0,200), cv::FILLED);
            cv::putText(capture, text.str(), cv::Point(x+5, y-5), cv::FONT_HERSHEY_DUPLEX, 0.3,
            cv::Scalar(0,0,0), 1, cv::LINE_AA);
        }

        // Visualizton code
        cv::imshow(WINDOW_CAMERA1, capture); // show image in a window

        // wait 10 ms for a keystroke ti exit (image window must be on focus)
        key = cv::pollKey();
        if (key == 'q' || key == 'Q' || key == 27) break;

    }
    //-------------------------------------------
	// free windows and camera resources
	//-------------------------------------------
	cv::destroyAllWindows();
	if (camera.isOpened())	camera.release();

	// programm exits with no errors
	return 0;

}
