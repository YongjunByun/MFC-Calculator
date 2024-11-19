#pragma once
#define _USE_MATH_DEFINES
#define NOMINMAX

#include "Mat.h"
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <future>

using namespace std;

class ImageProcessing
{
public:
	ImageProcessing();
	~ImageProcessing();

	bool RotateImage(Mat& src, Mat& dst, int theta);
	bool FlipImage(Mat& src, Mat& dst, bool vertical);
	bool ResizeImage(Mat& src, Mat& dst, double ratio); // �缱�� ������
	bool GaussianBlur(Mat& src, Mat& dst, int ksize = 5, int sigma = 1);
	bool SeparableGaussianBlur(Mat & src, Mat & dst, int ksize = 5, int sigma = 1);
	bool BilateralBlur(Mat & src, Mat & dst, int d = -1, double sigmaColor=3.0, double SigmaSpace = 0.25);
	bool MedianBlur(Mat& src, Mat& dst, int ksize = 3);
	bool MulThread_MedianBlur(Mat& src, Mat & dst, int ksize = 3) ;
	bool Normalize(Mat& src, Mat& dst, int minHist, int maxHist); // ������׷� ����ȭ
	bool Threshold(Mat& src, Mat& dst, int min_threshold, int max_threshold);
	bool Otsu(Mat & src, Mat & dst);
	bool Binarization(Mat& src, Mat& dst, int threshold);
	bool Contours(Mat& binary_img, vector<vector<Point_>>& contours);
	bool Sobel(Mat& src, Mat& dst); // ������ã������ �� ���̳ʸ��� �̹����� ��ǲ���� �޾ƺ�.
	bool DrawContours(Mat& src, Mat& dst, vector<vector<Point_>>& contours);
	bool ResizeContours(vector<vector<Point_>>& contours, double ratio);

	const int SIZEOF_UINT16 = 65535;
};

