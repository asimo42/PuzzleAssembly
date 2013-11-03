#include "stdafx.h"
#include <string>
#include <stack>
#include <process.h>
#include <stdio.h>
#include <Windows.h>
#using <System.dll>

#ifndef FILE_J
#define FILE_J

using namespace System::Collections::Generic;
/*  This class serves to share game data globally.  
It is only a thin layer of protection against the heavy risks of sharing global data.  Treat it as such!

A single instance of this class is created, and the handle ofthat instance is given to any function that needs to
access the element data.  Thus all changes are processed by this instance.  Functions can only change values one at a 
time, thanks to a system of mutex locks.  This way no two parts of the program can try to change something at once.  
Also, as all variables are always kept in one place, there 'should' be no duplicate or alternate versions of the same data; all parts 
of the program are using the same thing if handled properly.  
*/
ref class HandleVariables
{

	// some variables:
	// need for audio or visual hint (maybe should trigger a callback when this is hit)

	HANDLE myMutex;
	int NumNodes;
	int UnitMeasurement;
	int NumElements;
	int Exponent;
	int MaxNodeAssociations;
	int *NodeArray;
	double *XArray;
	double *YArray;
	double *ZArray;
	double OldX;
	double OldY;
	double OldZ;
	List<List<int>^>^ ElementList;
	
public: 

	System::String^ FileType;
	// initializing the variables
	void InitializeClass();
	void InitializeNodeArrays(int NumberNodes, int Unit);
	List<List<int>^>^ InitializeElementArray(int NumberElements);
	void SetElementList(List<List<int>^>^ list);
	void SetMaxNodeAssociations(int num);
	void SetNode(int index, int Node, double X, double Y, double Z);
	void SetFileType(System::String^ filetype);
	void ScaleNodes(double Scale, System::String^ dimension);

	// retrieving/ viewing the variables
	HandleVariables^ returnHandle() {return this;}
	List<List<int>^>^ GetElementList();
	int GetNumNodes();
	int GetNumElements();
	int GetMaxNodeAssociations();
	System::String^ GetMeasurement();
	int GetNodeFromNodeArray(int index);
	int GetElementFromElementList(int index); 
	List<int>^ GetElement(int element);
	double GetXFromNode(int Node);
	double GetYFromNode(int Node);
	double GetZFromNode(int Node);
	double * RetrieveXYZFromNode(int Node);
	int FindIndexOfNode(int Node);

	// changing the variables
	void RemoveSingleNode(int Node);
	void AddSingleNode();
	int ChangeNode(int Node, double newX, double newY, double newZ);
	List<int>^ RemoveSingleElement(int element);
	List<int>^ RemoveElementsUsingNode(int node);
	void AddElement(array<System::String^>^ associations);

private:
	void RemoveElements(List<int>^ indices);

};

#endif