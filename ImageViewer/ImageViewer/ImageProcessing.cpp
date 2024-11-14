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

	int minvalue = SIZE_UINT16;
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

	int minvalue = SIZE_UINT16;
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

	int minvalue = SIZE_UINT16;
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

bool ImageProcessing::Binarization(Mat & src, Mat & dst, int threshold)
{
	if (src.isEmpty()) 
		return false; 

	int width = src.GetWidth();
	int height = src.GetHeight();
	int bitDepth = src.GetbitDepth();

	int maxThreshold = (bitDepth == 8) ? 255 : SIZE_UINT16;
	if (threshold < 0 || threshold > maxThreshold) 
		return false;

	dst = src.Copy();
	const auto& srcData = src.getData();
	auto& dstData = dst.getData();

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int index = y * width + x;
			if(bitDepth == 8) 
				dstData[index] = (srcData[index] >= threshold) ? 255 : 0;
			else 
				dstData[index] = (srcData[index] >= threshold) ? 65535 : 0;
		}
	}
	dst.SetMinValue(0);
	dst.SetMaxValue(maxThreshold);
	return true;
}

bool ImageProcessing::Contours(Mat& binary_img, vector<vector<Point_>>& contours) {
	int width = binary_img.GetWidth();
	int height = binary_img.GetHeight();
	std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

	// 방향 벡터 (상, 하, 좌, 우, 대각선 포함)
	const int dx[8] = { 1, -1, 0, 0, 1, 1, -1, -1 };
	const int dy[8] = { 0, 0, 1, -1, 1, -1, 1, -1 };

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			// 이진 이미지에서 윤곽선 시작 위치: 픽셀 값이 255(흰색)이고 방문하지 않은 경우
			if (binary_img.at(x, y) == 255 && !visited[y][x]) {
				std::vector<Point_> contour;
				std::queue<Point_> q;
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
						if (!binary_img.isValid(nx, ny) || binary_img.at(nx, ny) == 0) {
							isEdge = true;
						}
						else if (binary_img.at(nx, ny) == 255 && !visited[ny][nx]) {
							visited[ny][nx] = true;
							q.push(Point_(nx, ny));
						}
					}

					// 가장자리에 해당하는 픽셀만 contour에 추가
					if (isEdge) {
						contour.push_back(p);
					}
				}

				// 검출된 윤곽선 추가
				if (!contour.empty()) {
					contours.push_back(contour);
				}
			}
		}
	}
	return !contours.empty();
}