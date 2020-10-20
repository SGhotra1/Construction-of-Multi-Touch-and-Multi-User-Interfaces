#include "MyTuioListener.h"
#include "TuioClient.h"
#include <thread>      
#include <chrono>
#include <stdlib.h>
#include <time.h>
int countdown = 60;

void countDown() {
	for (countdown = 60; countdown > 0; countdown--) {
		cout << countdown << " seconds left." << endl;
		this_thread::sleep_for(chrono::seconds(1));

	}
}

int main() {
	srand(time(NULL));
	GeometricRecognizer recognizer;
	recognizer.loadTemplates();
	MyTuioListener listener;
	TuioClient client(3333);
	client.addTuioListener(&listener);
	client.connect();
	boolean wasPrinted = false;
	boolean endGame = false;
	thread t1(countDown);
	int randomGesture = rand() % recognizer.getTemplates().size();
	int counter = 0;
	while (countdown != 0) {
		
		if (!wasPrinted) {
			cout << recognizer.getTemplates().at(randomGesture).name << " nachmachen" << endl;
			
		}
		wasPrinted = true;
		if (listener.getPlayer1Result().name == recognizer.getTemplates().at(randomGesture).name) {
			wasPrinted = false;
			//endGame = true;
			counter++;
			randomGesture = rand() % recognizer.getTemplates().size();
		}
	}
	t1.join();
	cout << "Game over!" << endl;
	cout << counter << " Punkte!" << endl;
}


void singlePlayerGame() {

}

