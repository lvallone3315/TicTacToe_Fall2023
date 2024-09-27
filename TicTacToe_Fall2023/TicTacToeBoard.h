#pragma once
/*
 * board class - TicTacToeBoard
 *     Scope - all aspects of the board, including defining the # rows & columns, win conditions, current/starting player
 *        supports retrieving data elements for displaying the board
 *        ideally, use BOARD_NUM_ROWS and BOARD_NUM_COLS to reference board dimensions
 * constructor - initializes board via resetBoard() method
 * int resetBoard() - initializes board
 * boolean isSquareEmpty(int row, int column) - true = empty, false otherwise
 * int writeSquare(int row, int column, Player player) returns ERROR if can’t write square
 * char getSquareContents(int row, int column) sreturns character for player (e.g. X, O, blank)
 * Player getPlayer()returns player (enum) whose turn it is
 * char getPlayerName()returns player (character) whose turn it is
 */
class TicTacToeBoard
{


#define BOARD_NUM_ROWS 3
#define BOARD_NUM_COLS 3
#define INITIAL_PLAYER X


public:
	enum Player { X, O, EMPTY};    // define player enums, map to display character

	TicTacToeBoard();
	void resetBoard();
	bool isSquareEmpty(int row, int col) const;
	bool writeSquare(int row, int col, Player currentPlayer);  // returns true if successfully written, false on failure
	char getSquareContents(int row, int col) const;       // used for displaying board, return as character
	Player getPlayer() const;								// returns internal ID (ie enum) of the player
	char getPlayerName() const;							// returns name of the player - hardcoded as 'X' or 'O'
	Player nextPlayer();   // swap player for next move, returns new player
	bool isWinner(Player playerToCheck) const; // check if specified player has won
	bool isDraw() const; // check if a draw

private:  // reserve memory for board & current player
	Player board[BOARD_NUM_ROWS][BOARD_NUM_COLS];      // board storage, indexed by row [0-2] and column [0-2]
	Player player = INITIAL_PLAYER;                    // tracks the current player, ie next symbol placed
	int takenSquareCount = 0;                        // # of spaces played in current game, reset for new games
	char playerMap(Player playerEnum) const;		// map player enum to player character - ToDo - create mapping list rather than switch statement
};