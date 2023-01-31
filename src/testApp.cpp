#include "testApp.h"
#include <boid.cpp>

testApp::~testApp()   // Destructor deletes all created boids
{
	for (int i = 0; i < boids.size(); i++)
	{
		delete boids[i];
	}
	for (int i = 0; i < boyds.size(); i++)
	{
		delete boyds[i];
	}
}

//--------------------------------------------------------------
void testApp::setup() {


	int screenW = ofGetScreenWidth();
	int screenH = ofGetScreenHeight();


	for (int i = 0; i < 50; i++)           // Instantiate new boids on the heap using new keyword
		boids.push_back(new Boid());

	for (int i = 0; i < 50; i++)           // Instantiate new boids on the heap using new keyword
		boyds.push_back(new Boyd());

}


//--------------------------------------------------------------
void testApp::update() {

	ofVec3f min(0, 0);
	ofVec3f max(ofGetWidth(), ofGetHeight());

	for (int i = 0; i < boids.size(); i++)
	{
		boids[i]->update(boids, min, max);           // Use boid's update function to update position for all boids
	}
	for (int i = 0; i < boyds.size(); i++)
	{
		boyds[i]->update(boyds, min, max);           // Use boid's update function to update position for all boids
	}
	
}

//--------------------------------------------------------------
void testApp::draw() {
	
	ofColor colorOne(50, 0, 0);
	ofColor colorTwo(0, 0, 0);
	ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_CIRCULAR);

	for (int i = 0; i < boids.size(); i++)
	{
		boids[i]->draw();                            // Use boid's draw function to draw boids to updated position
	}
	for (int i = 0; i < boyds.size(); i++)
	{   
		ofVec3f colour;
		colour.set(90, 10, 150);
		ofVec3f infectedColour;
		infectedColour.set(0, 255, 255);

		ofVec3f a = boyds[i]->getPosition();               //position.distance(otherBoids[i]->getPosition()) < neighbourhoodSize
		ofVec3f b = boids[i]->getPosition();
		if (a.distance(b) < 100) {
			boyds[i]->draw(infectedColour); // Use boid's draw function to draw boids to updated position
			continue;
		}
		else {
			boyds[i]->draw(colour);
			continue;
		}

		
		
	}

}


//--------------------------------------------------------------
void testApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {

}