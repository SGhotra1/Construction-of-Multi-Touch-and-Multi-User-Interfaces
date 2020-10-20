#pragma once
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/highgui.hpp>
#include <vector>

class GesturePath {
public:
	void addPoint(cv::Point2f p) { path.push_back(p); }
	void clearPath() { path.clear(); }
private:
	std::vector<cv::Point2f> path;
};