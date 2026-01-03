#include "Game.h"
#include <iostream>
#include <limits>

using namespace std;

// Definicje stalych (tu naprawde istnieja)
const int BOARD_SIZE = 3;
const char EMPTY_CHAR = '_';
const char PLAYER1_CHAR = 'X';
const char PLAYER2_CHAR = 'O';

// Prosty stan gry (na razie minimalny)
bool IsGameFinished = false;
int TurnNumber = 0;
char BOARD[3][3];
int SelectedRow = -1;
int SelectedCol = -1;

// Definicje funkcji
void Initialize()
{
    cout << "Welcome to tic-tac-toe game!" << endl;
    IsGameFinished = false;
    TurnNumber = 0;

    // Ustawiamy wszystkie pola na puste, aby plansza startowala "czysta"
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            BOARD[row][col] = EMPTY_CHAR;
        }
    }
}

void GetInput()
{
    while (true)
    {
        cout << "Podaj wiersz i kolumne (0-" << BOARD_SIZE - 1 << "), np. '0 2': ";

        int row = 0;
        int col = 0;

        if (!(cin >> row >> col))
        {
            cout << "Niepoprawne dane. Wpisz dwie liczby.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
        {
            cout << "Wspolrzedne poza zakresem 0-" << BOARD_SIZE - 1 << ". Sprobuj ponownie.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (BOARD[row][col] != EMPTY_CHAR)
        {
            cout << "Pole jest juz zajete. Wybierz inne.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        SelectedRow = row;
        SelectedCol = col;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // usuwamy reszte linii
        break;
    }
}

void Update()
{
    TurnNumber++;

    // test: po 3 turach konczymy gre
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

    cout << "Board (row, column):\n   ";
    for (int col = 0; col < BOARD_SIZE; ++col)
    {
        cout << col << ' ';
    }
    cout << "\n";

    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        cout << ' ' << row << ' ';
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            cout << BOARD[row][col] << ' ';
        }
        cout << "\n";
    }

    cout << "\nUse coordinates like '0 2' for row 0, column 2.\n\n";

    cout << "Press ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void Shutdown()
{
    cout << "\nGame over! Total turns: " << TurnNumber << endl;
}
