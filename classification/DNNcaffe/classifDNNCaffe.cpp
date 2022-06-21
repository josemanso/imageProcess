//  Classification DNNcaffe
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/all_layers.hpp>


using namespace std;
using namespace cv;
using namespace dnn;





int main( int argc, char** argv)
{
  vector<string> class_names;
  //ifstream ifs(string("/home/josemo/opencv/input/classification_classes_ILSVRC2012.txt").c_str());
  // We will leverage the pre-trained models. These models have been trained on the MS COCO dataset,
  ifstream ifs(string("/home/josemo/opencv/input/object_detection_classes_coco.txt").c_str());
  string line;
  while (getline(ifs, line)){
    class_names.push_back(line);
  }
  // load the pre-trained DEsnseNet121 model, or COCO
  // load the neuronal network model
  /**
  auto model = readNet("/home/josemo/opencv/input/DenseNet_121.prototxt",
                       "/home/josemo/opencv/input/DenseNet_121.caffemodel",
                       "Caffe");
  **/
  auto model = readNet("/home/josemo/opencv/input/frozen_inference_graph.pb",
                       "/home/josemo/opencv/input/ssd_mobilenet_v2_coco_2018_03_29.pbtxt.txt",
                       "TensprFlow");

  //Load the image from disk
  //Mat image = imread("/home/josemo/opencv/input/image_1.jpg");
  Mat image = imread("/home/josemo/opencv/input/image_2.jpg");
  int image_height = image.cols;
  int image_width = image.rows;
  // create a blob from image
  //Mat blob = blobFromImage(image, 0.01, Size(244, 244), Scalar(104, 117, 123)); 
  Mat blob = blobFromImage(image, 1.0, Size(300, 300), Scalar(127.5,127.5,127.5), true, false);


  // set the input blob for the neuronal network
  model.setInput(blob);
  // forward pass the image blob through the model
  Mat output = model.forward();
  Mat detectionMat(output.size[2], output.size[3], CV_32F, output.ptr<float>());

  // Looping Over the Detections and Drawing the Bounding Boxes
  for (int i = 0; i < detectionMat.rows; i++) {
    int class_id = detectionMat.at<float>(i, 1);
    float confidence = detectionMat.at<float>(i, 2);

    // Check if the detection is of good quality
    if (confidence > 0.4){
      int box_x = static_cast<int>(detectionMat.at<float>(i, 3) * image.cols);
      int box_y = static_cast<int>(detectionMat.at<float>(i, 4) * image.rows);
      int box_width = static_cast<int>(detectionMat.at<float>(i, 5) * image.cols - box_x);
      int box_height = static_cast<int>(detectionMat.at<float>(i, 6) * image.rows - box_y);
      rectangle(image, Point(box_x, box_y), Point(box_x+box_width, box_y+box_height),
                Scalar(255,255,255), 2);
      putText( image, class_names[class_id-1].c_str(), Point(box_x,box_y-5),
               FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,255,255), 1);
    }
  }

  /**
  Point classIdPoint;
  double final_prob;
  minMaxLoc(outputs.reshape(1, 1), 0, &final_prob, 0, &classIdPoint);
  int label_id = classIdPoint.x;
  // Print predicted class.
  string out_text = format("%s, %.3f", (class_names[label_id].c_str()), final_prob);
  //put the class name text on top of the image
  putText(image, out_text, Point(29, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255,0), 2);
  **/
  imshow("Image", image);
  //imawrite

    waitKey(0);
    destroyAllWindows();
    return 0;
}
