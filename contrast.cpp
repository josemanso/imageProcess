// contrast
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
	
	Mat imageContrastHigh2;
	image.convertTo(imageContrastHigh2, -1, 2, 0); //increase the contrast by 2
	
	Mat imageContrastHigh4;
	image.convertTo(imageContrastHigh4, -1, 4, 0); //increase the contrast by 4
	
	Mat imageContrastLow0_5;
	image.convertTo(imageContrastLow0_5, -1, 0.5, 0); //decrease the brightness by 0.5
	
	Mat imageContrastLow0_25;
	image.convertTo(imageContrastLow0_25, -1, 0.25, 0); //decrease the brightness by 0.25
	
	// Defining window name foe avobe images
	String windowNameOriginalImage = " Original Image";
	String windowNameContrastHigh2 = "Contrasrt Increase by 2";
	String windowNameContrastHigh4 = "Contrast Increase by 4";
	String windowNameContrastLow0_5 = "Contrast Decrease by 0.5";
	String windowNameContrastLow0_25 = "Contrast Decrease by 0.25";
	// create ans open windo for above images
	namedWindow( windowNameOriginalImage, WINDOW_NORMAL);
	namedWindow( windowNameContrastHigh2, WINDOW_NORMAL);
	namedWindow( windowNameContrastHigh4, WINDOW_NORMAL);
	namedWindow( windowNameContrastLow0_5, WINDOW_NORMAL);
	namedWindow( windowNameContrastLow0_25, WINDOW_NORMAL);
	
	// show
	imshow(windowNameOriginalImage, image);
	imshow(windowNameContrastHigh2, imageContrastHigh2);
	imshow( windowNameContrastHigh4, imageContrastHigh4);
	imshow( windowNameContrastLow0_5, imageContrastLow0_5);
	imshow( windowNameContrastLow0_25, imageContrastLow0_25);
	
	waitKey(0); // Wait for any ket stroke
	
	destroyAllWindows();
	
	return 0;
}
