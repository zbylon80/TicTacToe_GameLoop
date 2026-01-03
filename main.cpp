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

        // Pokazujemy plansze startowa, zanim gracz wykona pierwszy ruch
        Render();

        while (!IsGameFinished)
        {
            GetInput();
            Update();
            Render();
        }

        Shutdown();

        // Zapytaj gracza o ponowna gre
        while (true)
        {
            cout << "Zagrac ponownie? (y/n): ";
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
                cout << "Wpisz 'y' lub 'n'.\n";
            }
        }
    }

    return 0;
}
