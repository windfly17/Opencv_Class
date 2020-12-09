#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

double scale = 1;

int main() {
    cv::Mat src = imread("../2.jpg");
    cv::Mat dst_0,dst;
    cv::resize(src, src, Size(static_cast<int>(src.cols * scale), static_cast<int>(src.rows * scale)));
    dst = Mat::zeros(Size(src.cols, src.rows*2), CV_8UC3);
    std::vector<cv::Mat>dst_part(src.channels());
    std::vector<cv::Mat>src_part(src.channels());      //生成与通道数数目相等的图像容器
    cv::split(src, src_part);                          //分解与通道数数目相等的图像容器
    cv::equalizeHist(src_part[0], dst_part[0]);
    cv::equalizeHist(src_part[1], dst_part[1]);
    cv::equalizeHist(src_part[2], dst_part[2]);
    cv::merge(dst_part, dst_0);
    src.copyTo(dst(Rect (0, 0, src.cols, src.rows)));
    dst_0.copyTo(dst(Rect (0, src.rows, src.cols, src.rows)));
    cv::imshow("11", dst);
    while (true) {
        if (waitKey(1) == 27)
        {
            break;
        }
    }
    return 0;
}
