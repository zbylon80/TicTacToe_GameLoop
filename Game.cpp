#include "Game.h"
#include <iostream>
#include <limits>
#include <cctype>

using namespace std;

// Game constants
const int BOARD_SIZE = 3;
const char EMPTY_CHAR = '_';
const char PLAYER1_CHAR = 'X';
const char PLAYER2_CHAR = 'O';

// Game state variables
bool IsGameFinished = false;
int TurnNumber = 0;
char BOARD[3][3];
int SelectedRow = -1;
int SelectedCol = -1;
char CurrentPlayer = PLAYER1_CHAR;
char Winner = EMPTY_CHAR;
bool PlayVsComputer = false;
char HumanPlayer = PLAYER1_CHAR;
char ComputerPlayer = PLAYER2_CHAR;

// Helper functions
bool CheckWin(char player);
bool IsBoardFull();
bool FindWinningMove(char player, int& outRow, int& outCol);
void ChooseComputerMove();

void Initialize()
{
    cout << "Welcome to tic-tac-toe!" << endl;
    IsGameFinished = false;
    TurnNumber = 0;
    SelectedRow = -1;
    SelectedCol = -1;
    Winner = EMPTY_CHAR;
    CurrentPlayer = PLAYER1_CHAR;
    PlayVsComputer = false;
    HumanPlayer = PLAYER1_CHAR;
    ComputerPlayer = PLAYER2_CHAR;

    // Mode selection
    while (true)
    {
        cout << "Play against computer? (y/n): ";
        char answer = 0;
        if (!(cin >> answer))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        answer = static_cast<char>(tolower(static_cast<unsigned char>(answer)));
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (answer == 'y')
        {
            PlayVsComputer = true;
            break;
        }
        else if (answer == 'n')
        {
            PlayVsComputer = false;
            break;
        }
        else
        {
            cout << "Please enter 'y' or 'n'.\n";
        }
    }

    if (PlayVsComputer)
    {
        while (true)
        {
            cout << "Choose your symbol: X (first) or O (second): ";
            char symbol = 0;
            if (!(cin >> symbol))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            symbol = static_cast<char>(tolower(static_cast<unsigned char>(symbol)));
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (symbol == 'x')
            {
                HumanPlayer = PLAYER1_CHAR;
                ComputerPlayer = PLAYER2_CHAR;
                break;
            }
            else if (symbol == 'o')
            {
                HumanPlayer = PLAYER2_CHAR;
                ComputerPlayer = PLAYER1_CHAR;
                break;
            }
            else
            {
                cout << "Please enter 'X' or 'O'.\n";
            }
        }
    }

    // Clear the board to start with an empty grid
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
    if (PlayVsComputer && CurrentPlayer == ComputerPlayer)
    {
        ChooseComputerMove();
        return;
    }

    while (true)
    {
        cout << "Enter row and column (1-" << BOARD_SIZE << "), e.g. '1 3': ";

        int rowInput = 0;
        int colInput = 0;

        if (!(cin >> rowInput >> colInput))
        {
            cout << "Invalid data. Enter two numbers.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (rowInput < 1 || rowInput > BOARD_SIZE || colInput < 1 || colInput > BOARD_SIZE)
        {
            cout << "Coordinates must be between 1 and " << BOARD_SIZE << ". Try again.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Convert to 0-based indices for the array
        int row = rowInput - 1;
        int col = colInput - 1;

        if (BOARD[row][col] != EMPTY_CHAR)
        {
            cout << "Field already taken. Choose another.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        SelectedRow = row;
        SelectedCol = col;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // drop the rest of the line
        break;
    }
}

void Update()
{
    // Remember who moved (useful for win check)
    char playerJustMoved = CurrentPlayer;

    // Place the mark on the board
    BOARD[SelectedRow][SelectedCol] = playerJustMoved;

    // Advance to next turn
    TurnNumber++;

    // Check win/draw
    if (CheckWin(playerJustMoved))
    {
        Winner = playerJustMoved;
        IsGameFinished = true;
    }
    else if (IsBoardFull())
    {
        IsGameFinished = true; // draw
    }

    // Switch player only if the game continues
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

    // Clear chosen coordinates; new values will be set in GetInput
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

    cout << "TicTacToe\n";
    if (IsGameFinished)
    {
        cout << "Game finished.\n";
        if (Winner != EMPTY_CHAR)
        {
            cout << "Winner: " << Winner << "\n\n";
        }
        else
        {
            cout << "Result: draw.\n\n";
        }
    }
    else
    {
        cout << "Turn: " << TurnNumber << "\n";
        cout << "Current player: " << CurrentPlayer << "\n\n";
    }

    if (PlayVsComputer)
    {
        cout << "Mode: vs computer (You: " << HumanPlayer << ", Computer: " << ComputerPlayer << ")\n";
    }
    else
    {
        cout << "Mode: two players\n";
    }

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

    if (!IsGameFinished)
    {
        cout << "\nUse coordinates like '1 3' for row 1, column 3.\n";
    }
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
    // Rows
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        bool rowWin = true;
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            if (BOARD[row][col] != player)
            {
                rowWin = false;
                break;
            }
        }
        if (rowWin)
        {
            return true;
        }
    }

    // Columns
    for (int col = 0; col < BOARD_SIZE; ++col)
    {
        bool colWin = true;
        for (int row = 0; row < BOARD_SIZE; ++row)
        {
            if (BOARD[row][col] != player)
            {
                colWin = false;
                break;
            }
        }
        if (colWin)
        {
            return true;
        }
    }

    // Main diagonal
    bool mainDiag = true;
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        if (BOARD[i][i] != player)
        {
            mainDiag = false;
            break;
        }
    }
    if (mainDiag)
    {
        return true;
    }

    // Anti-diagonal
    bool antiDiag = true;
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        int col = BOARD_SIZE - 1 - i;
        if (BOARD[i][col] != player)
        {
            antiDiag = false;
            break;
        }
    }
    return antiDiag;
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

bool FindWinningMove(char player, int& outRow, int& outCol)
{
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            if (BOARD[row][col] != EMPTY_CHAR)
            {
                continue;
            }

            BOARD[row][col] = player;
            bool wins = CheckWin(player);
            BOARD[row][col] = EMPTY_CHAR;

            if (wins)
            {
                outRow = row;
                outCol = col;
                return true;
            }
        }
    }

    return false;
}

void ChooseComputerMove()
{
    // Priority: win > block > center > corners > first empty
    int row = -1;
    int col = -1;

    if (FindWinningMove(ComputerPlayer, row, col))
    {
        SelectedRow = row;
        SelectedCol = col;
        return;
    }

    if (FindWinningMove(HumanPlayer, row, col))
    {
        SelectedRow = row;
        SelectedCol = col;
        return;
    }

    int center = BOARD_SIZE / 2;
    if (BOARD[center][center] == EMPTY_CHAR)
    {
        SelectedRow = center;
        SelectedCol = center;
        return;
    }

    const int corners[4][2] = {
        {0, 0},
        {0, BOARD_SIZE - 1},
        {BOARD_SIZE - 1, 0},
        {BOARD_SIZE - 1, BOARD_SIZE - 1}
    };

    for (const auto& corner : corners)
    {
        int r = corner[0];
        int c = corner[1];
        if (BOARD[r][c] == EMPTY_CHAR)
        {
            SelectedRow = r;
            SelectedCol = c;
            return;
        }
    }

    for (int r = 0; r < BOARD_SIZE; ++r)
    {
        for (int c = 0; c < BOARD_SIZE; ++c)
        {
            if (BOARD[r][c] == EMPTY_CHAR)
            {
                SelectedRow = r;
                SelectedCol = c;
                return;
            }
        }
    }

    SelectedRow = 0;
    SelectedCol = 0;
}
