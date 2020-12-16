#include "opencv2/opencv.hpp"

using namespace cv;

int main() {
    VideoCapture cap(0);
    cv::Mat src, src_bg, frame, frame_G, pre, cur, cur_th, res, mask;
    int n=0;
    while (true) {
        cap >> frame;
        cv::cvtColor(frame, frame_G, COLOR_BGR2GRAY);
        if (n < 10){
            n++;
            frame_G.copyTo(pre);
        }
        else {
            absdiff(frame_G, pre, cur);
            cv::threshold(cur, cur_th, 70, 255, THRESH_BINARY);
            res = cv::Mat(frame.rows, frame.cols, CV_8UC3, Scalar(255,255,255));
            frame.copyTo(res, cur_th);

            cv::imshow("cur_th", cur_th);
            cv::imshow("frame", frame);
            cv::imshow("res", res);
        }
        if (waitKey(1) == 27) {
            break;
        }
    }
}
