#pragma once
#include <vector>
#include <algorithm>
#include "afxwin.h"

typedef struct Point_ {
	int x;
	int y;
	Point_(int x = 0, int y = 0) : x(x), y(y) {} // 생성자
};
///<summary>
/// 1채널 16비트, 1채널 8비트 이미지만 저장이 가능
///</summary>
class Mat
{
public:
	Mat(const CString & filePath);
	Mat();
	~Mat();
	Mat(int width, int height, int filetype);
	
	bool loadRaw(const CString& filePath);   // 16비트 unsigned 1채널만 인풋으로 고려함
	bool loadBitmap(const CString& filePath); // 24비트 BGR 불러와서 8비트로 저장
	void Convert_to_CImage(CImage& out); 
	bool ImgSave(CString path, Mat& src);
	unsigned char LinearScale_U16toU8(uint16_t in_byte, int min, int max); // 16비트 픽셀값을 0 ~ 255 범위로 정규화함

	Mat Copy();
	bool isEmpty();
	unsigned char at(int x, int y) const; // 16비트는 작동x
	bool isValid(int x, int y) const;
	// get & set
	int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }
	//int GetChannels() { return m_channels; }
	int GetbitDepth() { return m_bitDepth; }
	int GetMinValue() { return m_minvalue; }
	int GetMaxValue() { return m_maxvalue; }
	std::vector<uint16_t>& getData() { return m_data; }
	void SetMinValue(int minvalue) { this->m_minvalue = minvalue; }
	void SetMaxValue(int maxvalue) { this->m_maxvalue = maxvalue; }



private:
	int m_width;
	int m_height;
	//int m_channels;
	int m_bitDepth;
	int m_minvalue; // 이미지를 히스토그램으로 나타냈을 때 최소값
	int m_maxvalue; // 이미지를 히스토그램으로 나타냈을 때 최대값
	std::vector<uint16_t> m_data; // 픽셀 데이터를 저장할 벡터
};

