#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap;
    cap.open(0);
    if(!cap.isOpened())
    {
        std::cout << "无法打开" << std::endl;
        return -1;
    }

    double fps = cap.get(CAP_PROP_FPS);
    std::cout << "fps:" << fps << std::endl;
    while(1)
    {
        cv::Mat frame;
        bool rSucess = cap.read(frame);
        if(!rSucess)
        {
            std::cout<< "无法读取" << std::endl;
            break;
        }
        else
        {
            cv::imshow("frame", frame);
        }
        waitKey(30);
    }
}