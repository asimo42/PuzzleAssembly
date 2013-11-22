#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <string>
#include <opencv2\opencv.hpp>	

#define CODEFILE "C:/Users/Owner/Documents/401- Senior Design/TestInputForKnobPuzzle.txt";

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

	// THIS FILE LOCATION SHOULD BE DEFINED SOMEWHERE
	System::String^ inputFile = CODEFILE;
	array<System::String^>^ lines;
	// Read in all lines of code file into an array 'lines'
	try {
		lines = System::IO::File::ReadAllLines(inputFile);
	}
	// return error if there's a problem
	catch (System::Exception^ e) {
		System::Diagnostics::Debug::WriteLine(e);
		lines = gcnew array<System::String^>(1);
		System::Windows::Forms::MessageBox::Show("Error - can't read file");
		lines[0] = gcnew System::String("ERROR");
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
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------