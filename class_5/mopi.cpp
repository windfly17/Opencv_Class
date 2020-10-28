#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    VideoCapture cap(0, CAP_DSHOW);
    cv::Mat frame,hsvMat;
    double scale=1;

    //肤色范围
    Scalar  hsv_min = Scalar(0, 30, 60, 0);
    Scalar  hsv_max = Scalar(20, 150, 255, 0);

    while (true){
        cap >> frame;

        cv:Mat skin, skin_1, skin_blur, result_1, result, detectMat, detectMat_fs;
        Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale);
        cv::Mat rframe = Mat(ResImgSiz, frame.type());
        cv::resize(frame, rframe, ResImgSiz, INTER_LINEAR);
        cv::cvtColor(rframe, hsvMat, COLOR_BGR2HSV);

        cv::inRange(hsvMat, hsv_min, hsv_max, detectMat);
        cv::Mat element = cv::getStructuringElement(MORPH_RECT, Size(2, 2));
        cv::erode(detectMat, detectMat_fs, element);
        rframe.copyTo(skin, detectMat_fs);
        rframe.copyTo(skin_1, ~detectMat_fs);
        cv::medianBlur(skin, skin_blur, 5);
        result = skin_blur + skin_1;
        cv::imshow("q", result);
        if (waitKey(1) == 27)
        {
            break;
        }
    }
}