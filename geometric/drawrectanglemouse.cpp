//drawrectanglesmouse.cpp
#include <opencv2/opencv.hpp>

using namespace cv;

#define WIINDOW_NAME "Drawing Rectangle"

// Define our callback which we will install for mouse eventes
void on_MouseHandle(
  int event, int x, int y, int flags, void* param
);

void DrawRectangle(Mat& img, Rect box);

void ShowHelpText();

Rect g_rectangle;
bool g_bDrawingBox = false;
RNG g_rng(12345); // Generate random number

int main( int argc, char** argv) {
    system("color 9F");
    ShowHelpText();
    g_rectangle = Rect(-1,-1,0,0); // Rect_<<_Tp>::Rect_(_Tp_x, _Tp_y, _TP_width,_Tp_height)
    Mat srcImage(600, 800, CV_8UC3), tempImage;
    //Mat tempImage;
    //srcImage.copyTo(tempImage);
    //g_rectangle =
    srcImage = Scalar::all(0);
    namedWindow(WIINDOW_NAME);
    setMouseCallback(WIINDOW_NAME, on_MouseHandle, (void*) &srcImage);

    while(1) {
        srcImage.copyTo(tempImage);
        if(g_bDrawingBox) DrawRectangle(tempImage, g_rectangle);
        imshow(WIINDOW_NAME, tempImage);
        if (waitKey(10) == 27)  // stop drawing rectangle if key is ESC
           break;

    }
    return 0;
}

void on_MouseHandle(int event, int x, int y, int flags, void* param) {
    Mat& image = *(cv::Mat*) param;
    switch (event) {
        case EVENT_MOUSEMOVE: { 
            // When mouse moves, get the courrent rectangle's width and heigth
            if (g_bDrawingBox) {
                g_rectangle.width = x - g_rectangle.x;
                g_rectangle.height = y - g_rectangle.y;
            }
        }
        break;

        case EVENT_LBUTTONDOWN: { //Whwn the left mouse button is presserd down,
                                  // get the startingcorner's coordenates of the rectangle

            g_bDrawingBox = true;
            g_rectangle =  Rect(x,y,0,0);
        }
        break;

        case EVENT_LBUTTONUP: {  // When the left mouse button is released, 
                                // draw the rectangle
            g_bDrawingBox = false;
            if (g_rectangle.width < 0) {
                g_rectangle.x += g_rectangle.width;
                g_rectangle.width *= -1;
            }

            if (g_rectangle.height < 0) {
                g_rectangle.y += g_rectangle.height;
                g_rectangle.height *= -1;
            }
            DrawRectangle(image, g_rectangle);
        }
        break;
    }
}
void DrawRectangle( Mat& img, Rect box)
{
    // Draw thw rectangle with random color
    rectangle( img, box.tl(), box.br(), Scalar(g_rng.uniform(0,255), 
              g_rng.uniform(0, 255), g_rng.uniform(0,255)));
}

void ShowHelpText(){
    printf(" When mouse moves, get the courrent rectangle's width and heigth");
    printf("When the left mouse button is presserd down, ");
    printf("get the starting corner's coordenates of the rectangle");
    printf("When the left mouse button is released, draw the rectangle");
    printf(" Stop drawing rectangle if key is ESC");
}