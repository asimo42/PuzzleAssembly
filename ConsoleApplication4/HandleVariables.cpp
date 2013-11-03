#include "stdafx.h"
#include <string>
#include <process.h>
#using <System.dll>
#include <stdio.h>
#include <Windows.h>
#include <list>
#include "HandleVariables.h"

using namespace System::Collections::Generic;
using namespace System;


void HandleVariables::InitializeClass() 
{
	//this = gcnew HandleVariables();
	OldX = 0;
	OldY = 0;
	OldZ = 0;
	NumNodes = 0;
	NumElements = 0;
}
//----------------------------------------------------------------------------------------------------------

void HandleVariables::InitializeNodeArrays(int NumberNodes, int Unit) 
{
	this->NumNodes = NumberNodes;
	this->UnitMeasurement = Unit;
	NodeArray = new int[NumberNodes];
	XArray = new double[NumberNodes];
	YArray = new double[NumberNodes];
	ZArray = new double[NumberNodes];
}
//----------------------------------------------------------------------------------------------------------

List<List<int>^>^ HandleVariables::InitializeElementArray(int NumberElements) 
{
	this->NumElements = NumberElements;
	List<List<int>^>^ ElementList = gcnew List<List<int>^>(NumElements);
	for (int i = 0; i < NumElements; i++) {
		List<int>^ sublist = gcnew List<int>();
		ElementList->Add(sublist);
	}
	return ElementList;
}
//----------------------------------------------------------------------------------------------------------

void HandleVariables::SetMaxNodeAssociations(int num) 
{
	this->MaxNodeAssociations = num;
}
//----------------------------------------------------------------------------------------------------------

void HandleVariables::SetNode(int index, int Node, double X, double Y, double Z)
{
	NodeArray[index] = Node;
	XArray[index] = X;
	YArray[index] = Y;
	ZArray[index] = Z;
}

void HandleVariables::SetFileType(System::String^ filetype) {
	this->FileType = filetype;
}

//----------------------------------------------------------------------------------------------------------

void HandleVariables::SetElementList(List<List<int>^>^ list) 
{
	this->ElementList = list;
}

//----------------------------------------------------------------------------------------------------------

List<List<int>^>^ HandleVariables::GetElementList() 
{
	return this->ElementList;
}
//----------------------------------------------------------------------------------------------------------

int HandleVariables::GetMaxNodeAssociations() 
{
	return this->MaxNodeAssociations;
}

//----------------------------------------------------------------------------------------------------------

int HandleVariables::GetNumNodes() 
{
	return this->NumNodes;
}
//----------------------------------------------------------------------------------------------------------

System::String^ HandleVariables::GetMeasurement() 
{
	System::String^ str = gcnew System::String("");
	if (this->UnitMeasurement == 0) {
		str = "Units=m";
	}
	if (this->UnitMeasurement == 2) {
		str = "Units=cm";
	}
	if (this->UnitMeasurement == 3) {
		str = "Units=mm";
	}
	return str;
}
//----------------------------------------------------------------------------------------------------------

int HandleVariables::GetNumElements() 
{
	return this->NumElements;
}
//----------------------------------------------------------------------------------------------------------

int HandleVariables::GetNodeFromNodeArray(int index) 
{
	return NodeArray[index];
}

//----------------------------------------------------------------------------------------------------------

int HandleVariables::GetElementFromElementList(int index) 
{
	List<int>^ element = this->ElementList[index];
	return element[0];
}
//----------------------------------------------------------------------------------------------------------

double * HandleVariables::RetrieveXYZFromNode(int Node) {
	double *tmp;
	tmp = new double[3];
	int index = FindIndexOfNode(Node);
	tmp[0] = this->XArray[index];
	tmp[1] = this->YArray[index];
	tmp[2] = this->ZArray[index];
	return tmp;
}
//----------------------------------------------------------------------------------------------------------

double HandleVariables::GetXFromNode(int Node) {
	int index = FindIndexOfNode(Node);
	return XArray[index];
}
//----------------------------------------------------------------------------------------------------------

double HandleVariables::GetYFromNode(int Node) {
	int index = FindIndexOfNode(Node);
	return YArray[index];
}
//----------------------------------------------------------------------------------------------------------

double HandleVariables::GetZFromNode(int Node) {
	int index = FindIndexOfNode(Node);
	return ZArray[index];
}
//----------------------------------------------------------------------------------------------------------

int HandleVariables::FindIndexOfNode(int Node) 
{
	int index = -1;
	for (int i = 0; i < this->NumNodes; i++) {
		if (Node == NodeArray[i]) {
			index = i; 
			return index;
		}
	}
	if (index == -1) {
		System::Diagnostics::Debug::WriteLine("Error - could not find node {0} in list", Node); 
	}
	return index;
}

//----------------------------------------------------------------------------------------------------------

int HandleVariables::ChangeNode(int Node, double newX, double newY, double newZ) 
{
	//create mutex lock
	myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "ChangeNode");
	WaitForSingleObject(myMutex, INFINITE);
	// check for index of node
	int index = FindIndexOfNode(Node);
	// change node
	this->OldX = this->XArray[index];
	this->OldY = this->YArray[index];
	this->OldZ = this->ZArray[index];
	this->XArray[index] = newX;
	this->YArray[index] = newY;
	this->ZArray[index] = newZ;
	// release mutex lock
	ReleaseMutex(myMutex);
	System::Diagnostics::Debug::WriteLine("HEY YOU CHANGED A NODE:)");
	return index;
}

//----------------------------------------------------------------------------------------------------------

void HandleVariables::RemoveSingleNode(int Node) 
{
	myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "RemoveNode");
	WaitForSingleObject(myMutex, INFINITE);

	int newSize = this->NumNodes - 1;
	int * nodeArray; double * xArray; double * yArray; double * zArray;
	nodeArray = new int [newSize]; 
	xArray = new double[newSize];
	yArray = new double[newSize];
	zArray = new double[newSize];
	int index = FindIndexOfNode(Node);
	int count = 0;
	// copy over array, skipping the deleted node
	for (int i = 0; i < this->NumNodes; i++) {
		if (i == index) {
			continue;
		}
		if (i != index) {
			nodeArray[count] = count + 1;
			xArray[count] = this->XArray[i];
			yArray[count] = this->YArray[i];
			zArray[count] = this->ZArray[i];
			count++;
		}
	}
	this->NodeArray = nodeArray;
	this->XArray = xArray;
	this->YArray = yArray;
	this->ZArray = zArray;
	this->NumNodes = this->NumNodes - 1;

	ReleaseMutex(myMutex);
}
//----------------------------------------------------------------------------------------------------------

void HandleVariables::AddSingleNode() 
{
	myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "AddNode");
	WaitForSingleObject(myMutex, INFINITE);

	int newSize = this->NumNodes + 1;
	int * nodeArray; double * xArray; double * yArray; double * zArray;
	nodeArray = new int [newSize]; 
	xArray = new double[newSize];
	yArray = new double[newSize];
	zArray = new double[newSize];
	// copy over values to new arrays
	for (int i = 0; i < this->NumNodes; i++) {
		nodeArray[i] = this->NodeArray[i];
		xArray[i] = this->XArray[i];
		yArray[i] = this->YArray[i];
		zArray[i] = this->ZArray[i];
	}
	// initialize new node to 0 0 0
	nodeArray[this->NumNodes] = this->NumNodes + 1;
	xArray[this->NumNodes] = 0;
	yArray[this->NumNodes] = 0;
	zArray[this->NumNodes] = 0;
	//copy nodes to global
	NodeArray = nodeArray;
	XArray = xArray;
	YArray = yArray;
	ZArray = zArray;
	this->NumNodes = this->NumNodes + 1;

	ReleaseMutex(myMutex);
}
//----------------------------------------------------------------------------------------------------------

void HandleVariables::ScaleNodes(double Scale, System::String^ dimension)
{
	myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "AddNode");
	WaitForSingleObject(myMutex, INFINITE);
	if (dimension->Equals("X")) {
		for (int i = 0; i < this->NumNodes; i++) {
			XArray[i] = XArray[i] * Scale;
		}
	}
	if (dimension->Equals("Y")) {
		for (int i = 0; i < this->NumNodes; i++) {
			YArray[i] = YArray[i] * Scale;
		}
	}
	if (dimension->Equals("Z")) {
		for (int i = 0; i < this->NumNodes; i++) {
			ZArray[i] = ZArray[i] * Scale;
		}
	}
	ReleaseMutex(myMutex);
}
//----------------------------------------------------------------------------------------------------------

List<int>^ HandleVariables::RemoveElementsUsingNode(int node) {

	myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "RemoveElements");
	WaitForSingleObject(myMutex, INFINITE);

	int counter = 0;
	List<int>^ storage = gcnew List<int>();
	for each (List<int>^ Element in this->ElementList) {
		for (int i = 3; i < Element->Count; i++) {
			// if element uses node, delete element
			if (Element[i] == node) {
				storage->Add(counter);
				continue;
			}
			// all nodes above deleted node are pushed down 1 to keep labeling consistent
			// so if a node association is higher, then push it down one
			if (Element[i] > node) {
				Element[i] = Element[i] - 1;
			}
		}
		counter++;
	}
	if (storage->Count > 0) {
		RemoveElements(storage);
	}
	ReleaseMutex(myMutex);
	return storage;
}
//----------------------------------------------------------------------------------------------------------

List<int>^ HandleVariables::GetElement(int element) {
	for each (List<int>^ Element in this->ElementList) {
		if (Element[0] == element) {
			return Element;
		}
	}
	List<int>^ error = gcnew List<int>(1);
	return error;
}

//----------------------------------------------------------------------------------------------------------

List<int>^ HandleVariables::RemoveSingleElement(int element) {

	myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "RemoveElement");
	WaitForSingleObject(myMutex, INFINITE);

	int counter = 0;
	List<int>^ storage = gcnew List<int>();
	for each (List<int>^ Element in this->ElementList) {
		if (Element[0] == element) {
			storage->Add(counter);
		}
		if (Element[0] > element) {
			Element[0] = Element[0] - 1;
		}
		counter++;
	}
	if (storage->Count == 1) {
		RemoveElements(storage);
	}
	if (storage->Count != 1) {
		System::Windows::Forms::MessageBox::Show("Error, could not find element to delete");
	}
	ReleaseMutex(myMutex);
	return storage;
}
//----------------------------------------------------------------------------------------------------------

void HandleVariables::RemoveElements(List<int>^ indices) {
	System::Diagnostics::Debug::WriteLine("Current Number Elements : {0}", this->ElementList->Count);
	myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "RemoveElement");
	WaitForSingleObject(myMutex, INFINITE);
	// Remove backwards, so that indices for subsequent removals don't change
	for (int i = (indices->Count -1); i >= 0; i--) {
		System::Diagnostics::Debug::WriteLine("Removing Element: {0}", indices[i]);
		this->ElementList->RemoveAt(indices[i]);
	}
	// rename elements from 1 -> numElements
	int count = 1;
	for each (List<int>^ Element in this->ElementList) {
		Element[0] = count++;
	}
	this->NumElements = this->ElementList->Count;
	ReleaseMutex(myMutex);
	System::Diagnostics::Debug::WriteLine("Elements Remaining: {0} ", this->ElementList->Count);

}

//----------------------------------------------------------------------------------------------------------

void HandleVariables::AddElement(array<System::String^>^ associations) {

	myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "AddElement");
	WaitForSingleObject(myMutex, INFINITE);

	int numnodes = associations->Length;

	// if the new element has more nodes than the other elements, up the MaxNodeAssociations to expand the GUI table
	if (numnodes > this->MaxNodeAssociations) {
		this->MaxNodeAssociations = numnodes; 
	}
	int element = 0;
	List<int>^ newElement = gcnew List<int>(numnodes);
	newElement->Add(NumElements + 1);
	if (numnodes == 1 || numnodes == 2) {
		newElement->Add(1);
	}
	else if (numnodes == 4 || numnodes == 9) {
		newElement->Add(2);
	}
	else if (numnodes == 8 || numnodes == 27) {
		newElement->Add(3);
	}
	else {
		System::Diagnostics::Debug::WriteLine("Error : Unrecognized element type, with {0} nodes", numnodes);
		ReleaseMutex(myMutex);
		return;
	}
	newElement->Add(numnodes);
	for (int i = 0; i < numnodes; i++) {
		newElement->Add(System::Convert::ToInt32(associations[i]));
	}
	this->ElementList->Add(newElement);
	this->NumElements++;
	ReleaseMutex(myMutex);
	return;
}