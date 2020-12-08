#include <opencv2/opencv.hpp>
//#include "funtions.h"

using namespace cv;
using namespace std;

std::vector<Point>  mousePoints;
int selectPolygon(cv::Mat srcMat,cv::Mat &dstMat_0,cv::Mat &dstMat_1);
Point points;

int main()
{
	//��ʼ��ʱ
	double start = static_cast<double>(getTickCount());
    cv::Mat src_1 = imread("../testImages\\3.png", 0);
    cv::Mat src = imread("../testImages\\lena.jpg", 0);
    cv::Mat dst, dst_1;

    int m = getOptimalDFTSize(src.rows); //2,3,5�ı����и���Ч�ʵĸ���Ҷ�任
    int n = getOptimalDFTSize(src.cols);
    Mat padded_0, padded_1;
    //�ѻҶ�ͼ��������Ͻ�,���ұߺ��±���չͼ��,��չ�������Ϊ0;
    copyMakeBorder(src, padded_0, 0, m - src.rows, 0, n - src.cols, BORDER_CONSTANT, Scalar::all(0));
    copyMakeBorder(src_1, padded_1, 0, m - src_1.rows, 0, n - src_1.cols, BORDER_CONSTANT, Scalar::all(0));
    //planes[0]Ϊdft�任��ʵ����planes[1]Ϊ�鲿��phΪ��λ�� plane_true=magΪ��ֵ
    Mat planes[] = {Mat_<float>(padded_0), Mat::zeros(padded_0.size(), CV_32F) };
    Mat planes_1[] = { Mat_<float>(padded_1), Mat::zeros(padded_1.size(), CV_32F) };
    Mat planes_true = Mat_<float>(padded_0);
    Mat planes_true_1 = Mat_<float>(padded_1);
    Mat ph = Mat_<float>(padded_0);
    Mat ph_1 = Mat_<float>(padded_1);
    Mat complexImg, complexImg_1;
    //��ͨ��complexImg����ʵ�������鲿
    merge(planes, 2, complexImg);
    merge(planes_1, 2, complexImg_1);
    //���ϱߺϳɵ�mat���и���Ҷ�任,***֧��ԭ�ز���***,����Ҷ�任���Ϊ����.ͨ��1�����ʵ��,ͨ����������鲿
    dft(complexImg, complexImg);
    dft(complexImg_1, complexImg_1);
    //�ѱ任��Ľ���ָ����mat,һ��ʵ��,һ���鲿,�����������
    split(complexImg, planes);
    split(complexImg_1, planes_1);
    //---------------�˲���Ŀ��Ϊ���õ���ʾ��ֵ---�����ָ�ԭͼʱ�����ٴ���һ��-------------------------
    magnitude(planes[0], planes[1], planes_true);//������mag
    phase(planes[0], planes[1], ph);//��λ��ph
    Mat A_0 = planes[0];
    Mat B_0 = planes[1];
    Mat mag = planes_true;


    magnitude(planes_1[0], planes_1[1], planes_true_1);//������mag
    phase(planes_1[0], planes_1[1], ph_1);//��λ��ph
    Mat A_1 = planes_1[0];
    Mat B_1 = planes_1[1];
    Mat mag_1 = planes_true_1;

    mag += Scalar::all(1);//�Է�ֵ��1
    mag_1 += Scalar::all(1);//�Է�ֵ��1
    //������ķ�ֵһ��ܴ󣬴ﵽ10^4,ͨ��û�а취��ͼ������ʾ��������Ҫ�������log��⡣
    log(mag, mag);
    log(mag_1, mag_1);

    //ȡ�����е����ֵ�����ں�����ԭʱȥ��һ��
    double maxVal, maxVal_1;
    minMaxLoc(mag, 0, &maxVal, 0, 0);
    minMaxLoc(mag_1, 0, &maxVal_1, 0, 0);

    //�޼�Ƶ��,���ͼ����л������������Ļ�,����Ƶ���ǲ��ԳƵ�,���Ҫ�޼�
    mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));
    ph = ph(Rect(0, 0, mag.cols & -2, mag.rows & -2));
    mag_1 = mag_1(Rect(0, 0, mag_1.cols & -2, mag_1.rows & -2));
    ph_1 = ph_1(Rect(0, 0, mag_1.cols & -2, mag_1.rows & -2));
    Mat _magI = mag.clone();
    Mat _magI_1 = mag_1.clone();
    //�����ȹ�һ��������ʾ��Χ��
    normalize(_magI, _magI, 0, 1, NORM_MINMAX);
    normalize(_magI_1, _magI_1, 0, 1, NORM_MINMAX);
    //imshow("before rearrange", _magI);

    //��ʾ����Ƶ��ͼ
    static int cx = mag.cols / 2;
    static int cy = mag.rows / 2;

    //������������Ϊ��׼����magͼ��ֳ��Ĳ���
    Mat tmp;
    Mat q0(mag, Rect(0, 0, cx, cy));
    Mat q1(mag, Rect(cx, 0, cx, cy));
    Mat q2(mag, Rect(0, cy, cx, cy));
    Mat q3(mag, Rect(cx, cy, cx, cy));
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    Mat tmp_1;
    Mat q0_1(mag_1, Rect(0, 0, cx, cy));
    Mat q1_1(mag_1, Rect(cx, 0, cx, cy));
    Mat q2_1(mag_1, Rect(0, cy, cx, cy));
    Mat q3_1(mag_1, Rect(cx, cy, cx, cy));
    q0_1.copyTo(tmp_1);
    q3_1.copyTo(q0_1);
    tmp_1.copyTo(q3_1);
    q1_1.copyTo(tmp_1);
    q2_1.copyTo(q1_1);
    tmp_1.copyTo(q2_1);


    normalize(mag, mag, 0, 1, NORM_MINMAX);
    normalize(mag_1, mag_1, 0, 1, NORM_MINMAX);


    mag = mag * 255;
    mag_1 = mag_1 * 255;
    cv::imwrite("../ԭͼ1Ƶ��.jpg", mag);
    cv::imwrite("../ԭͼ2Ƶ��.jpg", mag_1);
    /*--------------------------------------------------*/

    mag = mag / 255;
    mag_1 = mag_1 / 255;
    cv::Mat mask_0, mask_1;
    Mat proceMag, proceMag_1;

    selectPolygon(mag, mask_0, mask_1);

    mag= mag.mul(mask_0);
    mag_1= mag_1.mul(mask_1);

    proceMag = mag * 255;
    proceMag_1 = mag_1 * 255;
    cv::imwrite("../�����ͼ1Ƶ��.jpg", proceMag);
    cv::imwrite("../�����ͼ2Ƶ��.jpg", proceMag_1);

    Mat q00(mag, Rect(0, 0, cx, cy));
    Mat q10(mag, Rect(cx, 0, cx, cy));
    Mat q20(mag, Rect(0, cy, cx, cy));
    Mat q30(mag, Rect(cx, cy, cx, cy));
    //��������
    q00.copyTo(tmp);
    q30.copyTo(q00);
    tmp.copyTo(q30);
    q10.copyTo(tmp);
    q20.copyTo(q10);
    tmp.copyTo(q20);
    mag = mag * maxVal;//����һ���ľ���ԭ
    exp(mag, mag);//��Ӧ��ǰ��ȥ����
    mag = mag - Scalar::all(1);//��Ӧǰ��+1
    polarToCart(mag, ph, planes[0], planes[1]);//�ɷ�����mag����λ��ph�ָ�ʵ��planes[0]���鲿planes[1]
    merge(planes, 2, complexImg);//��ʵ���鲿�ϲ�

    Mat q00_1(mag_1, Rect(0, 0, cx, cy));
    Mat q10_1(mag_1, Rect(cx, 0, cx, cy));
    Mat q20_1(mag_1, Rect(0, cy, cx, cy));
    Mat q30_1(mag_1, Rect(cx, cy, cx, cy));
    //��������
    q00_1.copyTo(tmp_1);
    q30_1.copyTo(q00_1);
    tmp_1.copyTo(q30_1);
    q10_1.copyTo(tmp_1);
    q20_1.copyTo(q10_1);
    tmp_1.copyTo(q20_1);
    mag_1 = mag_1 * maxVal_1;//����һ���ľ���ԭ
    exp(mag_1, mag_1);//��Ӧ��ǰ��ȥ����
    mag_1 = mag_1 - Scalar::all(1);//��Ӧǰ��+1
    polarToCart(mag_1, ph_1, planes_1[0], planes_1[1]);//�ɷ�����mag����λ��ph�ָ�ʵ��planes[0]���鲿planes[1]
    merge(planes_1, 2, complexImg_1);//��ʵ���鲿�ϲ�

    //-----------------------����Ҷ����任-----------------------------------
    Mat ifft(Size(src.cols, src.rows), CV_8UC1);
    //����Ҷ��任
    idft(complexImg, ifft, DFT_REAL_OUTPUT);
    normalize(ifft, ifft, 0, 1, NORM_MINMAX);
    Rect rect_0(0, 0, src.cols, src.rows);
    dst = ifft(rect_0);
    dst = dst * 255;

    Mat ifft_1(Size(src_1.cols, src_1.rows), CV_8UC1);
    //����Ҷ��任
    idft(complexImg_1, ifft_1, DFT_REAL_OUTPUT);
    normalize(ifft_1, ifft_1, 0, 1, NORM_MINMAX);
    Rect rect_1(0, 0, src_1.cols, src_1.rows);
    dst_1 = ifft_1(rect_1);
    dst_1 = dst_1 * 255;

    cv::Mat dspMat, dspMat_1, res;
    dst.convertTo(dspMat, CV_8UC1);
    dst_1.convertTo(dspMat_1, CV_8UC1);
    cv::addWeighted(dspMat, 0.5, dspMat_1, 0.5, 2, res);
    imshow("dst_0", dspMat);
    imshow("dst_1", dspMat_1);
    imshow("res", res);
    imshow("src_0", src);
    imshow("src_1", src_1);
    cv::imwrite("../�ϳ�ͼ��.jpg", res);

	double time = ((double)getTickCount() - start) / getTickFrequency();
	//��ʾʱ��
	cout << "processing time:" << time / 1000 << "ms" << endl;

	//�ȴ�������Ӧ�����������������
    while (true) {
        if (waitKey(1) == 27)
        {
            break;
        }
    }
    return 0;
}


void on_mouse(int EVENT, int x, int y, int flags, void* userdata)
{

    Mat hh;
    hh = *(Mat*)userdata;
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
    //����roi
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
