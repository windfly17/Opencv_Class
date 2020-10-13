#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

string window_name = "binaryMat";
int th=30;


void threshod_Mat(int th_1, void* ){
    th = th_1;
}

int main() {
    VideoCapture cap(0, CAP_DSHOW);

    cv::Mat frame, rFrame_G, dst;
    double scale=0.5;
    int th_min = 30;
    int th_max = 255;
    while(true) {

        cap >> frame;

        Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale);
        cv::Mat rFrame = Mat(ResImgSiz, frame.type());
        cv::resize(frame, rFrame, ResImgSiz, INTER_LINEAR);
        cv::cvtColor(rFrame, rFrame_G, COLOR_BGR2GRAY);
        cv::threshold(rFrame_G, dst, th, 255, 0);
        cv::imshow(window_name, dst);
        cv::createTrackbar("threshold", window_name, &th_min, th_max, threshod_Mat);

        if (waitKey(1) == 27)
        {
            break;
        }
    }
}

