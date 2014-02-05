#include "stdafx.h"
#include "Hints.h"
#include <iostream>
using std::cout;
using std::endl;

using namespace System;
using namespace System::Threading;

void hing_blink(int num_blinks)
{
	for(int i = 0; i < num_blinks; i++)
		cout << "Blink #" << i << endl;
}







