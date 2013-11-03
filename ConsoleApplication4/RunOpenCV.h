#include "stdafx.h"
#include <vcclr.h>
#include <opencv2\opencv.hpp>	//includes all OpenCV headers
#include "Functions.h"
#include "HandleVariables.h"
#include "HandleFlags.h"


// Class to define the custom Interactor Style for the VTK visualization window
// Is basically a mash up of vtkInteractorStyleTrackballActor and ctkInteractorStyleTrackballCamera,
// with desired components harvested from both source codes.  I have also added code
// to interact with the GUI appropriately.  

class RunOpenCV
{

  public:

	  RunOpenCV() {};
  
	virtual void Start();

  //these classes are for communicating between openCV (unmanaged) and the rest of the program
  // gcroot appears to magically transfer my classes from managed->unmanaged without consequences. Don't ask how.
  gcroot<HandleVariables^> Vars;
  gcroot<HandleFlags^> Flags;

  // some other globals
  double SurfaceColor[3];
  bool INITIALIZE_ME;

protected:


  // Description:
  // Event bindings controlling the effects of pressing mouse buttons
  // or moving the mouse.  These are overriden from vtkInteractorStyle
  //virtual void OnMouseMove();
  //virtual void OnLeftButtonDown();
  //virtual void OnLeftButtonUp();
  //virtual void OnMiddleButtonDown();
  //virtual void OnMiddleButtonUp();
  //virtual void OnRightButtonDown();
  //virtual void OnRightButtonUp();
  //virtual void OnMouseWheelForward();
  //virtual void OnMouseWheelBackward();
  //virtual void OnKeyPress();
  //virtual void OnTimer();

  //#define VTKIS_PANACTOR 10

  ////these are the keypress function definitions
  //void ProcessX();
  //void ProcessY();
  //void ProcessZ();
  //void ProcessUndo();
  //void ProcessExit();



private:

  RunOpenCV(const RunOpenCV&);  // Not implemented.
  void operator=(const RunOpenCV&);  // Not implemented.

};
