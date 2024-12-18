#include "Paddle.h"

/*!
Updates the paddle's position based on user input and elapsed time.
Calculates the movement direction from keyboard states, applies the paddle's speed, and ensures the paddle stays within game boundaries.
Provides smooth movement by incorporating frame time into position calculations.
*/
void Paddle::changePaddlePosition(bool sdlKeyboardStateUp, bool sdlKeyBoardStateDown, float deltaTime)
{
    _mPaddleDirection = 0;
    if (sdlKeyboardStateUp)
        _mPaddleDirection -= 1;
    if (sdlKeyBoardStateDown)
        _mPaddleDirection += 1;

    if (static_cast<int>(_position.y) + _length / 2 > _windowLimitY)
    {
        _position.y = static_cast<float>(_windowLimitY) - static_cast<float>(_length) / 2;
    }
    else if (static_cast<int>(_position.y) - _length / 2 < 0)
    {
        _position.y = 0 + static_cast<float>(_length) / 2;
    }
    else
        _position.y += static_cast<float>(_mPaddleDirection) * _mPaddleMovingSpeed * deltaTime;
}

/*!
Returns a pointer to the paddle's current movement direction.
This value indicates whether the paddle is moving up (-1), down (1), or is stationary (0), and is used for updating the paddle's position and potentially in game logic calculations.
*/
short int *Paddle::getPaddleDirection() { return &_mPaddleDirection; }

/*!
Returns a pointer to the paddle's current movement speed.
This value is used in calculating position updates, allowing for consistent and adjustable paddle movement speed throughout the game.
*/
float *Paddle::getPaddleMovingSpeed() { return &_mPaddleMovingSpeed; }
