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
	// ����һ��ͼƬ��poyanghu��Сͼ��    
	Mat SrcImg = imread("Test1.JPG", IMREAD_GRAYSCALE);
	//Mat SrcImg = imread("Test1.JPG");
	namedWindow("ͼƬ");

	// �ڴ�������ʾͼƬ   
	imshow("ͼƬ", SrcImg);
	// �ȴ�6000 ms�󴰿��Զ��ر� 



	CNoise m_Noise(SrcImg);
	Mat GaussionNoiseImage=m_Noise.getGaussionNoiseImage(2, 0.8);
	Mat SaltNoiseImage = m_Noise.getSaltPepperNoiseImage(2000);
	imshow("��������ͼƬ", SaltNoiseImage);
	MyImage GaussionData;
	GaussionData.getData(GaussionNoiseImage);
	MyImage SaltData;
	SaltData.getData(SaltNoiseImage);
	MyImage SrcData;
	SrcData.getData(SrcImg);

	

	std::cout << "��˹����ͼƬSNR: " << m_Noise.computeSNR(SrcData, GaussionData) << std::endl;
	std::cout << "��������ͼƬSNR: " << m_Noise.computeSNR(SrcData, SaltData) << std::endl;
	imshow("��˹����ͼƬ",GaussionNoiseImage);
	MyImage m_MyImage;
	m_MyImage.getData(SrcImg);
	imshow("MyImageToMat", m_MyImage.transToMat(SrcImg));
	CHarrWavelet m_HarrWavelet;
	Threshold MyThreshold;

	MyImage FirstLevelRowWave = m_HarrWavelet.waveletRowTransform(m_MyImage);
	//imshow("�зֽ�", FirstLevelRowWave.transToMat(SrcImg));
	MyImage FirstLevelColumnWave = m_HarrWavelet.waveletColumnTransform(FirstLevelRowWave);
	//imshow("�зֽ�", FirstLevelColumnWave.transToMat(SrcImg));
	MyImage SecondLevel = m_HarrWavelet.getNextData(FirstLevelColumnWave);
;
	MyImage SecondLevel1 = m_HarrWavelet.waveletTransform(SecondLevel);
	//imshow("1�ֽ�", SecondLevel1.transToMat(SrcImg));
	FirstLevelColumnWave=m_HarrWavelet.update(SecondLevel1, FirstLevelColumnWave);
	//imshow("2��", FirstLevelColumnWave.transToMat(SrcImg));

	MyImage Result = m_HarrWavelet.denoiseImage(GaussionData, 18, 18,false);
	std::cout << "��һ��ȥ��ͼƬSNR: " << m_Noise.computeSNR(SrcData, Result) << std::endl;
	//imshow("��˹������һ��ȥ����", Result.transToMat(SrcImg));
	MyImage Result1 = m_HarrWavelet.denoiseImage(Result, 8, 8,false);
	std::cout << "�ڶ���ȥ��ͼƬSNR: " << m_Noise.computeSNR(SrcData, Result1) << std::endl;
	imshow("��˹����ȥ����", Result1.transToMat(SrcImg));

	MyImage Result3 = m_HarrWavelet.denoiseImage(SaltData, 60, 60, false);
	//imshow("����������һ��ȥ����", Result3.transToMat(SrcImg));
	//std::cout << "��һ�ν���ȥ��ͼƬSNR: " << m_Noise.computeSNR(SrcData, Result3) << std::endl;
	MyImage Result4 = m_HarrWavelet.denoiseImage(Result3, 8, 8, false);
	//std::cout << "�ڶ��ν���ȥ��ͼƬSNR: " << m_Noise.computeSNR(SrcData, Result4) << std::endl;
	imshow("���������ڶ���ȥ����", Result4.transToMat(SrcImg));
	waitKey(60000);

	int c;
	std::cin >> c;
	return 0;
}
