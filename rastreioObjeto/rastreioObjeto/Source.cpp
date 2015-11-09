#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>



using namespace std;



// Global storage
//
// Float, 3-channel images
//
cv::Mat IavgF, IdiffF, IprevF, IhiF, IlowF;
cv::Mat tmp, tmp2;
// Float, 1-channel images
//
vector<cv::Mat> Igray(3);
vector<cv::Mat> Ilow(3);
vector<cv::Mat> Ihi(3);
// Byte, 1-channel image
//

cv::Mat Imaskt;
// Counts number of images learned for averaging later
//
float Icount;

// I is just a sample image for allocation purposes
// (passed in for sizing)
//

void AllocateImages(IplImage* I){
	CvSize sz = cvGetSize(I);
	IavgF = cv::Mat::zeros(sz, CV_32FC3);
	IdiffF = cv::Mat::zeros(sz, CV_32FC3);
	IprevF = cv::Mat::zeros(sz, CV_32FC3);
	IhiF = cv::Mat::zeros(sz, CV_32FC3);
	IlowF = cv::Mat::zeros(sz, CV_32FC3);
	Icount = 0.00001; // Protect against divide by zero
	tmp = cv::Mat::zeros(sz, CV_32FC3);
	tmp2 = cv::Mat::zeros(sz, CV_32FC3);
	Imaskt = cv::Mat(sz, CV_32FC1);
}

// Learn the background statistics for one more frame
// I is a color sample of the background, 3-channel, 8u
//
void accumulateBackground(cv::Mat& I){
	static int first = 1; // nb. Not thread safe
	I.convertTo(tmp, CV_32F); // convert to float
	if (!first){
		IavgF += tmp;
		cv::absdiff(tmp, IprevF, tmp2);
		IdiffF += tmp2;
		Icount += 1.0;
	}
	first = 0;
	IprevF = tmp;
}



void setHighThreshold(float scale) {
	IhiF = IavgF + (IdiffF * scale);
	cv::split(IhiF, Ihi);
}
void setLowThreshold(float scale) {
	IlowF = IavgF - (IdiffF * scale);
	cv::split(IlowF, Ilow);
}

void createModelsfromStats() {
	IavgF *= (1.0 / Icount);
	IdiffF *= (1.0 / Icount);
	// Make sure diff is always something
	//
	IdiffF += cv::Scalar(1.0, 1.0, 1.0);
	setHighThreshold(7.0);
	setLowThreshold(6.0);
}

// Create a binary: 0,255 mask where 255 means foreground pixel
// I Input image, 3-channel, 8u
// Imask Mask image to be created, 1-channel 8u
//
void backgroundDiff(
	cv::Mat& I,
	cv::Mat& Imask
	) {
	I.convertTo(tmp, CV_32F); // To float
	cv::split(tmp, Igray);
	// Channel 1
	//
	cv::inRange(Igray[0], Ilow[0], Ihi[0], Imask);
	// Channel 2
	//
	cv::inRange(Igray[1], Ilow[1], Ihi[1], Imaskt);
	Imask = cv::min(Imask, Imaskt);
	// Channel 3
	//
	cv::inRange(Igray[2], Ilow[2], Ihi[2], Imaskt);
	Imask = cv::min(Imask, Imaskt);
	// Finally, invert the results
	//
	Imask = 255 - Imask;
}

void help() {
	cout << "\n"
		<< "Read out RGB pixel values and store them to disk\nCall:\n"
		<< "./ch9_ex9_1 avi_file\n"
		<< "\n This will store to files blines.csv, glines.csv and rlines.csv\n\n"
		<< endl;
}

int main(int argc, char** argv) {

	cv::Mat image; //isso nao tinha no codigo original
	cv::Mat rawImage; //isso tambem nao

	cv::VideoCapture cap;



	if (argc != 2) { help(); return -1; }
	cv::namedWindow("Example9_2", cv::WINDOW_AUTOSIZE);


	if ((argc < 2) || !cap.open(argv[1])) {
		cerr << "Couldn't open video file" << endl;
		help();
		cap.open(0);
		return -1;
	}
	// FIRST PROCESSING LOOP (TRAINING):
	//

	while (1) {
		cap >> image;
		if (!image.data) exit(0);
		accumulateBackground(image);
		cv::imshow("Example9_2", rawImage);
		if (cv::waitKey(7) == 0x20) break;
	}
	// We have all of our data, so create the models
	//
	createModelsfromStats();
	// SECOND PROCESSING LOOP (TESTING):
	//
	cv::Mat mask;
	while (1) {
		cap >> image;
		if (!image.data) exit(0);
		backgroundDiff(image, mask);
		// A simple visualization is to write to the red channel
		//
		cv::split(image, Igray);
		Igray[2] = cv::max(mask, Igray[2]);
		cv::merge(Igray, image);
		cv::imshow("Example9_2", image);
		if (cv::waitKey(7) == 0x20) break;
	}
	exit(0);
}



//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc.hpp"
//using namespace cv;
//
////void main()
////{
////	std::cout << "OpenCV Version: " << CV_VERSION << std::endl;
////
////	//Criar matriz para armazenar imagem
////	Mat image;
////	VideoCapture cap;
////
////	cap.open(0);
////
////}
//
//int main(int argc, char** argv) {
//
//
//	cv::VideoCapture cap;
//	cap.open(0);
//	if (!cap.isOpened()){
//		return -1;
//	}
//	cv::Mat frame;
//	cv::namedWindow("Camera", cv::WINDOW_AUTOSIZE);
//	while (1) {
//		cap >> frame;
//		if (!frame.data) break; // Ran out of film
//		cv::imshow("Example3", frame);
//		if (cv::waitKey(33) >= 0) break;
//	}
//	return 0;
//
//}
//		
