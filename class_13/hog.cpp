#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void HOG(Mat& img, float * ref_hist, int cellSize);
void find(Mat& src, Mat& src_roi, int cellSize, float magnification);

int main()
{
    int cellSize = 16;
    float magnification = 0.2;
    cv::Mat tempMat, src_roi;
    Rect2d r;
    Mat src = imread("..//1_0.jpg");
//    Mat src_roi = imread("..//1_0_roi.jpg");
    r = cv::selectROI(src, true);
    tempMat = src(r);
    tempMat.copyTo(src_roi);
    destroyAllWindows();
    find(src, src_roi, cellSize, magnification);
    return 0;
}

void find(Mat& src, Mat& src_roi, int cellSize, float magnification){
    int bins = 1000000;
    Mat src_resize, src_roi_resize;
    resize(src, src_resize, Size (src.cols*magnification, src.rows*magnification));
    resize(src_roi, src_roi_resize, Size (src_roi.cols*magnification, src_roi.rows*magnification));
    cv::Mat res = cv::Mat::zeros(src_resize.rows - src_roi_resize.rows, src_resize.cols - src_roi_resize.cols,CV_64F);
    cv::Mat dst,src_copy;
    cv::Rect_<int> roi;
    roi.width = src_roi_resize.cols;
    roi.height = src_roi_resize.rows;
    float * ref_hist1 = new float[bins];
    memset(ref_hist1, 0, sizeof(float)*bins);
    HOG(src_roi_resize, ref_hist1, cellSize);
    for(int y = 0; y < src_resize.rows - roi.height; y++){
        for(int x =0; x < src_resize.cols - roi.width; x++){
            roi.x = x;
            roi.y = y;
            Mat src_0 = src_resize(roi);
            float * ref_hist = new float[bins];
            memset(ref_hist, 0, sizeof(float)*bins);
            HOG(src_0, ref_hist, cellSize);
            float sum1 = normL2Sqr(ref_hist, ref_hist1, bins);
            delete[] ref_hist;
            res.at<double>(y,x) = sqrt(sum1);
        }
    }
    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(res, &minVal, &maxVal ,&minLoc, &maxLoc, Mat());
    Point minLoc_resize = Point (minLoc.x / magnification , minLoc.y / magnification);
    Point minLoc_end = Point(minLoc_resize.x + src_roi.cols, minLoc_resize.y + src_roi.rows);
    rectangle(src, minLoc_resize, minLoc_end, Scalar(0, 0, 255), 1, LINE_AA);
    imshow("roi", src_roi);
    imshow("res", src);
    waitKey();
}

void HOG(Mat& img, float * ref_hist, int cellSize){
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