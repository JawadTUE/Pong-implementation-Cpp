#ifndef INC_26_PONG_CPP_BALL_H
#define INC_26_PONG_CPP_BALL_H

#include "PongObject.h"

/*!
\class Ball
\brief Represents the ball in a Pong game.

Derived from PongObject, this class manages the ball's position, velocity, and interactions with game boundaries and paddles.
Provides methods to update position, detect collisions, check for out-of-bounds conditions, and reset velocity.
Implements acceleration and bounce mechanics for realistic ball movement.
*/
class Ball : public PongObject
{
public:
    /*!
    \brief Constructs a Ball object with specified parameters.
    
    Initializes a Ball object with given window limits, wall thickness, and initial velocities.
    Sets up the ball's position, velocity, and other properties for game start.
    
    \param windowLimitX The maximum x-coordinate of the game window.
    \param windowLimitY The maximum y-coordinate of the game window.
    \param wallThickness The thickness of the game's boundary walls.
    \param movingSpeedX Initial horizontal velocity of the ball.
    \param movingSpeedY Initial vertical velocity of the ball.
    */
    Ball(unsigned short int &windowLimitX,
         unsigned short int &windowLimitY,
         unsigned short int &wallThickness,
         float movingSpeedX, float movingSpeedY) : PongObject(windowLimitX, windowLimitY, wallThickness),
                                                   _velocityX(movingSpeedX),
                                                   _velocityY(movingSpeedY),
                                                   _startVelocityX(movingSpeedX),
                                                   _startVelocityY(movingSpeedY),
                                                   _hasBounced(false),
                                                   _acceleration(0.02) {};

    /*!
    \brief Updates the ball's position and handles collisions.
    
    Calculates the ball's new position based on its velocity and elapsed time.
    Detects and handles collisions with walls and the paddle, applying acceleration and reversing velocity upon impact.
    Sets the _hasBounced flag when collisions occur.
    
    \param deltaTime Time elapsed since the last frame update.
    \param wallThickness Thickness of the game's boundary walls.
    \param paddlePositionY Vertical position of the paddle's center.
    \param paddleLength Length of the paddle.
    */
    void updatePosition(float &deltaTime, unsigned short int &wallThickness, float &paddlePositionY, unsigned short int &paddleLength);
    /*!
    \brief Checks if the ball has bounced.
    
    Provides access to the ball's bounce status, which is updated in the updatePosition method.
    Used for scoring and game feedback.
    
    \return Pointer to the boolean indicating whether the ball has bounced in the current frame.
    */
    bool *hasBounced();
    /*!
    \brief Checks if the ball is out of bounds.
    
    Determines whether the ball's position is outside the game's playable area by comparing its coordinates with the window limits.
    
    \return True if the ball is out of bounds, false otherwise.
    */
    bool ballOut();
    /*!
    \brief Resets the ball's velocity to its initial values.
    
    Restores the ball's velocity components to their starting values.
    Used when the ball goes out of bounds to ensure consistent gameplay and difficulty upon restart.
    */
    void resetVelocity();

private:
    float _startVelocityX;
    float _startVelocityY;
    float _velocityX;
    float _velocityY;
    float _acceleration;
    bool _hasBounced;
};

#endif
