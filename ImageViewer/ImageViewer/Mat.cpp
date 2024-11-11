#include "stdafx.h"
#include "Mat.h"
#include <fstream>

Mat::Mat(const CString& filePath)
{
	loadBitmap(filePath);
}
Mat::Mat()
{
}

Mat::Mat(int width, int height, int channels)
{
	m_width = width;
	m_height = height;
	m_channels = channels;
	data.resize(m_width * m_height * m_channels);
}

void Mat::loadRaw(const CString & filePath)
{
}


Mat::~Mat()
{
}
void Mat::loadBitmap(const CString& filePath)
{
	std::ifstream file(filePath, std::ios::binary);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open BMP file.");
	}

	// BMP 파일 헤더 읽기
	unsigned char bmpFileHeader[14];
	file.read(reinterpret_cast<char*>(bmpFileHeader), 14);

	unsigned char bmpInfoHeader[40];
	file.read(reinterpret_cast<char*>(bmpInfoHeader), 40);

	// 이미지 크기와 채널 수 설정
	m_width = *reinterpret_cast<int*>(&bmpInfoHeader[4]);
	m_height = *reinterpret_cast<int*>(&bmpInfoHeader[8]);
	m_channels = 3;  // 24비트 BMP 파일은 RGB 3채널

					 // BMP 데이터 크기에 맞게 data 크기 설정
	data.resize(m_width * m_height * m_channels);

	// BMP 파일의 데이터 오프셋 계산
	int offset = *reinterpret_cast<int*>(&bmpFileHeader[10]);
	file.seekg(offset, std::ios::beg);

	// 파일 데이터를 읽어 data에 저장 (BMP 파일은 상하 반전이므로 아래부터 읽음)
	for (int y = m_height - 1; y >= 0; y--)
	{
		file.read(reinterpret_cast<char*>(data.data() + y * m_width * m_channels), m_width * m_channels);
	}

	file.close();
}

void Mat::Convert_to_CImage(CImage& out)
{
	// CImage를 24비트 비트맵으로 생성 (3채널 RGB)
	out.Create(m_width, m_height, 24);

	// CImage 데이터 버퍼에 접근
	unsigned char* pImageData = reinterpret_cast<unsigned char*>(out.GetBits());
	int imagePitch = out.GetPitch();
	// Mat의 데이터에서 CImage로 복사
	for (int y = 0; y < m_height; ++y)
	{
		unsigned char* pImageRow = pImageData + y * imagePitch;  // CImage의 해당 행 시작 위치
		unsigned char* pMatRow = data.data() + y * m_width * m_channels;  // Mat의 해당 행 시작 위치

																		  // 행의 각 픽셀 복사
		for (int x = 0; x < m_width; ++x)
		{
			pImageRow[x * 3 + 2] = pMatRow[x * m_channels + 2]; // B
			pImageRow[x * 3 + 1] = pMatRow[x * m_channels + 1]; // G
			pImageRow[x * 3 + 0] = pMatRow[x * m_channels + 0]; // R
		}
	}
}

void Mat::CvtColor(Mat & input, Mat & output, enum_COLOR color)
{
	if (color == enum_COLOR::BGR2GRAY) {
		if (input.m_channels < 3) return;

		std::vector<unsigned char> grayscaleData(m_width * m_height);

		for (int y = 0; y < m_height; ++y)
		{
			for (int x = 0; x < m_width; ++x)
			{
				int index = (y * m_width + x) * m_channels;
				unsigned char r = data[index + 2]; // R
				unsigned char g = data[index + 1]; // G
				unsigned char b = data[index + 0]; // B

				unsigned char gray = static_cast<unsigned char>(0.299 * r + 0.587 * g + 0.114 * b);
				grayscaleData[y * m_width + x] = gray; // 그레이스케일 데이터 저장
			}
		}

		// 그레이스케일 데이터로 업데이트 (1채널로 변환)
		output.data = grayscaleData;
		output.m_channels = 1;
	}
	else if (color == enum_COLOR::GRAY2BGR) {

	}
}

void Mat::ImgSave(CString path)
{

}
