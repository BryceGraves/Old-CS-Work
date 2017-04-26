#include "ofApp.h"
#include "Walker.h"

const int NUMBER_OF_WALKERS = 1000;

void ofApp::setup() {
	ofSetBackgroundColor(0);
	for (int i = 0; i < NUMBER_OF_WALKERS; ++i) {
		walkers.push_back(new Walker(ofGetWidth() / 2, ofGetHeight() / 2, 1, ofColor(ofRandom(255), ofRandom(255), ofRandom(255))));
	}
	
	//ofSetFrameRate(60);
}


void ofApp::update() {
	for (int i = 0; i < walkers.size(); ++i) {
		walkers[i]->move();
	}
}


void ofApp::draw() {
	//ofDrawGrid(35, 50, false, false, false, true);
	
	for (int i = 0; i < walkers.size(); ++i) {
		walkers[i]->draw();
	}
}



void ofApp::keyPressed(int key) {

}


void ofApp::keyReleased(int key) {

}


void ofApp::mouseMoved(int x, int y ) {

}


void ofApp::mouseDragged(int x, int y, int button) {

}


void ofApp::mousePressed(int x, int y, int button) {

}


void ofApp::mouseReleased(int x, int y, int button) {

}


void ofApp::mouseEntered(int x, int y) {

}


void ofApp::mouseExited(int x, int y) {

}


void ofApp::windowResized(int w, int h) {

}


void ofApp::gotMessage(ofMessage msg) {

}


void ofApp::dragEvent(ofDragInfo dragInfo) {

}
