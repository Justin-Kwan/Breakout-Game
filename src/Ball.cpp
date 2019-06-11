/**
 * Class of ball game object, contains all attributes (size, flags, etc) and functions
 * of the ball
 */

#include "Ball.h"
#include <windows.h>
#include <iostream>
#include <cmath>

using namespace std;

/**
 * constructor sets attributes and values to a class instance
 * in this case, constructor calls reset function to set all Ball instance attributes to original values
 */
Ball::Ball() {
   reset();
}

Ball::~Ball(){}

/**
 * resets all ball instance attributes, useful for game restart
 */
void Ball::reset() {

    this->size      = 0.015;        // defines ball/sphere radius, same value passed into glutSolidSphere()
    this->xPos      = 0.5;          // ball x position (in reference to orthographic projection), center of sphere
    this->yPos      = 0.15;         // ball x position (in reference to orthographic projection), center of sphere
    this->xSpeed    = 0.0006;       // amount of incrementation for x position of sphere
    this->ySpeed    = 0.00078;       // amount of incrementation for y position of sphere
    this->width     = size * 2.0;   // entire width of sphere is 2 times the radius
    this->leftEdge;                 // stores calculated edges of sphere in 2D
    this->rightEdge;
    this->topEdge;
    this->bottomEdge;

}

/**
 * returns size of ball instance, basically is radius of sphere, same value passed into glutSolidSphere()
 */
float Ball::getSize() {
    return this->size;
}

/**
 * returns ball instance's current x coordinate (center of sphere)
 */
float Ball::getX() {
    return this->xPos;
}

/**
 * returns ball instance's current y coordinate (center of sphere)
 */
float Ball::getY() {
    return this->yPos;
}

/**
 * function that updates the position of ball so it can move on panel
 */
float Ball::updatePosition() {
    this->xPos = this->xPos + this->xSpeed;     // current ball's x position (center) adds by x value to increment by on x axis
    this->yPos = this->yPos + this->ySpeed;     // current ball's y position (center) adds by y value to increment by on y axis
}

/**
 * returns current x value incremented by on x axis for ball instance
 */
float Ball::getXSpeed() {
    return this->xSpeed;
}

/**
 * returns current y value incremented by on y axis for ball instance
 */
float Ball::getYSpeed() {
    return this->ySpeed;
}

/**
 * reflects ball's x direction traveling by reversing the x amount incremented by (speed)
 */
void Ball::reflectX() {
    this->xSpeed = - this->xSpeed;
}

/**
 * reflects ball's y direction traveling by reversing the y amount incremented by (speed)
 */
void Ball::reflectY() {
    this->ySpeed = - this->ySpeed;
}

/**
 * reverses ball's x direction traveling if ball hits very left or right edge of racket
 */
void Ball::bounceRight() {

    if(xSpeed < 0) {                            // if ball is incoming to racket from the right
        xSpeed = - xSpeed;                      // reverse x amount incremented by so ball goes other way to left
    }
}
void Ball::bounceLeft() {

    if(xSpeed > 0) {                            // if ball is incoming to racket from the left
        xSpeed = -xSpeed;                       // reverse x amount incremented by so ball goes other way to right
    }

}

/**
 * function that returns the width of ball instance
 */
float Ball::getWidth() {
    return this->width;
}

/**
 * finds and returns left edge position of ball instance
 */
float Ball::getLeftEdge() {
    this->leftEdge = this->xPos - size;         // finds left edge by subtracting radius by center x position
    return this->leftEdge;
}

/**
 * finds and returns right edge position of ball instance
 */
float Ball::getRightEdge() {
    this->rightEdge = this->xPos + size;        // finds right edge by adding radius to the center x position
    return this->rightEdge;
}

/**
 * finds and returns bottom edge position of ball instance
 */
float Ball::getBottomEdge() {
    this->bottomEdge = this->yPos - size;       // finds bottom edge by subtracting radius by the center y position
    return this->bottomEdge;
}

/**
 * finds and returns top edge position of ball instance
 */
float Ball::getTopEdge() {
    this->topEdge = this->yPos + size;         // finds top edge by adding radius to the center y position
    return this->topEdge;
}

/**
 * checks if ball collides with panel walls
 */
float Ball::checkBoundaries() {

    if(this->getRightEdge() >= 1.0 or this->getLeftEdge() <= 0) {   // if ball hits right panel wall or left panel wall
        this->reflectX();                       // reflects ball's x direction traveling
    }
    if(this->getTopEdge() >= 1.0) {             // if ball hits top panel wall
        this->reflectY();                       // reflects ball's y direction traveling
    }
}

/**
 * updates ball instance's x-position with value that was passed in
 */
void Ball::setX(float newX) {
    this->xPos = newX;
}

/**
 * updates ball instance's y-position with value that was passed in
 */
void Ball::setY(float newY) {
    this->yPos = newY;
}

/**
 * sets ball's x and y amount incremented by (speed) to 0 so ball ceases movement
 */
void Ball::freezeBall() {
    this->xSpeed = 0;
    this->ySpeed = 0;
}

/**
 * sets an increased speed for level 2
 */
void Ball::setSpeed2() {
    this->xSpeed = 0.0008;                  // updates x and y amounts incremented by on x and y axis
    this->ySpeed = 0.00088;
}

/**
 * sets an increased speed for level 3
 */
void Ball::setSpeed3() {
    this->xSpeed = 0.00095;                 // updates x and y amounts incremented by on x and y axis
    this->ySpeed = 0.001;
}
