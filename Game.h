#ifndef INC_26_PONG_CPP_GAME_H
#define INC_26_PONG_CPP_GAME_H

#include <SDL2/SDL.h>
#include <iostream>
#include <thread>
#include "Ball.h"
#include "Paddle.h"
#include <memory>

/*!
\class Game
\brief Manages the core functionality of a Pong game.

Handles game initialization, main loop, input processing, state updates, and rendering.
Utilizes SDL for graphics and window management.
Contains and manages game objects like ball and paddle.
Tracks game score, handles collisions, updates object positions, and manages visual output including color changes and wall rendering.
*/
class Game
{
public:
    /*!
    \brief Constructs a Game object with specified parameters.
    
    Initializes the Game object with given window dimensions, paddle size, and wall configuration.
    Sets up initial game state, including score, wall thickness, and creates Ball and Paddle objects.
    
    \param windowSizeX The width of the game window.
    \param windowSizeY The height of the game window.
    \param paddleSize The size (length) of the paddle.
    \param isRightWall Boolean indicating whether to include a right wall in the game.
    */
    Game(unsigned short int windowSizeX, unsigned short int windowSizeY, unsigned short int paddleSize, bool isRightWall);
    /*!
    \brief Initializes the game's graphical components.
    
    Sets up SDL video subsystem, creates the game window, and initializes the renderer.
    Handles any initialization errors by logging them and returning false.
    
    \return True if initialization is successful, false otherwise.
    */
    bool Initialize();
    /*!
    \brief Executes the main game loop.
    
    Runs the core game cycle continuously, processing input, updating game state, and rendering output in each iteration.
    Continues until the game is terminated.
    */
    void GameLoop();
    /*!
    \brief Cleans up and shuts down the game.
    
    Destroys the SDL window and renderer, and terminates the SDL subsystem.
    Ensures proper resource management and a clean exit of the game.
    */
    void ShutDownGame();

private:
    bool mIsRunning = true;

    /*!
    \brief Processes user input and system events.
    
    Handles SDL events, including quit events, and updates the game state.
    Captures the current keyboard state to detect key presses, such as the escape key for game exit.
    */
    void ProcessInput();
    /*!
    \brief Updates the game state for each frame.
    
    Calculates frame time, updates paddle and ball positions, checks for collisions and out-of-bounds conditions, manages scoring, and updates visual representations of game objects.
    Ensures game progression based on player actions and game events.
    */
    void UpdateGame();
    /*!
    \brief Renders the current game state to the screen.
    
    Clears the previous frame, draws game elements (walls, paddle, ball) with appropriate colors and positions.
    Handles visual effects like ball color swapping.
    Ensures the display reflects the current game state, providing smooth and responsive graphics.
    */
    void GenerateOutput();

    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    unsigned short int _windowSizeX;
    unsigned short int _windowSizeY;
    bool _isRightWall;
    unsigned short int _wallThickness;
    long int _score;
    bool _colorSwap;

    /*!
    \brief Retrieves the wall thickness.
    
    Provides access to the thickness of the game's walls, which is used for rendering and collision detection.
    
    \return Pointer to the unsigned short int representing the wall thickness.
    */
    unsigned short int *getWallThickness();

    const Uint8 *state;

    Uint32 mTicksCount;

    std::shared_ptr<Ball> ball1;
    std::shared_ptr<Paddle> paddle1;
};

#endif
