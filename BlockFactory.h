/**
 * Header file for BlockFactory.cpp class
 */

#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H
#include <GL/glut.h>
#include "Block.h"
#include <vector>

using namespace std;

class BlockFactory
{

    /**
     * lists all attributes and functions of BlockFactory.cpp class
     * that are accessible by other classes
     */
    public:

        BlockFactory();

        virtual ~BlockFactory();

        /**
         * these static functions can called on the class itself
         * no instance of that class is needed
         * they are independent of any attributes of the block class
         * the return is not dependent on the state (ex. visible, invisible) of the block either
         * functions shared by all block instances
         */
        static float calculateblockWidth(int, int);
        static float calculateblockHeight(int, int);

        void drawBlocks();
        vector<Block> createGrid(float, float);

   /**
    * lists all attributes and functions of BlockFactory.cpp class
    * that are only accessible by itself
    */
    protected:

        vector<float> getInitialPoint(float, float);

    private:


};

#endif // BLOCK_H
