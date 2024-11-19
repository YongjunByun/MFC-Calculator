#include "stdafx.h"
#include "ImageProcessing.h"

ImageProcessing::ImageProcessing()
{
}

ImageProcessing::~ImageProcessing()
{
}

bool ImageProcessing::RotateImage(Mat& src, Mat& dst, int theta)
{
	if (src.isEmpty())
		return false;

	int width = src.GetWidth();
	int height = src.GetHeight();
	const auto& srcData = src.getData();
	auto& dstData = dst.getData();

	double radians = theta * M_PI / 180.0;
	int newWidth = static_cast<int>(abs(width * cos(radians)) + abs(height * sin(radians)));
	int newHeight = static_cast<int>(abs(width * sin(radians)) + abs(height * cos(radians)));

	dst = Mat(newWidth, newHeight, src.GetbitDepth());
	
	int cx = width / 2;
	int cy = height / 2;
	int newCx = newWidth / 2;
	int newCy = newHeight / 2;

	int minvalue = SIZEOF_UINT16;
	int maxvalue = 0;
	for (int y = 0; y < newHeight; ++y) {
		for (int x = 0; x < newWidth; ++x) {
			int srcX = static_cast<int>((x - newCx) * cos(-radians) - (y - newCy) * sin(-radians) + cx);
			int srcY = static_cast<int>((x - newCx) * sin(-radians) + (y - newCy) * cos(-radians) + cy);

			if (srcX >= 0 && srcX < width && srcY >= 0 && srcY < height) {
				dstData[y * newWidth + x] = srcData[srcY * width + srcX];
			}
			else {
				dstData[y * newWidth + x] = 0;
			}
			minvalue = min(minvalue, dstData[y * newWidth + x]);
			maxvalue = max(maxvalue, dstData[y * newWidth + x]);
		}
	}
	dst.SetMinValue(minvalue);
	dst.SetMaxValue(maxvalue);
	return true;
}

bool ImageProcessing::FlipImage(Mat& src, Mat& dst, bool vertical)
{
	if (src.isEmpty()) return false;

	dst = src.Copy();
	int width = src.GetWidth();
	int height = src.GetHeight();

	const auto& srcData = src.getData();
	auto& dstData = dst.getData();

	if (vertical) {
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				dstData[(height - 1 - y) * width + x] = srcData[y * width + x];
			}
		}
	}
	else {
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				dstData[y * width + (width - 1 - x)] = srcData[y * width + x];
			}
		}
	}
	return true;
}

bool ImageProcessing::ResizeImage(Mat& src, Mat& dst, double ratio)
{
	if (ratio <= 0) 
		return false;
	if (src.isEmpty())
		return false;

	int width = src.GetWidth();
	int height = src.GetHeight();
	int newWidth = static_cast<int>(width * ratio);
	int newHeight = static_cast<int>(height * ratio);
	dst = Mat(newWidth, newHeight, src.GetbitDepth());

	const auto& srcData = src.getData();
	auto& dstData = dst.getData();

	int minvalue = SIZEOF_UINT16;
	int maxvalue = 0;
	for (int y = 0; y < newHeight; ++y) {
		for (int x = 0; x < newWidth; ++x) {
			double srcX = x / ratio;
			double srcY = y / ratio;

			int x1 = static_cast<int>(srcX);
			int y1 = static_cast<int>(srcY);
			int x2 = min(x1 + 1, width - 1);
			int y2 = min(y1 + 1, height - 1);

			double xWeight = srcX - x1;
			double yWeight = srcY - y1;

			double value =
				(1 - xWeight) * (1 - yWeight) * srcData[y1 * width + x1] +
				xWeight * (1 - yWeight) * srcData[y1 * width + x2] +
				(1 - xWeight) * yWeight * srcData[y2 * width + x1] +
				xWeight * yWeight * srcData[y2 * width + x2];

			dstData[y * newWidth + x] = static_cast<uint16_t>(value);
			minvalue = min(minvalue, dstData[y * newWidth + x]);
			maxvalue = max(maxvalue, dstData[y * newWidth + x]);
		}
	}
	dst.SetMinValue(minvalue);
	dst.SetMaxValue(maxvalue);
	return true;
}

bool ImageProcessing::GaussianBlur(Mat& src, Mat& dst, int ksize, int sigma)
{
	if (ksize <= 1 || ksize % 2 == 0)
		return false; // 커널 사이즈 예외처리
	if (sigma <= 0)
		return false;
	if (src.isEmpty())
		return false;

	int width = src.GetWidth();
	int height = src.GetHeight();
	dst = src.Copy();

	const auto& srcData = src.getData();
	auto& dstData = dst.getData();

	vector<vector<double>> kernel(ksize, vector<double>(ksize));
	int halfK = ksize / 2;
	double sum = 0.0;

	for (int i = -halfK; i <= halfK; ++i) {
		for (int j = -halfK; j <= halfK; ++j) {
			double value = exp(-(i * i + j * j) / (2.0 * sigma * sigma)) / (2.0 * M_PI * sigma * sigma); // 식
			kernel[i + halfK][j + halfK] = value;
			sum += value;
		}
	}
	
	for (int i = 0; i < ksize; ++i) {
		for (int j = 0; j < ksize; ++j) {
			kernel[i][j] /= sum; // 1로 정규화
		}
	}

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			double pixelSum = 0.0;

			for (int ky = -halfK; ky <= halfK; ++ky) {
				for (int kx = -halfK; kx <= halfK; ++kx) {
					int nx = min(max(x + kx, 0), width - 1);
					int ny = min(max(y + ky, 0), height - 1);
					pixelSum += srcData[ny * width + nx] * kernel[ky + halfK][kx + halfK];
				}
			}
			dstData[y * width + x] = static_cast<uint16_t>(pixelSum);
		}
	}

	return true;
}

bool ImageProcessing::SeparableGaussianBlur(Mat& src, Mat& dst, int ksize, int sigma)
{
	if (ksize <= 1 || ksize % 2 == 0)
		return false; // 커널 사이즈 예외처리
	if (sigma <= 0)
		return false;
	if (src.isEmpty())
		return false;

	int width = src.GetWidth();
	int height = src.GetHeight();
	dst = src.Copy();

	const auto& srcData = src.getData();
	auto& dstData = dst.getData();

	vector<double> kernel(ksize, 0);
	int halfK = ksize / 2;
	double sum = 0.0;

	for (int i = 0; i < ksize; ++i) { // 가우시안 필터 특성상 Gx만 구해서 계산해도 될듯
		double x = i - halfK;
		kernel[i] = exp(-(x * x) / (2.0 * sigma * sigma));
		sum += kernel[i];
	}

	for (int i = 0; i < ksize; ++i) {
		kernel[i] /= sum;
	}


	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			double pixelSum = 0.0;
			for (int i = -halfK; i <= halfK; ++i) {
				int nx = min(max(x + i, 0), width - 1);
				pixelSum += srcData[y * width + nx] * kernel[i + halfK];
			}
			dstData[y * width + x] = static_cast<uint16_t>(pixelSum);
		}
	}

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			double pixelSum = 0.0;
			for (int i = -halfK; i <= halfK; ++i) {
				int ny = min(max(y + i, 0), height - 1);
				pixelSum += dstData[ny * width + x] * kernel[i + halfK];
			}
			dstData[y * width + x] = static_cast<uint16_t>(pixelSum);
		}
	}
	return true;
}

bool ImageProcessing::BilateralBlur(Mat& src, Mat& dst, int d, double sigmaColor, double sigmaSpace) {
	if (src.isEmpty())
		return false;

	dst = src.Copy();
	int width = src.GetWidth();
	int height = src.GetHeight();
	int kernelSize = d;
	if(d == -1)
		kernelSize = static_cast<int>(2 * ceil(3 * sigmaSpace) + 1); // 필터 크기, 3*sigmaSpace 범위 사용
	int halfKernel = kernelSize / 2;

	// 가우시안 공간 필터 계산
	vector<vector<double>> spatialKernel(kernelSize, vector<double>(kernelSize));
	for (int i = -halfKernel; i <= halfKernel; ++i) {
		for (int j = -halfKernel; j <= halfKernel; ++j) {
			spatialKernel[i + halfKernel][j + halfKernel] =
				exp(-(i * i + j * j) / (2 * sigmaSpace * sigmaSpace));
		}
	}
	auto& dstData = dst.getData();
	// 필터링 작업
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			double wp = 0.0;        // 정규화 상수
			double pixelSum = 0.0; // 결과 픽셀 값

			for (int i = -halfKernel; i <= halfKernel; ++i) {
				for (int j = -halfKernel; j <= halfKernel; ++j) {
					int ny = min(max(y + i, 0), height - 1);
					int nx = min(max(x + j, 0), width - 1);

					// 색상 가우시안 필터
					double colorDiff = src.at(x, y) - src.at(nx, ny);
					double rangeWeight = exp(-(colorDiff * colorDiff) / (2 * sigmaColor * sigmaColor));

					// 최종 가중치
					double weight = spatialKernel[i + halfKernel][j + halfKernel] * rangeWeight;

					// 누적 합
					wp += weight;
					pixelSum += weight * src.at(nx, ny);
				}
			}

			// 필터링 결과 저장
			dstData[y * width + x] = static_cast<uint16_t>(pixelSum / wp);
		}
	}

	return true;
}

bool ImageProcessing::MedianBlur(Mat& src, Mat& dst, int ksize)
{

	if (ksize <= 1 || ksize % 2 == 0) 
		return false; // 커널 사이즈 예외처리
	if (src.isEmpty()) 
		return false;

	int width = src.GetWidth();
	int height = src.GetHeight();

	dst = src.Copy();
	const auto& srcData = src.getData();
	auto& dstData = dst.getData();

	int halfK = ksize / 2;

	int minvalue = SIZEOF_UINT16;
	int maxvalue = 0;
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			vector<uint16_t> neighborhood;

			for (int ky = -halfK; ky <= halfK; ++ky) {
				for (int kx = -halfK; kx <= halfK; ++kx) {
					int nx = min(max(x + kx, 0), width - 1);
					int ny = min(max(y + ky, 0), height - 1);
					neighborhood.push_back(srcData[ny * width + nx]);
				}
			}

			auto mid = neighborhood.begin() + neighborhood.size() / 2;
			nth_element(neighborhood.begin(), mid, neighborhood.end());
			uint16_t medianValue = *mid;

			dstData[y * width + x] = medianValue;

			minvalue = min(minvalue, dstData[y * width + x]);
			maxvalue = max(maxvalue, dstData[y * width + x]);
		}
	}
	dst.SetMinValue(minvalue);
	dst.SetMaxValue(maxvalue);
	return true;
}

bool ImageProcessing::MulThread_MedianBlur(Mat& src, Mat& dst, int ksize)
{
	if (ksize <= 1 || ksize % 2 == 0)
		return false; // 커널 사이즈 예외처리
	if (src.isEmpty())
		return false;

	int width = src.GetWidth();
	int height = src.GetHeight();

	dst = src.Copy();
	const auto& srcData = src.getData();
	auto& dstData = dst.getData();

	int halfK = ksize / 2;

	// 최소값 및 최대값 추적
	atomic<uint16_t> globalMinValue(static_cast<uint16_t>(SIZEOF_UINT16));
	atomic<uint16_t> globalMaxValue(0);

	// 스레드풀을 사용해 행 단위 작업 분배
	auto processRow = [&](int y) {
		uint16_t localMinValue = static_cast<uint16_t>(SIZEOF_UINT16);
		uint16_t localMaxValue = 0;

		for (int x = 0; x < width; ++x) {
			vector<uint16_t> neighborhood;

			for (int ky = -halfK; ky <= halfK; ++ky) {
				for (int kx = -halfK; kx <= halfK; ++kx) {
					int nx = min(max(x + kx, 0), width - 1);
					int ny = min(max(y + ky, 0), height - 1);
					neighborhood.push_back(srcData[ny * width + nx]);
				}
			}

			auto mid = neighborhood.begin() + neighborhood.size() / 2;
			nth_element(neighborhood.begin(), mid, neighborhood.end());
			uint16_t medianValue = *mid;

			dstData[y * width + x] = medianValue;

			localMinValue = min(localMinValue, medianValue);
			localMaxValue = max(localMaxValue, medianValue);
		}

		// 전역 최소/최대값 업데이트
		globalMinValue.store(min(globalMinValue.load(), localMinValue));
		globalMaxValue.store(max(globalMaxValue.load(), localMaxValue));
	};

	// Future로 작업 스케줄링
	vector<future<void>> futures;
	for (int y = 0; y < height; ++y) {
		futures.push_back(async(launch::async, processRow, y));
	}

	// 모든 작업 완료 대기
	for (auto& f : futures) {
		f.get();
	}

	// 결과값 설정
	dst.SetMinValue(globalMinValue.load());
	dst.SetMaxValue(globalMaxValue.load());

	return true;
}

bool ImageProcessing::Normalize(Mat& src, Mat& dst, int dst_min, int dst_max)
{
	if (src.isEmpty()) 
		return false;

	dst = src.Copy();
	int width = src.GetWidth();
	int height = src.GetHeight();
	vector<uint16_t> &dstData = dst.getData();
	vector<uint16_t> &srcData = src.getData();
	int src_min = src.GetMinValue();
	int src_max = src.GetMaxValue();
	dst.SetMinValue(dst_min);
	dst.SetMaxValue(dst_max);
	for (int i = 0; i < width * height; ++i){
		if (src_max == src_min) // division by zero 예외처리
			continue;
		dstData[i] = static_cast<uint16_t>((srcData[i] - src_min) * (dst_max - dst_min) / (src_max - src_min) + dst_min);
	}
	return true;
}

bool ImageProcessing::Threshold(Mat& src, Mat& dst, int min_threshold, int max_threshold)
{
	if (src.isEmpty()) 
		return false;

	dst = src.Copy();
	for (auto& pixel : dst.getData()) {
		if (pixel > max_threshold) {
			pixel = max_threshold;
		}
		if (pixel < min_threshold) {
			pixel = min_threshold;
		}
	}
	dst.SetMinValue(min_threshold);
	dst.SetMaxValue(max_threshold);
	return true;
}

bool ImageProcessing::Otsu(Mat& src, Mat& dst) {
	if (src.isEmpty())
		return false;

	int width = src.GetWidth();
	int height = src.GetHeight();
	int bitDepth = src.GetbitDepth();
	if (bitDepth != 8)
		Normalize(src, src, 0, 255); // 16비트 이미지면 정규화
	dst = src.Copy();

	vector<int> hist(256, 0);

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			hist[src.at(x, y)]++;
		}
	}
	
	int totalPixels = width * height;

	vector<double> probability(256, 0.0);
	vector<double> cumulativeSum(256, 0.0);
	vector<double> cumulativeMean(256, 0.0);

	// 히스토그램 확률 계산
	for (int i = 0; i < 256; ++i) {
		probability[i] = static_cast<double>(hist[i]) / totalPixels;
	}

	// 누적합과 누적평균
	for (int i = 0; i < 256; ++i) {
		cumulativeSum[i] = (i == 0) ? probability[i] : cumulativeSum[i - 1] + probability[i];
		cumulativeMean[i] = (i == 0) ? i * probability[i] : cumulativeMean[i - 1] + i * probability[i];
	}

	double maxVariance = 0.0;
	int otsuThreshold = 0;

	for (int t = 0; t < 256; ++t) {
		double w0 = cumulativeSum[t];
		double w1 = 1.0 - w0;        

		if (w0 == 0 || w1 == 0)
			continue;

		double mean0 = cumulativeMean[t] / w0;       // 클래스 1 평균
		double mean1 = (cumulativeMean[255] - cumulativeMean[t]) / w1; // 클래스 2 평균

		double variance = w0 * w1 * (mean0 - mean1) * (mean0 - mean1); // 클래스 간 분산

		if (variance > maxVariance) {
			maxVariance = variance;
			otsuThreshold = t;
		}
	}

	if (!Binarization(src, dst, otsuThreshold)) {
		return false;
	}
	return true;
}

bool ImageProcessing::Binarization(Mat & src, Mat & dst, int threshold)
{
	if (src.isEmpty()) 
		return false; 

	int width = src.GetWidth();
	int height = src.GetHeight();
	int bitDepth = src.GetbitDepth();

	int maxThreshold = (bitDepth == 8) ? 255 : SIZEOF_UINT16;
	if (threshold < 0 || threshold > maxThreshold) 
		return false;

	dst = src.Copy();
	const auto& srcData = src.getData();
	auto& dstData = dst.getData();

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int index = y * width + x;
			//if(bitDepth == 8) 
				dstData[index] = (srcData[index] >= threshold) ? 255 : 0; // 인풋이 16bit 이미지여도 그냥 0, 255로 이진화한다.
			//else 
			//	dstData[index] = (srcData[index] >= threshold) ? 65535 : 0;
		}
	}
	dst.SetMinValue(0);
	dst.SetMaxValue(255);
	return true;
}

bool ImageProcessing::Contours(Mat& binary_img, vector<vector<Point_>>& contours) {
	if (binary_img.isEmpty())
		return false;

	int width = binary_img.GetWidth();
	int height = binary_img.GetHeight();
	vector<vector<bool>> visited(height, vector<bool>(width, false));

	Mat grad;
	Sobel(binary_img, grad);

	const int dx[8] = { 1, -1, 0, 0, 1, 1, -1, -1 };
	const int dy[8] = { 0, 0, 1, -1, 1, -1, 1, -1 };

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			// 이진 이미지에서 윤곽선 시작 위치: 픽셀 값이 255(흰색)이고 방문하지 않은 경우
			if (grad.at(x, y) == 255 && !visited[y][x]) {
				vector<Point_> contour;
				queue<Point_> q;
				q.push(Point_(x, y));
				visited[y][x] = true;

				while (!q.empty()) {
					Point_ p = q.front();
					q.pop();

					// 윤곽선 여부 확인
					bool isEdge = false;
					for (int i = 0; i < 8; ++i) {
						int nx = p.x + dx[i];
						int ny = p.y + dy[i];

						// 유효한 위치인지 확인하고, 흰색 픽셀로 둘러싸여 있지 않으면 가장자리로 간주
						if (!grad.isValid(nx, ny) || grad.at(nx, ny) == 0) {
							isEdge = true;
						}
						else if (grad.at(nx, ny) == 255 && !visited[ny][nx]) {
							visited[ny][nx] = true;
							q.push(Point_(nx, ny));
						}
					}
					if (isEdge) {
						contour.push_back(p);
					}
				}
				if (contour.size() > 50) {
					contours.push_back(contour);
				}
			}
		}
	}
	return !contours.empty();
}

bool ImageProcessing::Sobel(Mat& src, Mat& dst) {
	if (src.isEmpty())
		return false;

	int width = src.GetWidth();
	int height = src.GetHeight();

	dst = src.Copy();
	const auto& srcData = src.getData();
	auto& dstData = dst.getData();

	vector<vector<double>> x_kernel{ {-1,0,1}, {-2,0,2}, {-1,0,1} };
	vector<vector<double>> y_kernel{ { -1,-2,-1 },{ 0,0,0 },{ 1,2,1 } };

	int minvalue = SIZEOF_UINT16;
	int maxvalue = 0;
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int sumX = 0;
			int sumY = 0;

			for (int ky = -1; ky <= 1; ++ky) {
				for (int kx = -1; kx <= 1; ++kx) {
					int nx = min(max(x + kx, 0), width - 1);
					int ny = min(max(y + ky, 0), height - 1);
					int pixel = src.at(nx, ny); 
					sumX += static_cast<int>(pixel * x_kernel[ky + 1][kx + 1]);
					sumY += static_cast<int>(pixel * y_kernel[ky + 1][kx + 1]);
				}
			}
			// 그레디언트의 크기 계산
			int magnitude = static_cast<int>(sqrt(sumX * sumX + sumY * sumY));
			magnitude = magnitude > 255 ? 255 : magnitude; // 0-255로 클램핑
			dstData[y * width + x] = magnitude; 

			minvalue = min(minvalue, dstData[y * width + x]);
			maxvalue = max(maxvalue, dstData[y * width + x]);
		}
	}
	dst.SetMinValue(minvalue);
	dst.SetMaxValue(maxvalue);
	return true;
}

bool ImageProcessing::DrawContours(Mat& src, Mat& dst, vector<vector<Point_>>& contours)
{
	if (src.isEmpty())
		return false;

	int width = src.GetWidth();
	dst = src.Copy();
	auto& dstData = dst.getData();

	for (const auto& contour : contours) {
		for (const auto& point : contour) {
			int x = point.x;
			int y = point.y;
			dstData[y * width + x] = 128;  // 8bit에서 컨투어를 표현하기 위한 숫자
		}
	}
	return true;
}

bool ImageProcessing::ResizeContours(vector<vector<Point_>>& contours, double ratio)
{
	if (ratio <= 0)
		return false;

	for (auto& contour : contours) {
		for (auto& point : contour) {
			point.x = static_cast<int>(point.x * ratio);
			point.y = static_cast<int>(point.y * ratio);
		}
	}
	return true;
}