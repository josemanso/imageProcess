//keypointsBRISK.cpp
#include <iostream>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;


int main(int argc, char** argv )
{
	Mat image = imread("/home/josemo/Documentos/imagenes/barco.jpg");
	if (image.empty()) {
		printf(" No image data.");
		getchar();
		return -1;
	}

	Ptr<cv::Feature2D> detect = BRISK::create();

	vector<KeyPoint> kp;
	detect->detect(image, kp);

	Mat result;
	drawKeypoints(image, kp, result, Scalar::all(-1), 
		DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imshow("Opencv :: "+ detect->getDefaultName(), result);
	waitKey(0);
	return 0; 
}
