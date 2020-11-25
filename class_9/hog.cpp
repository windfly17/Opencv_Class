#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void HOG(Mat& img, float * ref_hist);

int main()
{
    cv::Mat src0 = imread(R"(D:\Desktop\Opencv_Class\class_9\img1.jpg)");
    cv::Mat src1 = imread(R"(D:\Desktop\Opencv_Class\class_9\img2.jpg)");
    cv::Mat hogTemplate = imread(R"(D:\Desktop\Opencv_Class\class_9\hogTemplate.jpg)");
    int bins = 1000000;
    auto * ref_hist = new float[bins];
    memset(ref_hist, 0, sizeof(float)*bins);

    auto * ref_hist1 = new float[bins];
    memset(ref_hist1, 0, sizeof(float)*bins);

    auto * ref_hist2 = new float[bins];
    memset(ref_hist2, 0, sizeof(float)*bins);

    HOG(hogTemplate,ref_hist);
    HOG(src0, ref_hist1);
    HOG(src1, ref_hist2);


    float sum1 = normL2Sqr(ref_hist, ref_hist1, bins);
    sum1 = sqrt(sum1);
    cout << sum1 << endl;
    
    float sum2 = normL2Sqr(ref_hist, ref_hist2, bins);
    sum2 = sqrt(sum2);
    cout  << sum2 << endl;

    if (sum1 <= sum2) {
        cout << "img1与原图更相似"<< endl;
    }
    if (sum1 > sum2) {
        cout << "img2与原图更相似" << endl;
    }

    delete[] ref_hist;
    delete[] ref_hist1;
    delete[] ref_hist2;

    cv::waitKey();
    return 0;
}

void HOG(Mat& img, float * ref_hist){
    int cellSize = 16;
    int nAngle = 8;
    cv::Rect_<int> roi;
    roi.width = cellSize;
    roi.height = cellSize;
    float binAngle = 360 / nAngle;
    cv::Mat img_g;
    cvtColor(img, img_g, COLOR_BGR2GRAY);
    int nX = img.cols / cellSize;
    int nY = img.rows / cellSize;

    Mat gx, gy;
    Mat mag, angle;
    Sobel(img_g, gx, CV_32F, 1, 0, 1);
    Sobel(img_g, gy, CV_32F, 0, 1, 1);
    cartToPolar(gx, gy, mag, angle, true);

    for (int i =0; i < nY; i++){
        for (int j=0; j < nX; j++){
            cv::Mat roiMat,roiMag,roiAgl;
            roi.x = j * cellSize;
            roi.y = i * cellSize;
            roiMat = img_g(roi);
            roiMag = mag(roi);
            roiAgl = angle(roi);
            int head = (i*nX + j)*nAngle;
            for (int n = 0; n < roiMat.rows; n++){
                for (int m = 0; m < roiMat.cols; m++){
                    int pos = (int) (roiAgl.at<float>(n,m) / binAngle);
                    ref_hist[head+pos] += roiMag.at<float>(n,m);
                }
            }
        }
    }

}