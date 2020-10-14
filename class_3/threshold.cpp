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

Mat convertTo3Channels(const Mat& binImg)
{
    Mat three_channel = Mat::zeros(binImg.rows,binImg.cols,CV_8UC3);
    vector<Mat> channels;
    for (int i=0;i<3;i++)
    {
        channels.push_back(binImg);
    }
    merge(channels,three_channel);
    return three_channel;
}


int main() {
    VideoCapture cap(0, CAP_DSHOW);

    int block_size_min = 15;
    int block_size_max = 80;
    double scale=0.5;
    while(true) {
        cv::Mat frame, thresMat, thresMat_adapt, rFrame_G;

        cap >> frame;

        Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale);
        cv::Mat rFrame = Mat(ResImgSiz, frame.type());
        cv::resize(frame, rFrame, ResImgSiz, INTER_LINEAR);
        cv::Mat showMat = Mat::zeros(Size(rFrame.cols*3+4, rFrame.rows), CV_8UC3);


        cv::cvtColor(rFrame, rFrame_G, COLOR_BGR2GRAY);
        cv::threshold(rFrame_G,thresMat,150,255, THRESH_BINARY);
        cv::adaptiveThreshold(rFrame_G, thresMat_adapt, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, block_size, 10);

        thresMat  = convertTo3Channels(thresMat);
        thresMat_adapt = convertTo3Channels(thresMat_adapt);
        rFrame.copyTo(showMat(Rect(0,0, rFrame.cols, rFrame.rows)));
        thresMat.copyTo(showMat(Rect(rFrame.cols+2,0, rFrame.cols, rFrame.rows)));
        thresMat_adapt.copyTo(showMat(Rect(rFrame.cols*2+2,0, rFrame.cols, rFrame.rows)));
        cv::rectangle(showMat, Point(rFrame.cols,0), Point(rFrame.cols+2,rFrame.rows), (0,255,255), -1);
        cv::rectangle(showMat, Point(rFrame.cols*2,0), Point(rFrame.cols*2+2,rFrame.rows), (0,255,255), -1);


//        cv::imshow("frame", rFrame);
        cv::imshow("result", showMat);
        cv::createTrackbar("block_size","result",&block_size_min,block_size_max,blocksize);

        if (waitKey(1) == 27)
        {
            break;
        }
    }
}