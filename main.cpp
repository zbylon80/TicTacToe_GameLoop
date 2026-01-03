#include "Game.h"
#include <iostream>
#include <limits>
#include <cctype>

using namespace std;

int main()
{
    bool playAgain = true;

    while (playAgain)
    {
        Initialize();

        // Show the empty board before the first move
        Render();

        while (!IsGameFinished)
        {
            GetInput();
            Update();
            Render();
        }

        Shutdown();

        // Ask the player if they want to play again
        while (true)
        {
            cout << "Play again? (y/n): ";
            char answer = 0;
            if (!(cin >> answer))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            answer = static_cast<char>(tolower(static_cast<unsigned char>(answer)));

            if (answer == 'y')
            {
                playAgain = true;
                break;
            }
            else if (answer == 'n')
            {
                playAgain = false;
                break;
            }
            else
            {
                cout << "Please enter 'y' or 'n'.\n";
            }
        }
    }

    return 0;
}
