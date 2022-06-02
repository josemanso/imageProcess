//cartoon
// Include OpenCV's C++ Interface
#include "opencv2/opencv.hpp"

#include <iostream>

#include "cartoon.cpp"


using namespace cv;
using namespace std;

int main(){

    //Read input image
    Mat image = imread("/home/josemo/Camera/IMG_20160528_220954022.jpg");

    //check if image exists
    if (image.empty()){
        cout<<"can not find image"<<endl;
        return 0;
    }
    // Create a blank output image, that we will draw onto.
    Mat displayedImage(image.size(), CV_8UC3);

    // Run the cartooniier filter on the camear frame.
    cartoonifyImage(image, displayedImage);

    // Display the processed image onto the screen,
    imshow("Cartoonifier", displayedImage);


    waitKey(0);

    return 0;
}
