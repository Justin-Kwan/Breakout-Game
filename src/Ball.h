/**
 * Header file for Ball.cpp class
 */

#ifndef BALL_H
#define BALL_H

class Ball
{

    /**
     * lists all attributes and functions of Ball.cpp class
     * that are accessible by other classes
     */
    public:
        Ball();
        virtual ~Ball();

        float getSize();
        float getY();
        float getX();
        float updatePosition();
        float getSpeed();
        float checkBoundaries();
        float getXSpeed();
        float getYSpeed();
        float lossCount;
        void reflectY();
        void reflectX();
        float getWidth();
        float getLeftEdge();
        float getRightEdge();
        float getBottomEdge();
        float getTopEdge();
        void setX(float);
        void setY(float);
        void reset();
        void bounceLeft();
        void bounceRight();
        void freezeBall();
        void increaseSpeed();
        void setSpeed1();
        void setSpeed2();
        void setSpeed3();

    /**
     * lists all attributes and functions of Ball.cpp class
     * that are only accessible by itself
     */
    protected:

        float size;
        float xPos;
        float yPos;
        float xSpeed;
        float ySpeed;
        float width;
        float leftEdge;
        float rightEdge;
        float topEdge;
        float bottomEdge;

    private:
};

#endif // BALL_H
