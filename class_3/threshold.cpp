#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int block_size=15;

void blocksize(int block_size1, void* ){
    if(block_size1<3)
        block_size = 3;
    else if(block_size1%2)
        block_size = block_size1;
    else
        block_size = block_size1+1;
}

int main() {
    VideoCapture cap(0, CAP_DSHOW);

    int block_size_min = 15;
    int block_size_max = 80;
    double scale=1;
    while(true) {
        cv::Mat frame, thresMat, thresMat_adapt, rFrame_G;

        cap >> frame;

        Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale);
        cv::Mat rFrame = Mat(ResImgSiz, frame.type());
        cv::resize(frame, rFrame, ResImgSiz, INTER_LINEAR);
        cv::Mat showMat = Mat::zeros(Size(rFrame.cols*2+2, rFrame.rows), CV_8UC1);


        cv::cvtColor(rFrame, rFrame_G, COLOR_BGR2GRAY);
        cv::threshold(rFrame_G,thresMat,150,255, THRESH_BINARY);
        cv::adaptiveThreshold(rFrame_G, thresMat_adapt, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, block_size, 10);

        thresMat.copyTo(showMat(Rect(0,0, rFrame.cols, rFrame.rows)));
        thresMat_adapt.copyTo(showMat(Rect(rFrame.cols+2,0, rFrame.cols, rFrame.rows)));
        cv::rectangle(showMat, Point(rFrame.cols,0), Point(rFrame.cols+2,rFrame.rows), 255, -1);


        cv::imshow("frame", rFrame);
        cv::imshow("result", showMat);
        cv::createTrackbar("block_size","result",&block_size_min,block_size_max,blocksize);

        if (waitKey(1) == 27)
        {
            break;
        }
    }
}