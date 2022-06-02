// grabcut segmentation
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


// mouse events
void onMouse( int event, int x, int y, int flags, void* userdata);

Rect rect;
Mat src_img, roi_img, dst_img;

void showImg();

void help() {
  cout << " Call: First:\n" <<
  " use a mouse to draw regions in a image." << std::endl;
  cout << " And then: \n" <<
  " enter the leter o, to show region in a image." << std::endl;
}

int main( int argc, char** argv)
{
  help();
  src_img = imread("/home/josemo/Documentos/imagenes/tulipanes.jpg");
  namedWindow( "Original Image", WINDOW_AUTOSIZE);
  imshow("Original Image", src_img);
  setMouseCallback("Original Image", onMouse);
  Mat dest_img = Mat::zeros(src_img.size(), CV_8UC1);
  // Cut -- GrabCut
  // Dos variables matriciales temporales, utilizadas como variables intermedias del algoritmo
  // // Two temporary array variables, used as intermediate variables of the algorithm
  Mat bgModel, fgModel;
  char c = waitKey(0);
  if (c == 'o') {
    grabCut( src_img, dst_img, rect, bgModel, fgModel, 1, GC_INIT_WITH_RECT);
    // El valor de dst_img se compara con los posibles píxeles de primer plano antes de enviarlo a dst_img
    // The value of dst_img is compared to possible foreground pixels before sending it to dst_img
    compare(dst_img, GC_PR_FGD, dst_img, CMP_EQ);
    // Generate output
    Mat foreground( src_img.size(), CV_8UC3, Scalar(255, 255, 255));
    // Copie el área dst_img de la imagen original src_img en primer plano
    // Copie el área dst_img de la imagen original src_img en primer plano
    src_img.copyTo(foreground, dst_img);

    imshow("Final Image", foreground);
  }
  waitKey(0);
  return 0;
}

void showImg() {
  src_img.copyTo(roi_img);
  rectangle(roi_img, rect, Scalar(0, 0, 255), 2);
  imshow("src 1210", roi_img);
}

//Rectangle selection by mouse
void onMouse(int event, int x, int y, int flags, void* userdata) {
  switch ((event))
  {
    case EVENT_LBUTTONDOWN:   /* lef button */
      {
        rect.x = x;
        rect.y = y;
        rect.width = 1;
        rect.height = 1;
      }
    break;
    case EVENT_MOUSEMOVE:
      {
        if (flags && EVENT_FLAG_LBUTTON) {
          rect = Rect( Point( rect.x, rect.y), Point( x, y));
          showImg();
        }
      }
    break;
    case EVENT_LBUTTONUP:
    {
        if (rect.width > 1 && rect.height > 1) {
        showImg();
        }
    }
    break;

    default:     break;
  }
}
