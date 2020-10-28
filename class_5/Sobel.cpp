#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    VideoCapture cap(0, CAP_DSHOW);
    cv::Mat frame, result_x, result_y, result;
    double scale=0.5;
    while (true){
        cap >> frame;

        Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale);
        cv::Mat rframe = Mat(ResImgSiz, frame.type());
        cv::resize(frame, rframe, ResImgSiz, INTER_LINEAR);
        cv::Sobel(rframe, result_x, CV_8U, 1, 0, 3);
        cv::Sobel(rframe, result_y, CV_8U, 0, 1, 3);
        cv::addWeighted(result_x, 0.5, result_y, 0.5, 0, result);
        cv::imshow("q", rframe);
        cv::imshow("result", result);
        if (waitKey(1) == 27)
        {
            break;
        }
    }
}