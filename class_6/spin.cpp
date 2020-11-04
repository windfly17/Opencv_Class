#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    cv::Mat dst;
    cv::Mat pic = imread(R"(D:\Desktop\Opencv_Class\class_6\1.jpg)");
    if(pic.empty()) return -1;

    float angle = 10, scal = 1;
    cv:Point2f center(pic.cols*0.5, pic.rows*0.5);
    const cv::Mat affine_matrix = cv::getRotationMatrix2D(center, angle, scal);
    cv::warpAffine(pic, dst, affine_matrix, pic.size());
    cv::imshow("pic", pic);
    cv::imshow("dst", dst);
    while (true) {
        if (waitKey(1) == 27)
        {
            break;
        }
    }
    return 0;
}
