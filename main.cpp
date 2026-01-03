#include "Game.h"

int main()
{
    Initialize();

    while (!IsGameFinished)
    {
        GetInput();
        Update();
        Render();
    }

    Shutdown();
    return 0;
}
