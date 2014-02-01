#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <string>
#include "Functions.h"


using namespace System::Collections::Generic;

System::String^ searchPuzzleType(System::String^ code)
{
	System::String^ type = "";
	// Here I would search some database/list sort of thing for the type of puzzle. Or it starts the code.  Ex.
	if (code->Contains("KNOBPUZZLE")) {
		type = gcnew System::String("KnobPuzzle");
	}
	if (code->Contains("BLOCKPUZZLE")) {
		type = gcnew System::String("BlockPuzzle");
	}
	if (code->Contains("SNAKE")) {
		type = gcnew System::String("Snake");
	}
	return type;
}
//----------------------------------------------------------------------------------------------------------



array<System::String^>^ getCodeStrings(System::String^ code) {

	// path temporarily hardcoded here. Aren't using it currently; see below
	System::String^ inputFile = "C:/Users/Owner/Documents/401- Senior Design/PuzzleAssembly/PuzzleAssembly/ConsoleApplication4/TestInputForKnobPuzzle.txt";
	array<System::String^>^ lines;
	// Read in all lines of code file into an array 'lines'
	try {
		lines = System::IO::File::ReadAllLines(inputFile);
	}
	// return error if there's a problem
	catch (System::Exception^ e) {
		//System::Diagnostics::Debug::WriteLine(e);
		//lines = gcnew array<System::String^>(1);
		//System::Windows::Forms::MessageBox::Show("Error - can't read file");
		//lines[0] = gcnew System::String("ERROR");

		// for now, we will hardcode it so we don't get screwed over. CHANGE THIS LATER
		List<System::String^>^ tmpList = gcnew List<System::String^>();
		tmpList->Add( "KNOBPUZZLE1");
		tmpList->Add( "NO.PIECES 5"); 
		tmpList->Add( "LOC 1 1 COLOR 100 100 150 200 200 200 Square" );
		tmpList->Add( "LOC 2 2 COLOR 65 23 200 200 200 255 Rectangle" );
		tmpList->Add( "LOC 3 4 COLOR 10 10 10 100 100 100 Circle" );
		tmpList->Add( "LOC 5 3 COLOR 90 55 100 100 100 150 Star" );
		tmpList->Add( "LOC 6 7 COLOR 100 299 100 150 150 150 Pentagon" );
		tmpList->Add( "----------------------------------------------------------------");
		tmpList->Add( "** note: LOC xloc yloc COLOR Hmin Smin Vmin Hmax Smax Vmax name");
		lines = gcnew array<System::String^>(tmpList->Count);
		for (int i = 0; i < tmpList->Count; i++) {
			lines[i] = tmpList[i];
		}
		return lines; 
	}
	return lines;
}
//----------------------------------------------------------------------------------------------------------


int getCodeLocation(array<System::String^>^ lines, System::String^ code)
{
	int index = -1;
	// find location of start of puzzle info
	for each (System::String^ line in lines) {
		if(line->Contains(code)) {
			index = System::Array::IndexOf(lines, line);
			return index;
		}
	}
	// if never found, return error.
	if (index == -1) {
		System::Windows::Forms::MessageBox::Show("Error - cannot find puzzle");
		return -1;
	}
}
//----------------------------------------------------------------------------------------------------------

std::string intToStdString(int number){
	std::stringstream ss;
	ss << number;
	return ss.str();
}
//----------------------------------------------------------------------------------------------------------

// convert std::string to System::String^
System::String^ stdStringToSystemString(std::string str) {
	System::String^ MyString = gcnew System::String(str.c_str());
	return MyString;
}
//----------------------------------------------------------------------------------------------------------

// convert System::String^ to std::string
std::string systemStringToStdString(System::String^ str)
{
	if (str->Equals("")) {
		return "";
	}
     using System::Runtime::InteropServices::Marshal;
     System::IntPtr pointer = Marshal::StringToHGlobalAnsi(str);
     char* charPointer = reinterpret_cast<char*>(pointer.ToPointer());
     std::string returnString(charPointer, str->Length);
     Marshal::FreeHGlobal(pointer);
     return returnString;
}

//----------------------------------------------------------------------------------------------------------
List<int>^ scalarToList(cv::Scalar scalar) {
	List<int>^ myList = gcnew List<int>(0);
	myList->Add(scalar[0]); myList->Add(scalar[1]); myList->Add(scalar[2]);
	return myList;
}
//----------------------------------------------------------------------------------------------------------
// get elapsed seconds based on DateTime ticks
int getElapsedSeconds(long startTime) {
	DateTime tim = DateTime::Now;
	long placeTime = tim.Ticks - startTime; // 10,000 ticks in a millisecond, 1000 milliseconds in a second
	TimeSpan^ elapsed = gcnew TimeSpan(placeTime);
	return elapsed->TotalSeconds;
}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------