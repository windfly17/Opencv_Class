#include <opencv2/opencv.hpp>
#include <iostream>
#include <list>

class iterator;

using namespace cv;
using namespace std;

int main() {
    cv::Mat canny, pic_th, pic_g, corner, norm_dst, dst;
    std::vector<vector<Point> > contours;
    std::vector<Vec4i> hierarchy;
    list<Point2f> a;
    cv::Mat pic = imread(R"(D:\Desktop\Opencv_Class\class_6\1.jpg)");
    cv::cvtColor(pic, pic_g, COLOR_BGR2GRAY);
    cv::threshold(pic_g,pic_th,240,255,THRESH_BINARY);
    pic_th = ~pic_th;
    cv::findContours(pic_th ,contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    cv::Mat contoursImage(pic.rows,pic.cols,CV_8U,Scalar(0));
    for (int j = 0; j < contours[0].size(); j++) {
        //绘制出contours向量内所有的素点
        Point P = Point(contours[0][j].x, contours[0][j].y);
        contoursImage.at<uchar>(P) = 255;
    }
    cornerHarris(contoursImage, corner, 2, 3, 0.04, BORDER_DEFAULT);
    normalize(corner, norm_dst, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(norm_dst, norm_dst);
    Mat resultImg = pic.clone();

    for (int row = 0; row < resultImg.rows; row++)
    {
        uchar* currentRow = norm_dst.ptr(row);
        for (int col = 0; col < resultImg.cols; col++)
        {
            int value = (int)*currentRow;
            if (value > 130)
            {
                a.emplace_back(col, row);
//                circle(resultImg, Point (col,row), 2, Scalar(0, 0, 255), 2, 8,0);
            }
            currentRow++;

        }
    }
    Point2f a0 (a.back());
    a.pop_back();
    Point2f a1 (a.back());
    a.pop_back();
    Point2f a2 (a.back());
    cv::Point2f src_pt[] = {
            a0,a1,a2
    };
    cv::Point2f dst_pt[] = {
            cv::Point2f(pic.cols, pic.rows),
            cv::Point2f(0, pic.rows),
            cv::Point2f(pic.cols, 0)
    };
    const cv::Mat affine_matrix = cv::getAffineTransform(src_pt, dst_pt);

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
