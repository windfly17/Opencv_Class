#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    cv::Mat canny, pic_g;
    std::vector<vector<Point> > contours;
    std::vector<Vec4i> hierarchy;
    cv::Mat pic = imread(R"(D:\Desktop\Opencv_Class\class_6\1.jpg)", 0);
    threshold(pic,pic,240,255,THRESH_BINARY);
    cv::findContours(pic ,contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    cv::Mat contoursImage(pic.rows,pic.cols,CV_8U,Scalar(0));
    int i= 3;
//    for(int i=0;i<contours.size();i++) {
        //contours[i]代表的是第i个轮廓，contours[i].size()代表的是第i个轮廓上所有的像素点数
        for (int j = 0; j < contours[i].size(); j++) {
            //绘制出contours向量内所有的像素点
            Point P = Point(contours[i][j].x, contours[i][j].y);
            contoursImage.at<uchar>(P) = 255;
        }
//    }
    cv::imshow("pic", contoursImage);
    while (true) {
        if (waitKey(1) == 27)
        {
            break;
        }
    }
    return 0;
}
