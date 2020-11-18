#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    cv::Mat src, dst, pic_g, pic_th, pic_pz, pic_fs, pic_open, pic_close;
    cv::Mat pic = imread(R"(D:\Desktop\Opencv_Class\class_8\1.jpg)");
    cv::cvtColor(pic, pic_g, COLOR_BGR2GRAY);
    cv::threshold(~pic_g, pic_th, 150, 255, 0);

    cv::Mat element = cv::getStructuringElement(MORPH_RECT, Size(2, 2));
    cv::dilate(pic_th, pic_pz, element);
    cv::erode(pic_pz, pic_close, element);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    cv::findContours(pic_close, contours, hierarchy, RETR_LIST, CHAIN_APPROX_NONE);
    for (int i = 0; i < contours.size(); ++i){
        double area =contourArea(contours[i]);
        double factor = (area * 4 * CV_PI) /(pow(arcLength(contours[i], true), 2));
        if(factor >= 0.5 && area >= 300){
            cout << "factor:" << factor << " " << i << endl;  //计算出圆形度factor
            cout << "Area:" << area << endl;
            drawContours(pic, contours, i, Scalar(0,255,0), -1, LINE_AA, vector<Vec4i>(), 0);
        }
    }

    cv::imshow("Contours", pic);
    while (true) {
        if (waitKey(1) == 27)
        {
            break;
        }
    }
    return 0;
}


//void center_Points(vector<Point> &contours) {
//    double factor = (contourArea(contours) * 4 * CV_PI) /(pow(arcLength(contours, true), 2));
//    cout << "factor:" << factor << endl;  //计算出圆形度factor
//}