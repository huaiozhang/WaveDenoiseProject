#include<cmath>
#include<climits>
#include<cstdlib>
#include <iostream>  
#include "Noise.h" 
#include"HarrWavelet.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

int main()
{
	// 读入一张图片（poyanghu缩小图）    
	Mat SrcImg = imread("Test1.JPG", IMREAD_GRAYSCALE);
	//Mat SrcImg = imread("Test1.JPG");
	namedWindow("图片");

	// 在窗口中显示图片   
	imshow("图片", SrcImg);
	// 等待6000 ms后窗口自动关闭 



	CNoise m_Noise(SrcImg);
	Mat GaussionNoiseImage=m_Noise.getGaussionNoiseImage(2, 0.8);
	Mat SaltNoiseImage = m_Noise.getSaltPepperNoiseImage(2000);
	imshow("椒盐噪声图片", SaltNoiseImage);
	MyImage GaussionData;
	GaussionData.getData(GaussionNoiseImage);
	MyImage SaltData;
	SaltData.getData(SaltNoiseImage);
	MyImage SrcData;
	SrcData.getData(SrcImg);

	

	std::cout << "高斯噪声图片SNR: " << m_Noise.computeSNR(SrcData, GaussionData) << std::endl;
	std::cout << "椒盐噪声图片SNR: " << m_Noise.computeSNR(SrcData, SaltData) << std::endl;
	imshow("高斯噪声图片",GaussionNoiseImage);
	MyImage m_MyImage;
	m_MyImage.getData(SrcImg);
	imshow("MyImageToMat", m_MyImage.transToMat(SrcImg));
	CHarrWavelet m_HarrWavelet;
	Threshold MyThreshold;

	MyImage FirstLevelRowWave = m_HarrWavelet.waveletRowTransform(m_MyImage);
	//imshow("行分解", FirstLevelRowWave.transToMat(SrcImg));
	MyImage FirstLevelColumnWave = m_HarrWavelet.waveletColumnTransform(FirstLevelRowWave);
	//imshow("列分解", FirstLevelColumnWave.transToMat(SrcImg));
	MyImage SecondLevel = m_HarrWavelet.getNextData(FirstLevelColumnWave);
;
	MyImage SecondLevel1 = m_HarrWavelet.waveletTransform(SecondLevel);
	//imshow("1分解", SecondLevel1.transToMat(SrcImg));
	FirstLevelColumnWave=m_HarrWavelet.update(SecondLevel1, FirstLevelColumnWave);
	//imshow("2层", FirstLevelColumnWave.transToMat(SrcImg));

	MyImage Result = m_HarrWavelet.denoiseImage(GaussionData, 18, 18,false);
	std::cout << "第一次去噪图片SNR: " << m_Noise.computeSNR(SrcData, Result) << std::endl;
	//imshow("高斯噪声第一次去噪结果", Result.transToMat(SrcImg));
	MyImage Result1 = m_HarrWavelet.denoiseImage(Result, 8, 8,false);
	std::cout << "第二次去噪图片SNR: " << m_Noise.computeSNR(SrcData, Result1) << std::endl;
	imshow("高斯噪声去噪结果", Result1.transToMat(SrcImg));

	MyImage Result3 = m_HarrWavelet.denoiseImage(SaltData, 60, 60, false);
	//imshow("椒盐噪声第一次去噪结果", Result3.transToMat(SrcImg));
	//std::cout << "第一次椒盐去噪图片SNR: " << m_Noise.computeSNR(SrcData, Result3) << std::endl;
	MyImage Result4 = m_HarrWavelet.denoiseImage(Result3, 8, 8, false);
	//std::cout << "第二次椒盐去噪图片SNR: " << m_Noise.computeSNR(SrcData, Result4) << std::endl;
	imshow("椒盐噪声第二次去噪结果", Result4.transToMat(SrcImg));
	waitKey(60000);

	int c;
	std::cin >> c;
	return 0;
}
