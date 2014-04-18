/*
This form guides the user through the general calibration process. It launches the ColorCalibrationForm for the user to calibrate colors.
It then uses the newly calibrated colors and launches OpenCV to record the destination locations of each piece. 
*/

#include <Windows.h>
#include <atlstr.h>
#include "stdafx.h"
#include <WinBase.h>
#include <WinUser.h>
#using <System.dll>
#include <stdlib.h>
#include  <stdio.h>
#include <vcclr.h>
#include <opencv2\opencv.hpp>	//includes all OpenCV headers
#include "Shape.h"

#include "Functions.h"
#include "ColorCalibrationForm.h"
#include "CalibrationTracking.h"

#pragma once

namespace ConsoleApplication4 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for CalibrationMainPrompt
	/// </summary>
	public ref class CalibrationMainPrompt : public System::Windows::Forms::Form
	{
	public:
		CalibrationMainPrompt(void)
		{
			InitializeComponent();
			this->STARTED = false;
			this->calibratingColors = true;
			this->calibratingLocations = false;
			this->waitingToPlacePieces = false;
			this->puzzle = gcnew KnobPuzzle();
			this->calibNextButton->Focus();
			this->colorForm = gcnew ConsoleApplication4::ColorCalibrationForm();
			this->myCalibrator = gcnew CalibrationTracking();

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CalibrationMainPrompt()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  calibNextButton;
	private: System::Windows::Forms::Label^  startColorsText;
	private: System::Windows::Forms::Label^  placePiecesLabel;
	private: System::Windows::Forms::Label^  pleaseWaitLabel;
	private: bool calibratingColors;
	private: bool calibratingLocations;
	private: bool waitingToPlacePieces;
	private: bool STARTED;
	public: KnobPuzzle^ puzzle;
	private: ConsoleApplication4::ColorCalibrationForm^ colorForm;
	private: CalibrationTracking^ myCalibrator;
	private: ThreadShell myThreadShell;

	protected: 

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->calibNextButton = (gcnew System::Windows::Forms::Button());
			this->startColorsText = (gcnew System::Windows::Forms::Label());
			this->placePiecesLabel = (gcnew System::Windows::Forms::Label());
			this->pleaseWaitLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(13, 11);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(95, 20);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Calibration";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(17, 44);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(500, 32);
			this->label2->TabIndex = 2;
			this->label2->Text = L"To account for varying lighting conditions, calibrate color recognition before st" 
				L"arting \r\na new game. If the board doesn\'t seem to be tracking correctly, try rec" 
				L"alibrating. \r\n";
			// 
			// calibNextButton
			// 
			this->calibNextButton->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->calibNextButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->calibNextButton->Location = System::Drawing::Point(436, 122);
			this->calibNextButton->Name = L"calibNextButton";
			this->calibNextButton->Size = System::Drawing::Size(123, 37);
			this->calibNextButton->TabIndex = 3;
			this->calibNextButton->Text = L"Next...";
			this->calibNextButton->UseVisualStyleBackColor = true;
			this->calibNextButton->Click += gcnew System::EventHandler(this, &CalibrationMainPrompt::calibNextButton_Click);
			// 
			// startColorsText
			// 
			this->startColorsText->AutoSize = true;
			this->startColorsText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->startColorsText->Location = System::Drawing::Point(45, 122);
			this->startColorsText->Name = L"startColorsText";
			this->startColorsText->Size = System::Drawing::Size(261, 20);
			this->startColorsText->TabIndex = 4;
			this->startColorsText->Text = L"Click Next to begin calibrating colors";
			// 
			// placePiecesLabel
			// 
			this->placePiecesLabel->AutoSize = true;
			this->placePiecesLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->placePiecesLabel->Location = System::Drawing::Point(12, 99);
			this->placePiecesLabel->Name = L"placePiecesLabel";
			this->placePiecesLabel->Size = System::Drawing::Size(412, 60);
			this->placePiecesLabel->TabIndex = 5;
			this->placePiecesLabel->Text = L"Please place all puzzle pieces in their assigned locations. \r\nPiece  locations wi" 
				L"ll now be calibrated.\r\nWhen you are ready, click Next";
			this->placePiecesLabel->Visible = false;
			// 
			// pleaseWaitLabel
			// 
			this->pleaseWaitLabel->AutoSize = true;
			this->pleaseWaitLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->pleaseWaitLabel->Location = System::Drawing::Point(55, 130);
			this->pleaseWaitLabel->Name = L"pleaseWaitLabel";
			this->pleaseWaitLabel->Size = System::Drawing::Size(307, 20);
			this->pleaseWaitLabel->TabIndex = 6;
			this->pleaseWaitLabel->Text = L"Please wait while locations are calibrated...";
			this->pleaseWaitLabel->Visible = false;
			// 
			// CalibrationMainPrompt
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(571, 176);
			this->Controls->Add(this->pleaseWaitLabel);
			this->Controls->Add(this->placePiecesLabel);
			this->Controls->Add(this->startColorsText);
			this->Controls->Add(this->calibNextButton);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"CalibrationMainPrompt";
			this->Text = L"Calibration";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &CalibrationMainPrompt::CalibrationMainPrompt_FormClosing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void calibNextButton_Click(System::Object^  sender, System::EventArgs^  e) {

				 if (this->puzzle->getPieceList()->Count <= 0) {
					 System::Windows::Forms::MessageBox::Show("Error: cannot find puzzle piece information. Please check game ID and try again");
					 System::Console::WriteLine("CalibrationMainPrompt.h::calibNextButton_Click() : Error- puzzle has no pieces. Exiting calibration");
					 this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
					 this->Close();
					 return;
				 }

				 // disable the next button
				 this->calibNextButton->Enabled = false;

				 // if we are currently in the color stage, do the following
				 if (this->calibratingColors) {

					 // make the main calibration form invisible
					 this->Visible = false;


					 //pass puzzle class over to color form, launch it, and wait for it to return a dialogresult
					 this->colorForm->puzzle = this->puzzle;
					 System::Windows::Forms::DialogResult dialogResult = colorForm->ShowDialog(); 
					 if (dialogResult == System::Windows::Forms::DialogResult::OK) {
						 System::Console::WriteLine("CalibrationMainPrompt.h::calibNextButton_Click() : colorFrom returned dialogue result OK");
						 delete colorForm;
					 }
					 else if (dialogResult == System::Windows::Forms::DialogResult::Cancel) {
						 System::Console::WriteLine("CalibrationMainPrompt.h::calibNextButton_Click() : colorFrom returned dialogue result Cancel");
						 delete colorForm;
						 this->Close(); // cancel calibration; close form. This will result in DialogResult::Cancel
						 return;
					 }

					 // make this form visible again
					 this->Visible = true;

					 // switch text from 'startcolors' to 'please place pieces on board'
					 this->startColorsText->Visible = false;
					 this->placePiecesLabel->Visible = true;

					 // change current status from 'calibrating colors' to 'waiting for user to place pieces'
 					 this->calibratingColors = false;
					 this->waitingToPlacePieces = true;


					 // since the calibrator will be running and running, set STARTED to true so we can be sure to close it down.
					 this->STARTED = true;

					//re enable the next button
					this->calibNextButton->Enabled = true;

					 // set up the calibrator running. For now it will just show the gameboard.
					 // when waitingForUserToPlacePieces becomes false, it will start the location calibration.
					 this->myCalibrator = gcnew CalibrationTracking();
					 myCalibrator->setGame(this->puzzle);
					 myCalibrator->waitingForUserToPlacePieces = true;
					 // running it on a separate thread so we can still process the callbacks here.
					 //myCalibrator->startLocationCalibration();
					 this->myThreadShell.myThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(myCalibrator, &CalibrationTracking::startLocationCalibration));
					 this->myThreadShell.myThread->Start();

					return;
				 }

				 // if we are currently waiting for the user to place pieces, and the user clicks the next button, then start to calibrate locations:
				 if (this->waitingToPlacePieces) {

					 // change instructions from 'please place pieces' to 'please wait for locations to be calibrated'
					 this->placePiecesLabel->Visible = false; 
					 //this->placePiecesLabel->Text = "Please wait while locations are calibrated...";
					 //this->pleaseWaitLabel->Visible = true;
					 System::Threading::Thread::Sleep(100); // wait just a moment so it changes the label before the calibrator takes focus

					 // change current status from 'waiting for user to place pieces' to 'calibrating locations'
 					 this->waitingToPlacePieces = false; 
					 this->calibratingLocations = true; 

					 // set up a new CalibrationTracking^, pass it our puzzle, and ask it to find the locations
					 //CalibrationTracking^ locationTracker = gcnew CalibrationTracking();
					 //locationTracker->setGame(this->puzzle);
					 //locationTracker->startLocationCalibration();
					 myCalibrator->waitingForUserToPlacePieces = false;
					 while (!myCalibrator->IS_STOPPED) {
						 System::Threading::Thread::Sleep(30);
					 }

					 // here the user waits while it calibrates location

					 // this was the last step, so set dialog result to OK to leave calibration
					 this->DialogResult = System::Windows::Forms::DialogResult::OK;
					 this->Close();
					 return;
				 }

				 //re enable the next button
				 this->calibNextButton->Enabled = true;
			 }



// If this form is closed prematurely, close the spawned ColorCalibrationForm, which should stop any threads running there. 
private: System::Void CalibrationMainPrompt_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {

			if (this->STARTED == false) {
				 cv::destroyAllWindows();
				 this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				 return;
			}

			 // end thread showing gameboard picture

			 if (!myCalibrator->IS_STOPPED) {
				 myCalibrator->Stop();
				 while (!this->myCalibrator->IS_STOPPED) {
					Console::WriteLine("calibrationMainPrompt::FormClosing():: Waiting for calibrator thread to end");
					System::Threading::Thread::Sleep(5);
				 }
			 }
			 this->myThreadShell.myThread->Abort();
			 this->myThreadShell.myThread->Join();
			 cv::destroyAllWindows();

			 if (this->colorForm->Enabled) {
				 this->colorForm->Close();
				 delete colorForm;
			 }
			 if (this->DialogResult != System::Windows::Forms::DialogResult::OK) {
				this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			 }
			 delete myCalibrator;
			 cv::destroyAllWindows();
		}
};
}
