#pragma once

#include <iostream>
#include <time.h>
#include <math.h>
#include <vector>
#include <chrono>
#include <thread>
#include <map>
#include <vector>
#include <algorithm>
#include "Touch.h"
#include "TuioServer.h"
#include "TuioCursor.h"
#include "TuioTime.h"

class Tracking {
public:
	Tracking(double, double, TUIO::TuioServer&, int);
	vector<Touch> TrackFinger(vector<Point2f>);
	void findNearestNeighbour(Touch, vector<Point2f>&);
	int getCounter();
private:
	double maxDistance;
	int counter;
	vector<Touch> pastTouches;
	double videoWidth;
	double videoHeight;
	TUIO::TuioServer* server;
	int currentFrame;
};