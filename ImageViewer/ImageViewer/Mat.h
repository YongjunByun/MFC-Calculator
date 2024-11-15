#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include "afxwin.h"

typedef struct Point_ {
	int x;
	int y;
	Point_(int x = 0, int y = 0) : x(x), y(y) {} // ������
} Point_;

///<summary>
/// 1ä�� 16��Ʈ, 1ä�� 8��Ʈ �̹����� ������ ����
///</summary>
class Mat
{
public:
	Mat(const CString & filePath);
	Mat();
	~Mat();
	Mat(int width, int height, int filetype);
	
	bool loadRaw(const CString& filePath);   // 16��Ʈ unsigned 1ä�θ� ��ǲ���� �����
	bool loadBitmap(const CString& filePath); // 24��Ʈ BGR �ҷ��ͼ� 8��Ʈ�� ����
	void Convert_to_CImage(CImage& out); // 8bit ,16bit �׷��̽����� �̹����� 24RGB CImage�� �ٲ�
	bool ImgSave(CString path, Mat& src);
	unsigned char LinearScale_U16toU8(uint16_t in_byte, int min, int max); // 16��Ʈ �ȼ����� 0 ~ 255 ������ ����ȭ��
	Mat Copy();
	bool isEmpty();
	unsigned char at(int x, int y) const; // 16��Ʈ�� �۵�x
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
	int m_minvalue; // �̹��� �� �ȼ� �ּҰ�
	int m_maxvalue; // �̹��� �� �ȼ� �ִ밪
	std::vector<uint16_t> m_data; // �ȼ� �����͸� ������ ����
};

