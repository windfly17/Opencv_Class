#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    cv::Mat src_color = imread("D:\\Desktop\\Opencv_Class\\test_2\\sunpower.jpg");
    cv::Point pt;
    pt.x = 400;
    pt.y = 600;
    circle(src_color, pt, 200, CV_RGB(0, 255, 0), -1, 8, 0);
    imshow("picture", src_color);
    waitKey(0);
    return 0;
}

