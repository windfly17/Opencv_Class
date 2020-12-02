#include <opencv2/opencv.hpp>
#include "funtions.h"

using namespace cv;
using namespace std;

static int cx, cy;

int main()
{
	//��ʼ��ʱ
	double start = static_cast<double>(getTickCount());
    cv::Mat src_1 = imread("../testImages\\3.png", 0);
    cv::Mat src_0 = imread("../testImages\\lena.jpg", 0);

    cv::Mat dst_0, dst_1;

    int m = getOptimalDFTSize(src_0.rows); //2,3,5�ı����и���Ч�ʵĸ���Ҷ�任
    int n = getOptimalDFTSize(src_0.cols);
    Mat padded_0, padded_1;
    //�ѻҶ�ͼ��������Ͻ�,���ұߺ��±���չͼ��,��չ�������Ϊ0;
    copyMakeBorder(src_0, padded_0, 0, m - src_0.rows, 0, n - src_0.cols, BORDER_CONSTANT, Scalar::all(0));
    copyMakeBorder(src_1, padded_1, 0, m - src_1.rows, 0, n - src_1.cols, BORDER_CONSTANT, Scalar::all(0));
    //planes[0]Ϊdft�任��ʵ����planes[1]Ϊ�鲿��phΪ��λ�� plane_true=magΪ��ֵ
    Mat planes_0[] = { Mat_<float>(padded_0), Mat::zeros(padded_0.size(), CV_32F) };
    Mat planes_1[] = { Mat_<float>(padded_1), Mat::zeros(padded_1.size(), CV_32F) };
    Mat planes_true_0 = Mat_<float>(padded_0);
    Mat planes_true_1 = Mat_<float>(padded_1);
    Mat ph_0 = Mat_<float>(padded_0);
    Mat ph_1 = Mat_<float>(padded_1);
    Mat complexImg_0, complexImg_1;
    //��ͨ��complexImg����ʵ�������鲿
    merge(planes_0, 2, complexImg_0);
    merge(planes_1, 2, complexImg_1);
    //���ϱߺϳɵ�mat���и���Ҷ�任,***֧��ԭ�ز���***,����Ҷ�任���Ϊ����.ͨ��1�����ʵ��,ͨ����������鲿
    dft(complexImg_0, complexImg_0);
    dft(complexImg_1, complexImg_1);
    //�ѱ任��Ľ���ָ����mat,һ��ʵ��,һ���鲿,�����������
    split(complexImg_0, planes_0);
    split(complexImg_1, planes_1);
    //---------------�˲���Ŀ��Ϊ���õ���ʾ��ֵ---�����ָ�ԭͼʱ�����ٴ���һ��-------------------------
    magnitude(planes_0[0], planes_0[1], planes_true_0);//������mag
    phase(planes_0[0], planes_0[1], ph_0);//��λ��ph
    Mat A_0 = planes_0[0];
    Mat B_0 = planes_0[1];
    Mat mag_0 = planes_true_0;


    magnitude(planes_1[0], planes_1[1], planes_true_1);//������mag
    phase(planes_1[0], planes_1[1], ph_1);//��λ��ph
    Mat A_1 = planes_1[0];
    Mat B_1 = planes_1[1];
    Mat mag_1 = planes_true_1;

    mag_0 += Scalar::all(1);//�Է�ֵ��1
    mag_1 += Scalar::all(1);//�Է�ֵ��1
    //������ķ�ֵһ��ܴ󣬴ﵽ10^4,ͨ��û�а취��ͼ������ʾ��������Ҫ�������log��⡣
    log(mag_0, mag_0);
    log(mag_1, mag_1);

    //ȡ�����е����ֵ�����ں�����ԭʱȥ��һ��
    double maxVal_0, maxVal_1;
    minMaxLoc(mag_0, 0, &maxVal_0, 0, 0);
    minMaxLoc(mag_1, 0, &maxVal_1, 0, 0);

    //�޼�Ƶ��,���ͼ����л������������Ļ�,����Ƶ���ǲ��ԳƵ�,���Ҫ�޼�
    mag_0 = mag_0(Rect(0, 0, mag_0.cols & -2, mag_0.rows & -2));
    ph_0 = ph_0(Rect(0, 0, mag_0.cols & -2, mag_0.rows & -2));
    mag_1 = mag_1(Rect(0, 0, mag_1.cols & -2, mag_1.rows & -2));
    ph_1 = ph_1(Rect(0, 0, mag_1.cols & -2, mag_1.rows & -2));
    Mat _magI_0 = mag_0.clone();
    Mat _magI_1 = mag_1.clone();
    //�����ȹ�һ��������ʾ��Χ��
    normalize(_magI_0, _magI_0, 0, 1, NORM_MINMAX);
    normalize(_magI_1, _magI_1, 0, 1, NORM_MINMAX);
    //imshow("before rearrange", _magI);

    //��ʾ����Ƶ��ͼ
    static int cx = mag_0.cols / 2;
    static int cy = mag_0.rows / 2;

    //������������Ϊ��׼����magͼ��ֳ��Ĳ���
    Mat tmp_0;
    Mat q0(mag_0, Rect(0, 0, cx, cy));
    Mat q1(mag_0, Rect(cx, 0, cx, cy));
    Mat q2(mag_0, Rect(0, cy, cx, cy));
    Mat q3(mag_0, Rect(cx, cy, cx, cy));
    q0.copyTo(tmp_0);
    q3.copyTo(q0);
    tmp_0.copyTo(q3);
    q1.copyTo(tmp_0);
    q2.copyTo(q1);
    tmp_0.copyTo(q2);

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


    normalize(mag_0, mag_0, 0, 1, NORM_MINMAX);
    normalize(mag_1, mag_1, 0, 1, NORM_MINMAX);
//    Mat tmp_0, tmp_1;
//    double maxVal_0, maxVal_1;
//    mag(src_0, mag_0, ph_0,tmp_0,maxVal_0);
//    mag(src_1, mag_1, ph_0, tmp_1,maxVal_1);


    mag_0 = mag_0 * 255;
    mag_1 = mag_1 * 255;
    cv::imwrite("../ԭͼ1Ƶ��.jpg", mag_0);
    cv::imwrite("../ԭͼ2Ƶ��.jpg", mag_1);
    /*--------------------------------------------------*/

    mag_0 = mag_0 / 255;
    mag_1 = mag_1 / 255;
    cv::Mat mask_0, mask_1;
    Mat proceMag_0, proceMag_1;

    selectPolygon(mag_0,mask_0,mask_1);

    mag_0= mag_0.mul(mask_0);
    mag_1= mag_1.mul(mask_1);

    proceMag_0 = mag_0 * 255;
    proceMag_1 = mag_1 * 255;
    cv::imwrite("../�����ͼ1Ƶ��.jpg", proceMag_0);
    cv::imwrite("../�����ͼ2Ƶ��.jpg", proceMag_1);

    Mat q00(mag_0, Rect(0, 0, cx, cy));
    Mat q10(mag_0, Rect(cx, 0, cx, cy));
    Mat q20(mag_0, Rect(0, cy, cx, cy));
    Mat q30(mag_0, Rect(cx, cy, cx, cy));
    //��������
    q00.copyTo(tmp_0);
    q30.copyTo(q00);
    tmp_0.copyTo(q30);
    q10.copyTo(tmp_0);
    q20.copyTo(q10);
    tmp_0.copyTo(q20);
    mag_0 = mag_0 * maxVal_0;//����һ���ľ���ԭ
    exp(mag_0, mag_0);//��Ӧ��ǰ��ȥ����
    mag_0 = mag_0 - Scalar::all(1);//��Ӧǰ��+1
    polarToCart(mag_0, ph_0, planes_0[0], planes_0[1]);//�ɷ�����mag����λ��ph�ָ�ʵ��planes[0]���鲿planes[1]
    merge(planes_0, 2, complexImg_0);//��ʵ���鲿�ϲ�

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
    Mat ifft_0(Size(src_0.cols, src_0.rows), CV_8UC1);
    //����Ҷ��任
    idft(complexImg_0, ifft_0, DFT_REAL_OUTPUT);
    normalize(ifft_0, ifft_0, 0, 1, NORM_MINMAX);
    Rect rect_0(0, 0, src_0.cols, src_0.rows);
    dst_0 = ifft_0(rect_0);
    dst_0 = dst_0 * 255;

    Mat ifft_1(Size(src_1.cols, src_1.rows), CV_8UC1);
    //����Ҷ��任
    idft(complexImg_1, ifft_1, DFT_REAL_OUTPUT);
    normalize(ifft_1, ifft_1, 0, 1, NORM_MINMAX);
    Rect rect_1(0, 0, src_1.cols, src_1.rows);
    dst_1 = ifft_1(rect_1);
    dst_1 = dst_1 * 255;

    cv::Mat dspMat_0, dspMat_1, res;
    dst_0.convertTo(dspMat_0, CV_8UC1);
    dst_1.convertTo(dspMat_1, CV_8UC1);
    cv::addWeighted(dspMat_0, 0.5, dspMat_1, 0.5, 2, res);
    imshow("dst_0", dspMat_0);
    imshow("dst_1", dspMat_1);
    imshow("res", res);
    imshow("src_0", src_0);
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

