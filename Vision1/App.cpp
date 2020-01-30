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
	if (!cascade.load("classifier/classifier_stop/cascade.xml")) {
		std::cout << "Error when loading the cascade classfier!"
			<< std::endl;
		return -1;
	}

	std::cout << "FILE LOADED" << std::endl;

	while (running) {

		cap >> mainPicture;
		rgbPicture = mainPicture;

		/*mirror*/
	//	cv::flip(mainPicture, mainPicture, 2); 
		std::vector<cv::Rect> detections;

		cascade.detectMultiScale(mainPicture, // input image
			detections, // detection results
			1.1, // scale reduction factor
			2, // number of required neighbor 	detections
			0, // flags (not used)
			cv::Size(48, 48), // minimum object size to be detected
			cv::Size(300, 300)); // maximum object size to be detected

		std::cout << "DETECTION SIZE:" << detections.size() << std::endl;

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

int App::createBg()
{
	cv::VideoCapture cap(0);

	//initWindowDialogs(); 

	cv::CascadeClassifier cascade;
	if (!cascade.load("classifier/classifier_spoon/cascade.xml")) {
		std::cout << "Error when loading the cascade classfier!"
			<< std::endl;
		return -1;
	}

	std::cout << "FILE LOADED" << std::endl;

	int count = 1;
	std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);
	while (running) {
		count++;
		cap >> mainPicture;
		rgbPicture = mainPicture;
		cv::imwrite(count+"_bgxx.png", rgbPicture, compression_params);
		 
		std::cout << "-" << std::endl;
		cv::imshow("Cam", rgbPicture);
		cv::waitKey(1);
	}
	return 0;
}


