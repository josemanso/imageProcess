// Contours
#include "opencv2/imgcodecs.hpp" //Image file reading and writing
#include "opencv2/highgui.hpp"  //  High-level GUI 
#include "opencv2/imgproc.hpp"  // Image Processing
#include <iostream>

cv:: Mat img_gray, input_img;
int thresh = 100;
const int MAX_THRESH = 255;
void draw_and_fill_contours(std::vector<std::vector<cv::Point>>& contours,
                            std::vector<std::vector<cv::Point>>& hull,
                            std::vector<cv::Vec4i>& hierarchy);

void find_contours (int, void*);


int main (int argc, char** argv)
{
    input_img = cv::imread("/home/josemo/Documentos/imagenes/single.jpeg");
    if (input_img.empty()) {
        fprintf(stdout,"Could not open image\n\n");
        return -1;
    }

    cv::cvtColor( input_img, img_gray, cv::COLOR_BGR2GRAY);
    cv::blur(img_gray, img_gray, cv::Size(3,3));
    const std::string source_window("Source");
    cv::namedWindow(source_window.c_str());
    cv:imshow(source_window.c_str(), input_img);
    cv::createTrackbar("Thres: ", source_window,&thresh, MAX_THRESH, find_contours);
    find_contours(0,0);

    //draw_and_fill_contours(contours, hull, hierarchy);

    cv::waitKey();
    return 0;
}





void draw_and_fill_contours(std::vector<std::vector<cv::Point>>& contours,
                            std::vector<std::vector<cv::Point>>& hull,
                            std::vector<cv::Vec4i>& hierarchy)
{
    cv::Mat contours_result = input_img.clone();
    cv::Mat fill_contours_result = cv::Mat::zeros(img_gray.size(), CV_8UC3);

    for (unsigned int i = 0, n = contours.size(); i < n; ++i) {
        cv::Scalar color = cv::Scalar(0,0,255);
        cv::drawContours( contours_result, contours, i, color, 4, 8, hierarchy,0,cv::Point());
    }

    cv::fillPoly(fill_contours_result, hull, cv::Scalar(255,255,255));

    cv::imshow("contours_result", contours_result);
    cv::imshow("Fill Contours Result", fill_contours_result);
}

void find_contours (int, void*){
    cv::Mat canny_output;
    cv::Canny( img_gray, canny_output, thresh, thresh*2);
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours( canny_output, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    std::vector<std::vector<cv::Point>> hull(contours.size());
    for( unsigned int i = 0, n = contours.size();i < n; ++i) {
        cv::convexHull(cv::Mat(contours[i]), hull[i], false);
    }

    draw_and_fill_contours(contours, hull, hierarchy);
}

