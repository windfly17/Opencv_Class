#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat convertTo3Channels(const Mat& binImg)
{
    Mat three_channel = Mat::zeros(binImg.rows,binImg.cols,CV_8UC3);
    std::vector<Mat> channels;
    for (int i=0;i<3;i++)
    {
        channels.push_back(binImg);
    }
    merge(channels,three_channel);
    return three_channel;
}


int main() {
    cv::Mat yb = imread("D:\\Desktop\\Opencv_Class\\class_4\\yingbi.jpg");
    cv::Mat yb_gray, yb_th, yb_th_a, yb_fs, yb_pz, yb_close, yb_open;
    cv::cvtColor(yb,yb_gray,COLOR_BGR2GRAY);
    cv::threshold(yb_gray,yb_th,80,255, THRESH_BINARY);
    cv::adaptiveThreshold(yb_gray, yb_th_a, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 15, 10);
    cv::Mat element = cv::getStructuringElement(MORPH_RECT, Size(3, 3));
    cv::dilate(yb_th, yb_pz, element);
    cv::erode(yb_th, yb_fs, element);
    cv::dilate(yb_fs, yb_open, element);
    cv::erode(yb_pz, yb_close, element);

    yb_th = convertTo3Channels(yb_th);
    yb_th_a = convertTo3Channels(yb_th_a);
    yb_pz = convertTo3Channels(yb_pz);
    yb_fs = convertTo3Channels(yb_fs);
    yb_open = convertTo3Channels(yb_open);
    yb_close = convertTo3Channels(yb_close);

    cv::Mat src1 = Mat::zeros(Size(yb.cols*2+2, yb.rows), CV_8UC3);
    cv::Mat src2 = Mat::zeros(Size(yb.cols*2+2, yb.rows), CV_8UC3);
    cv::Mat src3 = Mat::zeros(Size(yb.cols*2+2, yb.rows), CV_8UC3);

    yb_th.copyTo(src1(Rect(0, 0, yb.cols, yb.rows)));
    yb_th_a.copyTo(src1(Rect(yb.cols+2, 0, yb.cols, yb.rows)));
    yb_fs.copyTo(src2(Rect(0, 0, yb.cols, yb.rows)));
    yb_pz.copyTo(src2(Rect(yb.cols+2, 0, yb.cols, yb.rows)));
    yb_open.copyTo(src3(Rect(0, 0, yb.cols, yb.rows)));
    yb_close.copyTo(src3(Rect(yb.cols+2, 0, yb.cols, yb.rows)));

    cv::imshow("threshold", src1);
    cv::imshow("erode_dilate", src2);
    cv::imshow("open_close", src3);
    while (true) {
        if (waitKey(1) == 27)
        {
            break;
        }
    }
    return 0;

}
