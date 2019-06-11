/**
 * Header file for Block.cpp class
 */

#ifndef BLOCK_H
#define BLOCK_H

class Block
{
    /**
     * declare class attributes and functions accessible by all classes
     */
    public:

        virtual ~Block();

        // constructor, input size and position, declares to block constructor in cpp
        Block(float, float, float);
        float getSize();
        float getY();
        float getX();
        bool  visible;
        float getLeftEdge();
        float getRightEdge();
        float getBottomEdge();
        float getTopEdge();
        void hide();
        void unHide();


    /**
     * declare class attributes and functions only accessible by Block.cpp class
     */
    protected:

        float size = 0;
        float xPos = 0;
        float yPos = 0;
        float leftEdge = 0;
        float rightEdge = 0;
        float bottomEdge = 0;
        float topEdge = 0;

    private:

};

#endif // BLOCK_H
