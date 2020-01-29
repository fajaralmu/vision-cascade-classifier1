#include "App.h"

using namespace std;

App::App()
{
}


App::~App()
{
}
 
int App::run()
{
	points.push_back({});
	bg_ = cv::imread("bg.jpg");

	cv::VideoCapture cap(0);

	//initWindowDialogs(); 

	cv::CascadeClassifier cascade;
	if (!cascade.load("classifier/cascades_face/haarcascade_mcs_nose.xml")) {
		std::cout << "Error when loading the cascade classfier!"
			<< std::endl;
		return -1;
	}

	std::cout << "FILE LOADED" << std::endl;

	while (running) {

		cap >> mainPicture;
		rgbPicture = mainPicture;

		/*mirror*/
		cv::flip(mainPicture, mainPicture, 2); 
		std::vector<cv::Rect> detections;

		cascade.detectMultiScale(mainPicture, // input image
			detections, // detection results
			1.1, // scale reduction factor
			2, // number of required neighbor 	detections
			0, // flags (not used)
			cv::Size(48, 48), // minimum object size to be detected
			cv::Size(128, 128)); // maximum object size to be detected
		for (int i = 0; i < detections.size(); i++)
			cv::rectangle(rgbPicture, detections[i],
				cv::Scalar(255, 255, 255), 2);
		imshow(ORIGINAL_WINDOW, rgbPicture);
		 

		/*
		process key input
		*/
		cv::waitKey(1);
	}
	/*cv::waitKey(0);*/
	return 0;
}


