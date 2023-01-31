#pragma once
/*

 *
 */

#ifndef _BOID
#define _BOID
#include <vector>
#include "ofMain.h"

class Boid
{

protected:
	
	

public:
	
	ofVec3f position;    // ofVec3f is an inbuilt vector class in OpenFrameworks
	ofVec3f velocity;    // Initialising two 3 dimensional vectors to store the velocity and position of every boid in the x, y, and z axes as floats

	float separationWeight;   // Initialising variables that store factor of corresponding functions' impact
	float cohesionWeight;
	float alignmentWeight;

	float separationThreshold;
	float neighbourhoodSize;

	ofVec3f virtual separation(std::vector<Boid*>& otherBoids);   //Functions that take pointers to instances of the same class as arguments
	ofVec3f virtual cohesion(std::vector<Boid*>& otherBoids);
	ofVec3f virtual alignment(std::vector<Boid*>& otherBoids);


	Boid();   // Constructor with 0 arguments
	Boid(ofVec3f& pos, ofVec3f& vel);   // Overriden constructor that initialises with references to vectors containing position and velocity of boid

	~Boid();     // Destructor

	ofVec3f getPosition();   // Getters with return type of Vec3f
	ofVec3f getVelocity();


	float getSeparationWeight();  // Getters of return type float for each private variable
	float getCohesionWeight();
	float getAlignmentWeight();

	float getSeparationThreshold();
	float getNeighbourhoodSize();

	void setSeparationWeight(float f);
	void setCohesionWeight(float f);
	void setAlignmentWeight(float f);

	void setSeparationThreshold(float f);
	void setNeighbourhoodSize(float f);

	void virtual update(std::vector<Boid*>& otherBoids, ofVec3f& min, ofVec3f& max);  // Update function

	void walls(ofVec3f& min, ofVec3f& max);   // To stay clear of walls

	void virtual draw();   // Draw function
};


class Boyd : public Boid {
public: 

	Boyd();   
	Boyd(ofVec3f& pos, ofVec3f& vel);   
	~Boyd();


	ofVec3f separation(std::vector<Boyd*>& otherBoyds);   //Functions that take pointers to instances of the same class as arguments
	ofVec3f cohesion(std::vector<Boyd*>& otherBoyds);
	ofVec3f alignment(std::vector<Boyd*>& otherBoyds);

	void virtual update(std::vector<Boyd*>& otherBoyds, ofVec3f& min, ofVec3f& max);  // Update function
	void draw(ofVec3f colour);



};

#endif