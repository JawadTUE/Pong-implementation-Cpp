#include "Game.h"

/*!
Initializes the game with specified window dimensions, paddle size, and wall configuration.
Sets up the initial game state, including score and wall thickness.
Creates Ball and Paddle objects with predefined parameters, positioning them within the game window.
Prepares the game for start by initializing all necessary components and settings.
*/
Game::Game(unsigned short int windowSizeX, unsigned short int windowSizeY, unsigned short int paddleSize, bool isRightWall) : _windowSizeX(windowSizeX),
                                                                                                                              _windowSizeY(windowSizeY),
                                                                                                                              _isRightWall(isRightWall),
                                                                                                                              _wallThickness(15),
                                                                                                                              _score(0),
                                                                                                                              _colorSwap(false),
                                                                                                                              ball1(new Ball(windowSizeX, windowSizeY, _wallThickness, 200.0f, 250.0f)),
                                                                                                                              paddle1(new Paddle(windowSizeX, windowSizeY, _wallThickness, 300.0f, paddleSize)) {};

/*!
Initializes the game's graphical components using SDL.
Sets up the video subsystem, creates the game window, and initializes the renderer.
Handles initialization errors by logging them.
Returns true if successful, false otherwise, allowing the main function to proceed with the game loop or terminate if initialization fails.
*/
bool Game::Initialize()
{
    int sdlInitializeResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlInitializeResult != 0)
    {
        SDL_Log("Have not been able to initialize SDL; error message: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("Pong in C++ - by Tamas Dinh", 300, 100, _windowSizeX, _windowSizeY, 0);

    if (mWindow == nullptr)
    {
        SDL_Log("Game window initialization failed! Error message: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
    if (mRenderer == nullptr)
    {
        SDL_Log("Game renderer initialization failed! Error message: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);
    SDL_RenderPresent(mRenderer);

    return true;
}

/*!
Performs cleanup operations to shut down the game.
Destroys the SDL window and renderer, and terminates the SDL subsystem.
This function ensures proper resource management and a clean exit of the game, preventing memory leaks and other potential issues.
*/
void Game::ShutDownGame()
{
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

/*!
Executes the main game loop, continuously processing input, updating game state, and rendering output.
This function runs until the game is terminated, calling ProcessInput, UpdateGame, and GenerateOutput in each iteration to maintain gameplay flow and responsiveness.
*/
void Game::GameLoop()
{

    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

/*!
Handles user input and system events using SDL.
Processes quit events and captures the current keyboard state, specifically checking for the escape key to exit the game.
Updates the game's running state based on these inputs, allowing for responsive user interaction and game control.
*/
void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        }
    }
    state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE])
        mIsRunning = false;
}

/*!
Updates the game state for each frame.
Calculates frame time, updates paddle and ball positions, checks for collisions and out-of-bounds conditions, and manages scoring.
Handles ball reset when out of bounds, updates visual representations of game objects, and ensures game progression based on player actions and game events.
*/
void Game::UpdateGame()
{

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    mTicksCount = SDL_GetTicks();

    if (deltaTime > 0.05f)
        deltaTime = 0.05f;

    paddle1->changePaddlePosition(state[SDL_SCANCODE_W], state[SDL_SCANCODE_S], deltaTime);

    ball1->updatePosition(deltaTime, _wallThickness, paddle1->getPosition()->y, *(paddle1->getLength()));
    if (ball1->ballOut())
    {
        _score -= 10;
        std::cout << "\nBALL OUT!!! Score decremented by 10pts --" << " SCORE: " << _score << "\n"
                  << std::endl;
        ball1->setPosition(_windowSizeX / 2, _windowSizeY / 2);
        ball1->resetVelocity();
        _colorSwap = true;
    }
    if (*(ball1->hasBounced()))
    {
        _score += 1;
        std::cout << "BOUNCE!!! Score incremented by 1pts --" << " SCORE: " << _score << std::endl;
    }

    paddle1->updateDrawingObject();
    ball1->updateDrawingObject();
}

/*!
Renders the current game state to the screen using SDL.
Clears the previous frame, draws game elements (walls, paddle, ball) with appropriate colors and positions.
Handles visual effects like ball color swapping when triggered.
Ensures the display accurately reflects the current game state, providing smooth and responsive graphics.
*/
void Game::GenerateOutput()
{

    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mRenderer);

    const int thickness = 15;
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    SDL_Rect wallTop{0, 0, _windowSizeX, thickness};
    SDL_RenderFillRect(mRenderer, &wallTop);

    SDL_Rect wallBottom{0, _windowSizeY - thickness, _windowSizeX, thickness};
    SDL_RenderFillRect(mRenderer, &wallBottom);

    if (_isRightWall)
    {
        SDL_Rect wallRight{_windowSizeX - thickness, 0, thickness, _windowSizeY};
        SDL_RenderFillRect(mRenderer, &wallRight);
    }

    SDL_RenderFillRect(mRenderer, paddle1->getDrawingObject());
    if (_colorSwap)
        ball1->switchColor();
    SDL_SetRenderDrawColor(mRenderer, ball1->getColor()[0], ball1->getColor()[1], ball1->getColor()[2], 255);
    SDL_RenderFillRect(mRenderer, ball1->getDrawingObject());

    SDL_RenderPresent(mRenderer);

    if (_colorSwap)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        _colorSwap = false;
    }
}

/*!
Returns a pointer to the wall thickness value, which is used for rendering game boundaries and collision detection.
This accessor method allows other parts of the game to reference the wall thickness for consistent gameplay mechanics.
*/
unsigned short int *Game::getWallThickness() { return &_wallThickness; }
