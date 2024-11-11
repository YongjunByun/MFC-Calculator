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
	std::vector<unsigned char> data;  // �ȼ� �����͸� ������ ����

public:
	Mat(const CString & filePath);
	Mat();
	~Mat();
	Mat(int width, int height, int channels);
	void loadRaw(const CString& filePath);   // RAW ���� �ҷ����� �Լ� (16��Ʈ unsigned 1ä��) 
	void loadBitmap(const CString& filePath); // BMP ���� �ҷ����� �Լ� (24��Ʈ BGR �ŲٷεǾ�����)
	void Convert_to_CImage(CImage& out);
	void CvtColor(Mat& input, Mat& output, enum_COLOR color);
	void ImgSave(CString path);
	unsigned char* getData() { return data.data(); } // �����Ϳ� �����ϴ� �Լ�

};

