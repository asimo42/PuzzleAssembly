#include "stdafx.h"

#include "PuzzlePiece.h"
#include "Functions.h"
#include <iostream>
#include <string>
#include <vector>
#include "MainGUIForm.h"
//#include <opencv2\opencv.hpp>	//includes all OpenCV headers

using namespace PuzzleAssembly;

[STAThreadAttribute]
int _tmain(int argc, _TCHAR* argv[]) 
{

	//System::Windows::Forms::MessageBox::Show("You stopped the game!");

	// show GUI for selecting game
	// Lookup game in table, use to initialize board class
	// set up board class and other classes
	// pull in info from gameboard class
	 // turn on monitor

	//*****This is how my other prog starts off the mainform loop
	// Enabling Windows XP visual effects before any controls are created
	System::Windows::Forms::Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew PuzzleAssembly::MainGUIForm());


	return 0;
}