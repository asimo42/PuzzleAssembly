#include "stdafx.h"

#include "Functions.h"
#include "HandleVariables.h"
#include "HandleFlags.h"
#include "RunOpenCV.h"

#using <System.dll>

using namespace System::Collections::Generic;

int initializeOpenCV(HandleVariables^ %handleVars, HandleFlags^ %Flags, KnobPuzzle^ %Game)
{
	// Initialize OpenCV running class
   RunOpenCV* newOpenCV = new RunOpenCV();
   newOpenCV->Flags = Flags;
   newOpenCV->Vars = handleVars;
   newOpenCV->setGame(Game);
   newOpenCV->gameName = systemStringToStdString(Game->GetName());
   newOpenCV->Start();

  // set flag that visualization has exited
  System::Diagnostics::Debug::WriteLine("Render ended");
  //Flags->resetEndOpenCV();

  return EXIT_SUCCESS;
}