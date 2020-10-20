#pragma once
#include "TuioListener.h"
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/highgui.hpp>
#include "GesturePath.h"
#include "GeometricRecognizer.h"
#include <map>

using namespace TUIO;
using namespace std;
using namespace cv;
using namespace DollarRecognizer;
class MyTuioListener: public TuioListener {
public:
	MyTuioListener();
	void addTuioObject(TuioObject*);
	void updateTuioObject(TuioObject*);
	void removeTuioObject(TuioObject*);
	void addTuioCursor(TuioCursor* );
	void updateTuioCursor(TuioCursor*);
	void removeTuioCursor(TuioCursor*);
	void refresh(TuioTime);
	RecognitionResult getPlayer1Result() { return player1; }
private:
	map<int, Path2D> paths;
	GeometricRecognizer recognizer;
	RecognitionResult player1 = RecognitionResult("", 0);
	RecognitionResult player2 = RecognitionResult("", 0);
};