#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    VideoCapture cap(0, CAP_DSHOW);

    double scale=1;
    //肤色范围
    double i_minH=0;
    double i_maxH=20;

    double i_minS=43;
    double i_maxS=255;

    double i_minV=55;
    double i_maxV=255;
    while(true) {
        cv::Mat frame;
        cv::Mat hsvMat;
        cv::Mat detectMat;

        cap >> frame;
        Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale);
        cv::Mat rFrame = Mat(ResImgSiz, frame.type());
        resize(frame, rFrame, ResImgSiz, INTER_LINEAR);

        cv::cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);

        rFrame.copyTo(detectMat);

        cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

        cv::imshow("whie: in the range", detectMat);
        cv::imshow("frame", rFrame);

        if (waitKey(1) == 27)
        {
            break;
        }
    }
}