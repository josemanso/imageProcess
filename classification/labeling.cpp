// Image connected component labeling
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

RNG rng(12345);
void connected_component_demo(Mat &image);
void connected_component_stats_demo(Mat &image);
int main(int argc, char** argv)
{
  Mat src = imread("/home/josemo/Documentos/imagenes/lampara.jpg");
  if (src.empty()){
    printf("Could not load image...\n");
    return -1;
  }
  imshow("input", src);
  connected_component_stats_demo(src);
  connected_component_demo(src);
  waitKey(0);
  return 0;
}


void connected_component_demo( Mat &image)
{
  // binaruzation
  Mat gray, binary;
  cvtColor(image, gray, COLOR_BGR2GRAY);
  threshold(gray, binary, 0,255, THRESH_BINARY |THRESH_OTSU);

  // morfology
  Mat k = getStructuringElement(MORPH_RECT, Size(3,3), Point(-1, -1));
  morphologyEx(binary, binary, MORPH_OPEN, k);
  morphologyEx(binary, binary, MORPH_CLOSE, k);
  imshow("binary", binary);
  //imwrite
  Mat labels = Mat::zeros(image.size(), CV_32S);
  int num_labels = connectedComponents(binary, labels, 8, CV_32S);
  printf("Total labels: %d\n",(num_labels - 1) );
  vector<Vec3b>colors(num_labels);

  // background colors
  colors[0] = Vec3b(0,0,0);

  // object color
  for (int i = 1; i < num_labels; i++) {
    colors[i] = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0,256));
  }

  // render result
  Mat dst = Mat::zeros(image.size(), image.type());
  int w = image.cols;
  int h = image.rows;
  for( int row = 0; row < h; row++){
    for( int col = 0; col < w; col++) {
      int label = labels.at<int>(row, col);
      if( label==0) continue;
      dst.at<Vec3b>(row, col) = colors[label];
    }
  }
  imshow("ccla_demo", dst);
}

void connected_component_stats_demo(Mat &image)
{
  // binaruzation
  Mat gray, binary;
  cvtColor(image, gray, COLOR_BGR2GRAY);
  threshold(gray, binary, 0,255, THRESH_BINARY |THRESH_OTSU);

  // morfology
  Mat k = getStructuringElement(MORPH_RECT, Size(3,3), Point(-1, -1));
  morphologyEx(binary, binary, MORPH_OPEN, k);
  morphologyEx(binary, binary, MORPH_CLOSE, k);

  //morfologyEX(binary, binary, MORPH_OPEN, k);
//morfologyEX(binary, binary, MORPH_CLOSE, k);
  imshow("binary", binary);

  Mat labels = Mat::zeros(image.size(), CV_32S);
  Mat stats, centroids;
  int num_labels = connectedComponentsWithStats(binary, labels, stats, centroids, 8,4);
  printf("Total labels: %d\n",(num_labels - 1) );
  vector<Vec3b>colors(num_labels);

  // background colors
  colors[0] = Vec3b(0, 0, 0);
  //object color.
  int b = rng.uniform(0, 256);
  int g = rng.uniform(0, 256);
  int r = rng.uniform(0, 256);
  for (int i = 0; i < num_labels; i++) {
    colors[i] = Vec3b(0, 255, 0);
  }
  // render result
  Mat dst = Mat::zeros(image.size(), image.type());
  int w = image.cols;
  int h = image.rows;
  for( int row = 0; row < h; row++){
    for( int col = 0; col < w; col++) {
      int label = labels.at<int>(row, col);
      if( label==0) continue;
      dst.at<Vec3b>(row, col) = colors[label];
    }
  }
  for (int i = 1; i < num_labels; i++) {
    Vec2b pt = centroids.at<Vec2d>(i,0);
    int x = stats.at<int>(i, CC_STAT_LEFT);
    int y = stats.at<int>(i, CC_STAT_TOP);
    int width = stats.at<int>(i,CC_STAT_WIDTH);
    int height = stats.at<int>(i, CC_STAT_HEIGHT);
    int area = stats.at<int>(i, CC_STAT_AREA);
    printf("area: %d, center pouint(%2f, %2f)\n", area, pt[0], pt[1] );
    circle(dst, Point(pt[0], pt[1]), 2, Scalar(0, 0, 255), -1, 8, 0);
    rectangle(dst, Rect(x, y, width, height), Scalar(255, 0, 255), 1, 8, 0);
  }
  imshow("ccla_demo stats", dst);

}
