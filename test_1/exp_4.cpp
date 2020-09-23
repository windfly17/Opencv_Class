#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main() {
    cv::Mat srcMat = imread("D:\\Desktop\\Opencv_Class\\test_1\\Lena.jpg");
    cv::Mat deepMat;
    cv::Mat shallowMat;
    shallowMat = srcMat;
    srcMat.copyTo(deepMat);
    int height = srcMat.rows;
    int width = srcMat.cols;
    for (int j = 0;j < height;j++) {
        for (int i = 0; i < width; i++){
            uchar average = (srcMat.at<Vec3b>(j,i)[0]+srcMat.at<Vec3b>(j,i)[1]+srcMat.at<Vec3b>(j,i)[2])/3;
            srcMat.at<Vec3b>(j,i)[0]=average;
            srcMat.at<Vec3b>(j,i)[1]=average;
            srcMat.at<Vec3b>(j,i)[2]=average;
        }
    }
    imshow("test_4_shallowMat",shallowMat);
    imshow("test_4_deepMat",deepMat);
    waitKey(0);
}
