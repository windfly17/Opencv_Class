#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int gamma_10 = 50;
double scale = 1;
cv::Mat src = imread("../1.jpg");
cv::Mat dst, dst_0;
void gammaCorrection(const Mat& src, float gamma, Mat &dst);
void on_trackbar(int gamma_10, void *);

int main() {
    cv::resize(src, src, Size(static_cast<int>(src.cols * scale), static_cast<int>(src.rows * scale)));
    dst = Mat::zeros(Size(src.cols, src.rows*2), CV_8UC3);
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

void gammaCorrection(const Mat& src, float gamma, Mat &dst){
    float Lut[256];
    for( int i=0;i<256;i++){
        float f=(float)( i +0.5)/256;//归一化
        f= pow(f, 1 / gamma);//预补偿
        Lut[i]=(float)(f*256-0.5);//反归一化
    }

    dst = src.clone();
    MatIterator_<Vec3b> it, end;
    for( it = dst.begin<Vec3b>(), end = dst.end<Vec3b>(); it != end; it++ )
    {
        //(*it)[0] = pow((float)(((*it)[0])/255.0), fGamma) * 255.0;
        //(*it)[1] = pow((float)(((*it)[1])/255.0), fGamma) * 255.0;
        //(*it)[2] = pow((float)(((*it)[2])/255.0), fGamma) * 255.0;
        (*it)[0] = Lut[((*it)[0])];
        (*it)[1] = Lut[((*it)[1])];
        (*it)[2] = Lut[((*it)[2])];
    }
}

void on_trackbar(int gamma_0, void *)
{
    float gamma = (float)gamma_0/10;
    gammaCorrection(src, gamma, dst_0);
    dst_0.copyTo(dst(Rect (0, 0, src.cols, src.rows)));
    imshow("dst", dst);
}
