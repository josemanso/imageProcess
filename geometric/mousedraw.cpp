// draw boxes on the ; mousedraw.cpp
#include <opencv2/opencv.hpp>
#include <iostream>


// Define our callback which we will install for mouse eventes
void my_mouse_callback(
  int event, int x, int y, int flags, void* param
);

cv::Rect box;
bool drawing_box = false;

// A littel subroutine to draw onto an image
void draw_box( cv::Mat& img, cv::Rect box){
  cv::rectangle(
    img,
    box.tl(),
    box.br(),
    cv::Scalar(0x00, 0x00, 0xff) /*red*/
  );
}

void help() {
  std::cout << " Call: ./ch4_ex4_1\n" <<
  " show how to use a mouse to draw regions in a image." << std::endl;
}

int main( int argc, char** argv){

  help();
  box = cv::Rect( -1, -1, 0, 0);
  cv::Mat image(600, 600, CV_8UC3), temp;
  image.copyTo(temp);

  box = cv::Rect(-1,-1, 0, 0);
  image = cv::Scalar::all(0);

  cv::namedWindow( "Box Example");

  // wil have the image to edit.
  cv::setMouseCallback(
    "Box Example",
    my_mouse_callback,
    (void*)&image
  );
  // The main program loop. Here we copy the working image
  // to the temp image, and if the user is drawing, then
  // put the currently contemplated box onto that temp image.
  // Display the temp image, and wait 15ms for a keystroke,
  // then repeat.
  for(;;) {
    image.copyTo(temp);
    if( drawing_box)draw_box( temp, box);

    if( cv::waitKey( 15 ) == 27) break;
  }

  return 0;
}

// Our mouse callback
void my_mouse_callback(
  int event, int x, int y, int flags, void* param
) {
  cv::Mat& image = *(cv::Mat*) param;

  switch (event) {
    case cv::EVENT_MOUSEMOVE: {
      if( drawing_box){
        box.width = x-box.x;
        box.height = y-box.y;
      }
    }
    break;
    case cv::EVENT_LBUTTONDOWN: {
      drawing_box = true;
      box = cv::Rect(x, y, 0, 0);
    }
    break;
    case cv::EVENT_LBUTTONUP: {
      drawing_box = false;
      if( box.width < 0){
        box.x += box.width;
        box.width *= -1;
      }
      if( box.height < 0){
        box.y -= box.height;
        box.height *= -1;
      }
      draw_box( image, box);
    }
    break;
  }
}
