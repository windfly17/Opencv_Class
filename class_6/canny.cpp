#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    cv::Mat canny, pic_g;
    std::vector<cv::Point2f> corners;
    cv::Mat pic = imread(R"(D:\Desktop\Opencv_Class\class_6\1.jpg)");
    cv::cvtColor(pic, pic_g, COLOR_BGR2GRAY);
    cv::Canny(pic, canny, 55, 250, 3);
    cv::imshow("pic", canny);
    while (true) {
        if (waitKey(1) == 27)
        {
            break;
        }
    }
    return 0;
}
