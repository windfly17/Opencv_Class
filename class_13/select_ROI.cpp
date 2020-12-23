#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(){
    VideoCapture capVideo(0);
    cv::Mat src, tempMat, refMat;
    Rect2d r;
    int cnt = 0;
    int wait_frame = 20;
    while(true){
        capVideo >> src;
        if(cnt == wait_frame){
            r = cv::selectROI(src, true);
            tempMat = src(r);
            tempMat.copyTo(refMat);
            destroyAllWindows();
        }
        cnt++;
        cv::imshow("src", src);
        if(cnt == wait_frame + 1){
            cv::imshow("refMat", refMat);
        }
        if (waitKey(1) == 27){
            break;
        }
    }
    return 0;
}