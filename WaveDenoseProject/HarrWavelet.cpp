#pragma once
//#include<iostream>
#include "HarrWavelet.h"

//CHarrWavelet::CHarrWavelet(MyImage &vSrcImage)
//{
//	m_SrcImage = vSrcImage.clone();
//}

Mat MyImage::transToMat(Mat& voImage)
{
	Mat Image=voImage.clone();

	for (int i = 0; i < Height; i++)
	{
		for (int k = 0; k < Width; k++)
		{
			Image.ptr<uchar>(i)[k] = (Data[i][k]+0.5);
		}
	}
	return Image;
}

void MyImage::getData(Mat& vSrcImage)
{
	Height = vSrcImage.rows;
	Width = vSrcImage.cols*vSrcImage.channels();
	Data.resize(Height);
	for (int i = 0; i < Height; i++)
	{
		Data[i].resize(Width);
	}

	for (int i = 0; i < Height; i++)
	{
		for (int k = 0; k < Width; k++)
		{
			Data[i][k] = vSrcImage.ptr<uchar>(i)[k];
		}
	}
}

MyImage Threshold::processedWithHard(MyImage& vSrcImage,double vVariance)
{
	MyImage Image;
	Image.Height = vSrcImage.Height;
	Image.Width = vSrcImage.Width;
	Image.Data = vSrcImage.Data;
	double Threshold =vVariance;
	int HalfHeight = Image.Height / 2;
	int HalfWidth = Image.Width / 2;

	for (int i = 0; i < HalfHeight; i++)
	{
		for (int j = HalfWidth; j < Image.Width; j++)
		{
			int Temp = vSrcImage.Data[i][j];
			if (Temp < 0)
				Image.Data[i][j] = -Image.Data[i][j];

			if (vSrcImage.Data[i][j] < Threshold)
				Image.Data[i][j] = 0;
		/*	else
				Image.Data[i][j] = Threshold;*/
			if (Temp < 0)
				Image.Data[i][j] = -Image.Data[i][j];
		}
	}
	for (int i = HalfHeight; i < Image.Height; i++)
	{
		for (int j = 0; j < HalfWidth; j++)
		{
			int Temp = vSrcImage.Data[i][j];
			if (Temp < 0)
				Image.Data[i][j] = -Image.Data[i][j];

			if (vSrcImage.Data[i][j] < Threshold)
				Image.Data[i][j] = 0;
			/*else
				Image.Data[i][j] = Threshold;*/
			if (Temp < 0)
				Image.Data[i][j] = -Image.Data[i][j];
		}
	}
	for (int i = HalfHeight; i < Image.Height; i++)
	{
		for (int j = HalfWidth; j < Image.Width; j++)
		{
			int Temp = vSrcImage.Data[i][j];
			if (Temp < 0)
				Image.Data[i][j] = -Image.Data[i][j];

			if (vSrcImage.Data[i][j] < Threshold)
				Image.Data[i][j] = 0;
			else
				Image.Data[i][j] = Threshold;
			if (Temp < 0)
				Image.Data[i][j] = -Image.Data[i][j];
		}
	}
	return Image;
}

MyImage Threshold::processedWithSoft(MyImage& vSrcImage,double vVariance)
{
	MyImage Image;

	Image.Height = vSrcImage.Height;
	Image.Width = vSrcImage.Width;
	Image.Data = vSrcImage.Data;
	double Threshold = vVariance;
	int HalfHeight = Image.Height / 2;
	int HalfWidth = Image.Width / 2;

	for (int i = 0; i < HalfHeight; i++)
	{
		for (int j = HalfWidth; j < Image.Width; j++)
		{
			int Temp = vSrcImage.Data[i][j];
			if (Temp < 0)
				Image.Data[i][j] = -Image.Data[i][j];

			if (vSrcImage.Data[i][j] < Threshold)
				Image.Data[i][j] = 0;
			else
					Image.Data[i][j] -= Threshold;
			if (Temp < 0)
				Image.Data[i][j] = -Image.Data[i][j];
		}
	}
	for (int i = HalfHeight; i < Image.Height; i++)
	{
		for (int j = 0; j < HalfWidth; j++)
		{
			int Temp = vSrcImage.Data[i][j];
			if (Temp < 0)
				Image.Data[i][j] = -Image.Data[i][j];

			if (vSrcImage.Data[i][j] < Threshold)
				Image.Data[i][j] = 0;
			else
				Image.Data[i][j] -= Threshold;
			if (Temp < 0)
				Image.Data[i][j] = -Image.Data[i][j];
		}
	}
	for (int i = HalfHeight; i < Image.Height; i++)
	{
		for (int j = HalfWidth; j < Image.Width; j++)
		{
			int Temp = vSrcImage.Data[i][j];
			if (Temp < 0)
				Image.Data[i][j] = -Image.Data[i][j];

			if (vSrcImage.Data[i][j] < Threshold)
				Image.Data[i][j] = 0;
			else
				Image.Data[i][j] = Threshold;
			if (Temp < 0)
				Image.Data[i][j] = -Image.Data[i][j];
		}
	}

	return Image;
}

MyImage CHarrWavelet::waveletTransform(MyImage &vSrcImage)
{
	MyImage RowHandledImage = waveletRowTransform(vSrcImage);
	return waveletColumnTransform(RowHandledImage);
}
MyImage CHarrWavelet::waveletRowTransform(MyImage& vSrcImage)
{
	int Height = vSrcImage.Height;
	int Width = vSrcImage.Width;

	MyImage Image;
	Image.Height = Height;
	Image.Width = Width;
	Image.Data.resize(Height);
	for (int i = 0; i < Height; i++)
	{
		Image.Data[i].resize(Width);
	}

	_ASSERT(Width % 2 == 0);
	_ASSERT(Height % 2 == 0);

	int HalfWidth = Width /2;
	for (int i = 0; i < Height; i++)
	{
		for (int k = 0; k < Width; k+=2)
		{
			double FirstValue = vSrcImage.Data[i][k];
			double SecondValue = vSrcImage.Data[i][k + 1];
			int Index = k >> 1;
			Image.Data[i][Index] = (FirstValue + SecondValue) / 2;
			Image.Data[i][Index+HalfWidth] = (FirstValue -SecondValue) / 2;
		}
	}
	return Image;
}
MyImage CHarrWavelet::waveletColumnTransform(MyImage& vSrcImage)
{
	int Height = vSrcImage.Height;
	int Width = vSrcImage.Width;

	MyImage Image;
	Image.Height = Height;
	Image.Width = Width;
	Image.Data.resize(Height);
	for (int i = 0; i < Height; i++)
	{
		Image.Data[i].resize(Width);
	}

	_ASSERT(Width % 2 == 0);
	_ASSERT(Height % 2 == 0);

	int HalfHeight = Height / 2;
	for (int i = 0; i < Height; i+=2)
	{
		for (int k = 0; k < Width; k ++)
		{
			double FirstValue = vSrcImage.Data[i][k];
			double SecondValue = vSrcImage.Data[i+1][k];
			int Index = i >> 1;
			Image.Data[Index][k] = (FirstValue + SecondValue) / 2;
			Image.Data[Index+HalfHeight][k] = (FirstValue - SecondValue) / 2;
		}
	}
	return Image;
}
MyImage CHarrWavelet::estiMyImageeThreshlod()
{
	MyImage a;
	return a;
}

MyImage CHarrWavelet::inverWaveletTransform(MyImage& vSrcImage)
{
	MyImage ColumnHandledImage = inverWaveletColumnTransform(vSrcImage);
	return inverWaveletRowTransform(ColumnHandledImage);
}

MyImage CHarrWavelet::inverWaveletRowTransform(MyImage& vSrcImage)
{
	int Height = vSrcImage.Height;
	int Width = vSrcImage.Width;

	MyImage Image;
	Image.Height = Height;
	Image.Width = Width;
	Image.Data.resize(Height);
	for (int i = 0; i < Height; i++)
	{
		Image.Data[i].resize(Width);
	}

	_ASSERT(Width % 2 == 0);
	_ASSERT(Height % 2 == 0);

	int HalfWidth = Width / 2;
	for (int i = 0; i < Height; i++)
	{
		for (int k = 0; k < HalfWidth; k++)
		{
			double FirstValue = vSrcImage.Data[i][k];
			double SecondValue = vSrcImage.Data[i][k + HalfWidth];
			Image.Data[i][k * 2] = FirstValue + SecondValue;
			Image.Data[i][k * 2 + 1] = FirstValue - SecondValue;
		}
	}
	return Image;
}
MyImage CHarrWavelet::inverWaveletColumnTransform(MyImage& vSrcImage)
{
	int Height = vSrcImage.Height;
	int Width = vSrcImage.Width;

	MyImage Image;
	Image.Height = Height;
	Image.Width = Width;
	Image.Data.resize(Height);
	for (int i = 0; i < Height; i++)
	{
		Image.Data[i].resize(Width);
	}


	_ASSERT(Width % 2 == 0);
	_ASSERT(Height % 2 == 0);

	int HalfHeight = Height / 2;
	for (int i = 0; i < HalfHeight; i++)
	{
		for (int k = 0; k < Width; k++)
		{
			double FirstValue = vSrcImage.Data[i][k];
			double SecondValue = vSrcImage.Data[i + HalfHeight][k];

			Image.Data[i * 2][k] = FirstValue + SecondValue ;
			Image.Data[i * 2 + 1][k] = FirstValue - SecondValue;
		}
	}

	return Image;
}

MyImage CHarrWavelet::getNextData(MyImage& vSrcImage)
{
	MyImage Image;
	Image.Width = vSrcImage.Width/2;
	Image.Height = vSrcImage.Height/2;
	Image.Data.resize(Image.Height);
	for (int i = 0; i < Image.Height; i++)
	{
		Image.Data[i].resize(Image.Width);
	}

	for (int i = 0; i < Image.Height; i++)
	{
		for (int j = 0; j < Image.Width; j++)
		{
			Image.Data[i][j] = vSrcImage.Data[i][j];
		}
	}
	return Image;
}

MyImage CHarrWavelet::update(MyImage& vNextImage,MyImage& vOriginalImage)
{
	MyImage Image;
	Image.Width = vOriginalImage.Width;
	Image.Height = vOriginalImage.Height;
	Image.Data = vOriginalImage.Data;

	for (int i = 0; i < vNextImage.Height; i++)
	{
		for (int j = 0; j < vNextImage.Width; j++)
		{
			Image.Data[i][j] = vNextImage.Data[i][j];
		}
	}
	return Image;
}

MyImage CHarrWavelet::denoiseImage(MyImage& vSrcImage, double vThreshold1, double vThreshold2,bool vIsHard)
{
	MyImage FirstLevelWaveImage = waveletTransform(vSrcImage);
	
	MyImage SecondLevelImage = getNextData(FirstLevelWaveImage);
	MyImage SecondLevelWaveImage = waveletTransform(SecondLevelImage);
	MyImage SecondLevelDenoiseWaveImage;
	if(vIsHard)
	SecondLevelDenoiseWaveImage= m_Threshold.processedWithHard(SecondLevelDenoiseWaveImage, vThreshold2);
	else
		SecondLevelDenoiseWaveImage = m_Threshold.processedWithSoft(SecondLevelDenoiseWaveImage, vThreshold2);
	MyImage SecondLevelInverseWaveImage = inverWaveletTransform(SecondLevelDenoiseWaveImage);

	FirstLevelWaveImage=update(SecondLevelInverseWaveImage, FirstLevelWaveImage);
	MyImage FirstLevelDenoiseWaveImage;
	if (vIsHard)
	FirstLevelDenoiseWaveImage = m_Threshold.processedWithHard(FirstLevelWaveImage, vThreshold1);
	else
		FirstLevelDenoiseWaveImage = m_Threshold.processedWithSoft(FirstLevelWaveImage, vThreshold1);
	MyImage FirstLevelInverseWaveImage = inverWaveletTransform(FirstLevelDenoiseWaveImage);
	return FirstLevelInverseWaveImage;
}
