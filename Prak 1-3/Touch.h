#pragma once
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/highgui.hpp>
using namespace std;
using namespace cv;

class Touch {
public:
	Touch();
	Touch(int, Point2f);
	Point2f getPosition();
	void setPosition(Point2f);
	int getId();
	bool operator==(const Touch&) const;
private:
	int id;
	Point2f position;
	int size;
};