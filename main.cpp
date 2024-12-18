#include "Game.h"

/*!
\brief Entry point of the Pong game application.

Creates a Game object, initializes it, runs the game loop if initialization is successful, and performs cleanup before exiting.

\param argc Number of command-line arguments (unused in this implementation).
\param argv Array of command-line argument strings (unused in this implementation).

\return 0 if the program exits successfully.
*/
int main(int argc, char **argv)
{
    Game game(600, 500, 100, true);
    bool success = game.Initialize();
    if (success)
        game.GameLoop();
    game.ShutDownGame();
    return 0;
}