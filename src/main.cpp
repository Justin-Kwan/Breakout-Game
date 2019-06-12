/**
 * Name        -> Justin Kwan
 * Date        -> January 9, 2019
 * Description -> This program is a game of brick breaker similar to Atari Breakout,
 *                where the user must reflect a bouncing ball off a moveable racket to destroy
 *                all blocks
 */

#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>
#include <string>
#include <GL/glut.h>
#include "BlockFactory.h"
#include "Ball.h"
#include "Racket.h"

/**
 * allows to use functions anywhere in file, not in order of use
 */
float calculateblockWidth(int);
float calculateblockHeight(int);
void drawBlocks();
void resetGame();
void controlGameReplay();
void drawLoseText();
void drawWinText(string);
void drawGreyedOutObjects();
void checkGameOver();
bool doBlocksExist();
bool hasBallHitBottom();
void drawGameObjects();
void drawBall();
void drawRacket();
void drawLevelCounter();
void updateBallSpeed();
void handleNoBlocksLeft();

using namespace std;

const int SCREEN_WIDTH  = 500;
const int SCREEN_HEIGHT = 500;

float ballXSpeed    = 0;        // declare variable to hold ball's x amount incremented by
float ballYSpeed    = 0;        // declare variable to hold ball's y amount incremented by
float racketXSpeed  = 0;        // declare variable to hold racket's x amount incremented by
float racketYSpeed  = 0;        // declare variable to hold racket's y amount incremented by

int levelCount      = 1;        // game level starts at 1

Ball ball;                      // create globally accessible instance of game object class ball
Racket racket;                  // create globally accessible instance of game object class ball

/**
 *  booleans that flag game and game level states
 */
bool levelIsLost = false;
bool levelIsWon  = false;
bool gameIsWon = false;
bool isLeftKeyPressed = false;
bool isRightKeyPressed = false;

vector<Block> blocks;           // declare vector of block instances

/**
 * function that runs all functions that draw game objects
 */
void drawGameObjects() {
    drawBlocks();
    drawBall();
    drawRacket();
    drawLevelCounter();         // draw level count as text on display
}

/**
 * draws game block instances in grid format
 */
void drawBlocks() {

    for(int i = 0; i <= blocks.size(); i++)  {                  // loop through vector of block instances

        if(levelIsLost == true && levelIsWon == false) {        // if current game level was lost
            glColor3f(0.25, 0.25, 0.25);                        // print blocks/remaining blocks gray
        }
        else if(levelIsWon == true && levelIsLost == false) {   // otherwise if current game level was won
            // draw gold
            glColor3f(0.24725, 0.1995, 0.0745);                 // yellow color
        }
        else if(levelCount == 1) {                              // if level is 1, these colors
            if(i >= 0 && i <= 9)                                // row 1 (top)
                glColor3f(0, 1, 1);
            else if(i >= 10 && i <= 19)                         // row 2
                glColor3f(225, 69, 0);
            else if(i >= 20 && i <= 29)                         // row 3
                glColor3f(0, 225, 0);
            else if(i >= 30 && i <= 39)                         // row 4 (bottom)
                glColor3f(225, 0, 0);
        }
        else if(levelCount == 2) {                              // different color for level 2
            if(i >= 0 && i <= 9)                                // row 1 (top)
                glColor3f(1.0, 0.0, 1.0);
            else if(i >= 10 && i <= 19)                         // row 2
                glColor3f(0, 0, 1);
            else if(i >= 20 && i <= 29)                         // row 3
                glColor3f(1, 0.5, 0);
            else if(i >= 30 && i <= 39)                         // row 4 (bottom)
                glColor3f(225, 0, 0);
        }
        else if(levelCount == 3) {                              // different color for level 3
            if(i >= 0 && i <= 9)                                // row 1 (top)
                glColor3f(0.0, 1.0, 1.0);
            else if(i >= 10 && i <= 19)                         // row 2
                glColor3f(1, 0, 1);
            else if(i >= 20 && i <= 29)                         // row 3
                glColor3f(0, 1.0, 1.0);
            else if(i >= 30 && i <= 39)                         // row 4 (bottom)
                glColor3f(1.0, 0.0, 1.0);
        }

        Block * block = &blocks[i];                             // returns block in current index and stores in alias  that points to the address of 'i'th block

        glTranslatef(block->getX(), block->getY(), 0.0);        // translate origin back to original position

        if(block->visible == true) {                            // check pointing to block object's state/boolean "visible" if the current block has not yet been hit
            if(levelCount == 3) {                               // if level is 3
                glutWireCube(block->getSize());                 // draw wire cube pointing to block object's function to get size (each frame this occurs)
            }
            else {
                glutSolidCube(block->getSize());                // solid cube draw
            }

        }

        glTranslatef(-block->getX(), -block->getY(), 0.0);      // translate origin so that viewing port's left corner will become the new origin, the place to draw block

    }

}

/**
 * function that draws the instance of ball game object declared globally
 */
void drawBall() {

    if(levelIsLost == true && levelIsWon == false) {            // if current game level is lost
        glColor3f(0.25, 0.25, 0.25);                            // ball will be gray
    }
    else if(levelIsWon == true && levelIsLost == false) {       // level is won
        glColor3f(1, 1, 0);                                     // ball will be yellow
    }
    else {                                                      // game not ended
        glColor3f(1.0f, 1.0f, 1.0f);                            // ball is white
    }

    ball.checkBoundaries();                                     // call ball instance's function that checks if ball collides with L/R/T panel walls
    ball.updatePosition();                                      // call function that updates the position of ball so it can move on panel

    glTranslatef(ball.getX(), ball.getY(), 0);                  // translate origin back to original position
    glutSolidSphere(ball.getSize(), 100, 100);                  // draw solid sphere with radius as return value of getSize() function
    glTranslatef(-ball.getX(), -ball.getY(), 0);                // translate origin so that viewing port's left corner will become the new origin, the place to draw ball

}

/**
 * function that handles calling racket movement functions of racket instance
 */
void racketMovement(string racketMovementDirection) {

    racket.checkBoundaries(racket.getX(), racket.getY());       // function that sees if racket hits right or left walls of panel/screen, passes in coordinates to check
    racketXSpeed = racket.getXSpeed();                          // gets racket's amount incremented each time in x and y axis (speed)
    racketYSpeed = racket.getYSpeed();
    racket.updatePosition(racketXSpeed, racketYSpeed, racketMovementDirection); // function that updates the position of racket so it can move on panel, considering cases of touching panel edges
                                                                                // sends racket x,y coordinates and direction moved
}

/**
 * function that draws the instance of racket game object declared globally
 */
void drawRacket() {

    if(levelIsLost == true && levelIsWon == false) {           // checks game/level states to determine what to color the racket
        glColor3f(0.25, 0.25, 0.25);
    }
    else if(levelIsWon == true && levelIsLost == false) {
        glColor3f(1, 1, 0);
    }
    else {
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    glPushMatrix();                                             // pushes current matrix translation stack
    glTranslatef(racket.getX(), racket.getY(), 0);              // translate origin back to original position
    glScalef(racket.getWidth(), racket.getHeight(), 0.0);       // scales racket with predefined width and height returned from class instance
    glutSolidCube(racket.getSize());                            // draws solid cube with size as function return of instance's getSize()
    glTranslatef(-racket.getX(), -racket.getY(), 0);            // translate origin so that viewing port's left corner will become the new origin, the place to draw racket
    glPopMatrix();                                              // pops current matrix translation stack

}

/**
 * function that draws the text on panel of level count
 */
void drawLevelCounter() {

    glColor3f(1.0, 1.0, 1.0);                                   // white text
    glPushMatrix();                                             // pushes current matrix translation stack

    string levelCountStr = to_string(levelCount);               // convert int to string
    string printLevelCount = "LEVEL: ";                         // string to be iterated through to display (level count #)
    printLevelCount.append(levelCountStr);                      // cast int value to string and concatenates to string

    glTranslatef(0.04, 0.03, 0);                                // translate origin back to original position
    glScaled(0.0003, 0.0002, 0);                                // scale text smaller

    for(int i = 0; i < printLevelCount.size(); i++) {           // loop through string and display each character
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, printLevelCount[i]);    // draw line-segmented stroke character
    }

    glTranslatef(-0.04, -0.03, 0);                              // translate origin so that viewing port's left corner will become the new origin, the place to draw text
    glPopMatrix();                                              // pops current matrix translation stack

}

/**
 * function that draws the text on panel of Game Loss
 */
void drawLoseText() {

    glColor3f(1.0, 1.0, 1.0);                                       // white text
    glPushMatrix();                                                 // pushes current matrix translation stack

    string printLives = "YOU LOST! CONTINUE? (ENTER)";              // string to be iterated through to display

    glTranslatef(0.07, 0.43, 0);                                    // translate origin back to original position
    glScaled(0.0003, 0.0004, 0);                                    // scale text

    for(int i = 0; i < printLives.size(); i++) {                    // loop through string and display each character
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, printLives[i]); // draw line-segmented stroke character
    }

    glTranslatef(-0.07, -0.43, 0);                                  // translate origin so that viewing port's left corner will become the new origin, the place to draw text
    glPopMatrix();                                                  // pops current matrix translation stack

}

/**
 * function that draws the text on panel of Level Won
 */
void drawWinText(string displayText) {

    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();

    glTranslatef(0.07, 0.43, 0);                                    // translate origin back to original position
    glScaled(0.0003, 0.0004, 0);                                    // scale text

    for(int i = 0; i < displayText.size(); i++) {                   // loop through string and display each character
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, displayText[i]);// draw line-segmented stroke character
    }

    glTranslatef(-0.07, -0.43, 0);                                  // translate origin so that viewing port's left corner will become the new origin, the place to draw text
    glPopMatrix();

}

/**
 * function that draws the text on panel of Game Over
 */
void drawGameOverText(string displayText) {

    glColor3f(1.0, 1.0, 1.0);                                       // white text
    glPushMatrix();

    glTranslatef(0.08, 0.43, 0);                                    // translate origin back to original position
    glScaled(0.0002, 0.0003, 0);                                    // scale text

    for(int i = 0; i < displayText.size(); i++) {                   // loop through string and display each character
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, displayText[i]);// draw line-segmented stroke character
    }

    glTranslatef(-0.08, -0.43, 0);                                  // translate origin so that viewing port's left corner will become the new origin, the place to draw text
    glPopMatrix();

}

/**
 * handles racket collisions with the ball
 */
void doRacketCollisions() {

    bool topHit = ball.getRightEdge() > racket.getX() - racket.getWidth() / 2.0         // check if ball's right edge is within left and right edge of racket
                  && ball.getLeftEdge() < racket.getX() + racket.getWidth() / 2.0
                  && ball.getBottomEdge() <= racket.getY() + racket.getHeight() / 2.0   // check if ball's bottom edge is lower than racket top edge
                  && ball.getY() > racket.getY();                                       // and compare ball and racket's center

    bool bottomHit = ball.getRightEdge() > racket.getX() - racket.getWidth() / 2.0      // check if right edge of ball is within right, left racket edges
                     && ball.getLeftEdge() < racket.getX() + racket.getWidth() / 2.0
                     && ball.getTopEdge() >= racket.getY() - racket.getHeight() / 2.0   // and ball's top edge is higher than racket's bottom edge (SAFETY CHECK)
                     && ball.getY() < racket.getY();                                    // and compare ball's center with racket's center (y values)

    bool leftHit = ball.getBottomEdge() <= racket.getY() + racket.getHeight() / 2.0     // check if ball's bottom edge is within racket's top and bottom edges
                   && ball.getTopEdge() >= racket.getY() - racket.getHeight() / 2.0
                   && ball.getRightEdge() >= racket.getX() - racket.getWidth() / 2.0    // and ball's right edge is greater than racket's left edge
                   && ball.getX() < racket.getX();                                      // and ball's center is less than racket's center

    bool rightHit = ball.getBottomEdge() <= racket.getY() + racket.getHeight() / 2.0    // check if ball's bottom edge is within racket's top and bottom edges
                    && ball.getTopEdge() >= racket.getY() - racket.getHeight() / 2.0
                    && ball.getLeftEdge() <= racket.getX() + racket.getWidth() / 2.0    // and ball's left edge is less than racket's right edge
                    && ball.getX() > racket.getX();                                     // and ball's center is greater than racket's center

    if(topHit) {                            // if ball hits top of racket

        if(ball.getX() < racket.getX() - racket.getWidth() * (0.3)) {   // checks if ball hits first 20% of racket
            ball.bounceLeft();              // ball bounces left (reverse xSpeed)
        }
        else if(ball.getX() > racket.getX() + racket.getWidth() * (0.3)) {  // checks if ball hits last 20% of racket
            ball.bounceRight();             // ball bounces right (reverse xSpeed)
        }
        ball.setY(ball.getY() + 0.03);      // force ball up
        ball.reflectY();                    // reflect ball direction traveling in y axis
    }
    else if(bottomHit) {                    // if ball hits bottom of racket (should never happen)
        ball.setY(ball.getY() - 0.03);      // force ball down
        ball.reflectY();                    // reflect ball direction traveling in y axis
    }
    else if(leftHit) {                      // if ball hits right of racket
        ball.setX(ball.getX() - 0.03);      // force ball left
        ball.reflectX();                    // reflect ball direction traveling in x axis
    }
    else if(rightHit) {                     // of ball hits left of racket
        ball.setX(ball.getX() + 0.03);      // force ball right
        ball.reflectX();                    // reflect ball direction traveling in x axis
    }

}


/**
 * loop through all blocks instances and check for collisions with ball
 * called upon each frame in display function
 */
void doBlockCollision() {

    string lastCollisionSide = "";          // string stores direction of racket movement (from user key press)
    checkGameOver();                        // check game over state (win/loss) on every frame

    for(int i = 0; i < blocks.size(); i++) {// loop through entire block instance vector

        Block * block = &blocks[i];         // use alias that points to address of block at 'i'th index

        if(block->visible == true) {        // if current block is not already destroyed

            /**
             * because the current collision detection sometimes may detect a vertical and horizontal block/ball collision at once (ex. top right corner)
             * we are finding the shortest distance of each collisions, and the shortest collision direction's distance will over rule the other
             */

            vector<float> distances;                    // declare vector of directions from block edges to ball edges

            // calculate distance from ball to each edge of block
            float leftDistance   = abs(ball.getRightEdge()  - block->getLeftEdge());        // distance of ball's right edge to block's left edge
            float rightDistance  = abs(ball.getLeftEdge()   - block->getRightEdge());       // distance of ball's left edge to block's right edge
            float topDistance    = abs(ball.getBottomEdge() - block->getTopEdge());         // distance of ball's bottom edge to block's top edge
            float bottomDistance = abs(ball.getTopEdge()    - block->getBottomEdge());      // distance of ball's top edge to block's bottom edge

            // push these values into vector
            distances.push_back(leftDistance);
            distances.push_back(rightDistance);
            distances.push_back(topDistance);
            distances.push_back(bottomDistance);

            sort(distances.begin(), distances.end());      // sort these values from least to greatest to find side of shortest distance

            /**
             * checking which direction ball comes from into the block's 4 different
             * edge position value
             * 2 or more conditions could be true at once, because the ball must have
             * within the block's range horizontally or vertically for a collision
             */
            bool hitLeftBlock   = ball.getRightEdge() >= block->getLeftEdge() &&
                                  ball.getRightEdge() <= block->getRightEdge();

            bool hitRightBlock  = ball.getLeftEdge() >= block->getLeftEdge() &&
                                  ball.getLeftEdge() <= block->getRightEdge();

            bool hitTopBlock    = ball.getBottomEdge() >= block->getBottomEdge() &&
                                  ball.getBottomEdge() <= block->getTopEdge();

            bool hitBottomBlock = ball.getTopEdge() >= block->getBottomEdge() &&
                                  ball.getTopEdge() <= block->getTopEdge();

            /**
             * determines actual side of collision for the block in order to reverse direction accurately using combo of conditions (2 cond)
             * further conditions will over rule one (h and v)
             * multiple will flag
             */
            bool leftHit        = hitLeftBlock && (hitTopBlock or hitBottomBlock);      // ball's right within block right and left edge and either top or bottom of ball within top or bottom of block
            bool rightHit       = hitRightBlock && (hitTopBlock or hitBottomBlock);     // ball's left within block right and left edge and either top or bottom of ball within top or bottom of block
            bool topHit         = hitTopBlock && (hitLeftBlock or hitRightBlock);       // ball's bottom within block top and bottom edge and either right or left of ball within right or left of block
            bool bottomHit      = hitBottomBlock && (hitLeftBlock or hitRightBlock);    // ball's top within block top and bottom edge and either right or left of ball within right or left of block

            if(topHit && distances[0] == topDistance && lastCollisionSide != "TOP") {   // if ball's bottom hits top of block and this distance is shortest, and the last collision was not this
                ball.reflectY();                // calls function that reflects ball travel direction in the y-axis
                block->hide();                  // sets block state to destroyed from function in class
                lastCollisionSide = "TOP";      // last collision set as top to prevent double collisions at once
            }
            else if(bottomHit && distances[0] == bottomDistance && lastCollisionSide != "BOTTOM") { // if ball's top hits bottom of block and this distance is shortest, and the last collision was not this
                ball.reflectY();                // calls function that reflects ball travel direction in the y-axis
                block->hide();                  // sets block state to destroyed from function in class
                lastCollisionSide = "BOTTOM";   // last collision set as top to prevent double collisions at once
            }
            else if(leftHit && distances[0] == leftDistance && lastCollisionSide != "LEFT") {    // if ball's right hits left of block and this distance is shortest, and the last collision was not this
                ball.reflectX();                // calls function that reflects ball travel direction in the y-axis
                block->hide();                  // sets block state to destroyed from function in class
                lastCollisionSide = "LEFT";     // last collision set as top to prevent double collisions at once
            }
            else if(rightHit && distances[0] == rightDistance && lastCollisionSide != "RIGHT") { // if ball's left hits right of block and this distance is shortest, and the last collision was not this
                ball.reflectX();                // calls function that reflects ball travel direction in the y-axis
                block->hide();                  // sets block state to destroyed from function in class
                lastCollisionSide = "RIGHT";    // last collision set as top to prevent double collisions at once
            }
        }
    }

}

/**
 * function that checks if game is over
 */
void checkGameOver() {

    bool blocksExist = doBlocksExist();     // calls function that checks if any blocks still exits (not state of destroyed)

    if(blocksExist) {                       // if blocks still exits

        bool ballHitBottom = hasBallHitBottom();    // check if ball has bit bottom of panel yet

        if(ballHitBottom) {                 // if ball has hit bottom of panel
            levelIsLost = true;             // set game state to lost so all objects will print out gray
            levelIsWon = false;             // set level state as not won
            drawLoseText();                 // calls function to draw lose text on display
            levelCount = 1;                 // reset level to 1
            racket.gameLevelCount = 1;
            racket.reset();                 // reset racket instance to original values (ex. size)
        }

    }
    else {                                  // otherwise if blocks don't exist (all destroyed and level is won)
        handleNoBlocksLeft();               // handle this case
    }

    if(levelIsWon && !gameIsWon) {          // if current level is won but the game isn't won yet (either level 1 or level 2 are won)
        drawWinText("YOU WON! CONTINUE? (ENTER)");  // call function to draw text
    }
    else if(levelIsWon && gameIsWon) {      // otherwise if current level is won and game is won (level 3 won)
        drawGameOverText("YOU BEAT THE GAME! CONTINUE? (ENTER)");   // call function to draw text
    }

}

/**
 * function that returns if ball's bottom edge is less than 0 (hits bottom for loss)
 */
bool hasBallHitBottom() {
    return ball.getBottomEdge() < 0;
}

/**
 * function that handles case if there are no blocks left (all destroyed)
 */
void handleNoBlocksLeft() {

    ball.freezeBall();                      // stop ball movement on win page

    if(levelIsWon == false) {               // if game win state is false so this is the first time only (after being flagged false in control func)
        levelCount++;                       // level should only increment once
        racket.gameLevelCount = levelCount;
        levelIsWon = true;                  // game states flagged as won for coloring

        if(levelCount <= racket.MAX_RACKET_SIZE_LEVELS) {   // check if game level is less than max times racket can be shrunken
            racket.shrinkWidth();           // shrink racket's width upon each level increment
            levelIsLost = false;            // set level is not lost
        }
        else {                              // otherwise if level 3 won (game is won) (levelCount = 4 here)
            gameIsWon = true;               // game state is won
            racket.reset();                 // reset racket instance attributes
            levelCount = 1;                 // reset to level 1
            racket.gameLevelCount = levelCount;
        }
    }
}


/**
 * function updates ball speed based on game level
 */
void updateBallSpeed() {
    // checks which level game is on to call specific function from ball instance that sets different ball speeds
    if(levelCount == 2) {
        ball.setSpeed2();
    }
    else if(levelCount == 3) {
        ball.setSpeed3();
    }
}

/**
 * function checks if all blocks have been destroyed or not
 */
bool doBlocksExist() {

    for(int i = 0; i < blocks.size(); i++) {// loop through block instance vector

        if(blocks[i].visible) {             // if there is still a block flagged as visible (not hit by ball yet)
            return true;                    // return a flag
        }
    }

    return false;                           // return a flag indicating all blocks destroyed if loop completed
}

/**
 * function that runs game object collision detection functions
 */
void computeCollisions() {
    doRacketCollisions();
    doBlockCollision();
}

/**
 * callback function that handles keys pressed to replay game
 */
void controlGameReplay(unsigned char key, int x, int y) {

    if(levelIsWon == true or levelIsLost == true) { // check that game is over either by win or loss before enter key can be enabled for use

        switch(key) {                               // checking key variable for ASCII key pressed
        case 13:                                    // if enter key is pressed
            // reset game state to false
            levelIsLost = false;
            levelIsWon  = false;
            gameIsWon = false;
            resetGame();                            // reset game objects
            break;
        }
    }
    glutPostRedisplay();                            // call glut display function
}

/**
 * function that handles reseting for new game by resetting blocks and ball states and attributes
 */
void resetGame() {

    for(int i = 0; i < blocks.size(); i++) {                    // loops through vector of blocks and un-flags all booleans to not destroyed state
        blocks[i].unHide();                                     // call current ball instance object's function to un-flag that it is destroyed
    }

    ball.reset();                                               // call ball instance object's function to reset all of its attributes
    updateBallSpeed();                                          // update ball's x and y speed based on game level each time game is reset
}

/**
 * function that creates and sets up all game objects for the first time
 */
void initGameObjects() {

    BlockFactory blockFactory;                                  // creates instance of class that creates blocks

    float windowHeight = glutGet(GLUT_WINDOW_HEIGHT);           // built in lib function that retrieves simple glut states, window height (pixels) in this case
    float windowWidth = glutGet(GLUT_WINDOW_WIDTH);             // built in lib function that retrieves simple glut states, window width (pixels) in this case

    // pre-defined number of block rows and columns
    const int blockRowCount = 4;
    const int blockColumnCount = 10;

    blocks = blockFactory.createGrid(windowWidth, windowHeight);    // call blockfactory's function to create and return vector of block instances

}

/**
 * checks global variable to see which way to move racket, calling function that interacts with racket instance functions
 */
void checkRacketKeyDirection() {

    string racketMovementDirection = "";    // string to store key pressed arrow direction

    if(isRightKeyPressed == true) {         // if right arrow key currently depressed
        racketMovementDirection = "RIGHT";  // store direction as right
        racketMovement(racketMovementDirection);    // call function that handles calling racket instance movement functions
    }
    else if(isLeftKeyPressed == true) {     // if left arrow key currently depressed
        racketMovementDirection = "LEFT";   // store direction as right
        racketMovement(racketMovementDirection);    // call function that handles calling racket instance movement functions
    }

}

/**
 * controls racket movement using arrows, passed in as callback function
 * to execute upon keystroke
 */
void controlRacketMovement(int key, int x, int y) {

    string racketMovementDirection = "";    // string stores which direction of key pressed to move racket

    switch(key) {                           // check key variable

    case GLUT_KEY_RIGHT:                    // for right arrow key
        isRightKeyPressed = true;
        break;
    case GLUT_KEY_LEFT:                     // for right arrow key
        isLeftKeyPressed = true;
        break;
    }
    glutPostRedisplay();                    // re-call glut display

}

/**
 * checks global variable to see if left/right arrow key released to stop moving racket, passed as callback in main
 */
void releaseKeyStopRacket(int key, int x, int y) {

    switch(key) {                           // check key variable

    case GLUT_KEY_RIGHT:                    // for right arrow key
        isRightKeyPressed = false;          // set flag that indicates right key is depressed false
        break;
    case GLUT_KEY_LEFT:                     // for right arrow key
        isLeftKeyPressed = false;           // set flag that indicates left key is depressed false
        break;
    }
    glutPostRedisplay();                    // re-call glut display

}

/**
 * function that draws all components
 */
void display() {

    glClear(GL_COLOR_BUFFER_BIT);                               // buffers currently enabled for color writing
    glLoadIdentity();                                           // set matrix into the original state
    glOrtho(0.0, 1, 0, 1, 0.0, 1.0);                            // viewing projection from 0-1 on x axis and 0-1 on y axis

    computeCollisions();                                        // check for game object collisions
    drawGameObjects();                                          // draws all game objects
    checkRacketKeyDirection();                                  // call function to see which way to move racket based on which arrow key pressed

    glutSwapBuffers();
    glFlush();                                                  // executes accumulated stack of function calls

}


/**
 * callback function always called upon screen update,
 * calls display function again
 */
static void idleFunc(void) {
    glutPostRedisplay();
}

/**
 * main function
 */
int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Breakout");
    // draws front and back of all polygons
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // call function that sets up all game objects
    initGameObjects();
    // pass callback function that detect racket movement
    glutSpecialFunc(controlRacketMovement);
    // pass callback function that detects keyboard strokes for ASCII keys
    glutKeyboardFunc(controlGameReplay);

    glutSpecialUpFunc(releaseKeyStopRacket);

    glutDisplayFunc(display);
    glutIdleFunc(idleFunc);
    glutMainLoop();
}
