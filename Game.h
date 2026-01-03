#pragma once

// Game Params
extern const int BOARD_SIZE;
extern const char EMPTY_CHAR;
extern const char PLAYER1_CHAR;
extern const char PLAYER2_CHAR;

// Game State
extern bool IsGameFinished;
extern int TurnNumber;
extern char BOARD[3][3];
extern int SelectedRow;
extern int SelectedCol;
extern char CurrentPlayer;

// Game Loop functions
void Initialize();
void GetInput();
void Update();
void Render();
void Shutdown();
