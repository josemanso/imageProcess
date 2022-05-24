// histogram
#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    Mat src, dst;
    //string imageName("/home/josemo/Documentos/imagenes/uned.png");
    //string imageName("/home/josemo/Documentos/imagenes/hangtrong.jpg");
    string imageName("/home/josemo/Camera/IMG_20190628_221425466.jpg");
    if (argc > 1)
    {
        imageName = argv[1];
    }
    // Load the source image
    src = imread( imageName, IMREAD_COLOR );

    if (src.empty() ){
        cout<<"Could not open file"<<endl;
        return -1;
    }
    // Separatethe source image in its three R, G and B planes,
    // funtion split, divided image in thre channels 
    vector<Mat> bgr_planes;
    split(src, bgr_planes);

    // Number of bins
    int histSize = 256;

    // Range of values
    float range[] = {0, 256};
    const float* histRange = {range};

    bool uniform = true; bool accumulate = false;

    // create a Mat objets to save our histogram
    Mat b_hist, g_hist, r_hist;

    // Calculate the histogram by using OpenCv function calHist
    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);


    // Draw the histogram for B, G and R
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize);

    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar(0,0,0));

    // Normalice(function) out of ramge values
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    // Access the bin (in this case in this 1D-Histogram):

    for ( int  i = 1; i < histSize; i++)
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1))),
                         Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(1))),
                         Scalar( 255, 0, 0), 2, 8, 0);
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1))),
                         Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(1))),
                         Scalar( 0, 255, 0), 2, 8, 0);
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1))),
                         Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(1))),
                         Scalar( 0, 0, 255), 2, 8, 0);
    }

    namedWindow("calcHist Demo", WINDOW_AUTOSIZE);
    imshow("calcHist Demo",histImage);

    waitKey(0);

    return 0;
}
