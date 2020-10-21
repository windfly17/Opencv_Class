#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

RNG rng(12345);

int main() {
    cv::Mat yb = imread("D:\\Desktop\\Opencv_Class\\class_4\\yingbi.jpg");
    cv::Mat yb_gray, yb_th, yb_fs;
    cv::Mat yb_labels, yb_stats, yb_centroids;
    int num = 0;
    cv::cvtColor(yb,yb_gray,COLOR_BGR2GRAY);
    cv::threshold(yb_gray,yb_th,80,255, THRESH_BINARY);
    cv::Mat element = cv::getStructuringElement(MORPH_RECT, Size(3, 3));
    cv::erode(yb_th, yb_fs, element);

    num = cv::connectedComponentsWithStats(yb_fs, yb_labels, yb_stats, yb_centroids, 8, CV_32S);

    vector<Vec3b> colors(num);
    // background color
    colors[0] = Vec3b(0, 0, 0);
    // object color
    for (int i = 1; i < num; i++) {
        colors[i] = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
    }
    // render result
    cv::Mat dst = Mat::zeros(yb.size(), CV_8UC3);
    int w = yb.cols;
    int h = yb.rows;
    for (int row = 0; row < h; row++) {
        for (int col = 0; col < w; col++) {
            int label = yb_labels.at<int>(row, col);
            if (label == 0) continue;
            dst.at<Vec3b>(row, col) = colors[label];
        }
    }

    for (int i = 1; i < num; i++) {
        cv::rectangle(yb, Point(yb_stats.at<int>(i,0), yb_stats.at<int>(i,1)), Point(yb_stats.at<int>(i,0)+yb_stats.at<int>(i,2), yb_stats.at<int>(i,1)+yb_stats.at<int>(i,3)), Scalar (0,255,0), 1);
    }

    cv::imshow("result0", dst);
    cv::imshow("result", yb);
    cout << num -1  << endl;
    while (true) {
        if (waitKey(1) == 27)
        {
            break;
        }
    }
    return 0;
}