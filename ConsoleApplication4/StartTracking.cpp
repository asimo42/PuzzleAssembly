#include "stdafx.h"

#include "Functions.h"
#include "RunTracking.h"

//#using <System.dll>

using namespace System::Collections::Generic;
using namespace System::Windows::Forms;

//int initializeTracking(HandleVariables^ %handleVars, KnobPuzzle^ %Game, ScoreKeeping^ %ScoreKeeper)
int initializeTracking(HandleVariables^ %handleVars, KnobPuzzle^ %Game)
{
	// Initialize OpenCV running class
   RunTracking* newOpenCV = new RunTracking();
   newOpenCV->Vars = handleVars;
   newOpenCV->setGame(Game);
   newOpenCV->gameName = systemStringToStdString(Game->GetName());
   newOpenCV->Start();
   // Pull the game results and add them to the over-arching ScoreKeeper class instance for record-keeping
   MessageBox::Show("Got out of RunOpenCV");
	GamePlayed^ gameResults = newOpenCV->returnScore();
	//ScoreKeeper->AddNewGame(gameResults);
	// set the GAME_OVER flag so that the GUI can fetch it and process everything
	handleVars->setGameOver();
  return EXIT_SUCCESS;
}

