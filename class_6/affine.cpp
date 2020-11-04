#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    cv::Mat dst;
    cv::Mat src = imread(R"(D:\Desktop\Opencv_Class\class_6\1.jpg)");
    if(src.empty()) return -1;
    //变换前
    const cv::Point2f src_pt[] = {
            cv::Point2f(200, 200),
            cv::Point2f(250, 200),
            cv::Point2f(200, 100)
            };
    //变换后
    const cv::Point2f dst_pt[] = {
            cv::Point2f(300, 100),
            cv::Point2f(300, 50),
            cv::Point2f(200, 100)
    };
    //计算仿射矩阵
    const cv::Mat affine_matrix = cv::getAffineTransform(src_pt, dst_pt);

    cv::warpAffine(src, dst, affine_matrix, src.size());

    cv::imshow("pic", src);
    cv::imshow("dst", dst);
    while (true) {
        if (waitKey(1) == 27)
        {
            break;
        }
    }
    return 0;
}
