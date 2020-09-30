#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int main() {
    cv::Mat src_color = imread("D:\\Desktop\\Opencv_Class\\test_2\\sunpower.jpg");
    std::vector<cv::Mat> channels;
    cv::split(src_color,channels);
    cv::Mat B = channels.at(0);
    cv::Mat G = channels.at(1);
    cv::Mat R = channels.at(2);
    cv::imshow("red", R);
    cv::imshow("green", G);
    cv::imshow("blue", B);
    cv::imshow("original_Mat", src_color);
    waitKey(0);
    return 0;
}
