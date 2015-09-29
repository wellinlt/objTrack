#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;

//void main()
//{
//	std::cout << "OpenCV Version: " << CV_VERSION << std::endl;
//
//	//Criar matriz para armazenar imagem
//	Mat image;
//	VideoCapture cap;
//
//	cap.open(0);
//
//}

int main(int argc, char** argv) {


	cv::VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened()){
		return -1;
	}
	cv::Mat frame;
	cv::namedWindow("Camera", cv::WINDOW_AUTOSIZE);
	while (1) {
		cap >> frame;
		if (!frame.data) break; // Ran out of film
		cv::imshow("Example3", frame);
		if (cv::waitKey(33) >= 0) break;
	}
	return 0;

}
		
