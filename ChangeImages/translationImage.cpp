// transformImage translation
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main (int argc, char** argv)
{
  Mat image = imread("/home/josemo/Documentos/imagenes/barco.jpg");

  // get the hight and width of the image
  int height = image.cols;

  int width = image.rows;
  std::cout << "Heigth colunm;  " << height << std::endl; // '\n';
  

  // get tx and ty values for translation
  float tx = float(width)/4;
  float ty = float(height)/4;
  // create the translation matix
  float warp_values[] = {1.0, 0.0, tx, 0.0, 1.0, ty};
  Mat translation_matrix = Mat(2,3, CV_32F, warp_values);
  // save the resulting image in translated_image matrix
	Mat translated_image;
	// apply affine transformation to the original image using the translation matrix
	warpAffine(image, translated_image, translation_matrix, image.size());

  //display the original and the Translated images
	imshow("Translated image", translated_image);
	imshow("Original image", image);
	waitKey(0);

  return 0;

}
