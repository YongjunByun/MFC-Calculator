#include "stdafx.h"
#include "Mat.h"

Mat::Mat(const CString& filePath)
{
	CString temp;
	AfxExtractSubString(temp, filePath, 1, '.');
	int isLoadSuccess = false;
	if(temp == L"BMP" || temp == L"bmp")
		isLoadSuccess = loadBitmap(filePath);
	else 
		isLoadSuccess = loadRaw(filePath);

	if (isLoadSuccess == false)
		throw std::exception("FAILED TO READ\n\n�ҷ��� �� �ִ� �̹��� ���� :\nRGB Bitmap | 16bit Unsinged Raw");
}
Mat::Mat()
{
}
Mat::~Mat()
{
}
Mat::Mat(int width, int height, int bitDepth)
{
	m_width = width;
	m_height = height;
	m_bitDepth = bitDepth;
	m_data.resize(m_width * m_height);
}

bool Mat::loadRaw(const CString & filePath)
{
	// �̹��� ũ�� ���ڿ� �Ľ��ؼ� �˾Ƴ�
	CString temp, w, h;
	AfxExtractSubString(temp, filePath, 1, '_');
	AfxExtractSubString(temp, temp, 0, '.');
	AfxExtractSubString(w, temp, 0, 'x');
	AfxExtractSubString(h, temp, 1, 'x');
	m_width = _ttoi(w);
	m_height = _ttoi(h);
	m_bitDepth = 16;

	m_data.resize(m_width * m_height);

	std::ifstream file(filePath, std::ios::binary);

	file.seekg(0, std::ios::end);
	int fileSize = static_cast<int>(file.tellg());
	file.seekg(0, std::ios::beg); // ���� �����͸� ó������ �̵�
	if (fileSize != m_width * m_height * 2) {
		//return false;
		AfxMessageBox(L"Warning\n�̹��� ������� ���μ��� ũ�Ⱑ ���� �ʽ��ϴ�!");
	}

	file.read(reinterpret_cast<char*>(m_data.data()), m_data.size() * sizeof(uint16_t));
	m_minvalue = *std::min_element(m_data.begin(), m_data.end());
	m_maxvalue = *std::max_element(m_data.begin(), m_data.end());
	file.close();

	return true;
}

bool Mat::loadBitmap(const CString& filePath)
{
	std::ifstream file(filePath, std::ios::binary);
	if (!file.is_open())
		return false;

	// ��Ʈ�� ���
	unsigned char bmpFileHeader[14]; 
	file.read(reinterpret_cast<char*>(bmpFileHeader), 14);
	unsigned char bmpInfoHeader[40];
	file.read(reinterpret_cast<char*>(bmpInfoHeader), 40);

	m_width = *reinterpret_cast<int*>(&bmpInfoHeader[4]);
	m_height = *reinterpret_cast<int*>(&bmpInfoHeader[8]);
	int bitDepth = *reinterpret_cast<short*>(&bmpInfoHeader[14]);

	if (bitDepth != 24) {
		file.close();
		return false;
	}
	m_bitDepth = 8;
	int dataOffset = *reinterpret_cast<int*>(&bmpFileHeader[10]);

	file.seekg(dataOffset, std::ios::beg); // ���� �����͸� ó������ �̵�
	m_data.resize(m_width * m_height); // 1ä�� �̹����� ����

	int rowSize = ((m_width * 3 + 3) & (~3)); // �� ���� 4����Ʈ�� ����� �ǵ��� �е� ó��
	std::vector<unsigned char> rowData(rowSize); // �� ���� �����͸� �ӽ÷� ������ ����

	for (int y = 0; y < m_height; ++y)
	{
		file.read(reinterpret_cast<char*>(rowData.data()), rowSize);

		// BMP�� �ϴܺ��� ��� ������ ����ǹǷ�, y ���� �Ųٷ� ���
		int invertedY = m_height - 1 - y;

		for (int x = 0; x < m_width; ++x)
		{
			unsigned char blue = rowData[x * 3];
			unsigned char green = rowData[x * 3 + 1];
			unsigned char red = rowData[x * 3 + 2];
			uint16_t grayValue = static_cast<uint16_t>(0.299 * red + 0.587 * green + 0.114 * blue);
			
			m_data[invertedY * m_width + x] = grayValue;
		}
	}
	m_minvalue = *std::min_element(m_data.begin(), m_data.end());
	m_maxvalue = *std::max_element(m_data.begin(), m_data.end());
	file.close();
	return true;
}

void Mat::Convert_to_CImage(CImage& out)
{
	out.Create(m_width, m_height, 24);  // 24��Ʈ �÷� �̹���

	unsigned char* pImageData = reinterpret_cast<unsigned char*>(out.GetBits()); // CImage ������ ������ ���
	int imagePitch = out.GetPitch();

	for (int y = 0; y < m_height; ++y) {
		unsigned char* pDstRow = pImageData + y * imagePitch;
		const uint16_t* pSrcRow = m_data.data() + y * m_width;

		for (int x = 0; x < m_width; ++x) {
			if (m_bitDepth == 8) {
				unsigned char gray = static_cast<unsigned char>(pSrcRow[x]);
				pDstRow[x * 3 + 0] = gray; // Blue
				pDstRow[x * 3 + 1] = gray; // Green
				pDstRow[x * 3 + 2] = gray; // Red
			}
			else {
				uint16_t value = pSrcRow[x];
				unsigned char gray = LinearScale_U16toU8(value, m_minvalue, m_maxvalue);
				pDstRow[x * 3 + 0] = gray; // Blue
				pDstRow[x * 3 + 1] = gray; // Green
				pDstRow[x * 3 + 2] = gray; // Red
			}
		}
	}
}

bool Mat::ImgSave(CString path, Mat& src)
{
	CString extension = path.Right(3).MakeLower();

	if (extension == L"bmp") {
		std::ofstream outputFile(CT2A(path), std::ios::binary);
		if (!outputFile) {
			return false;
		}

		uint16_t fileType = 0x4D42; // 'BM' ��ũ
		uint32_t fileSize = 54 + src.m_data.size(); // ���� ��ü ũ�� (54����Ʈ�� ��� + �̹��� ������ ũ��)
		uint32_t reserved = 0; // ����� ��
		uint32_t offsetData = 54; // �ȼ� �������� ���� ��ġ (��� ũ��)

		uint32_t infoHeaderSize = 40; // BITMAPINFOHEADER�� ���� ũ��
		int32_t width = src.m_width;
		int32_t height = src.m_height;
		uint16_t planes = 1; // �׻� 1�� ����
		uint16_t bitCount = 3 * 8; // �׻� 3ä�η� ����
		uint32_t compression = 0; // ���� ����
		uint32_t imageSize = src.m_data.size(); // �̹��� ������ ũ��
		int32_t xPixelsPerMeter = 0, yPixelsPerMeter = 0;
		uint32_t colorsUsed = 0, colorsImportant = 0;

		// ���� ��� ����
		outputFile.write(reinterpret_cast<const char*>(&fileType), sizeof(fileType));
		outputFile.write(reinterpret_cast<const char*>(&fileSize), sizeof(fileSize));
		outputFile.write(reinterpret_cast<const char*>(&reserved), sizeof(reserved));
		outputFile.write(reinterpret_cast<const char*>(&offsetData), sizeof(offsetData));

		outputFile.write(reinterpret_cast<const char*>(&infoHeaderSize), sizeof(infoHeaderSize));
		outputFile.write(reinterpret_cast<const char*>(&width), sizeof(width));
		outputFile.write(reinterpret_cast<const char*>(&height), sizeof(height));
		outputFile.write(reinterpret_cast<const char*>(&planes), sizeof(planes));
		outputFile.write(reinterpret_cast<const char*>(&bitCount), sizeof(bitCount));
		outputFile.write(reinterpret_cast<const char*>(&compression), sizeof(compression));
		outputFile.write(reinterpret_cast<const char*>(&imageSize), sizeof(imageSize));
		outputFile.write(reinterpret_cast<const char*>(&xPixelsPerMeter), sizeof(xPixelsPerMeter));
		outputFile.write(reinterpret_cast<const char*>(&yPixelsPerMeter), sizeof(yPixelsPerMeter));
		outputFile.write(reinterpret_cast<const char*>(&colorsUsed), sizeof(colorsUsed));
		outputFile.write(reinterpret_cast<const char*>(&colorsImportant), sizeof(colorsImportant));

		// �ȼ� ������ ����
		for (int y = height - 1; y >= 0; --y) {  // BMP ������ �Ʒ����� ���� ����
			for (int x = 0; x < width; ++x) {
				
				if (src.GetbitDepth() == 8) {
					uint8_t grayValue = static_cast<uint8_t>(src.m_data[y * width + x]);  // ���� �׷��̽����� �� ��������
					uint8_t rgb[3] = { grayValue, grayValue, grayValue };  // RGB ä�ο� ������ �� �Ҵ� (24��Ʈ)
					outputFile.write(reinterpret_cast<const char*>(rgb), sizeof(rgb));  // RGB 3ä�� ������ ����
				}
				else {
					uint16_t grayValue = src.m_data[y * width + x];
					uint8_t scaled = src.LinearScale_U16toU8(grayValue, src.GetMinValue(), src.GetMaxValue());
					uint8_t rgb[3] = { scaled, scaled, scaled };
					outputFile.write(reinterpret_cast<const char*>(rgb), sizeof(rgb)); 
				}
				
			}
		}
		outputFile.close();
	}
	else if (extension == L"raw") {
		std::ofstream outputFile(CT2A(path), std::ios::binary);
		if (!outputFile) {
			return false;
		}

		// RAW ���Ͽ� ���� �ȼ� �����͸� ����
		outputFile.write(reinterpret_cast<const char*>(src.m_data.data()), src.m_data.size() * sizeof(uint16_t));
		outputFile.close();
	}
	return true;
}

unsigned char Mat::LinearScale_U16toU8(uint16_t in_byte, int min, int max) {
	if (min == max) // division by zero ����ó��
		return max;
	unsigned char scaledValue = static_cast<unsigned char>(255 * (in_byte - min) / (max - min));
	return scaledValue;
}

Mat Mat::Copy()
{
	Mat copy(m_width, m_height, m_bitDepth);  // �� Mat ��ü ����
	copy.m_data = m_data;  // �ȼ� ������ ���� ����
	copy.m_maxvalue = m_maxvalue;
	copy.m_minvalue = m_minvalue;
	return copy;
}

bool Mat::isEmpty()
{
	if (m_data.size() == 0)
		return true;
	return false;
}

unsigned char Mat::at(int x, int y) const
{
	return static_cast<unsigned char>(m_data[y * m_width + x]); 
}

bool Mat::isValid(int x, int y) const
{
	return x >= 0 && x < m_width && y >= 0 && y < m_height;
}

