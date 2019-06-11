/**
 * Class of block game object, contains all attributes (size, flags, etc) and functions
 * of block
 */

#include "Block.h"
#include <iostream>

using namespace std;

/**
 * constructor sets attributes and values to a class instance
 */
Block::Block(float size, float xPos, float yPos) {      // constructor accepts size, and x/y axis positions to set as attributes for block when new instance is declared

    this->size = size;              // setting size value to the specific block instance being built
    this->xPos = xPos;              // x and y positions of block instance in reference to ortho projection (center of squared cube)
    this->yPos = yPos;
    this->visible = true;           // flag that indicates if block instance is destroyed yet by ball
    this->leftEdge;                 // x position of block's left edge
    this->rightEdge;                // x position of block's right edge
    this->bottomEdge;               // y position of block's bottom edge
    this->topEdge;                  // y position of block's top edge

}

Block::~Block()
{
    //dtor
}

/**************************************************** Class Function Definitions *******************************************************/

/**
 * returns size of block instance
 */
float Block::getSize() {
    return this->size;
}

/**
 * returns x-position of block instance
 */
float Block::getX() {
    return this->xPos;
}

/**
 * returns y-position of block instance
 */
float Block::getY() {
    return this->yPos;
}

/**
 * returns bottom left edge position (x value) of block instance
 */
float Block::getLeftEdge() {
    leftEdge = xPos - (size / 2);               // finds left edge by subtracting half of block width by center x position
    return this->leftEdge;
}

/**
 * returns bottom right edge position (x value) of block instance
 */
float Block::getRightEdge() {
    rightEdge = xPos + (size / 2);              // finds right edge by adding half of block width by center x position
    return this->rightEdge;
}

/**
 * returns bottom edge position (y value) of block instance
 */
float Block::getBottomEdge() {
    bottomEdge = yPos - (size / 2);             // finds bottom edge by subtracting half of block height by center y position
    return this->bottomEdge;
}

/**
 * returns top edge position (y value) of block instance
 */
float Block::getTopEdge() {
    topEdge = yPos + (size / 2);                // finds top edge by adding half of block height by center y position
    return this->topEdge;
}

/**
 * flags block instance state boolean as destroyed (if hit by ball)
 */
void Block::hide() {
    this->visible = false;
}

/**
 * un-flag block instance state boolean as not destroyed for new game
 */
void Block::unHide() {
    this->visible = true;
}
