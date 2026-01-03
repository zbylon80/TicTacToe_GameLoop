#include "Game.h"

int main()
{
    Initialize();

    // Pokazujemy planszę startową, zanim gracz wykona pierwszy ruch
    Render();

    while (!IsGameFinished)
    {
        GetInput();
        Update();
        Render();
    }

    Shutdown();
    return 0;
}
