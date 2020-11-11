#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    cv::Mat pic = imread(R"(D:\Desktop\Opencv_Class\class_7\2.jpg)");
    if (pic.empty()) return -1;
    cv::Mat pic_g, pic_th, pic_canny;
    cv::cvtColor(pic, pic_g,COLOR_BGR2GRAY);
    cv::threshold(pic_g, pic_th, 100, 255, 0);
    cv::Canny(pic_th, pic_canny, 50, 120, 3);

    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(pic_canny, lines, 1, CV_PI / 180, 43, 20, 15);

    std::cout << "line number: " << lines.size() << std::endl;
    for (auto & i : lines){
        int x1 = i[0];
        int y1 = i[1];
        int x2 = i[2];
        int y2 = i[3];
        line(pic, Point(x1,y1), Point(x2,y2), cv::Scalar(255, 255, 0), 2);
    }
    for (int i=0;i<lines.size();i++){
        cout << lines[i] << endl;
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