#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    cv::Mat srcMat = imread("D:\\Desktop\\Opencv_Class\\test_2\\sunpower.jpg");
    float histgram_R[256];
    float histgram_G[256];
    float histgram_B[256];
    int height = srcMat.rows;
    int width = srcMat.cols;
    int B,G,R;
    for (int i = 0; i < 256; i++) {
        histgram_R[i]=0;
        histgram_G[i]=0;
        histgram_B[i]=0;
    }
    for (int j = 0;j < height;j++) {
        for (int i = 0; i < width; i++) {
            B = srcMat.at<Vec3b>(j,i)[0];
            G = srcMat.at<Vec3b>(j,i)[1];
            R = srcMat.at<Vec3b>(j,i)[2];
            histgram_B[B]++;
            histgram_G[G]++;
            histgram_R[R]++;
        }
    }
    std::cout<< histgram_B[10] <<std::endl;
    return 0;
}