#include "App.h"
#define CASCADE_SPOON_PATH   "classifier/classifier_spoon/cascade.xml"
#define CASCADE_BALSEM_PATH   "classifier/classifier_balsem/cascade.xml"
#define CASCADE_PERFUME_PATH   "classifier/classifier_perfume/cascade.xml"

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

	 
	cv::CascadeClassifier cascadeBalsem;
	if (!cascadeBalsem.load(CASCADE_BALSEM_PATH)) {
		std::cout << "Error when loading the cascade classfier!"
			<< std::endl;
		return -1;
	}
	cv::CascadeClassifier cascadePerfume;
	if (!cascadePerfume.load(CASCADE_PERFUME_PATH)) {
		std::cout << "Error when loading the cascade classfier!"
			<< std::endl;
		return -1;
	}

	std::cout << "FILE LOADED" << std::endl;

	while (running) {

		cap >> mainPicture;
		rgbPicture = mainPicture;

		/*mirror*/
		//cv::flip(mainPicture, mainPicture, 2); 
		std::vector<cv::Rect> balsemDetections;

		std::vector<cv::Rect> perfumeDetections;

		/*
			balsem
		*/
		cascadeBalsem.detectMultiScale(mainPicture, // input image
			balsemDetections, // detection results
			1.1, // scale reduction factor
			50, // number of required neighbor 	detections
			0, // flags (not used)
			cv::Size(110,110), // minimum object size to be detected
			cv::Size(400, 400)); // maximum object size to be detected

		drawDetection(balsemDetections, rgbPicture, "BALSEM", cv::Scalar(0,255,255));

		/*
			perfume
		*/ 
		cascadePerfume.detectMultiScale(mainPicture, // input image
			perfumeDetections, // detection results
			1.1, // scale reduction factor
			80, // number of required neighbor 	detections
			0, // flags (not used)
			cv::Size(70, 70), // minimum object size to be detected
			cv::Size(400, 400)); // maximum object size to be detected

		drawDetection(perfumeDetections, rgbPicture, "PERFUME",cv::Scalar(0,0,255));

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

int App::drawDetection(std::vector<cv::Rect> detections, cv::Mat pict, cv::String name, cv::Scalar color)
{
	for (int i = 0; i < detections.size(); i++) {
		cv::Rect detectionRect = detections[i];

		std::string text = name+" - " + std::to_string(detectionRect.x) + "." + std::to_string(detectionRect.y);
		text += "|" + std::to_string(detectionRect.width) + "x" + std::to_string(detectionRect.height);

		cv::putText(pict, text, cv::Point(detectionRect.x, detectionRect.y),
			1, 1.50, color, 2);
		cv::rectangle(pict, detectionRect,
			color, 2);
	}
	return 0;
}


