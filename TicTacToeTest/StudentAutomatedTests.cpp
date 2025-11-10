#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../TicTacToe_Fall2023/TicTacToeBoard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Some helpful notes
//   Player enum values are referenced by TicTacToeBoard::O or TicTacToeBoard::X or TicTacToeBoard::EMPTY

namespace TicTacToeTest
{
	TEST_CLASS(TicTacToeStudentAutomatedTests)
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

		TEST_METHOD(HelloStudentTests) {
			Logger::WriteMessage("Running student tests on the Board object");
			Assert::IsTrue(true);
		}
	};
}
