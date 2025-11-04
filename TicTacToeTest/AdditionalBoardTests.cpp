#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../TicTacToe_Fall2023/TicTacToeBoard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TicTacToeTest
{
	TEST_CLASS(TicTacToeAdditionalBoardTests)
	{
		TicTacToeBoard board;

	public:

		TEST_CLASS_INITIALIZE(_Setup_BoardClassTest)
		{
			// this method is run once for the TicTacToeTest class
			//    intentionally blank (other than the log message) - nothing to initialize at this time
			Logger::WriteMessage("Test class initialized\n");
		}

		TEST_METHOD_INITIALIZE(_Setup_MethodTest) {
			// this method is run prior to EVERY test case inside the class (ie this file)
			Logger::WriteMessage("Initializing Board object for additional tests.\n");
			board.resetBoard();          // reinitialize board via method, rather than creating a new board object
		}

		TEST_METHOD(HelloAdditionalTests) {
			Logger::WriteMessage("Running additional tests on the Board object");
		}

		// the following test expands on the test verifying player X starts
		//   and verifies 
		//      getPlayer() returns the correct enum &
		//      nextPlayer() correctly switches from X to O &
		//        also correctly switches from O back to X
		TEST_METHOD(ExpandedGameStartPlayerX)
		{
			Logger::WriteMessage("Testing X is selected as first player\n");
			// verify X is to play, O is NOT to play
			Assert::AreEqual(board.getPlayerName(), 'X');
			Assert::AreNotEqual(board.getPlayerName(), 'O');

			// expanding test to verify the enum returned is X
			Logger::WriteMessage("Testing enum returned by getPlayer() is also X\n");
			Assert::AreEqual(static_cast<int>(TicTacToeBoard::X),
				static_cast<int>(board.getPlayer()));

			// test switching to player O
			Logger::WriteMessage("Switch players via board.nextPlayer() to O, and verify all methods\n");
			board.nextPlayer();
			//    getPlayer() enum
			Assert::AreEqual(static_cast<int>(TicTacToeBoard::O),
				static_cast<int>(board.getPlayer()));
			Assert::AreNotEqual(static_cast<int>(TicTacToeBoard::X),
				static_cast<int>(board.getPlayer()));
			//    getPlayerName() character
			Assert::AreEqual(board.getPlayerName(), 'O');
			Assert::AreNotEqual(board.getPlayerName(), 'X');

			// test switching back to player X
			Logger::WriteMessage("Switch players via board.nextPlayer() back to X, and verify all methods\n");
			board.nextPlayer();
			//    getPlayer() enum
			Assert::AreEqual(static_cast<int>(TicTacToeBoard::X),
				static_cast<int>(board.getPlayer()));
			Assert::AreNotEqual(static_cast<int>(TicTacToeBoard::O),
				static_cast<int>(board.getPlayer()));
			//    getPlayerName() character
			Assert::AreEqual(board.getPlayerName(), 'X');
			Assert::AreNotEqual(board.getPlayerName(), 'O');
		}

		TEST_METHOD(TestDrawLV1) {
			Logger::WriteMessage("Draw scenario - v1, all spaces marked, no one wins");
			// verify no one has won & there isn't a draw
			// Precondition checks - no draw, no one-has won
			Assert::IsFalse(board.isDraw());
			Assert::IsFalse(board.isWinner(TicTacToeBoard::O));
			Assert::IsFalse(board.isWinner(TicTacToeBoard::X));
			// Create a draw condition   X O X
			//                           O X O
			//                           O X O
			board.writeSquare(0, 0, TicTacToeBoard::X);
			board.writeSquare(0, 1, TicTacToeBoard::O);
			board.writeSquare(0, 2, TicTacToeBoard::X);
			board.writeSquare(1, 0, TicTacToeBoard::O);
			board.writeSquare(1, 1, TicTacToeBoard::X);
			board.writeSquare(1, 2, TicTacToeBoard::O);
			board.writeSquare(2, 0, TicTacToeBoard::O);
			board.writeSquare(2, 1, TicTacToeBoard::X);
			// Prior to final move - rerun precondition checks
			Assert::IsFalse(board.isDraw());
			Assert::IsFalse(board.isWinner(TicTacToeBoard::O));
			Assert::IsFalse(board.isWinner(TicTacToeBoard::X));
			// Create the draw
			board.writeSquare(2, 2, TicTacToeBoard::O);
			// Verify no winner, and there exists a draw
			Assert::IsTrue(board.isDraw(), L"Post final move: expect a Draw, but isDraw() returned false");
			Assert::IsFalse(board.isWinner(TicTacToeBoard::O), L"Post final move, expect no one has won, but O did win");
			Assert::IsFalse(board.isWinner(TicTacToeBoard::X), L"Post final move, expect no one has won, but X did win");
		}
	};
}
