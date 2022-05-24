// transformImage.cpp
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main (int argc, char** argv)
{
  Mat image = imread("/home/josemo/Documentos/imagenes/barco.jpg");
  imshow( "Original Image ", image);

  waitKey(0);

  double angle = 45;

  //get the center coordenates of image to create the 2D rotation
  Point2f center((image.cols - 1)/ 2.0, (image.rows -1)/ 2.0);
  // using getRotationMatrix2D to get rotation matrix
  Mat rotation_matrix = getRotationMatrix2D(center, angle, 1.0);
  // The finction return 2D-rotation matix
  // wich will be used in the next step to rotate the image
  // We will save the resulting image in rotate_image matrix
  // rotate using warpAffine
  Mat rotated_image;
  warpAffine( image, rotated_image, rotation_matrix, image.size());
  imshow(" Rotated Image warAffine", rotated_image);
  waitKey(0);
  return 0;

}
