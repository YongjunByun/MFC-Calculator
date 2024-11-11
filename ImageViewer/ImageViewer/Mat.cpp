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

	// BMP ���� ��� �б�
	unsigned char bmpFileHeader[14];
	file.read(reinterpret_cast<char*>(bmpFileHeader), 14);

	unsigned char bmpInfoHeader[40];
	file.read(reinterpret_cast<char*>(bmpInfoHeader), 40);

	// �̹��� ũ��� ä�� �� ����
	m_width = *reinterpret_cast<int*>(&bmpInfoHeader[4]);
	m_height = *reinterpret_cast<int*>(&bmpInfoHeader[8]);
	m_channels = 3;  // 24��Ʈ BMP ������ RGB 3ä��

					 // BMP ������ ũ�⿡ �°� data ũ�� ����
	data.resize(m_width * m_height * m_channels);

	// BMP ������ ������ ������ ���
	int offset = *reinterpret_cast<int*>(&bmpFileHeader[10]);
	file.seekg(offset, std::ios::beg);

	// ���� �����͸� �о� data�� ���� (BMP ������ ���� �����̹Ƿ� �Ʒ����� ����)
	for (int y = m_height - 1; y >= 0; y--)
	{
		file.read(reinterpret_cast<char*>(data.data() + y * m_width * m_channels), m_width * m_channels);
	}

	file.close();
}

void Mat::Convert_to_CImage(CImage& out)
{
	// CImage�� 24��Ʈ ��Ʈ������ ���� (3ä�� RGB)
	out.Create(m_width, m_height, 24);

	// CImage ������ ���ۿ� ����
	unsigned char* pImageData = reinterpret_cast<unsigned char*>(out.GetBits());
	int imagePitch = out.GetPitch();
	// Mat�� �����Ϳ��� CImage�� ����
	for (int y = 0; y < m_height; ++y)
	{
		unsigned char* pImageRow = pImageData + y * imagePitch;  // CImage�� �ش� �� ���� ��ġ
		unsigned char* pMatRow = data.data() + y * m_width * m_channels;  // Mat�� �ش� �� ���� ��ġ

																		  // ���� �� �ȼ� ����
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
				grayscaleData[y * m_width + x] = gray; // �׷��̽����� ������ ����
			}
		}

		// �׷��̽����� �����ͷ� ������Ʈ (1ä�η� ��ȯ)
		output.data = grayscaleData;
		output.m_channels = 1;
	}
	else if (color == enum_COLOR::GRAY2BGR) {

	}
}

void Mat::ImgSave(CString path)
{

}
