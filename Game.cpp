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
char CurrentPlayer = PLAYER1_CHAR;
char Winner = EMPTY_CHAR;

// Funkcje pomocnicze
bool CheckWin(char player);
bool IsBoardFull();

// Definicje funkcji
void Initialize()
{
    cout << "Welcome to tic-tac-toe game!" << endl;
    IsGameFinished = false;
    TurnNumber = 0;
    CurrentPlayer = PLAYER1_CHAR;
    SelectedRow = -1;
    SelectedCol = -1;
    Winner = EMPTY_CHAR;

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
        cout << "Podaj wiersz i kolumne (1-" << BOARD_SIZE << "), np. '1 3': ";

        int rowInput = 0;
        int colInput = 0;

        if (!(cin >> rowInput >> colInput))
        {
            cout << "Niepoprawne dane. Wpisz dwie liczby.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (rowInput < 1 || rowInput > BOARD_SIZE || colInput < 1 || colInput > BOARD_SIZE)
        {
            cout << "Wspolrzedne poza zakresem 1-" << BOARD_SIZE << ". Sprobuj ponownie.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Konwertujemy na indeksy 0-based do tablicy
        int row = rowInput - 1;
        int col = colInput - 1;

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
    // Zapamietujemy, kto wykonal ruch (uzyteczne przy sprawdzaniu wygranej)
    char playerJustMoved = CurrentPlayer;

    // Zapisz ruch biezacego gracza na planszy
    BOARD[SelectedRow][SelectedCol] = playerJustMoved;

    // Przechodzimy do kolejnej tury
    TurnNumber++;

    // Sprawdz wygrana
    if (CheckWin(playerJustMoved))
    {
        Winner = playerJustMoved;
        IsGameFinished = true;
    }
    else if (IsBoardFull())
    {
        IsGameFinished = true; // remis
    }

    // Zmien gracza na nastepnego tylko jesli gra trwa dalej
    if (!IsGameFinished)
    {
        if (CurrentPlayer == PLAYER1_CHAR)
        {
            CurrentPlayer = PLAYER2_CHAR;
        }
        else
        {
            CurrentPlayer = PLAYER1_CHAR;
        }
    }

    // Wyczysc wybory ruchu, zostana ustawione w GetInput
    SelectedRow = -1;
    SelectedCol = -1;
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
    cout << "(Gra konczy sie, gdy ktos wygra lub plansza sie zapelni)\n\n";

    cout << "Board (row, column):\n   ";
    for (int col = 0; col < BOARD_SIZE; ++col)
    {
        cout << (col + 1) << ' ';
    }
    cout << "\n";

    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        cout << ' ' << (row + 1) << ' ';
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            cout << BOARD[row][col] << ' ';
        }
        cout << "\n";
    }

    cout << "\nUse coordinates like '1 3' for row 1, column 3.\n";
}

void Shutdown()
{
    cout << "\nGame over! Total turns: " << TurnNumber << endl;
    if (Winner != EMPTY_CHAR)
    {
        cout << "Winner: " << Winner << endl;
    }
    else
    {
        cout << "Result: draw." << endl;
    }
}

bool CheckWin(char player)
{
    // Sprawdz wiersze
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        if (BOARD[row][0] == player &&
            BOARD[row][1] == player &&
            BOARD[row][2] == player)
        {
            return true;
        }
    }

    // Sprawdz kolumny
    for (int col = 0; col < BOARD_SIZE; ++col)
    {
        if (BOARD[0][col] == player &&
            BOARD[1][col] == player &&
            BOARD[2][col] == player)
        {
            return true;
        }
    }

    // Przekatne
    if (BOARD[0][0] == player &&
        BOARD[1][1] == player &&
        BOARD[2][2] == player)
    {
        return true;
    }

    if (BOARD[0][2] == player &&
        BOARD[1][1] == player &&
        BOARD[2][0] == player)
    {
        return true;
    }

    return false;
}

bool IsBoardFull()
{
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            if (BOARD[row][col] == EMPTY_CHAR)
            {
                return false;
            }
        }
    }
    return true;
}
