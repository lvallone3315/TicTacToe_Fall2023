#include "TicTacToeBoard.h"
#include <iostream>
#include <stdlib.h>

/*
 * ToDo - Validate row & columns everywhere  (highest priority - poor OO coding!!!
 * ToDo - create ENUM for players
 * ToDo - Separate player name from 'X' and 'O' characters - e.g. default player name to character, but then allow it to change
 * ToDo - Create mapping function from enum to display character
 * ToDo - create define or constant for Error returns
*/

/*
 * Instance variables (declared in header file)
 *   board[][] - two dimensional array indexed by row (0-2) & column (0-2), cleared when starting a new game
 *   takenSquareCount - integer tracking # of moves in the game, reset at instance creation & on starting a new game
 *   player - character indicating the player making the current move
 *     notes - default player defined in board class header file,
 *     current player is tracked and can be retrived by the board class, but is updated from outside the class via nextPlayer()
 */

// Constructor -- initialize all board spaces to empty, starting player intialized in .h file when memory allocated
TicTacToeBoard::TicTacToeBoard() {
	resetBoard();
}

// Reset board and variable tracking # of spaces played in current game
void TicTacToeBoard::resetBoard() {
	takenSquareCount = 0;
	for (int r = 0; r < BOARD_NUM_ROWS; r++) {
		for (int c = 0; c < BOARD_NUM_COLS; c++) {
			board[r][c] = EMPTY;
		}
	}
}

// If specified space is empty - return true
bool TicTacToeBoard::isSquareEmpty(int row, int col) const {
	if (board[row][col] == EMPTY)
		return true;
	else
		return false;
}

// Updates space to the player (marker) specified, return false if space not empty
//   ToDo - bad - not validating row & col prior to indexing into array
bool TicTacToeBoard::writeSquare(int row, int col, Player currentPlayer) {
	if (this -> isSquareEmpty(row, col)) {
		board[row][col] = currentPlayer;
		takenSquareCount++;
		return true;
	}
	else {
		return false;
	}
}

// Returns character (ie player marker) in the given row/col, throws exception if args invalid
char TicTacToeBoard::getSquareContents(int row, int col) {
	if ((row >= BOARD_NUM_ROWS) || (col >= BOARD_NUM_COLS)) {
		throw std::invalid_argument("Invalid row or column passed to getSquareContents\n");
	}
	// else - good row & column passed
	return playerMap(board[row][col]);
}

// Returns the current player (enum)
TicTacToeBoard::Player TicTacToeBoard::getPlayer() {
	return player;
}

// Returns player name (character)
char TicTacToeBoard::getPlayerName() {
	return playerMap(player);
}

// Toggles next to play (e.g. if current player is X, next to play is O)
TicTacToeBoard::Player TicTacToeBoard::nextPlayer() {
	if (player == X)
		player = O;
	else
		player = X;
	return player;
}

// Return true if specified player has won the game
//   ToDo - tighten up this check - works but could be cleaner
bool TicTacToeBoard::isWinner(Player playerToCheck) {
	// check rows
	for (int r = 0; r < BOARD_NUM_ROWS; r++) {
		if ((board[r][0] == playerToCheck) &&
			(board[r][1] == playerToCheck) &&
			(board[r][2] == playerToCheck))
			return(true);
	}

	// check columns
	for (int c = 0; c < BOARD_NUM_COLS; c++) {
		if ((board[0][c] == playerToCheck) &&
			(board[1][c] == playerToCheck) &&
			(board[2][c] == playerToCheck))
			return(true);
	}

	// check diagonals
	if ((board[0][0] == playerToCheck) &&
		(board[1][1] == playerToCheck) &&
		(board[2][2] == playerToCheck))
			return(true);
	// reverse
	if ((board[0][2] == playerToCheck) &&
		(board[1][1] == playerToCheck) &&
		(board[2][0] == playerToCheck))
			return(true);

	return(false);              // no winner this time
}


// Return true if game is a Draw - all squares filled and no one has won
bool TicTacToeBoard::isDraw() {
	if ((takenSquareCount >= BOARD_NUM_ROWS * BOARD_NUM_COLS) && !this->isWinner(X) && !this->isWinner(O)) {
		return (true);
	}
	else
		return(false);
}

// map enum to character
char TicTacToeBoard::playerMap(Player player) {
	switch (player) {
	case X:
		return 'X';
	case O:
		return 'O';
	default:
		return ' ';
	}
}
