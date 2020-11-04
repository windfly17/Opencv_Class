#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    cv::Mat dst;
    cv::Mat src = imread(R"(D:\Desktop\Opencv_Class\class_6\1.jpg)");
    if(src.empty()) return -1;
    //变换前
    cv::Point2f pts1[] = {
            cv::Point2f(150, 150),
            cv::Point2f(150, 300),
            cv::Point2f(350, 300),
            cv::Point2f(350, 150)
    };
    //变换后
    cv::Point2f pts2[] = {
            cv::Point2f(200, 150),
            cv::Point2f(200, 300),
            cv::Point2f(340, 270),
            cv::Point2f(340, 180)
    };
    //计算仿射矩阵
    cv::Mat perspective_matrix = cv::getPerspectiveTransform(pts1, pts2);

    cv::warpPerspective(src, dst, perspective_matrix, src.size());
//
    cv::imshow("pic", src);
//    cv::imshow("dst", dst);
    while (true) {
        if (waitKey(1) == 27)
        {
            break;
        }
    }
    return 0;
}
