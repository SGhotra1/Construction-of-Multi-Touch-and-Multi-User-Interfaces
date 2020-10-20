#include "MyTuioListener.h"

MyTuioListener::MyTuioListener() {
	recognizer.loadTemplates();
	
}

void MyTuioListener::addTuioObject(TuioObject* obj){
	cout << "Is there an TuioObject added?" << endl;
}

void MyTuioListener::updateTuioObject(TuioObject* obj){

}

void MyTuioListener::removeTuioObject(TuioObject* obj){

}

void MyTuioListener::addTuioCursor(TuioCursor* tcur) {
	cout << "Cursor " << tcur->getCursorID() << " added" << endl;
	//path.addPoint(Point2f(tcur->getX(), tcur->getY()));
	pair <int, Path2D> p;
	Path2D start;
	start.push_back(Point2D(tcur->getX(), tcur->getY()));
	p = make_pair(tcur->getCursorID(), start);
	paths.emplace(p);
}

void MyTuioListener::updateTuioCursor(TuioCursor* tcur){
	cout << "Cursor " << tcur->getCursorID()  << " updated" << " Speed: " << tcur->getYSpeed() << endl;
	//path.push_back(Point2D(tcur->getX(), tcur->getY()));
	paths.at(tcur->getCursorID()).push_back(Point2D(tcur->getX(), tcur->getY()));
}

void MyTuioListener::removeTuioCursor(TuioCursor* tcur){
	cout << "Cursor deleted" << endl;
	//path.clearPath();
	if (paths.at(tcur->getCursorID()).empty()) {
		return;
	}
	if (tcur->getCursorID() == 0) {
		player1 = recognizer.recognize(paths.at(tcur->getCursorID()));
		cout << "Player 1 made Gesture " << player1.name << endl;
		paths.at(tcur->getCursorID()).clear();
	}
	else { 
		player2 = recognizer.recognize(paths.at(tcur->getCursorID()));
		cout << "Player 2 made Gesture " << player2.name << endl;
		paths.at(tcur->getCursorID()).clear();
	}
	
}

void MyTuioListener::refresh(TuioTime ftime){
	
}
