#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

void gaussianThreshold(cv::Mat srcMat,cv::Mat srcMat_3, cv::Mat meanMat, cv::Mat varMat, float weight, cv::Mat& dstMat);
void calcGaussianBackground(std::vector<cv::Mat> srcMats, cv::Mat& meanMat, cv::Mat& varMat);


int main()
{
    VideoCapture capVideo(0);
    //�������㱳��ģ�͵�ͼ��
    std::vector<cv::Mat> srcMats;
    //��������
    int nBg = 100;		//������������ģ�͵�����
    float wVar = 2;		//����Ȩ��

    int cnt = 0;
    cv::Mat frame, src;
    cv::Mat meanMat;
    cv::Mat varMat;
    cv::Mat dstMat;

    while (true)
    {
        capVideo >> frame;
        capVideo >> src;
        cvtColor(frame, frame, COLOR_BGR2GRAY);
        //ǰ���nBg֡�����㱳��
        if (cnt < nBg) {
            srcMats.push_back(frame);
            if (cnt == 0) {
                std::cout << "reading frame " << std::endl;
            }        }
        else if (cnt == nBg) {
            //����ģ��
            meanMat.create(frame.size(), CV_8UC1);
            varMat.create(frame.size(), CV_32FC1);
            std::cout << "calculating background models" << std::endl;
            calcGaussianBackground(srcMats, meanMat, varMat);
        }
        else {
            //�������
            dstMat.create(frame.size(), CV_8UC3);
            gaussianThreshold(frame, src, meanMat, varMat, wVar, dstMat);
            imshow("result", dstMat);
            imshow("frame", src);
            if (waitKey(1) == 27) {
                break;
            }
        }
        cnt++;
    }

    return 0;
}

void gaussianThreshold(cv::Mat srcMat,cv::Mat srcMat_3, cv::Mat meanMat, cv::Mat varMat, float weight, cv::Mat& dstMat)
{
    int srcI, meanI;
    int dstI;
    int rows = srcMat.rows;
    int cols = srcMat.cols;

    for (int h = 0; h < rows; h++)
    {
        for (int w = 0; w < cols; w++)
        {
            srcI = srcMat.at<uchar>(h, w);
            meanI = meanMat.at<uchar>(h, w);
            int dif = abs(srcI - meanI);
            int th = weight * varMat.at<float>(h, w);
            if (dif > th) {
                dstMat.at<Vec3b>(h, w)[0] = srcMat_3.at<Vec3b>(h, w)[0];
                dstMat.at<Vec3b>(h, w)[1] = srcMat_3.at<Vec3b>(h, w)[1];
                dstMat.at<Vec3b>(h, w)[2] = srcMat_3.at<Vec3b>(h, w)[2];
            }
            else {
                dstMat.at<Vec3b>(h, w)[0] = 0;
                dstMat.at<Vec3b>(h, w)[1] = 0;
                dstMat.at<Vec3b>(h, w)[2] = 0;
            }
        }
    }
}


void calcGaussianBackground(std::vector<cv::Mat> srcMats, cv::Mat& meanMat, cv::Mat& varMat)
{    int rows = srcMats[0].rows;
    int cols = srcMats[0].cols;
    for (int h = 0; h < rows; h++)
    {
        for (int w = 0; w < cols; w++)
        {
            int sum = 0;
            float var = 0;
            //���ֵ
            for (int i = 0; i < srcMats.size(); i++) {
                sum += srcMats[i].at<uchar>(h, w);
            }
            meanMat.at<uchar>(h, w) = sum / srcMats.size();
            //�󷽲�
            for (int i = 0; i < srcMats.size(); i++) {
                var += pow((srcMats[i].at<uchar>(h, w) - meanMat.at<uchar>(h, w)), 2);
            }
            varMat.at<float>(h, w) = var / srcMats.size();
        }
    }
}