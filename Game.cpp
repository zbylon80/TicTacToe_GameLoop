#include "Game.h"
#include <iostream>
#include <limits>

using namespace std;

// Definicje stałych (tu naprawdę istnieją)
const int BOARD_SIZE = 3;
const char EMPTY_CHAR = '_';
const char PLAYER1_CHAR = 'X';
const char PLAYER2_CHAR = 'O';

// Prosty stan gry (na razie minimalny)
bool IsGameFinished = false;
int TurnNumber = 0;

// Definicje funkcji (na razie puste / testowe)
void Initialize()
{
    cout << "Welcome to tic-tac-toe game!" << endl;
    IsGameFinished = false;
    TurnNumber = 0;
}

void GetInput()
{
    // Na razie: brak prawdziwego inputu
    // W kolejnym kroku będziemy brać współrzędne od gracza
}

void Update()
{
    TurnNumber++;

    // test: po 3 turach kończymy grę
    if (TurnNumber >= 3)
    {
        IsGameFinished = true;
    }
}

void Render()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    cout << "TicTacToe - Game Loop test\n";
    cout << "Turn: " << TurnNumber << "\n";
    cout << "(After 3 turns the game will finish - test mode)\n\n";

    cout << "Press ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void Shutdown()
{
    cout << "\nGame over! Total turns: " << TurnNumber << endl;
}
