#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void histgram(Mat src, float histgram_R[256], Scalar color)
{
    for (int i = 0; i < 255; i++) {
        Point p1(i*2, 300-histgram_R[i]*1700);
        Point p2(i*2+2, 300-histgram_R[i+1]*1700);
        line(src,p1,p2,color,2);
    }
}

int main()
{
    Mat img0 = Mat::zeros(Size(560,300), CV_8UC3);
    img0.setTo(0);
    Mat img1 = Mat::zeros(Size(560,300), CV_8UC3);
    img1.setTo(0);
    Mat img2 = Mat::zeros(Size(560,300), CV_8UC3);
    img2.setTo(0);
    cv::Mat srcMat = imread("D:\\Desktop\\Opencv_Class\\test_2\\1.png");
    float histgram_R[256],histgram_G[256],histgram_B[256];
    int height = srcMat.rows;
    int width = srcMat.cols;
    int pix = height*width;
    int B,G,R;
    vector<Mat>bgr_planes;
    split(srcMat, bgr_planes);
    for (int i = 0; i < 256; i++) {
        histgram_R[i]=0;
        histgram_G[i]=0;
        histgram_B[i]=0;
    }

    for (int j = 0;j < height;j++) {
        for (int i = 0; i < width; i++) {
            B = bgr_planes[0].at<uchar>(j,i);
            G = bgr_planes[1].at<uchar>(j,i);
            R = bgr_planes[2].at<uchar>(j,i);
            histgram_B[B]++;
            histgram_G[G]++;
            histgram_R[R]++;
        }
    }
    for (int i = 0; i < 256; i++) {
        histgram_R[i]=histgram_R[i]/pix;
        histgram_G[i]=histgram_G[i]/pix;
        histgram_B[i]=histgram_B[i]/pix;
    }

    histgram(img0,histgram_B,Scalar(255,0,0));
    histgram(img0,histgram_G,Scalar(0,255,0));
    histgram(img0,histgram_R,Scalar(0,0,255));

    imshow("B",img0);
//    imshow("G",img1);
//    imshow("R",img2);
    waitKey(0);
//    std::cout<< histgram_B[0] <<std::endl;
    return 0;
}