#pragma once
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp> 
using namespace cv;

class MyImage
{
public:
	int Width;
	int Height;
	std::vector<std::vector<double>> Data;

	Mat transToMat(Mat& voImage);
	void getData(Mat& vSrcImage);
};

class Threshold
{
public:
	MyImage processedWithHard(MyImage& vSrcImage,double vVariance);
	MyImage processedWithSoft(MyImage& vSrcImage,double vVariance);
};


class CHarrWavelet
{
public:
	//CHarrWavelet(MyImage &vSrcImage);
	MyImage waveletTransform(MyImage &vSrcImage);
	MyImage inverWaveletTransform(MyImage &vSrcImage);

	MyImage m_SrcImage;
	Threshold m_Threshold;
	MyImage waveletRowTransform(MyImage& vSrcImage);
	MyImage waveletColumnTransform(MyImage& vSrcImage);
	MyImage estiMyImageeThreshlod();
	MyImage inverWaveletRowTransform(MyImage& vSrcImage);
	MyImage inverWaveletColumnTransform(MyImage& vSrcImage);
	MyImage getNextData(MyImage& vSrcImage);
	MyImage update(MyImage& vNextImage, MyImage& vOriginalImage);
	MyImage denoiseImage(MyImage& vSrcImage, double vThreshold1, double vThreshold2,bool vIsHard);
};