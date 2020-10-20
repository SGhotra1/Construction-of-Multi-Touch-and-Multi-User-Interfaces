#include "Touch.h"

Touch::Touch(){

}

Touch::Touch(int i, Point2f p){
	id = i;
	position = p;
}

Point2f Touch::getPosition(){
	return position;
}

void Touch::setPosition(Point2f newPos) {
	position = newPos;
}

int Touch::getId() {
	return id;
}

bool Touch::operator==(const Touch&t) const
{
	return position == t.position;
}
