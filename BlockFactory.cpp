/**
 * Class that is responsible for creating multiple blocks, by calculating and setting their attributes
 */

#include "BlockFactory.h"
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "Block.h"

using namespace std;

// constructor
BlockFactory::BlockFactory()
{
}

BlockFactory::~BlockFactory()
{
}

/**************************************************** Class Function Definitions *******************************************************/


/**
 * function that calculates and returns width of block instance (square cube)
 */
float BlockFactory::calculateblockWidth(int blockColumnCount, int windowWidth) {    // accepts # of block columns to have and width of window in px

        // each block width is the window width (in pixels) divided num of block columns to evenly split the window by
        // so a single block width (in pixels) divided by entire window width (in pixels) gives % or ratio
        // return as float so not rounded down
        float blockWidth = ((float)(windowWidth) / blockColumnCount) / windowWidth;
        return blockWidth;
}

/**
 * function that calculates and returns width of block instance (square cube)
 */
float BlockFactory::calculateblockHeight(int blockRowCount, int windowHeight) {     // accepts # of block rows to have and height of window in px

        // each block height is the window height (in pixels) divided num of block rows to evenly split the window by
        // so a single block height (in pixels) divided by entire window height (in pixels) gives % or ratio
        // return as float so not rounded down
        float blockHeight = ((float)(windowHeight) / blockRowCount) / windowHeight;
        return blockHeight;
}

/**
 * function that finds and returns the initial coordinates of the first block in grid
 */
vector<float> BlockFactory::getInitialPoint(float blockWidth, float blockHeight) {

    vector<float> initialPoint;                     // vector to store x value in first index and y value in second index

    initialPoint.push_back(blockWidth / 2);         // first block's x position is value of half block width, bc block's center drawn at origin
    initialPoint.push_back(1 - (blockHeight / 2));  // first block's y position is 100% of screen height minus half block height, bc block's center drawn at origin

    return initialPoint;

}

/**
 * function creates and returns vector of block instances to display in main, block holds it's own info such as size, position, etc
 */
vector<Block> BlockFactory::createGrid(float windowWidth, float windowHeight) { // function accepts window width & height in px

    // call function that calculates block width/height, passing in # of block rows/columns to have and window width/height in pixels
    float blockWidth = calculateblockWidth(10, windowWidth);
    float blockHeight = calculateblockHeight(10, windowHeight);

    vector<Block> blocks;                                                   // declare vector of type block objects
    vector<float> firstPoint = getInitialPoint(blockWidth, blockHeight);    // call function that finds and returns initial point of first block given block's width and height

    float X = firstPoint[0];                    // first index is x coordinate of first block
    float Y = firstPoint[1];                    // second index is y coordinate of first block

    for(int row = 0; row < 4; row++) {          // loop through 4 times for rows

        for(int col = 0; col < 10; col++) {     // for each row, loop through 10 times for 10 columns

            Block newBlock(blockWidth, X, Y);   // create instance of block, passing in width, x, and y position to the constructor of this instance

            blocks.push_back(newBlock);         // push this new block instance into vector

            X = X + blockWidth;                 // increment x position so next block instance will be to the right (position wise)
        }

        Y = Y - blockHeight;                    // after each row, decrease y position by block height so next block will be down
        X = blockWidth / 2;                     // reset block x position so that first block in new row will start at very left

    }

    return blocks;                              // return filled vector of block instances to main

}
