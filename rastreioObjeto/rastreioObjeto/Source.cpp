#include <cstdio>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>
#include <opencv\cv.hpp>
using namespace cv;

void main()
{
	std::cout << "OpenCV Version: " << CV_VERSION << std::endl;

	//Criar matriz para armazenar imagem
	Mat image;
	VideoCapture cap;

	cap.open(0);

}