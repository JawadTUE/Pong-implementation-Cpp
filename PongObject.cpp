#include "PongObject.h"

/*!
Updates the object's position to the specified x and y coordinates.
This function is used for repositioning game objects, such as resetting the ball's position after it goes out of bounds or initializing object positions during game setup.
*/
void PongObject::setPosition(float x, float y)
{
    _position.x = x;
    _position.y = y;
}

/*!
Updates the internal window limit values for the game object.
These limits are used to constrain the object's movement and determine out-of-bounds conditions, ensuring that game elements stay within the defined game area.
*/
void PongObject::setWindowLimits(unsigned short int windowLimitX, unsigned short int windowLimitY)
{
    _windowLimitX = windowLimitX;
    _windowLimitY = windowLimitY;
}

/*!
Returns a pointer to the SDL_Rect structure representing the object's visual boundaries.
This function is crucial for the rendering process, providing the necessary information to accurately display the object on screen.
*/
SDL_Rect *PongObject::getDrawingObject() { return &_drawingObject; }

/*!
Updates the SDL_Rect structure used for rendering, synchronizing it with the object's current position and dimensions.
This ensures that the visual representation of the game object accurately reflects its current state on the screen.
*/
void PongObject::updateDrawingObject()
{
    _drawingObject.x = _position.x - static_cast<float>(_thickness) / 2;
    _drawingObject.y = _position.y - static_cast<float>(_length) / 2;
    _drawingObject.w = _thickness;
    _drawingObject.h = _length;
}

/*!
Randomly changes the object's color by generating new RGB values between 50 and 255 for each component.
This function is used to create visual effects, potentially indicating special game events or state changes.
*/
void PongObject::switchColor()
{
    std::random_device fluxCapacitor;
    std::uniform_int_distribution randomColor(50, 255);
    std::mt19937 randomGen(fluxCapacitor());
    for (int i = 0; i < 3; i++)
    {
        _color[i] = randomColor(randomGen);
    }
}

/*!
Returns a vector of three unsigned short integers representing the RGB values of the object's current color.
This function is used in the rendering process to apply the correct color to the object, which may change dynamically during gameplay.
*/
std::vector<unsigned short int> PongObject::getColor() { return _color; }

/*!
Returns a pointer to the object's current position, stored as an XYPosition structure.
This function is essential for accessing the object's coordinates, facilitating collision detection and physics calculations in the game.
*/
XYPosition *PongObject::getPosition() { return &_position; }

/*!
Returns a pointer to the object's length, represented as an unsigned short integer.
This function is essential for accessing the object's size, which is crucial for collision detection and physics calculations, particularly in paddle-ball interactions.
*/
unsigned short int *PongObject::getLength() { return &_length; }

/*!
Returns a pointer to the object's thickness, stored as an unsigned short integer.
This function provides access to the object's width, which is used for rendering and potentially in collision detection calculations.
*/
unsigned short int *PongObject::getThickness() { return &_thickness; }
