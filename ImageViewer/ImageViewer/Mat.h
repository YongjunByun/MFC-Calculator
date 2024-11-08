#pragma once
class Mat
{
private:
	int m_width;
	int m_height;
	int m_channels;
	void *data;

public:
	Mat();
	~Mat();
};

