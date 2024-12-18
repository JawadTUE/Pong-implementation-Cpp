#ifndef INC_26_PONG_CPP_PONGOBJECT_H
#define INC_26_PONG_CPP_PONGOBJECT_H

#include <vector>
#include <random>
#include <SDL2/SDL.h>

/*!
\class XYPosition
\brief Represents a 2D position with floating-point coordinates.

A simple data structure containing two members, x and y, which store the horizontal and vertical components of a position respectively.
Used to manage and track the positions of various game objects in a 2D space.
*/
struct XYPosition
{
    float x;
    float y;
};

/*!
\class PongObject
\brief Base class for game objects in a Pong game.

Provides common attributes and methods for position, size, color, and rendering of game objects.
Manages object dimensions, window boundaries, and drawing properties.
Offers functions to update visual representation, switch colors randomly, and access or modify object properties.
Serves as the foundation for specific game elements like paddles and balls.
*/
class PongObject
{
public:
    /*!
    \brief Constructs a PongObject with specified game boundaries and wall thickness.
    
    Initializes a PongObject with given window limits and wall thickness.
    Sets the object's initial position to the center of the game area, initializes its dimensions, and sets up the drawing object for rendering.
    
    \param windowLimitX The maximum x-coordinate of the game window.
    \param windowLimitY The maximum y-coordinate of the game window.
    \param wallThickness The thickness of the game's boundary walls, also used as the initial length and thickness of the object.
    */
    PongObject(unsigned short int &windowLimitX, unsigned short int &windowLimitY, unsigned short int &wallThickness) : _thickness(wallThickness),
                                                                                                                        _length(wallThickness),
                                                                                                                        _position({static_cast<float>(windowLimitX) / 2, static_cast<float>(windowLimitY) / 2}),
                                                                                                                        _windowLimitX(windowLimitX),
                                                                                                                        _windowLimitY(windowLimitY),
                                                                                                                        _color({255, 255, 255})
    {
        _drawingObject.x = _position.x - static_cast<float>(_thickness) / 2;
        _drawingObject.y = _position.y - static_cast<float>(_length) / 2;
        _drawingObject.w = _thickness;
        _drawingObject.h = _length;
    };
    /*!
    \brief Destructor for the PongObject class.
    
    Virtual destructor that allows for proper cleanup of derived classes.
    Currently, it does not perform any specific cleanup operations as the class doesn't manage any dynamically allocated resources.
    */
    ~PongObject() {};

    /*!
    \brief Updates the drawing object's dimensions and position.
    
    Synchronizes the SDL_Rect structure used for rendering with the current position and dimensions of the game object.
    Ensures accurate visual representation of the object's state on screen.
    */
    void updateDrawingObject();
    /*!
    \brief Randomly changes the object's color.
    
    Generates a new random color for the object by setting each RGB component to a value between 50 and 255.
    Used for visual effects to indicate special game events or state changes.
    */
    void switchColor();

    /*!
    \brief Retrieves the object's current position.
    
    Provides access to the object's position, crucial for collision detection and physics calculations in the game.
    
    \return Pointer to the XYPosition structure containing the object's x and y coordinates.
    */
    XYPosition *getPosition();
    /*!
    \brief Retrieves the object's drawing rectangle.
    
    Provides access to the SDL_Rect structure that represents the object's visual boundaries.
    Used in the rendering process to accurately display the object on screen.
    
    \return Pointer to the SDL_Rect structure containing the object's position and dimensions for rendering.
    */
    SDL_Rect *getDrawingObject();
    /*!
    \brief Retrieves the object's current color.
    
    Provides access to the object's color, which may change dynamically during gameplay.
    Used in the rendering process to apply the correct color to the object.
    
    \return Vector of three unsigned short integers representing the RGB values of the object's color.
    */
    std::vector<unsigned short int> getColor();

    /*!
    \brief Retrieves the object's length.
    
    Provides access to the object's length, crucial for collision detection and physics calculations, especially for paddle-ball interactions.
    
    \return Pointer to the unsigned short int representing the object's length.
    */
    unsigned short int *getLength();
    /*!
    \brief Retrieves the object's thickness.
    
    Provides access to the object's thickness, which is used for rendering and potentially for collision detection calculations.
    
    \return Pointer to the unsigned short int representing the object's thickness.
    */
    unsigned short int *getThickness();
    /*!
    \brief Sets the object's position.
    
    Updates the object's position to the specified coordinates.
    Used for resetting the ball's position after it goes out of bounds or for initializing object positions.
    
    \param x The new x-coordinate of the object's position.
    \param y The new y-coordinate of the object's position.
    */
    void setPosition(float x, float y);
    /*!
    \brief Sets the window boundaries for the object.
    
    Updates the internal window limit values used for constraining the object's movement and determining out-of-bounds conditions.
    
    \param windowLimitX The maximum x-coordinate of the game window.
    \param windowLimitY The maximum y-coordinate of the game window.
    */
    void setWindowLimits(unsigned short int, unsigned short int);

protected:
    unsigned short int _windowLimitX;
    unsigned short int _windowLimitY;
    XYPosition _position;
    unsigned short int _length;
    unsigned short int _thickness;
    std::vector<unsigned short int> _color;
    SDL_Rect _drawingObject;
};

#endif
