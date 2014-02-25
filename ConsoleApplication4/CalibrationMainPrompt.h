#include <Windows.h>
#include "stdafx.h"
#include <WinBase.h>
#include <WinUser.h>
#using <System.dll>
#include <stdlib.h>
#include  <stdio.h>
#include <vcclr.h>
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
			this->calibratingColors = true;
			this->calibratingLocations = false;
			this->waitingToPlacePieces = false;
			this->puzzle = gcnew KnobPuzzle();
			this->calibNextButton->Focus();
			this->colorForm = gcnew ConsoleApplication4::ColorCalibrationForm();
			//
			//TODO: Add the constructor code here
			//
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
	public: KnobPuzzle^ puzzle;
	private: ConsoleApplication4::ColorCalibrationForm^ colorForm;

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
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(17, 44);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(532, 30);
			this->label2->TabIndex = 2;
			this->label2->Text = L"To account for varying lighting conditions, calibrate color recognition before st" 
				L"arting a new game. \r\nIf the board doesn\'t seem to be tracking correctly, try rec" 
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
					 this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
					 this->Close();
					 return;
				 }

				 // disable the next button
				 this->calibNextButton->Enabled = false;

				 // if we are in the color stage, show appropriate prompt
				 if (this->calibratingColors) {

					 //CalibrationTracking^ locationTracker = gcnew CalibrationTracking();
					 //locationTracker->setGame(this->puzzle);
					 //locationTracker->startLocationCalibration();
					 //return;


					 this->Visible = false;
					 // launch a new color calibration form
					 //ConsoleApplication4::ColorCalibrationForm^ colorForm = gcnew ConsoleApplication4::ColorCalibrationForm();
					 //pass puzzle class over to color form
					 this->colorForm->puzzle = this->puzzle;
					 if (this->colorForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
					 }

					 // make this form visible again, then now switch to placing pieces
					 this->Visible = true;
					 this->startColorsText->Visible = false;
 					 this->calibratingColors = false;
					 // instruct user to place pieces
					 this->placePiecesLabel->Visible = true;
					 this->waitingToPlacePieces = true;
					//re enable the next button
					this->calibNextButton->Enabled = true;
					return;
				 }

				 // if waiting for the user to place pieces, and then the user clicks the next button:
				 if (this->waitingToPlacePieces) {
					 this->waitingToPlacePieces = false; // stop waiting for pieces, remove instructions to do so
					 this->placePiecesLabel->Visible = false;
					 this->pleaseWaitLabel->Visible = true;  // instruct user to wait for the system to calibrate
					 this->calibratingLocations = true;  //set system to calibration
				 }

				 // if we are in the calibrating location stage, do the following
				 if (this->calibratingLocations) {
					 CalibrationTracking^ locationTracker = gcnew CalibrationTracking();
					 locationTracker->setGame(this->puzzle);
					 locationTracker->startLocationCalibration();

					 // start finding locations

					 // this is the last stage, so set dialog result to OK to leave calibration
					 this->DialogResult = System::Windows::Forms::DialogResult::OK;

				 }

				 //re enable the next button
				 this->calibNextButton->Enabled = true;
			 }

// If this form is closed prematurely, close the spawned ColorCalibrationForm, which should stop any threads running there. 
private: System::Void CalibrationMainPrompt_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			 this->colorForm->Close();
		}
};
}
