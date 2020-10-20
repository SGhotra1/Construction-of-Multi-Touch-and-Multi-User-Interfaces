#include "Tracking.h"

using namespace cv;

Tracking::Tracking(double w, double h, TUIO::TuioServer& s, int c){
	counter = 1;
	maxDistance = 35;
	videoWidth = w;
	videoHeight = h;
	server = &s;
	currentFrame = c;
}


vector<Touch> Tracking::TrackFinger(vector<Point2f> fingers)
{
	for (int i = 0; i < pastTouches.size(); i++) {
		findNearestNeighbour(pastTouches[i], fingers);
	}

	if (fingers.size() > pastTouches.size()) {
		for (Point2f finger : fingers) {
			Touch t(counter, finger);
			pastTouches.push_back(t);
			TUIO::TuioCursor* tcur = new TUIO::TuioCursor(t.getId(), t.getId(),
				t.getPosition().x / videoWidth, t.getPosition().y / videoHeight);
			server->addExternalTuioCursor(tcur);
			counter++;
		}
	}
	return pastTouches;
}

void Tracking::findNearestNeighbour(Touch t, vector<Point2f> &fingers) {
	Point2f max(9999999, 9999999);
	pair<Point2f, int> nearestNeighbor(max, 9999999);
	double distance = 0;

	for (Point2f finger : fingers) {
		distance = norm(t.getPosition() - finger);
		if (distance <= maxDistance && distance <= nearestNeighbor.second) {
			nearestNeighbor = make_pair(finger, distance);
		}
	}
	
	if (nearestNeighbor.first == max) {
		pastTouches.erase(remove(pastTouches.begin(), pastTouches.end(), t));
		server->removeTuioCursor(server->getTuioCursor(t.getId()));
		
		return;
	}

	auto itr = find(pastTouches.begin(), pastTouches.end(), t);
	int x = std::distance(pastTouches.begin(), itr);
	pastTouches[x].setPosition(nearestNeighbor.first);
	
	server->updateTuioCursor(server->getTuioCursor(pastTouches[x].getId()), pastTouches[x].getPosition().x / videoWidth, pastTouches[x].getPosition().y / videoHeight);
	fingers.erase(remove(fingers.begin(), fingers.end(), nearestNeighbor.first));
}

int Tracking::getCounter(){
	return counter;
}

