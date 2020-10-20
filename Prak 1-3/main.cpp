#include "Tracking.h"
#include "TuioServer.h"
#include "TuioTime.h"
#include "TuioCursor.h"
#include "TuioObject.h"


using namespace std;
using namespace cv;
using namespace TUIO;

int main() {
	Mat background, result, frame, original, blurred, binary, gray, backgroundsubs;
	//background = imread("background.jpg");
	VideoCapture vid("../../mt_camera_raw.AVI");
	if (!vid.isOpened())
	{
		std::cout << "ERROR: Could not open camera / video stream.\n";
		return -1;
	}
	double videoWidth = vid.get(cv::CAP_PROP_FRAME_WIDTH);
	double videoHeight = vid.get(cv::CAP_PROP_FRAME_HEIGHT);


	int currentFrame = 0; // frame counter
	clock_t ms_start, ms_end, ms_time; // time
	multimap <int, pair<int, Point2f>> foundObjects;

	char buffer[10]; // buffer for int to ascii conversion -> itoa(...)
	
	vector<Touch> trackedTouches;
	

	TuioServer* server = new TuioServer();
	Tracking t(videoWidth, videoHeight, *server, currentFrame);

	while (true) {
		ms_start = clock(); // time start
		
		vid >> frame; // get a new frame from the videostream
		if (currentFrame == 0) {
			background = frame.clone();
		}
		//this_thread::sleep_for(chrono::milliseconds(75));
		if (frame.data == NULL) // terminate the program if there are no more frames
		{
			std::cout << "TERMINATION: Camerastream stopped or last frame of video reached.\n";
			break;
		}

		original = frame.clone();
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		absdiff(original, background, result);
		blur(result, blurred, Size(15,15));
		//GaussianBlur(result, blurred, Size(5, 5), 100);
		absdiff(result, blurred, result);
		blur(result, result, Size(6, 6));
		cvtColor(result, result, COLOR_BGR2GRAY);
		threshold(result, result, 10, 255, THRESH_BINARY);
		
		findContours(result, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
		// iterate through all the top-level contours -> "hierarchy" may not be empty!)
		vector<Moments> mu(contours.size());
		Point2f p;
		vector<Point2f> fingers;
		if (hierarchy.size() > 0)
		{
			for (int idx = 0; idx >= 0; idx = hierarchy[idx][0])
			{
				// check contour size (number of points) and area ("blob" size)
				if (contourArea(Mat(contours.at(idx))) > 30 && contours.at(idx).size() > 4) // Changing the contourArea to 25 for example recognizes more fingers
				{
					RotatedRect rr = fitEllipse(Mat(contours.at(idx)));
					ellipse(original, rr,
						Scalar(0, 0, 255), 1, 8); // fit & draw ellipse to contour at index
					drawContours(original, contours, idx, Scalar(255, 0, 0), 1, 8,
						hierarchy); // draw contour at index
					
					mu[idx] = moments(contours[idx], false);
					
					p = Point2f(mu[idx].m10 / mu[idx].m00, mu[idx].m01 / mu[idx].m00);
					pair<int, Point2f> pair = make_pair(contourArea(Mat(contours.at(idx))), p);
					foundObjects.emplace(currentFrame, pair);
					fingers.emplace_back(p);
				}
			}
		}
		
		trackedTouches = t.TrackFinger(fingers); 
		server->initFrame(TuioTime::getSessionTime());
		server->sendFullMessages();
		/*server->initFrame(TuioTime::getSessionTime());
		server->sendFullMessages();*/
		for (Touch to : trackedTouches) {
			putText(original, to_string(to.getId()), to.getPosition(), FONT_HERSHEY_PLAIN, 1, Scalar(255,255,255));
		}
		if (waitKey(10) == 27) // wait for user input
		{
			std::cout << "TERMINATION: User pressed ESC\n";
			break;
		}
		
	
		currentFrame++;
		ms_end = clock(); //not used right now
		ms_time = ms_end - ms_start;
		
		imshow("windowresult", original);
	}
	std::cout << endl;
	std::cout << foundObjects.size() << " Objects found." << endl;
	std::cout << t.getCounter() << " Fingertouches detected." << endl;
	std::cout << "SUCCESS: Program terminated like expected.\n";
	return 1;
}