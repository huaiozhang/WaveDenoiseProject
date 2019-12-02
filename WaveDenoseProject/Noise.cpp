#pragma once
#include "Noise.h"
CNoise::CNoise(const char* vImageFilePath)
{
	SrcImage = imread(vImageFilePath);
}
CNoise::CNoise(Mat &vSrcImage)
{
	SrcImage = vSrcImage.clone();
}
Mat CNoise::getGaussionNoiseImage(double vMu, double vSigma)
{
	return addGaussianNoise(vMu,vSigma);
}

double CNoise::generateGaussianNoise(double vMu, double vSigma)
{
	//定义小值
	const double epsilon = std::numeric_limits<double>::min();
	static double z0, z1;
	static bool flag = false;
	flag = !flag;
	//flag为假构造高斯随机变量X
	if (!flag)
		return z1 * vSigma + vMu;
	double u1, u2;
	//构造随机变量
	do
	{
		u1 = rand() * (1.0 / RAND_MAX);
		u2 = rand() * (1.0 / RAND_MAX);
	} while (u1 <= epsilon);
	//flag为真构造高斯随机变量
	z0 = sqrt(-2.0*log(u1))*cos(2 * CV_PI*u2);
	z1 = sqrt(-2.0*log(u1))*sin(2 * CV_PI*u2);
	return z0 * vSigma + vMu;
}
Mat CNoise::addGaussianNoise(double vMu, double vSigma)
{
	Mat dstImage = SrcImage.clone();
	int channels = dstImage.channels();
	int rowsNumber = dstImage.rows;
	int colsNumber = dstImage.cols*channels;
	//推断图像的连续性
	if (dstImage.isContinuous())
	{
		colsNumber *= rowsNumber;
		rowsNumber = 1;
	}
	for (int i = 0; i < rowsNumber; i++)
	{
		for (int j = 0; j < colsNumber; j++)
		{
			//加入高斯噪声
			int val = dstImage.ptr<uchar>(i)[j] +
				generateGaussianNoise(vMu, vSigma)*32 ;
			if (val < 0)
				val = 0;
			if (val > 255)
				val = 255;
			dstImage.ptr<uchar>(i)[j] = (uchar)val;
		}
	}
	return dstImage;
}

double  CNoise::computeSNR(MyImage& vOriginalImage, MyImage& vTestImage)
{
	double Signal=0.0;
	double Noise=0.0;

	int Height = vOriginalImage.Height;
	int Width = vOriginalImage.Width;

	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			Signal += vTestImage.Data[i][j]*vTestImage.Data[i][j];
			Noise += (vTestImage.Data[i][j] - vOriginalImage.Data[i][j])*(vTestImage.Data[i][j] - vOriginalImage.Data[i][j]);
		}
	}
	double SNR = Signal / Noise;
	SNR = 10 * log10(SNR);
	return SNR;
}	

Mat CNoise::getSaltPepperNoiseImage(int vNumber)
{
	Mat dstImage = SrcImage.clone();
	int channels = dstImage.channels();
	int rowsNumber = dstImage.rows;
	int colsNumber = dstImage.cols*channels;

	for (int i = 0; i < vNumber/2; i++)
	{
		int k = std::rand() % rowsNumber;
		int m = std::rand() % colsNumber;
		dstImage.ptr<uchar>(k)[m] = 255;
	}
	for (int i = 0; i < vNumber / 2; i++)
	{
		int k = std::rand() % rowsNumber;
		int m = std::rand() % colsNumber;
		dstImage.ptr<uchar>(k)[m] = 0;
	}
	return dstImage;
}