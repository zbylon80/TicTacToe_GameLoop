#include "Game.h"
#include <iostream>

using namespace std;

// Definicje stałych (tu naprawdę istnieją)
const int BOARD_SIZE = 3;
const char EMPTY_CHAR = '_';
const char PLAYER1_CHAR = 'X';
const char PLAYER2_CHAR = 'O';

// Prosty stan gry (na razie minimalny)
bool IsGameFinished = false;

// Definicje funkcji (na razie puste / testowe)
void Initialize()
{
    cout << "Welcome to tic-tac-toe game!" << endl;
}

void GetInput()
{
    // później
}

void Update()
{
    // później
}

void Render()
{
    // później
}

void Shutdown()
{
    cout << "Game over!" << endl;
}
