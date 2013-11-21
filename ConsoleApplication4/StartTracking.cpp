#include "stdafx.h"

#include "Functions.h"
#include "HandleVariables.h"
#include "RunTracking.h"

#using <System.dll>

using namespace System::Collections::Generic;

int initializeOpenCV(HandleVariables^ %handleVars, KnobPuzzle^ %Game)
{
	// Initialize OpenCV running class
   RunTracking* newOpenCV = new RunTracking();
   newOpenCV->Vars = handleVars;
   newOpenCV->setGame(Game);
   newOpenCV->gameName = systemStringToStdString(Game->GetName());
   newOpenCV->Start();
   // Pull the game results to do something with them
	GamePlayed^ gameResults = newOpenCV->returnScore();
	// set the GAME_OVER flag so that the GUI can fetch it and process everything
	handleVars->setGameOver();

  return EXIT_SUCCESS;
}

