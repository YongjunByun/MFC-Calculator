#pragma once
#include <vector>
#include "afxwin.h"
enum class enum_COLOR{
	GRAY2BGR, BGR2GRAY
};
enum class enum_ImageType {
	GRAYSCALE16, GRAYSCALE8, BGR8C3
};
class Mat
{
private:
	int m_width;
	int m_height;
	int m_channels;
	std::vector<unsigned char> data;  // 픽셀 데이터를 저장할 벡터

public:
	Mat(const CString & filePath);
	Mat();
	~Mat();
	Mat(int width, int height, int channels);
	void loadRaw(const CString& filePath);   // RAW 파일 불러오기 함수 (16비트 unsigned 1채널) 
	void loadBitmap(const CString& filePath); // BMP 파일 불러오기 함수 (24비트 BGR 거꾸로되어있음)
	void Convert_to_CImage(CImage& out);
	void CvtColor(Mat& input, Mat& output, enum_COLOR color);
	void ImgSave(CString path);
	unsigned char* getData() { return data.data(); } // 데이터에 접근하는 함수

};

