#include "funtions.h"


std::vector<Point>  mousePoints;
Point points;
/******************************************************************************************************************************
														傅里叶变换demo（主函数）
*****************************************************************************************************************************/


/***************************************鼠标响应函数*******************************************/
void on_mouse(int EVENT, int x, int y, int flags, void* userdata)
{

	Mat hh;
	hh = *(Mat*)userdata;
	Point p(x, y);
	switch (EVENT)
	{
	case EVENT_LBUTTONDOWN:
	{
		points.x = x;
		points.y = y;
		mousePoints.push_back(points);
		circle(hh, points, 4, Scalar(255, 255, 255), -1);
		imshow("mouseCallback", hh);
	}
	break;
	}

}


int selectPolygon(cv::Mat srcMat, cv::Mat &dstMat_0, cv::Mat &dstMat_1)
{
	
	vector<vector<Point>> contours;
	cv::Mat selectMat;

	cv::Mat m_0 = cv::Mat::zeros(srcMat.size(), CV_32F);
    cv::Mat m_1 = cv::Mat::zeros(srcMat.size(), CV_32F);

	m_1 = 1;

	if (!srcMat.empty()) {
		srcMat.copyTo(selectMat);
		srcMat.copyTo(dstMat_0);
        srcMat.copyTo(dstMat_1);
	}
	else {
		std::cout << "failed to read image!:" << std::endl;
		return -1;
	}

	namedWindow("mouseCallback");
	imshow("mouseCallback", selectMat);
	setMouseCallback("mouseCallback", on_mouse, &selectMat);
	waitKey(0);
	destroyAllWindows();
	//计算roi
	contours.push_back(mousePoints);
	if (contours[0].size() < 3) {
		std::cout << "failed to read image!:" << std::endl;
		return -1;
	}

    drawContours(m_0, contours, 0, Scalar(1), -1);
	drawContours(m_1, contours, 0, Scalar(0), -1);
	m_0.copyTo(dstMat_0);
    m_1.copyTo(dstMat_1);

	return 0;
}


//int mag(cv::Mat src, cv::Mat &mag, cv::Mat &ph, cv::Mat &tmp_0, double &maxVal){
//    mag += Scalar::all(1);//对幅值加1
//    //计算出的幅值一般很大，达到10^4,通常没有办法在图像中显示出来，需要对其进行log求解。
//    log(mag, mag);
//
//    //取矩阵中的最大值，便于后续还原时去归一化
//    minMaxLoc(mag, 0, &maxVal, 0, 0);
//
//    //修剪频谱,如果图像的行或者列是奇数的话,那其频谱是不对称的,因此要修剪
//    mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));
//    ph = ph(Rect(0, 0, mag.cols & -2, mag.rows & -2));
//
//    Mat _magI = mag.clone();
//    //将幅度归一化到可显示范围。
//    normalize(_magI, _magI, 0, 1, NORM_MINMAX);
//    //imshow("before rearrange", _magI);
//
//    //显示规则频谱图
//    static int cx = mag.cols / 2;
//    static int cy = mag.rows / 2;
//
//    //这里是以中心为标准，把mag图像分成四部分
//    Mat tmp;
//    Mat q0(mag, Rect(0, 0, cx, cy));
//    Mat q1(mag, Rect(cx, 0, cx, cy));
//    Mat q2(mag, Rect(0, cy, cx, cy));
//    Mat q3(mag, Rect(cx, cy, cx, cy));
//    q0.copyTo(tmp);
//    q3.copyTo(q0);
//    tmp.copyTo(q3);
//    q1.copyTo(tmp);
//    q2.copyTo(q1);
//    tmp.copyTo(q2);
//
//    normalize(mag, mag, 0, 1, NORM_MINMAX);
//    return 0;
//}


