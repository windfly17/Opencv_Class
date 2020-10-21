#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

RNG rng(12345);

int main() {
    cv::Mat src = imread("D:\\Desktop\\Opencv_Class\\class_4\\xianluban.jpg");
    cv::Mat src_gray, src_th, src_pz, src_fs, src_open, src_close;
    cv::Mat src_labels, src_stats, src_centroids;
    int num = 0;
    cv::cvtColor(src, src_gray, COLOR_BGR2GRAY);
    cv::threshold(src_gray,src_th,80,255, THRESH_OTSU);
    src_th = ~src_th;
    cv::Mat element0 = cv::getStructuringElement(MORPH_RECT, Size(20, 20));
    cv::Mat element1 = cv::getStructuringElement(MORPH_ELLIPSE, Size(22, 22));

    cv::erode(src_th, src_fs, element0);
    cv::dilate(src_fs, src_open, element1);

    num = cv::connectedComponentsWithStats(src_open, src_labels, src_stats, src_centroids, 8, CV_32S);

    vector<Vec3b> colors(num);
    // background color
    colors[0] = Vec3b(0, 0, 0);
    // object color
    for (int i = 1; i < num; i++) {
        colors[i] = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
    }
    // render result
    cv::Mat dst = Mat::zeros(src.size(), src.type());
    int w = src.cols;
    int h = src.rows;
    for (int row = 0; row < h; row++) {
        for (int col = 0; col < w; col++) {
            int label = src_labels.at<int>(row, col);
            if (label == 0) continue;
            dst.at<Vec3b>(row, col) = colors[label];
        }
    }


    for (int i = 1; i < num; i++) {
        cv::rectangle(src, Point(src_stats.at<int>(i,0), src_stats.at<int>(i,1)), Point(src_stats.at<int>(i,0)+src_stats.at<int>(i,2), src_stats.at<int>(i,1)+src_stats.at<int>(i,3)), Scalar (0,255,0), 1);
    }

    cv::imshow("result", dst);
    cv::imshow("result1", src);
    cout << num - 1 << endl;
    while (true) {
        if (waitKey(1) == 27)
        {
            break;
        }
    }
    return 0;

}