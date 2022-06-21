//keypointsBRISK.cpp
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>

using namespace cv;
using namespace std;


int main(int argc, char** argv )
{
	Mat imageA = imread("/home/josemo/Documentos/imagenes/objects.jpg");
	Mat imageB = imread("/home/josemo/Documentos/imagenes/objects2.jpg");
	if (imageA.empty() || imageB.empty()) {
		printf(" No image data.");
		getchar();
		return -1;
	}

	Ptr<cv::Feature2D> detect = BRISK::create();

	vector<KeyPoint> kpA, kpB;
	Mat descA, descB;

	detect->detectAndCompute(imageA,noArray(), kpA, descA);
	detect->detectAndCompute(imageB,noArray(), kpB, descB);

	vector<DMatch> matches;

	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING, true);
	matcher->match(descA, descB, matches);

	sort(matches.begin(), matches.end());
	matches.erase(matches.begin() + 35, matches.end());

	Scalar color = Scalar::all(-1);
    //int flags = DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS;

    Mat result;
    drawMatches(imageA, kpA, imageB, kpB, matches, result, color, color,
     vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	imshow("Opencv :: MATCH Keypoints", result);
	waitKey(0);
	return 0; 
}