// objectDetection.cpp

#include <iostream>	// c++ standar input/output

#include <opencv2/opencv.hpp>  // OpenCV library 
#include <opencv2/features2d.hpp>


//*************************************************************************
// C++ namespaces C++ (avoid using prefix for standard classes)
// for OpenCV we will use  cv::  prefix
//*************************************************************************
using namespace std;

//*************************************************************************
// Funciones
//*************************************************************************
int main( int argc, char** argv)
{
	//// 1. Create mask control window with default HSV range to detect blue color
	auto const MASK_WINDOW = "Mask Settings";
    cv::namedWindow(MASK_WINDOW, cv::WINDOW_AUTOSIZE);

    // HSV range to detect blue color
    int minHue = 90, maxHue = 140;
    int minSat = 74, maxSat = 255;
    int minVal =  0, maxVal = 255;


    // Create trackbars in mask settings window
    cv::createTrackbar("Min Hue", MASK_WINDOW, &minHue, 179);
    cv::createTrackbar("Max Hue", MASK_WINDOW, &maxHue, 179);
    cv::createTrackbar("Min Sat", MASK_WINDOW, &minSat, 255);
    cv::createTrackbar("Max Sat", MASK_WINDOW, &maxSat, 255);
    cv::createTrackbar("Min Val", MASK_WINDOW, &minVal, 255);
    cv::createTrackbar("Max Val", MASK_WINDOW, &maxVal, 255);


	
//// 2. Capture from default camera
    cv::VideoCapture videoCapture(0);
	
	//-------------------------------------------
	// Main processing loop
	//-------------------------------------------
	// while there are images ...
	while(true) {

		//// 3. Capture and convert video to HSV color space
		cv::Mat inputVideo;
		videoCapture.read(inputVideo);
		cv::flip(inputVideo, inputVideo, 1);
		cv::Mat inputVideoHSV;
		cv::cvtColor(inputVideo, inputVideoHSV, cv::COLOR_BGR2GRAY);

		//// 4. Create mask and result (masked) video
		cv::Mat mask;
		// params: input array, lower boundary array, upper boundary array, output array
		cv::inRange(
			inputVideoHSV,
			cv::Scalar(minHue, minSat, minVal),
			cv::Scalar(maxHue, maxSat, maxVal),
			mask);
		cv::Mat resultVideo;
		// params: src1	array, src2 array, output array, mask
		cv::bitwise_and(inputVideo, inputVideo, resultVideo, mask);

		// 5. Show videos
		cv::imshow("Input Video", inputVideo);
		cv::imshow("Result (Masked) Video", resultVideo);

		//wait for 'esc'
		if (cv::waitKey(30) == 27) break;
	

		
	}
	
}