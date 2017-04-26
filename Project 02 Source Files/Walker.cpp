#include "Walker.h"
#include "ofMain.h"


Walker::Walker() {
	x = ofGetWindowWidth();
	y = ofGetWindowHeight();
	size = 5;
	color = ofColor();
}

Walker::Walker(int x, int y, int size, ofColor color) {
	this->x = x;
	this->y = y;
	this->size = size;
	this->color = color;
}

void Walker::move() {
	int direction = ofRandom(4);
	if (direction == 0) {
		moveDown();
	} else if (direction == 1) {
		moveUp();
	} else if (direction == 2) {
		moveRight();
	} else if (direction == 3) {
		moveLeft();
	}
}

void Walker::draw() {
	ofSetColor(color);
	ofDrawCircle(x, y, size);
}

void Walker::moveDown() {
	y--;
}

void Walker::moveUp() {
	y++;
}

void Walker::moveLeft() {
	x--;
}

void Walker::moveRight() {
	x++;
}