#include <opencv2/opencv.hpp>
#include "funtions.h"

using namespace cv;
using namespace std;

static int cx, cy;

int main()
{
	//开始计时
	double start = static_cast<double>(getTickCount());
    cv::Mat src_1 = imread("../testImages\\3.png", 0);
    cv::Mat src_0 = imread("../testImages\\lena.jpg", 0);

    cv::Mat dst_0, dst_1;

    int m = getOptimalDFTSize(src_0.rows); //2,3,5的倍数有更高效率的傅里叶变换
    int n = getOptimalDFTSize(src_0.cols);
    Mat padded_0, padded_1;
    //把灰度图像放在左上角,在右边和下边扩展图像,扩展部分填充为0;
    copyMakeBorder(src_0, padded_0, 0, m - src_0.rows, 0, n - src_0.cols, BORDER_CONSTANT, Scalar::all(0));
    copyMakeBorder(src_1, padded_1, 0, m - src_1.rows, 0, n - src_1.cols, BORDER_CONSTANT, Scalar::all(0));
    //planes[0]为dft变换的实部，planes[1]为虚部，ph为相位， plane_true=mag为幅值
    Mat planes_0[] = { Mat_<float>(padded_0), Mat::zeros(padded_0.size(), CV_32F) };
    Mat planes_1[] = { Mat_<float>(padded_1), Mat::zeros(padded_1.size(), CV_32F) };
    Mat planes_true_0 = Mat_<float>(padded_0);
    Mat planes_true_1 = Mat_<float>(padded_1);
    Mat ph_0 = Mat_<float>(padded_0);
    Mat ph_1 = Mat_<float>(padded_1);
    Mat complexImg_0, complexImg_1;
    //多通道complexImg既有实部又有虚部
    merge(planes_0, 2, complexImg_0);
    merge(planes_1, 2, complexImg_1);
    //对上边合成的mat进行傅里叶变换,***支持原地操作***,傅里叶变换结果为复数.通道1存的是实部,通道二存的是虚部
    dft(complexImg_0, complexImg_0);
    dft(complexImg_1, complexImg_1);
    //把变换后的结果分割到两个mat,一个实部,一个虚部,方便后续操作
    split(complexImg_0, planes_0);
    split(complexImg_1, planes_1);
    //---------------此部分目的为更好地显示幅值---后续恢复原图时反着再处理一遍-------------------------
    magnitude(planes_0[0], planes_0[1], planes_true_0);//幅度谱mag
    phase(planes_0[0], planes_0[1], ph_0);//相位谱ph
    Mat A_0 = planes_0[0];
    Mat B_0 = planes_0[1];
    Mat mag_0 = planes_true_0;


    magnitude(planes_1[0], planes_1[1], planes_true_1);//幅度谱mag
    phase(planes_1[0], planes_1[1], ph_1);//相位谱ph
    Mat A_1 = planes_1[0];
    Mat B_1 = planes_1[1];
    Mat mag_1 = planes_true_1;

    mag_0 += Scalar::all(1);//对幅值加1
    mag_1 += Scalar::all(1);//对幅值加1
    //计算出的幅值一般很大，达到10^4,通常没有办法在图像中显示出来，需要对其进行log求解。
    log(mag_0, mag_0);
    log(mag_1, mag_1);

    //取矩阵中的最大值，便于后续还原时去归一化
    double maxVal_0, maxVal_1;
    minMaxLoc(mag_0, 0, &maxVal_0, 0, 0);
    minMaxLoc(mag_1, 0, &maxVal_1, 0, 0);

    //修剪频谱,如果图像的行或者列是奇数的话,那其频谱是不对称的,因此要修剪
    mag_0 = mag_0(Rect(0, 0, mag_0.cols & -2, mag_0.rows & -2));
    ph_0 = ph_0(Rect(0, 0, mag_0.cols & -2, mag_0.rows & -2));
    mag_1 = mag_1(Rect(0, 0, mag_1.cols & -2, mag_1.rows & -2));
    ph_1 = ph_1(Rect(0, 0, mag_1.cols & -2, mag_1.rows & -2));
    Mat _magI_0 = mag_0.clone();
    Mat _magI_1 = mag_1.clone();
    //将幅度归一化到可显示范围。
    normalize(_magI_0, _magI_0, 0, 1, NORM_MINMAX);
    normalize(_magI_1, _magI_1, 0, 1, NORM_MINMAX);
    //imshow("before rearrange", _magI);

    //显示规则频谱图
    static int cx = mag_0.cols / 2;
    static int cy = mag_0.rows / 2;

    //这里是以中心为标准，把mag图像分成四部分
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
    cv::imwrite("../原图1频谱.jpg", mag_0);
    cv::imwrite("../原图2频谱.jpg", mag_1);
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
    cv::imwrite("../处理后图1频谱.jpg", proceMag_0);
    cv::imwrite("../处理后图2频谱.jpg", proceMag_1);

    Mat q00(mag_0, Rect(0, 0, cx, cy));
    Mat q10(mag_0, Rect(cx, 0, cx, cy));
    Mat q20(mag_0, Rect(0, cy, cx, cy));
    Mat q30(mag_0, Rect(cx, cy, cx, cy));
    //交换象限
    q00.copyTo(tmp_0);
    q30.copyTo(q00);
    tmp_0.copyTo(q30);
    q10.copyTo(tmp_0);
    q20.copyTo(q10);
    tmp_0.copyTo(q20);
    mag_0 = mag_0 * maxVal_0;//将归一化的矩阵还原
    exp(mag_0, mag_0);//对应于前述去对数
    mag_0 = mag_0 - Scalar::all(1);//对应前述+1
    polarToCart(mag_0, ph_0, planes_0[0], planes_0[1]);//由幅度谱mag和相位谱ph恢复实部planes[0]和虚部planes[1]
    merge(planes_0, 2, complexImg_0);//将实部虚部合并

    Mat q00_1(mag_1, Rect(0, 0, cx, cy));
    Mat q10_1(mag_1, Rect(cx, 0, cx, cy));
    Mat q20_1(mag_1, Rect(0, cy, cx, cy));
    Mat q30_1(mag_1, Rect(cx, cy, cx, cy));
    //交换象限
    q00_1.copyTo(tmp_1);
    q30_1.copyTo(q00_1);
    tmp_1.copyTo(q30_1);
    q10_1.copyTo(tmp_1);
    q20_1.copyTo(q10_1);
    tmp_1.copyTo(q20_1);
    mag_1 = mag_1 * maxVal_1;//将归一化的矩阵还原
    exp(mag_1, mag_1);//对应于前述去对数
    mag_1 = mag_1 - Scalar::all(1);//对应前述+1
    polarToCart(mag_1, ph_1, planes_1[0], planes_1[1]);//由幅度谱mag和相位谱ph恢复实部planes[0]和虚部planes[1]
    merge(planes_1, 2, complexImg_1);//将实部虚部合并

    //-----------------------傅里叶的逆变换-----------------------------------
    Mat ifft_0(Size(src_0.cols, src_0.rows), CV_8UC1);
    //傅里叶逆变换
    idft(complexImg_0, ifft_0, DFT_REAL_OUTPUT);
    normalize(ifft_0, ifft_0, 0, 1, NORM_MINMAX);
    Rect rect_0(0, 0, src_0.cols, src_0.rows);
    dst_0 = ifft_0(rect_0);
    dst_0 = dst_0 * 255;

    Mat ifft_1(Size(src_1.cols, src_1.rows), CV_8UC1);
    //傅里叶逆变换
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
    cv::imwrite("../合成图像.jpg", res);

	double time = ((double)getTickCount() - start) / getTickFrequency();
	//显示时间
	cout << "processing time:" << time / 1000 << "ms" << endl;

	//等待键盘响应，按任意键结束程序
    while (true) {
        if (waitKey(1) == 27)
        {
            break;
        }
    }
    return 0;
}

