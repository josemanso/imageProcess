// change brightness image
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	// Read the image file
	Mat image = imread("/home/josemo/Documentos/imagenes/parck.jpg");
	
	// Check
	if (image.empty()){
		cout << "Could not open or find the image " << endl;
		cin.get(); // wait for any key
		return -1;
	}
	
	Mat imageBrightnessHigh50;
	image.convertTo(imageBrightnessHigh50, -1, 1, 50); //increase the brightness by 50
	
	Mat imageBrightnessHigh100;
	image.convertTo(imageBrightnessHigh100, -1, 1, 100); //increase the brightness by 100
	
	Mat imageBrightnessLow50;
	image.convertTo(imageBrightnessLow50, -1, 1, -50); //decrease the brightness by 50
	
	Mat imageBrightnessLow100;
	image.convertTo(imageBrightnessLow100, -1, 1, -100); //decrease the brightness by 100
	
	// Defining window name foe avobe images
	String windowNameOriginalImage = " Original Image";
	String windowNameBrightnessHigh50 = "Brightness Increase by 50";
	String windowNameBrightnessHigh100 = "Brightness Increase by 100";
	String windowNameBrightnessLow50 = "Brightness Decrease by 50";
	String windowNameBrightnessLow100 = "Brightness Decrease by 100";
	// create ans open windo for above images
	namedWindow( windowNameOriginalImage, WINDOW_NORMAL);
	namedWindow( windowNameBrightnessHigh50, WINDOW_NORMAL);
	namedWindow( windowNameBrightnessHigh100, WINDOW_NORMAL);
	namedWindow( windowNameBrightnessLow50, WINDOW_NORMAL);
	namedWindow( windowNameBrightnessLow100, WINDOW_NORMAL);
	
	// show
	imshow(windowNameOriginalImage, image);
	imshow(windowNameBrightnessHigh50, imageBrightnessHigh50);
	imshow( windowNameBrightnessHigh100, imageBrightnessHigh100);
	imshow( windowNameBrightnessLow50, imageBrightnessLow50);
	imshow( windowNameBrightnessLow100, imageBrightnessLow100);
	
	waitKey(0); // Wait for any ket stroke
	
	destroyAllWindows();
	
	return 0;
}
	
	
