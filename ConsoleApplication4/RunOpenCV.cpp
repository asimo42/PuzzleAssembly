#include "stdafx.h"

#include <opencv2\opencv.hpp>	
#include "Functions.h"
#include "RunOpenCV.h"


void RunOpenCV::Start() {
	startTrack();
	System::Diagnostics::Debug::WriteLine("Hey, opencv is done");
	System::Windows::Forms::MessageBox::Show(this->Flags->JunkLine);
}
