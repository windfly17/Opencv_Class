#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    VideoCapture cap(0, CAP_DSHOW);
    cv::Mat frame, frame_G, result;
    int ksize = 5;
    while (true){
        cap >> frame;

        cv::cvtColor(frame, frame_G, COLOR_BGR2GRAY);
        cv::medianBlur(frame_G, result, ksize);
        cv::imshow("q", frame_G);
        cv::imshow("result", result);
        if (waitKey(1) == 27)
        {
            break;
        }
    }
}