#pragma once
class ImageProcessing
{
public:
	ImageProcessing();
	~ImageProcessing();
	
	static bool RotateImage();
	static bool FlipImage();
	static bool ResizeImage();
	static bool GaussianBlur();
	static bool MedianBlur();
	static bool BGADetection();

	
protected:

private:


};

