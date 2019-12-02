#pragma once
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>
#include "HarrWavelet.h"
using namespace cv;

class CNoise
{
public:
	CNoise(const char* vImageFilePath);
	CNoise(Mat &vSrcImage);
	Mat getGaussionNoiseImage(double vMu,double vSigma);// 2 0.8
	Mat getSaltPepperNoiseImage(int vNumber);
	double computeSNR(MyImage& vOriginalImage, MyImage& vTestImage);
private:
	Mat SrcImage;
	double generateGaussianNoise(double m, double sigma);
	Mat addGaussianNoise(double vMu, double vSigma);
	
};