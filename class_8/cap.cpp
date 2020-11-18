#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    cv::Mat pic_g, pic_th, pic_pz, pic_hsv, pic_close;
    cv::Mat pic = imread(R"(D:\Desktop\Opencv_Class\class_8\3.jpg)");
    Size ResImgSiz = Size(pic.cols * 0.1, pic.rows * 0.1);
    cv::Mat pic_r = Mat(ResImgSiz, pic.type());
    resize(pic, pic_r, ResImgSiz, INTER_LINEAR);
    cv::cvtColor(pic_r, pic_hsv, COLOR_BGR2HSV);
    cv::Mat pic_detect_0,pic_detect_1,pic_detect;
    Scalar  hsv_min_0 = Scalar(0, 55, 55);
    Scalar  hsv_max_0 = Scalar(5, 255, 255);
    cv::inRange(pic_hsv, hsv_min_0, hsv_max_0, pic_detect_0);
    Scalar  hsv_min_1 = Scalar(156, 55, 55);
    Scalar  hsv_max_1 = Scalar(180, 255, 255);
    cv::inRange(pic_hsv, hsv_min_1, hsv_max_1, pic_detect_1);
    pic_detect = pic_detect_0 + pic_detect_1;

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    cv::findContours(pic_detect, contours, hierarchy, RETR_LIST, CHAIN_APPROX_NONE);
    for (int i = 0; i < contours.size(); ++i){
        double area =contourArea(contours[i]);
        if( 400 <= area){
            cout << "Area:" << area << " " << i << endl;
            Rect rect = boundingRect(contours[i]);//检测外轮廓
            rectangle(pic_r, rect, Scalar(0,0,255), 2);//对外轮廓加矩形框
            drawContours(pic_r, contours, i, Scalar(0,255,0), 1, LINE_AA, vector<Vec4i>(), 0 );
        }
    }


    cv::imshow("Contours", pic_r);
    while (true) {
        if (waitKey(1) == 27)
        {
            break;
        }
    }
    return 0;
}