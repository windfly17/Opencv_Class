#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    cv::Mat pic = imread(R"(D:\Desktop\Opencv_Class\class_7\2.jpg)");
    if (pic.empty()) return -1;
    cv::Mat pic_g, pic_th, pic_canny;
    cv::cvtColor(pic, pic_g,COLOR_BGR2GRAY);
    cv::Mat elementRect;
//    elementRect = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(3,3),cv::Point(-1,-1));
//    cv::morphologyEx(pic_g,pic_g,cv::MORPH_CLOSE,elementRect);
    cv::threshold(pic_g, pic_th, 100, 255, 0);
    cv::Canny(pic_th, pic_canny, 50, 100, 3);

    std::vector<cv::Vec2f> lines;
    cv::HoughLines(pic_canny, lines, 1, CV_PI / 180, 93);

    std::cout << "line number: " << lines.size() << std::endl;
    for (auto & i : lines)
    {
        float rho = i[0], theta = i[1];
        cv::Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(pic, pt1, pt2, cv::Scalar(255, 0, 0), 2);
    }

    cv::imshow("pic_th", pic_canny);
    cv::imshow("dst", pic);
    while (true) {
        if (waitKey(1) == 27)
        {
            break;
        }
    }
    return 0;
}