#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    cv::Mat pic_g, pic_th, pic_pz, pic_close;
    cv::Mat pic = imread(R"(D:\Desktop\Opencv_Class\class_8\2.jpg)");
    cv::cvtColor(pic, pic_g, COLOR_BGR2GRAY);
    cv::threshold(pic_g, pic_th, 180, 255, 0);

    cv::Mat element = cv::getStructuringElement(MORPH_RECT, Size(2, 2));
    cv::dilate(pic_th, pic_pz, element);
    cv::erode(pic_pz, pic_close, element);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    cv::findContours(pic_close, contours, hierarchy, RETR_LIST, CHAIN_APPROX_NONE);
    for (int i = 0; i < contours.size(); ++i){
        double area =contourArea(contours[i]);
        if(2000 <= area && area <= 3000){
            cout << "Area:" << area << " " << i << endl;
            RotatedRect rect = minAreaRect(contours[i]);
            rectangle(pic,rect.boundingRect(),Scalar(0,0,255));
            drawContours(pic, contours, i, Scalar(0,255,0), 1, LINE_AA, vector<Vec4i>(), 0);
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
