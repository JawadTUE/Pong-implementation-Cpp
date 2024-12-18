#include "Ball.h"

/*!
Returns a pointer to the boolean flag indicating whether the ball has bounced in the current frame.
This status is updated in the updatePosition method and is used for scoring and providing game feedback.
*/
bool *Ball::hasBounced() { return &_hasBounced; }

/*!
Checks if the ball has moved outside the game's boundaries by comparing its position to the window limits.
Returns true if the ball is out of bounds, false otherwise, allowing the game to handle scoring and ball reset.
*/
bool Ball::ballOut()
{
    return _position.x < 0 ||
           _position.y < 0 ||
           _position.x > static_cast<float>(_windowLimitX) ||
           _position.y > static_cast<float>(_windowLimitY);
}

/*!
Resets the ball's velocity to its initial values, restoring both x and y components.
This function is typically called when the ball goes out of bounds to ensure consistent gameplay and maintain the initial difficulty level upon restarting.
*/
void Ball::resetVelocity()
{
    _velocityX = _startVelocityX;
    _velocityY = _startVelocityY;
}

/*!
Updates the ball's position based on its velocity and elapsed time.
Handles collisions with walls and the paddle, reversing velocity and applying acceleration upon impact.
Sets the _hasBounced flag when a collision occurs, allowing for score tracking and game state updates.
*/
void Ball::updatePosition(float &deltaTime, unsigned short int &wallThickness, float &paddlePositionY, unsigned short int &paddleLength)
{
    _position.x += _velocityX * deltaTime;
    _position.y += _velocityY * deltaTime;

    _hasBounced = false;

    if (_position.y <= static_cast<float>(wallThickness) && _velocityY < 0)
    {
        _velocityY *= -(1 + _acceleration);
        _hasBounced = true;
    }
    if (_position.y >= static_cast<float>(_windowLimitY - wallThickness) && _velocityY > 0)
    {
        _velocityY *= -(1 + _acceleration);
        _hasBounced = true;
    }
    if (_position.x >= static_cast<float>(_windowLimitX - wallThickness) && _velocityX > 0)
    {
        _velocityX *= -(1 + _acceleration);
        _hasBounced = true;
    }

    if (_position.x <= static_cast<float>(wallThickness) &&
        _velocityX < 0 &&
        _position.y <= paddlePositionY + paddleLength / 2 &&
        _position.y >= paddlePositionY - paddleLength / 2)
    {
        _velocityX *= -(1 + _acceleration);
        _hasBounced = true;
    }
}
