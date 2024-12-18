#ifndef INC_26_PONG_CPP_PADDLE_H
#define INC_26_PONG_CPP_PADDLE_H

#include "PongObject.h"

/*!
\class Paddle
\brief Represents a paddle in a Pong game.

Derived from PongObject, this class manages the paddle's position, movement speed, and direction.
Provides methods to update the paddle's position based on user input, ensuring it stays within game boundaries.
Offers access to paddle direction and moving speed for game logic and collision detection.
*/
class Paddle : public PongObject
{
public:
    /*!
    \brief Constructs a Paddle object with specified parameters.
    
    Initializes a Paddle object with given window limits, wall thickness, moving speed, and length.
    Sets the paddle's initial position to the middle of the left side of the game area.
    
    \param windowLimitX The maximum x-coordinate of the game window.
    \param windowLimitY The maximum y-coordinate of the game window.
    \param wallThickness The thickness of the game's boundary walls.
    \param movingSpeed The speed at which the paddle moves.
    \param length The vertical length of the paddle.
    */
    Paddle(unsigned short int &windowLimitX, unsigned short int &windowLimitY, unsigned short int &wallThickness, float movingSpeed, unsigned short int length) : PongObject(windowLimitX, windowLimitY, wallThickness), _mPaddleMovingSpeed(movingSpeed), _mPaddleDirection(0)
    {
        _length = length;
        _position.x = static_cast<float>(_thickness) / 2;
        _position.y = static_cast<float>(_windowLimitY) / 2;
    };

    /*!
    \brief Updates the paddle's position based on user input.
    
    Calculates the paddle's new position based on keyboard input and elapsed time.
    Ensures the paddle stays within the game boundaries and provides smooth movement.
    
    \param sdlKeyboardStateUp Boolean indicating if the 'up' key (W) is pressed.
    \param sdlKeyBoardStateDown Boolean indicating if the 'down' key (S) is pressed.
    \param deltaTime Time elapsed since the last frame update, used for smooth movement calculation.
    */
    void changePaddlePosition(bool, bool, float);

    /*!
    \brief Retrieves the paddle's movement direction.
    
    Provides access to the current direction of the paddle's movement, which is used for updating the paddle's position and potentially for game logic.
    
    \return Pointer to the short int representing the paddle's direction (-1 for up, 0 for stationary, 1 for down).
    */
    short int *getPaddleDirection();
    /*!
    \brief Retrieves the paddle's movement speed.
    
    Provides access to the current movement speed of the paddle, which is used for calculating the paddle's position updates.
    
    \return Pointer to the float representing the paddle's moving speed.
    */
    float *getPaddleMovingSpeed();
    ;

private:
    short int _mPaddleDirection;
    float _mPaddleMovingSpeed;
};

#endif
