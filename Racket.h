/**
 * Header file for Racket.cpp class
 */

#ifndef RACKET_H
#define RACKET_H
#include <iostream>

using namespace std;

class Racket
{
    /**
     * lists all attributes and functions of racket.cpp class
     * that are accessible by other classes
     */
    public:
        Racket();
        virtual ~Racket();

        float getSize();
        float getY();
        float getX();
        float updatePosition(float, float, string);
        float getSpeed();
        float checkBoundaries(float, float);
        float getXSpeed();
        float getYSpeed();
        float getWidth();
        float getHeight();
        float firstThird;
        float secondThird;
        float thirdThird;
        void shrinkWidth();
        int gameLevelCount;
        int countShrinks;
        // max # of game levels/racket size decreases allowed
        // constant attribute
        const int MAX_RACKET_SIZE_LEVELS = 3;
        void reset();

    /**
     * lists all attributes and functions of Racket.cpp class
     * that are only accessible by itself
     */
    protected:

        float size;
        float xPos;
        float yPos;
        float xSpeed;
        float ySpeed;
        bool isTouchingLeftWall;
        bool isTouchingRightWall;
        string racketMovementDirection;
        float height;
        float width;

    private:
};

#endif // RACKET_H
