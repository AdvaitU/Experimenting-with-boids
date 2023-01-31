/*
 *  boid.cpp
 *  boids
 *
 *  Created by Marco Gillies on 05/10/2010.
 *  Copyright 2010 Goldsmiths, University of London. All rights reserved.
 *
 */

#include "boid.h"
#include "ofMain.h"

Boid::Boid()       // Constructor Class
{
	separationWeight = 1.3f;          // Setting factors for boid functions' implementation
	cohesionWeight = 0.2f;
	alignmentWeight = 0.1f;

	separationThreshold = 15;
	neighbourhoodSize = 100;

	position = ofVec3f(ofRandom(0, 200), ofRandom(0, 200));     // Randomising initial position
	velocity = ofVec3f(ofRandom(-2, 2), ofRandom(-2, 2));
}

Boid::Boid(ofVec3f& pos, ofVec3f& vel)    // When instantiated with arguments
{
	separationWeight = 1.0f;
	cohesionWeight = 0.2f;
	alignmentWeight = 0.1f;

	separationThreshold = 15;
	neighbourhoodSize = 100;

	position = pos;     // Set to arguments
	velocity = vel;
}

Boid::~Boid()   // No destructor as stored on the stack
{

}

// Getters

float Boid::getSeparationWeight()
{
	return separationWeight;
}
float Boid::getCohesionWeight()
{
	return cohesionWeight;
}

float Boid::getAlignmentWeight()
{
	return alignmentWeight;
}


float Boid::getSeparationThreshold()
{
	return separationThreshold;
}

float Boid::getNeighbourhoodSize()
{
	return neighbourhoodSize;
}

// Setters

void Boid::setSeparationWeight(float f)
{
	separationWeight = f;
}
void Boid::setCohesionWeight(float f)
{
	cohesionWeight = f;
}

void Boid::setAlignmentWeight(float f)
{
	alignmentWeight = f;
}


void Boid::setSeparationThreshold(float f)
{
	separationThreshold = f;
}

void Boid::setNeighbourhoodSize(float f)
{
	neighbourhoodSize = f;
}

// Getters for vector members position and velocity

ofVec3f Boid::getPosition()
{
	return position;
}

ofVec3f Boid::getVelocity()
{
	return velocity;
}


// IMPORTANT FUNCTIONS ---------------------------------------------------------------------------------------------------------------------

// SEPARATION - Makes the boids avoid each other by changing the direction of a boid if it is within the separationThreshold distance of any of the others (to avoid collisions)

ofVec3f Boid::separation(std::vector<Boid*>& otherBoids)
{
	// finds the first collision and avoids that
	// should probably find the nearest one
	// can you figure out how to do that?
	for (int i = 0; i < otherBoids.size(); i++)   // For all boid objects
	{
		if (position.distance(otherBoids[i]->getPosition()) < separationThreshold)   // If distance to boid at i is less than separationThreshold
		{
			ofVec3f v = position - otherBoids[i]->getPosition();     // Reverse the vector that gives velocity
			v.normalize();                // Scale it such that its magnitude is 1 i.e. only the direction is relevant now
			return v;                     // Return normalised v 
		}
	}
}


// COHESION - Sets the position of a boid towards the centre of mass of the other boids (that are less than 100 units away from it) Makes them 'flock' come back to each other and not go too far away

ofVec3f Boid::cohesion(std::vector<Boid*>& otherBoids)
{
	ofVec3f average(0, 0, 0);   // New variables to calculate average i.e. centre of mass of all points
	int count = 0;   // New variable to save the count

	for (int i = 0; i < otherBoids.size(); i++)         // For all the boids apart from this one
	{
		if (position.distance(otherBoids[i]->getPosition()) < neighbourhoodSize)   // If distance between a boid and the other boid is less than 100
		{
			average += otherBoids[i]->getPosition();      // Add position of that other boid to average vector
			count += 1;                                   // Increase 
		}
	}
	average /= count;       // Get average by dividing position by count
	ofVec3f v = average - position;    // Create v to save the average minus the position of the boid
	v.normalize();                     // Normalize
	return v;                          // Return
}

// ALIGNMENT - Makes them move as a group based on the movement of the average

ofVec3f Boid::alignment(std::vector<Boid*>& otherBoids)
{
	ofVec3f average(0, 0, 0);
	int count = 0;
	for (int i = 0; i < otherBoids.size(); i++)
	{
		if (position.distance(otherBoids[i]->getPosition()) < neighbourhoodSize)    // If distance to another boid is less than neighbourhoodSize
		{
			average += otherBoids[i]->getVelocity();
			count += 1;
		}
	}
	average /= count;
	ofVec3f v = average - velocity;
	v.normalize();
	return v;
}

// UPDATE - This function

void Boid::update(std::vector<Boid*>& otherBoids, ofVec3f& min, ofVec3f& max) // Takes vector of other boids and a min and max range
{
	velocity += separationWeight * separation(otherBoids);    // increase velocity according to separation of other boids and a predefined factor
	velocity += cohesionWeight * cohesion(otherBoids);        // Same for cohesion and alignment
	velocity += alignmentWeight * alignment(otherBoids);

	walls(min, max);   // Clipping function
	position += velocity;   // Add velocity vector to current position vector
}

// WALLS - Clipping function so that the boids don't go outside the bounds

void Boid::walls(ofVec3f& min, ofVec3f& max)  // Takes min and max
{
	if (position.x < min.x) {         
		position.x = min.x;
		velocity.x *= -1;
	}
	else if (position.x > max.x) {
		position.x = max.x;
		velocity.x *= -1;
	}

	if (position.y < min.y) {
		position.y = min.y;
		velocity.y *= -1;
	}
	else if (position.y > max.y) {
		position.y = max.y;
		velocity.y *= -1;
	}


}

// DRAW - Create a circle of colour X at position x and y with a radius of 5

void Boid::draw()
{
	ofSetColor(0, 255, 255);
	ofCircle(position.x, position.y, 5);
}



// --------------------------------------------------------- BOYD DEFINITIONS --------------------------------------------------------------------------------//



Boyd::Boyd()
{
	separationWeight = 1.0f;          // Setting factors for boid functions' implementation
	cohesionWeight = 0.2f;
	alignmentWeight = 0.1f;

	separationThreshold = 15;
	neighbourhoodSize = 100;

	position = ofVec3f(ofRandom(800, 1000), ofRandom(500, 700));     // Randomising initial position
	velocity = ofVec3f(ofRandom(-10, 10), ofRandom(-10, 10));
}

Boyd::Boyd(ofVec3f& pos, ofVec3f& vel)
{
	separationWeight = 1.0f;
	cohesionWeight = 0.2f;
	alignmentWeight = 0.1f;

	separationThreshold = 15;
	neighbourhoodSize = 100;

	position = pos;     // Set to arguments
	velocity = vel;
}

Boyd::~Boyd()
{

}

ofVec3f Boyd::separation(std::vector<Boyd*>& otherBoids)
{

	for (int i = 0; i < otherBoids.size(); i++)   
	{
		if (position.distance(otherBoids[i]->getPosition()) < separationThreshold)   // If distance to boid at i is less than separationThreshold
		{
			ofVec3f v = position - otherBoids[i]->getPosition();     
			v.normalize();                
			return v;                     
		}
	}
}

ofVec3f Boyd::cohesion(std::vector<Boyd*>& otherBoids)
{
	ofVec3f average(0, 0, 0);   // New variables to calculate average i.e. centre of mass of all points
	int count = 0;   // New variable to save the count

	for (int i = 0; i < otherBoids.size(); i++)         // For all the boids apart from this one
	{
		if (position.distance(otherBoids[i]->getPosition()) < neighbourhoodSize)   // If distance between a boid and the other boid is less than 100
		{
			average += otherBoids[i]->getPosition();      // Add position of that other boid to average vector
			count += 1;                                   // Increase 
		}
	}
	average /= count;       // Get average by dividing position by count
	ofVec3f v = average - position;    // Create v to save the average minus the position of the boid
	v.normalize();                     // Normalize
	return v;                          // Return
}

ofVec3f Boyd::alignment(std::vector<Boyd*>& otherBoids)
{
	ofVec3f average(0, 0, 0);
	int count = 0;
	for (int i = 0; i < otherBoids.size(); i++)
	{
		if (position.distance(otherBoids[i]->getPosition()) < neighbourhoodSize)    // If distance to another boid is less than neighbourhoodSize
		{
			average += otherBoids[i]->getVelocity();
			count += 1;
		}
	}
	average /= count;
	ofVec3f v = average - velocity;
	v.normalize();
	return v;
}

void Boyd::update(std::vector<Boyd*>& otherBoyds, ofVec3f& min, ofVec3f& max)
{
	velocity += separationWeight * separation(otherBoyds) * 0.2;    // increase velocity according to separation of other boids and a predefined factor
	velocity += cohesionWeight * cohesion(otherBoyds) * 0.5;        // Same for cohesion and alignment
	velocity += alignmentWeight * alignment(otherBoyds) * 0.2;

	Boid::walls(min, max);   // Clipping function
	position += velocity;   // Add velocity vector to current position vector
}

void Boyd::draw(ofVec3f colour)
{
	ofSetColor(colour.x, colour.y, colour.z);
	ofDrawTriangle(position.x, position.y, position.x + 15, position.y, position.x + 7.5, position.y + 12);
	
}
