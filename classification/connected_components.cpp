///
//#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main( int argc, const char** argv )
{
  //Read image over which cca will be applied
  Mat image = imread("/home/josemo/Documentos/imagenes/lampara.jpg", IMREAD_GRAYSCALE);
  if(image.empty())
  {
    cout << "Could not read input image file " << endl; //inputImage << endl;
    return EXIT_FAILURE;
  }
  // get binary image
  Mat binaryImage;
  threshold(image, binaryImage, 127, 255, THRESH_BINARY);
  // Get connected components
  Mat labelImage;
  connectedComponents(binaryImage, labelImage);

  //Get the clone of input image to work on so that we can compare input and output images finally
  Mat imLableClone = labelImage.clone();

  //Find min and max pixel values and their location in the image
  Point minPos, maxPos;
  double min, max;
  minMaxLoc(imLableClone, &min, &max, &minPos, &maxPos);

  // Normalize the image so that min value in 0, and max value is 255
  imLableClone = 255 * (imLableClone - min)/(max-min);

  // Convert image to 8 bits
  imLableClone.convertTo(imLableClone, CV_8U);

  Mat imLableCloneColorMap;

  // Applay color map to image
  applyColorMap( imLableClone, imLableCloneColorMap, COLORMAP_JET);

  // Create windows to display images
  namedWindow("input image", WINDOW_NORMAL);
  namedWindow("cca image", WINDOW_NORMAL);
  namedWindow("cca image color map", WINDOW_NORMAL);

  // display
  imshow( "input image", binaryImage);
  imshow( "cca image", imLableClone);
  imshow( "cca image color map", imLableCloneColorMap);


  waitKey(0);
  // close all the windows
  destroyAllWindows();
  return EXIT_SUCCESS;

}
