#include "TicTacToeBoard.h"
#include <iostream>
#include <stdlib.h>
#include <array>    // set refactor
#include <algorithm>  // set refactor

/*
 * ToDo - Validate row & columns everywhere  (highest priority - poor OO coding!!!
 * ToDo - Separate player name from 'X' and 'O' characters - e.g. default player name to character, but then allow it to change
*/

/*
 * Instance variables (declared in header file)
 *   board[][] - two dimensional array indexed by row (0-2) & column (0-2), cleared when starting a new game
 *   takenSquareCount - integer tracking # of moves in the game, reset at instance creation & on starting a new game
 *   player - character indicating the player making the current move
 *     notes - default player defined in board class header file,
 *     current player is tracked and can be retrived by the board class, but is updated from outside the class via nextPlayer()
 * 
 * Notes
 *   Error handling
 *      For writeSquare() - returns true if update was successful, false if not (e.g. space already occupied)
 *      For all methods w/ row & column params - invalid argument exception thrown if params are out of range
 *  Pattern approach, row & column are mapped into a position [0,8]
 *    writeSquare() fills in legacy board[][], as well as tracking X & Os positions played (xMoves & oMoves)
 *    matchesWinningPattern() checks if any of the winning patterns (e.g. 0,4,8 - forward diagonal) is a subset of the player's moves
 *    isWinner() can be configured (via removing/adding the comment around the method call) either approach
 *      ToDo - maybe change this to a Feature Flag
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
	// clear the set of player moves (used in the pattern implementation of isWinner()
	xMoves.clear();
	oMoves.clear();
}

// If specified space is empty - return true
bool TicTacToeBoard::isSquareEmpty(int row, int col) const {
	if (board[row][col] == EMPTY)
		return true;
	else
		return false;
}

// Updates space to the player (marker) specified, return false if space not empty
//   intentional arg check issue
bool TicTacToeBoard::writeSquare(int row, int col, Player currentPlayer) {
	if ((row >= BOARD_NUM_ROWS) || (col >= BOARD_NUM_COLS)) {
		// note: if we get here, everything after the above throw line is skipped — it never runs.
		throw std::invalid_argument("Invalid row or column passed to writeSquare\n");
	}
	// if within range & the square is empty, enter the player's move, update # of spaces played & return true
	if (this -> isSquareEmpty(row, col)) {
		board[row][col] = currentPlayer;
		takenSquareCount++;
		// used for set based refactoring of win condition
		if (currentPlayer == X)
			xMoves.insert(rowColToPosition(row, col));
		else
			oMoves.insert(rowColToPosition(row, col));
		return true;
	}
	else { // the space was already occupied, return false
		return false;
	}
}

// Returns character (ie player marker) in the given row/col, throws exception if args invalid
//    another intentional arg check failure
char TicTacToeBoard::getSquareContents(int row, int col) const {
	if ((row >= BOARD_NUM_ROWS) || (col >= BOARD_NUM_COLS)) {
		throw std::invalid_argument("Invalid row or column passed to getSquareContents\n");
	}
	// else - good row & column passed
	return playerMap(board[row][col]);
}

// Returns the current player (enum)
TicTacToeBoard::Player TicTacToeBoard::getPlayer() const {
	return player;
}

// Returns player name (character)
char TicTacToeBoard::getPlayerName() const {
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
//   Legacy version - exhaustive check - cell by cell
//   Refactored version - define winning patterns & check those against the moves played
bool TicTacToeBoard::isWinner(Player playerToCheck) const {

	return matchesWinningPattern(playerToCheck);   // set based refactor

	// check rows
	for (int r = 0; r < BOARD_NUM_ROWS; r++) {
		if ((board[r][0] == playerToCheck) &&
			(board[r][1] == playerToCheck) &&
			(board[r][2] == playerToCheck))
			return true;
	}

	// check columns
	for (int c = 0; c < BOARD_NUM_COLS; c++) {
		if ((board[0][c] == playerToCheck) &&
			(board[1][c] == playerToCheck) &&
			(board[2][c] == playerToCheck))
			return true;
	}

	// check diagonals
	if ((board[0][0] == playerToCheck) &&
		(board[1][1] == playerToCheck) &&
		(board[2][2] == playerToCheck))
		return true;
	// reverse
	if ((board[0][2] == playerToCheck) &&
		(board[1][1] == playerToCheck) &&
		(board[2][0] == playerToCheck))
		return true;

	return false;              // no winner this time
}


// Return true if game is a Draw - all squares filled and no one has won
bool TicTacToeBoard::isDraw() const {
	if ((takenSquareCount > BOARD_NUM_ROWS * BOARD_NUM_COLS) && 
		!this->isWinner(X) && !this->isWinner(O)) {
		return true;
	}
	else
		return false;
}

// map enum to character
char TicTacToeBoard::playerMap(Player playerEnum) const {
	switch (playerEnum) {
	case X:
		return 'X';
	case O:
		return 'O';
	default:
		return ' ';
	}
}

//                      Set based refactoring
// the following set based code is based on LV's python design that implemented set based win checks
//   for expediency, the implementation is based on code from chatgpt
bool TicTacToeBoard::matchesWinningPattern(Player p) const {
	const std::set<int>& moves = (p == X) ? xMoves : oMoves;   // select players individual moves

	for (const auto& pattern : winPatterns) {
		bool allFound = true;
		// check all 3 positions for each pattern
		for (int pos : pattern) {
			if (moves.count(pos) == 0) {
				allFound = false; // a position inside the pattern was not found in the player's moves
				break;   // check the next pattern
			}
		}
		if (allFound)
			return true;
	}

	return false;   // no winner yet
}

// helper function to compute position from row & column
// position numbering is row 0 -> 0, 1, 2 .... row 2 -> 6, 7, 8
int TicTacToeBoard::rowColToPosition(int row, int column) {
	if ((row >= BOARD_NUM_ROWS) || (column >= BOARD_NUM_COLS) || 
		 (row < 0) || (column < 0)) {
		throw std::invalid_argument("Invalid row or column passed to getSquareContents\n");
	}
	return row * BOARD_NUM_COLS + column;
}
