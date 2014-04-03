#include "stdafx.h"

#include "Functions.h"
#include "Shape.h"
#include "RunTracking.h"

using namespace cv;
using namespace std;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;

// when adding tests, it is desirable to name them Test1, Test2...
// because each test is matched up to an integer, which is used for test selection


// 1 second between piece placement. Assign times directly to Puzzle Pieces
void RunTracking::Test1() {
	MessageBox::Show("RUNNING TEST 1: 1 second between each piece placement.");
	int placeTime;
	//for each (PuzzlePiece^ piece in this->Game->getPieceList())
	//{
	//	placeTime = getElapsedSeconds(this->gameRecord->getTimeStarted()->Ticks);
	//	piece->setTimePlacedToNow();
	//	Debug::WriteLine("time is " + placeTime);
	//	System::Threading::Thread::Sleep(1*1000); // wait for 1 second (1000 ms)
	//}

	// put down pieces in reverse order
	for (int i = this->Game->getPieceList()->Count -1; i >= 0; i--) {
		System::Threading::Thread::Sleep(1*1000); // wait for 1 second (1000 ms)
		this->Game->getPieceList()[i]->setTimePlacedToNow();
	}

	// now reset the time placed of the third piece, and then the second piece
	//System::Threading::Thread::Sleep(3*1000); // wait for 1 second (1000 ms)
	//this->Game->getPieceList()[2]->setTimePlacedToNow();
	//System::Threading::Thread::Sleep(3*1000); // wait for 1 second (1000 ms)


	this->endTrack();

}

//----------------------------------------------------------------------------------------------------------
// 1 second between placement. Assign time to Pentagon TrackedPiece, and convert over to PuzzlePiece. Fill in other times with junk
void RunTracking::Test2() {
	// * in this test, colors not used; only names
	MessageBox::Show("RUNNING TEST 1: Basic Transfer of placement time, TrackedPiece to PuzzlePiece.");
	TrackedPiece red_circle = TrackedPiece("Circle", Scalar(165, 107, 25), Scalar(185, 233, 256));
	TrackedPiece green_rectangle = TrackedPiece("Rectangle", Scalar(74, 75, 50), Scalar(88, 214, 256));
	TrackedPiece yellow_pentagon = TrackedPiece("Pentagon", Scalar(16, 47, 47), Scalar(32, 200, 256));
	TrackedPiece white_square = TrackedPiece("Square", Scalar(77, 0, 168), Scalar(158, 63, 256));

	// fill in all the times with junk
	int placeTime;
	for each (PuzzlePiece^ piece in this->Game->getPieceList())
	{
		placeTime = getElapsedSeconds(this->gameRecord->getTimeStarted().Ticks);
		piece->setTimePlacedToNow();
		Debug::WriteLine("time is " + placeTime);
		System::Threading::Thread::Sleep(1); // wait for 1 ms
	}

	for each (PuzzlePiece^ piece in this->Game->getPieceList()) {
		if (piece->getName()->Equals(stdStringToSystemString(yellow_pentagon.getName()))) {
			piece->setTimePlacedToNow();
			Debug::WriteLine("Pentagon placed at 600 s ");
		}
	}

	return;
}

//----------------------------------------------------------------------------------------------------------
void RunTracking::Test3() {}
//----------------------------------------------------------------------------------------------------------
void RunTracking::Test4() {}
//----------------------------------------------------------------------------------------------------------
void RunTracking::Test5() {}
//----------------------------------------------------------------------------------------------------------
void RunTracking::Test6() {}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------