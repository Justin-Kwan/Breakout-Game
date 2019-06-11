/**
 * Class of racket game object, contains all attributes (size, speed, etc) and functions
 * of the racket
 */

#include "Racket.h"     // include racket header file

/**
 * constructor sets attributes and values to a class instance
 * in this case, constructor calls reset function to set all racket attributes to original values
 */
Racket::Racket() {
    reset();
}

Racket::~Racket()
{
    //dtor
}

/**************************************************** Class Function Definitions *******************************************************/

/**
 * resets all racket instance attributes, useful for game restart
 */
void Racket::reset() {

  this->size      = 1.0;                        // set original racket size to 1 by 1 (matching ortho projection), based on height and width
  this->xPos      = 0.5;                        // ball at middle of screen
  this->yPos      = 0.1;
  this->xSpeed    = 0.002;                       // amount to increment by x and y values
  this->ySpeed    = 0;                          // racket does not move vertically
  // size (1) * 0.04 = 0.04
  // exactly that size on screen
  this->height    = 0.025;                      // height of racket (value to scale by in y axis)
  this->width     = 0.2;                        // width of racket (value to scale by in x axis)
  this->gameLevelCount = 0;
  this->countShrinks = 0;
  this->isTouchingLeftWall  = false;            // boolean flags if racket is touching left wall of panel
  this->isTouchingRightWall = false;            // boolean flags if racket is touching right wall of panel
  this->racketMovementDirection   = "";         // string that updatePosition() receives from main to determine which way racket was moved

}

/**
 * returns size of racket instance
 */
float Racket::getSize() {
    return this->size;
}

/**
 * returns x position of racket instance (center of racket)
 */
float Racket::getX() {
    return this->xPos;
}

/**
 * returns y position of racket instance (center of racket)
 */
float Racket::getY() {
    return this->yPos;
}

/**
 * function that updates the position of racket so it can move on panel, and handles if it is touching a panel wall
 * receives x and y values to increment by on x and y axis, and a string indicating left or right
 */
float Racket::updatePosition(float updateX, float updateY, string racketMovementDirection) {

    if(racketMovementDirection == "LEFT") {         // if racket is moving left from left key push

        if(isTouchingRightWall == true) {           // and the racket is touching right wall of panel
            xPos = xPos - updateX;                  // update x value by decrementing x position to go left
        }
        else if(isTouchingRightWall == false && isTouchingLeftWall == false) {  // otherwise if racket is not touching any walls
            xPos = xPos - updateX;                  // update x value by decrementing x position to go left
        }

    }
    else if(racketMovementDirection == "RIGHT") {   // if racket is moving right from right key push

        if(isTouchingLeftWall == true) {            // and racket is touching right wall of panel
            xPos = xPos + updateX;                  // move racket right
        }
        else if(isTouchingLeftWall == false && isTouchingRightWall == false) {      // otherwise if racket isn't touching any walls
            xPos = xPos + updateX;                  // move racket right
        }

    }

}

/**
 * function that returns the value for racket to increment by on x axis
 */
float Racket::getXSpeed() {
    return this->xSpeed;                   // return value for racket to increment on x axis relative to screen orthographic projection
}

/**
 * function that returns the value for racket to increment by on y axis
 */
float Racket::getYSpeed() {
    return this->ySpeed;                   // return value for racket to increment on y axis relative to screen orthographic projection
}

/**
 * function that returns the width of racket (value to scale by in x axis)
 */
float Racket::getWidth() {
    return this->width;
}

/**
 * function that returns the height of racket (value to scale by in y axis)
 */
float Racket::getHeight() {
    return this->height;
}



/**
 * function that updates value for racket (square cube) to scale by in x axis
 * decreases width for added difficulty as game level increments
 */
void Racket::shrinkWidth() {

    width = width - 0.05;                   // x value to scale by (in main) decreases

    countShrinks++;
    cout<<":"<<countShrinks<<endl;
    if(countShrinks == 3) {
            cout<<"resetting val"<<endl;
        countShrinks = 0;
    }


}

/**
 * function that sees if racket hits right or left walls of panel/screen
 */
float Racket::checkBoundaries(float checkX, float checkY) {     // function receives x and y coordinates of racket to compare against

    if(countShrinks == 0) {

        if(checkX > 1.0 - 0.1) {                                    // if racket hits or passes right side of panel (plus offset)
            this->isTouchingRightWall = true;                       // flag instance's boolean to indicate so
        }
        else if(checkX < 0 + 0.1) {                                 // otherwise if racket hits or passes left side of panel (plus offset)
            this->isTouchingLeftWall = true;                        // flag instance's boolean to indicate so
        }
        else {                                                      // otherwise if racket has not collided with a panel wall
            this->isTouchingLeftWall = false;                       // booleans flagged as false to indicate so
            this->isTouchingRightWall = false;
        }

    }
    else if(countShrinks == 1) {

        if(checkX > 1.0 - 0.068) {                                    // if racket hits or passes right side of panel (plus offset)
            this->isTouchingRightWall = true;                       // flag instance's boolean to indicate so
        }
        else if(checkX < 0 + 0.068) {                                 // otherwise if racket hits or passes left side of panel (plus offset)
            this->isTouchingLeftWall = true;                        // flag instance's boolean to indicate so
        }
        else {                                                      // otherwise if racket has not collided with a panel wall
            this->isTouchingLeftWall = false;                       // booleans flagged as false to indicate so
            this->isTouchingRightWall = false;
        }

    }
    else if(countShrinks == 2) {

        if(checkX > 1.0 - 0.055) {                                    // if racket hits or passes right side of panel (plus offset)
            this->isTouchingRightWall = true;                       // flag instance's boolean to indicate so
        }
        else if(checkX < 0 + 0.055) {                                 // otherwise if racket hits or passes left side of panel (plus offset)
            this->isTouchingLeftWall = true;                        // flag instance's boolean to indicate so
        }
        else {                                                      // otherwise if racket has not collided with a panel wall
            this->isTouchingLeftWall = false;                       // booleans flagged as false to indicate so
            this->isTouchingRightWall = false;
        }

    }



}
