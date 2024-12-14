#ifndef INC_26_PONG_CPP_GAME_H
#define INC_26_PONG_CPP_GAME_H

#include <SDL2/SDL.h>
#include <iostream>
#include <thread>
#include "Ball.h"
#include "Paddle.h"
#include <memory>

class Game
{
public:
    Game(unsigned short int windowSizeX, unsigned short int windowSizeY, unsigned short int paddleSize, bool isRightWall);
    bool Initialize();
    void GameLoop();
    void ShutDownGame();

private:
    bool mIsRunning = true;

    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    unsigned short int _windowSizeX;
    unsigned short int _windowSizeY;
    bool _isRightWall;
    unsigned short int _wallThickness;
    long int _score;
    bool _colorSwap;

    unsigned short int *getWallThickness();

    const Uint8 *state;

    Uint32 mTicksCount;

    std::shared_ptr<Ball> ball1;
    std::shared_ptr<Paddle> paddle1;
};

#endif
