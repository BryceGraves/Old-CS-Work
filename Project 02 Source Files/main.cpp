#include "ofMain.h"
#include "ofApp.h"

//Bryce Graves
//Description: this program shows the concept of the "Drunkards Walk" or Brownian Motion. This "walk" has a 25% chance to take a "step" in any given direction.
//My portfolio: https://brycegraves.github.io/

int main( ) {
	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
