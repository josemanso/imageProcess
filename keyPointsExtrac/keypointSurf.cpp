// SURF
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"

using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;


int main( int argc, char* argv[] )
{
	Mat image = imread("/home/josemo/Documentos/imagenes/barco.jpg");
	if (image.empty()) {
		printf(" No image data.");
		getchar();
		return -1;
	}
	//  Detect keypoints using SURF detector
	int minHessian = 400;
	Ptr<SURF> detector = SURF::create( minHessian);
	vector<KeyPoint> keypoints;
	detector->detect(image, keypoints);

	// Draw keypoints
	Mat img_keypoints;
	drawKeypoints( image, keypoints, img_keypoints);

	imshow("Image Keypoints", img_keypoints);

	waitKey(0);
	return 0;
}
