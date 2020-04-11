#include<opencv2/imgproc.hpp>
#include<opencv2/videoio.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
#include<string>
#include<vector>

enum {
	ESCAPE = 27,
	ENTER = 13,
	PROBEL = 32,
	ENDLESSLY = 0
};

static const int MAX_VALUE = 256;
static cv::RNG rng(12345);

static const std::string WINDOW_CAPTURE_NAME	= "Video Capture";
static const std::string WINDOW_DETECTION_NAME = "Object Detection";
static const std::string WINDOW_SETTINGS_NAME  = "Settings";

static int B_min = 0, G_min = 0, R_min = 0;
static int B_max = 256, G_max = 256, R_max = 256;

static void on_low_B_thresh_trackbar(int, void *);
static void on_high_B_thresh_trackbar(int, void *);
static void on_low_G_thresh_trackbar(int, void *);
static void on_high_G_thresh_trackbar(int, void *);
static void on_low_R_thresh_trackbar(int, void *);
static void on_high_R_thresh_trackbar(int, void *);


int main(int argc, char** argv) {

	cv::VideoCapture cap(cv::CAP_ANY);

	if (!cap.isOpened()) { std::cout << "error.camera" << std::endl; return -1; }


	cv::Mat frame, frame_threshold, frame_temp;

	std::vector<std::vector<cv::Point>> contours;

	std::vector<cv::Vec4i> hierarchy;


	cv::namedWindow(WINDOW_CAPTURE_NAME);
	cv::namedWindow(WINDOW_DETECTION_NAME);
	cv::namedWindow(WINDOW_SETTINGS_NAME);

	cv::createTrackbar("B min", WINDOW_SETTINGS_NAME, &B_min, MAX_VALUE, on_low_B_thresh_trackbar);
	cv::createTrackbar("B max", WINDOW_SETTINGS_NAME, &B_max, MAX_VALUE, on_high_B_thresh_trackbar);
	cv::createTrackbar("G min", WINDOW_SETTINGS_NAME, &G_min, MAX_VALUE, on_low_G_thresh_trackbar);
	cv::createTrackbar("G max", WINDOW_SETTINGS_NAME, &G_max, MAX_VALUE, on_high_G_thresh_trackbar);
	cv::createTrackbar("R min", WINDOW_SETTINGS_NAME, &R_min, MAX_VALUE, on_low_R_thresh_trackbar);
	cv::createTrackbar("R max", WINDOW_SETTINGS_NAME, &R_max, MAX_VALUE, on_high_R_thresh_trackbar);


	for (char ch = 0; ch != ESCAPE; ch = static_cast<char>(cv::waitKey(1))) {

		cap >> frame;

		if (frame.empty()) break;


		cv::inRange(frame, cv::Scalar(B_min, G_min, R_min), cv::Scalar(B_max, G_max, R_max), frame_threshold);

		cv::findContours(frame_threshold, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);


		for (size_t i = 0; i < contours.size(); i++){

			cv::Scalar color = cv::Scalar(255, 107, 0);

			drawContours(frame, contours, static_cast<int>(i), color, 3, cv::LINE_8, hierarchy);
		}
		
		
		cv::imshow(WINDOW_CAPTURE_NAME, frame);
		cv::imshow(WINDOW_DETECTION_NAME, frame_threshold);
	}
	
	return 0;
}


static void on_low_B_thresh_trackbar(int, void *){

	B_min = cv::min(B_max - 1, B_min);

	cv::setTrackbarPos("B min", WINDOW_SETTINGS_NAME, B_min);
}


static void on_high_B_thresh_trackbar(int, void *){

	B_max = cv::max(B_max, B_min + 1);

	cv::setTrackbarPos("B max", WINDOW_SETTINGS_NAME, B_max);
}


static void on_low_G_thresh_trackbar(int, void *){

	G_min = cv::min(G_max - 1, G_min);

	cv::setTrackbarPos("G min", WINDOW_SETTINGS_NAME, G_min);
}


static void on_high_G_thresh_trackbar(int, void *){

	G_max = cv::max(G_max, G_min + 1);

	cv::setTrackbarPos("G max", WINDOW_SETTINGS_NAME, G_max);
}


static void on_low_R_thresh_trackbar(int, void *){

	R_min = cv::min(R_max - 1, R_min);

	cv::setTrackbarPos("R min", WINDOW_SETTINGS_NAME, R_min);
}


static void on_high_R_thresh_trackbar(int, void *){

	R_max = cv::max(R_max, R_min + 1);

	cv::setTrackbarPos("R max", WINDOW_SETTINGS_NAME, R_max);
}
