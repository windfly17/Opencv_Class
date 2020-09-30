#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace cv;

int hist_w = 510;
int hist_h = 300;

void histgram(Mat src, float histgram_R[256], Scalar color)
{
    for (int i = 0; i < 255; i++) {
        Point p1(i*2, hist_h-histgram_R[i]*1700);
        Point p2(i*2+2, hist_h-histgram_R[i+1]*1700);
        line(src,p1,p2,color,1);
    }
}

int main()
{
    cv::Mat img_show = Mat::zeros(Size(hist_w*2+4,hist_h*2+4), CV_8UC3);
    cv::Mat img = Mat::zeros(Size(hist_w,hist_h), CV_8UC3);
    cv::Mat img_R,img_G,img_B;
    img.setTo(0);
    img.copyTo(img_R);
    img.copyTo(img_G);
    img.copyTo(img_B);
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

    histgram(img,histgram_B,Scalar(255,0,0));
    histgram(img,histgram_G,Scalar(0,255,0));
    histgram(img,histgram_R,Scalar(0,0,255));

    histgram(img_B,histgram_B,Scalar(255,0,0));
    histgram(img_G,histgram_G,Scalar(0,255,0));
    histgram(img_R,histgram_R,Scalar(0,0,255));

    img.copyTo(img_show(Rect(0,0,hist_w,hist_h)));
    img_R.copyTo(img_show(Rect(hist_w+4,0,hist_w,hist_h)));
    img_G.copyTo(img_show(Rect(0,hist_h+4,hist_w,hist_h)));
    img_B.copyTo(img_show(Rect(hist_w+4,hist_h+4,hist_w,hist_h)));

    rectangle(img_show,Point(hist_w+1,0),Point(hist_w+3,hist_h*2+4),Scalar(200, 200, 200),-1);
    rectangle(img_show,Point(0,hist_h+1),Point(hist_w*2+4,hist_h+3),Scalar(200, 200, 200),-1);

    imshow("RGB",img_show);
//    imshow("B",img_B);
//    imshow("G",img_G);
//    imshow("R",img_R);
    while (true) {
        if (waitKey(1) == 27)
        {
            break;
        }
    }
    return 0;
}