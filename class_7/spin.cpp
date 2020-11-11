#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    cv::Mat dst;
    cv::Mat pic = imread(R"(D:\Desktop\Opencv_Class\class_7\1.jpg)");
    if(pic.empty()) return -1;

    float angle = 10, scale = 1;
    cv::Point2f center(pic.cols*0.5, pic.rows*0.5);
    cv::Mat rot = cv::getRotationMatrix2D(center, angle, scale);
    cv::Rect bbox = cv::RotatedRect(center, pic.size(), angle).boundingRect();
    rot.at<double>(0,2) += bbox.width / 2.0 - center.x;
    rot.at<double>(1,2) += bbox.height / 2.0 - center.y;
//    const cv::Mat affine_matrix = cv::getRotationMatrix2D(center, angle, scale);
    cv::warpAffine(pic, dst, rot, bbox.size());
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
