#include "stdafx.h"

/* Computer etiquette tells me I should have some sort of error handling/logging.
This is seriously rudimentary for now.
*/


#define LOG_FILE "./logfile.txt"


void writeToLog(System::String^ myMessage) {
	System::DateTime^ date1 = gcnew System::DateTime;
	date1 = date1->Now;
	System::String^ tim = date1->ToString("F");
	System::Diagnostics::Debug::WriteLine(tim + "  :  " + myMessage + "\n");
	//if (!System::IO::File::Exists(LOG_FILE)) {
	//	System::IO::File::Create(LOG_FILE);
	//}
 //   if(System::IO::File::Exists(LOG_FILE))
 //   {
        //using (FileStream fs = new FileStream("c:\\"+DateTime.Now.ToString("yyyy-MM-dd")+"err.log",FileMode.Append))
	if (!System::IO::File::Exists(LOG_FILE)) {
		System::IO::StreamWriter^ sw = gcnew System::IO::StreamWriter(LOG_FILE);
		sw->Write(tim + "  :  " + myMessage + "\n");
		sw->Close();
	}
	else {
		System::IO::StreamWriter^ sw = gcnew System::IO::StreamWriter(LOG_FILE, true);
		sw->Write(tim + "  :  " + myMessage + "\n");
		sw->Close();
	}

     //} 
}