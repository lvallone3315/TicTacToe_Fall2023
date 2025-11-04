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
			board = TicTacToeBoard();          // reinitialize board
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
	};
}
