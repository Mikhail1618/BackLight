#include<opencv2/imgproc.hpp>
#include<opencv2/videoio.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
#include<string>
#include<vector>
#include"config.h"

enum {
	ESCAPE = 27,
	ENTER = 13,
	PROBEL = 32,
	ENDLESSLY = 0
};

static const int MAX_VALUE = 255;

static const std::string WINDOW_CAPTURE_NAME = "Video Capture";
static const std::string WINDOW_DETECTION_NAME = "Object Detection";
static const std::string WINDOW_SETTINGS_NAME = "Settings";

static int  H_min = 0,
			S_min = 0,
			V_min = 0;

static int	H_max = MAX_VALUE,
			S_max = MAX_VALUE,
			V_max = MAX_VALUE;

static void on_low_H_thresh_trackbar(int, void *);
static void on_high_H_thresh_trackbar(int, void *);
static void on_low_S_thresh_trackbar(int, void *);
static void on_high_S_thresh_trackbar(int, void *);
static void on_low_V_thresh_trackbar(int, void *);
static void on_high_V_thresh_trackbar(int, void *);


int main(int argc, char** argv) {

	std::cout << "BackLight-"
	<< PROJECT_VERSION_MAJOR << "."
	<< PROJECT_VERSION_MINOR << "."
	<< PROJECT_VERSION_PATCH
	<< std::endl;

	cv::VideoCapture cap(cv::CAP_ANY);

	if (!cap.isOpened()) { std::cout << "error.camera" << std::endl; return -1; }


	cv::Mat frame, frame_threshold, frame_temp;

	std::vector<std::vector<cv::Point>> contours;

	std::vector<cv::Vec4i> hierarchy;


	cv::namedWindow(WINDOW_CAPTURE_NAME);
	cv::namedWindow(WINDOW_DETECTION_NAME);
	cv::namedWindow(WINDOW_SETTINGS_NAME);

	cv::createTrackbar("H min", WINDOW_SETTINGS_NAME, &H_min, MAX_VALUE, on_low_H_thresh_trackbar);
	cv::createTrackbar("H max", WINDOW_SETTINGS_NAME, &H_max, MAX_VALUE, on_high_H_thresh_trackbar);
	cv::createTrackbar("S min", WINDOW_SETTINGS_NAME, &S_min, MAX_VALUE, on_low_S_thresh_trackbar);
	cv::createTrackbar("S max", WINDOW_SETTINGS_NAME, &S_max, MAX_VALUE, on_high_S_thresh_trackbar);
	cv::createTrackbar("V min", WINDOW_SETTINGS_NAME, &V_min, MAX_VALUE, on_low_V_thresh_trackbar);
	cv::createTrackbar("V max", WINDOW_SETTINGS_NAME, &V_max, MAX_VALUE, on_high_V_thresh_trackbar);


	for (char ch = 0; ch != ESCAPE; ch = static_cast<char>(cv::waitKey(30))) {

		cap >> frame;

		if (frame.empty()) break;


		cv::cvtColor(frame, frame_temp, cv::COLOR_BGR2HSV_FULL);

		cv::inRange(frame_temp, cv::Scalar(H_min, S_min, V_min), cv::Scalar(H_max, S_max, V_max), frame_threshold);

		cv::findContours(frame_threshold, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

		cv::Scalar color = cv::Scalar(0x336699);

		for (size_t i = 0; i < contours.size(); i++) {			

			drawContours(frame, contours, static_cast<int>(i), color, 2, cv::LINE_8, hierarchy);
		}


		cv::imshow(WINDOW_CAPTURE_NAME, frame);
		cv::imshow(WINDOW_DETECTION_NAME, frame_threshold);
	}

	return 0;
}


static void on_low_H_thresh_trackbar(int, void *) {

	H_min = cv::min(H_max - 1, H_min);

	cv::setTrackbarPos("H min", WINDOW_SETTINGS_NAME, H_min);
}


static void on_high_H_thresh_trackbar(int, void *) {

	H_max = cv::max(H_max, H_min + 1);

	cv::setTrackbarPos("H max", WINDOW_SETTINGS_NAME, H_max);
}


static void on_low_S_thresh_trackbar(int, void *) {

	S_min = cv::min(S_max - 1, S_min);

	cv::setTrackbarPos("S min", WINDOW_SETTINGS_NAME, S_min);
}


static void on_high_S_thresh_trackbar(int, void *) {

	S_max = cv::max(S_max, S_min + 1);

	cv::setTrackbarPos("S max", WINDOW_SETTINGS_NAME, S_max);
}


static void on_low_V_thresh_trackbar(int, void *) {

	V_min = cv::min(V_max - 1, V_min);

	cv::setTrackbarPos("V min", WINDOW_SETTINGS_NAME, V_min);
}


static void on_high_V_thresh_trackbar(int, void *) {

	V_max = cv::max(V_max, V_min + 1);

	cv::setTrackbarPos("V max", WINDOW_SETTINGS_NAME, V_max);
}
