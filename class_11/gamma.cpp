#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int gamma_10 = 50;
double scale = 1;
cv::Mat_<uchar> src = imread("../1.jpg", 0);
cv::Mat_<uchar> dst;
void gammaCorrection(const Mat& src, float gamma, Mat_<uchar> &dst);
void on_trackbar(int gamma_10, void *);

int main() {
    cv::resize(src, src, Size(static_cast<int>(src.cols * scale), static_cast<int>(src.rows * scale)));
    dst = Mat::zeros(Size(src.cols, src.rows*2), CV_8UC1);
    src.copyTo(dst(Rect (0, src.rows, src.cols, src.rows)));
    on_trackbar(50, nullptr);
    cv::imshow("dst", dst);
    cv::createTrackbar("Gamma", "dst", &gamma_10, 200, on_trackbar);

    while (true) {
        if (waitKey(1) == 27)
        {
            break;
        }
    }
    return 0;
}

void gammaCorrection(const Mat& src, float gamma, Mat_<uchar> &dst){
    float Lut[256];
    for( int i=0;i<256;i++){
        float f=(float)( i +0.5)/256;//归一化
        f= pow(f, 1 / gamma);//预补偿
        Lut[i]=(float)(f*256-0.5);//反归一化
    }
    cv::Mat_<uchar> src_normalized;
    cv::resize(src, src_normalized, Size(src.cols, src.rows));
    for (int x=0; x < src.rows; x++ ){
        for (int y = 0; y < src.cols; y++){
            dst(x,y) = static_cast<uchar>(Lut[src_normalized(x, y)]);
        }
    }
}

void on_trackbar(int gamma_0, void *)
{
    float gamma = (float)gamma_0/10;
    gammaCorrection(src, gamma, dst);
    imshow("dst", dst);
}
