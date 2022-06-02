// K-Means
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int main( int argc, char** argv)
{
  Mat img(500, 500, CV_8UC3);
  RNG rng(12345);

  Scalar colorTab[] = {
    Scalar(0, 0, 255),
    Scalar(255, 0, 0),
  };

  int numCluster = 2;
  int sampleCount = rng.uniform(5, 500);
  Mat points(sampleCount, 1, CV_32FC2);

  // Generate random number
  for (int k = 0; k < numCluster; k++) {
    Point center;
    center.x = rng.uniform(0, img.cols);
    center.y = rng.uniform(0, img.rows);
    Mat pointChunk = points.rowRange(k*sampleCount/numCluster,
            k == numCluster - 1 ? sampleCount : (k+1)*sampleCount/numCluster);
    rng.fill(pointChunk, RNG::NORMAL, Scalar(center.x, center.y),
            Scalar(img.cols*0.05, img.rows*0.05));
  }
  randShuffle(points, 1, &rng);

  // using Kmeans
  Mat labels;
  Mat centers;
  //kmeans(points, numCluster, labels, TermCriteria(TermCriteria::EPS + TermCriteria))
  kmeans(points, numCluster, labels, TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1),
              3, KMEANS_PP_CENTERS, centers);
	//The sample data entered by points must be organized by line.
  // Each line has one sample data, and the sample dimensions are listed;
  // k represents the number of final classifications
	//bestlabels represents the label of each sample for final classification,
  // criteria represents the stop condition for kmeans segmentation,
  // and attempts represents the number of attempts to sample different initialization labels,
  // which is generally equivalent to K flag represents the center initialization method,
  // and centers represents the center position of each cluster after final segmentation

  // Display categories in diferent colors
  img = Scalar::all(255);
  for (int i = 0; i < sampleCount; i++) {
    int index = labels.at<int>(i);
    Point p = points.at<Point2f>(i);
    circle(img, p, 2, colorTab[index], -1, 8);
  }

  // Circle is drawn at the center of each cluster
  for (int i = 0; i < centers.rows; i++) {
    int x = centers.at<float>(i, 0);
    int y = centers.at<float>(i, 1);
    printf("c.x= %d, c.y = %d\n", x, y );
    circle(img, Point(x,y), 40, colorTab[i], 1, LINE_AA);
  }

  imshow("Kmeans-Data-Demo", img);
  waitKey(0);
  return 0;
}
