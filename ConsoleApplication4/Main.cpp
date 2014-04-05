#include "stdafx.h"

#include "PuzzlePiece.h"
#include "Functions.h"
#include <iostream>
#include <string>
#include <vector>
#include "MainGUIForm.h"
#include <msclr\marshal_cppstd.h> //to convert managed string to std::string
//#include <opencv2\opencv.hpp>	//includes all OpenCV headers

using namespace PuzzleAssembly;
using namespace msclr::interop;

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

	// Run external executable to set camera settings
	// path can't have spaces in it or it won't work
	System::String^ cameraprefs = System::Windows::Forms::Application::StartupPath + "/../../CameraPrefs/CameraPrefs.exe";
	string stdcameraprefs = marshal_as<string>(cameraprefs);
//	System::Console::WriteLine(cameraprefs);
	system(stdcameraprefs.c_str());

	// Create the main window and run it
	Application::Run(gcnew PuzzleAssembly::MainGUIForm());


	return 0;
}