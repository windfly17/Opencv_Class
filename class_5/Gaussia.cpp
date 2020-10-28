#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    VideoCapture cap(0, CAP_DSHOW);
    cv::Mat frame, frame_G, result;
    while (true){
        cap >> frame;

        cv::cvtColor(frame, frame_G, COLOR_BGR2GRAY);
        cv::GaussianBlur(frame_G, result, Size(5,5), 0,0, BORDER_DEFAULT);
        cv::imshow("q", frame_G);
        cv::imshow("result", result);
        if (waitKey(1) == 27)
        {
            break;
        }
    }
}