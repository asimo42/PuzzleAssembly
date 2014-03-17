#include <Windows.h>
#include "stdafx.h"
#include <WinBase.h>
#include <WinUser.h>
#using <System.dll>
#include <stdlib.h>
#include  <stdio.h>
#include <vcclr.h>
#include "Functions.h"
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
	/// Summary for ColorCalibrationForm
	/// </summary>
	public ref class ColorCalibrationForm : public System::Windows::Forms::Form
	{
	public:
		ColorCalibrationForm(void)
		{
			InitializeComponent();

			// initialize our global variables here
			this->puzzle = gcnew KnobPuzzle(); // this holds our puzzle, which will be passed in by CalibrationMainPrompt.h
			this->pieceIndex = 0; // this tells us which piece we are currently calibrating
			this->piece = gcnew PuzzlePiece(); // this is the piece we are currently calibrating
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ColorCalibrationForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  okButton;
	protected: 

	public: KnobPuzzle^ puzzle;
	private: int pieceIndex;
	private: PuzzlePiece^ piece;
	private: bool NEXT;
	private: CalibrationTracking calibrator;
	private: ThreadShell myThreadShell;
	private: System::Windows::Forms::Label^  label1;
	public: 
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  currentPieceLabel;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ColorCalibrationForm::typeid));
			this->okButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->currentPieceLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// okButton
			// 
			this->okButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->okButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->okButton->Location = System::Drawing::Point(322, 214);
			this->okButton->Name = L"okButton";
			this->okButton->Size = System::Drawing::Size(110, 60);
			this->okButton->TabIndex = 0;
			this->okButton->Text = L"OK";
			this->okButton->UseVisualStyleBackColor = true;
			this->okButton->Click += gcnew System::EventHandler(this, &ColorCalibrationForm::okButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(194, 16);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Calibrate Colors for Each Piece";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(16, 44);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(411, 78);
			this->label2->TabIndex = 2;
			this->label2->Text = resources->GetString(L"label2.Text");
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(19, 172);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(74, 13);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Current Piece:";
			// 
			// currentPieceLabel
			// 
			this->currentPieceLabel->AutoSize = true;
			this->currentPieceLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->currentPieceLabel->Location = System::Drawing::Point(100, 171);
			this->currentPieceLabel->Name = L"currentPieceLabel";
			this->currentPieceLabel->Size = System::Drawing::Size(145, 24);
			this->currentPieceLabel->TabIndex = 4;
			this->currentPieceLabel->Text = L"click ok to begin";
			// 
			// ColorCalibrationForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(444, 286);
			this->Controls->Add(this->currentPieceLabel);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->okButton);
			this->Name = L"ColorCalibrationForm";
			this->Text = L"Calibrate Colors";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &ColorCalibrationForm::ColorCalibrationForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &ColorCalibrationForm::ColorCalibrationForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ColorCalibrationForm_Load(System::Object^  sender, System::EventArgs^  e) {
			 }


	private: System::Void okButton_Click(System::Object^  sender, System::EventArgs^  e) {

				// make sure the puzzle has been properly assigned first 
				 if (!this->puzzle->checkIsInitialized()) {
					 Console::WriteLine("ColorCalibrationForm.h::okButton_Click: Error - this form was not properly initialized with a puzzle. Please give it a puzzle.");
					 this->DialogResult = System::Windows::Forms::DialogResult::Cancel;		// if not, return DialogResult::Cancel			 
				 }

				 // if the last piece has been calibrated, stop the calibrator, change the dialog result to OK and close this form
				 // note that the color calibration form is handling updating the colors in the PuzzlePiece instances
				 if (this->pieceIndex >= this->puzzle->getPieceList()->Count && this->puzzle->getPieceList()->Count != 0) {
					 //MessageBox::Show("That was the last piece!");

					 // lock thread while we wait for calibration thread to end
					 HANDLE myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "calibration");
			   		 WaitForSingleObject(myMutex, INFINITE);

					 // tell calibrator to stop, and wait until it responds that it has done so
					 this->calibrator.Stop();
					 while (!this->calibrator.IS_STOPPED) {
						 Console::WriteLine("Waiting for calibrator thread to end");
						 System::Threading::Thread::Sleep(5);
					 }
					 // now abort the calibration thread and join it to the current one
					 this->myThreadShell.myThread->Abort();
					 this->myThreadShell.myThread->Join();

					 // release mutex and exit out of this form with the dialogresult::OK
					 ReleaseMutex(myMutex);
					 this->DialogResult = System::Windows::Forms::DialogResult::OK;
					 this->Close();
					 return;
				 }

				 // if on the first piece, set up the new thread for the calibration. Thread will start tracking first piece.
				 if (this->pieceIndex == 0) {
					 // display current piece name on gui
					 this->piece = this->puzzle->getPieceList()[this->pieceIndex];
					 this->currentPieceLabel->Text = this->piece->getName();

					 // setup calibrator thread with puzzle and start it (I'm wondering if it would be better to pass it the puzzle piece to track instead - probably)
					 this->calibrator.setGame(this->puzzle);
					 this->myThreadShell.myThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(calibrator.returnHandle(), &CalibrationTracking::Start));
					 this->myThreadShell.myThread->Start(); 
					 // the first piece will start calibrating automatically

					// update piece index to next piece
					 this->pieceIndex++;

					 return;
				 }

				 // to iterate to next piece, tell calibrator thread to move to next piece, and then move to the next piece in this thread as well
				 if (this->puzzle->getPieceList()->Count != 0) {
					 this->calibrator.Next();
					 this->piece = this->puzzle->getPieceList()[this->pieceIndex];
					 this->currentPieceLabel->Text = this->piece->getName();
					 this->pieceIndex++;
					 return;
				 }

			 }

// if the form is closed prematurely, stop the calibrator thread
			 // already calibrated pieces will retain the new calibration information
 private: System::Void ColorCalibrationForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {

		// if the calibrator is already stopped, don't have to do anything
		if (!this->calibrator.IS_STOPPED) {
			Console::WriteLine("ColorCalibrationForm.h: this form is ending prematurely");
			// if it isn't, go ahead and stop it
			this->calibrator.Stop();
			while (!this->calibrator.IS_STOPPED) {
				 Console::WriteLine("Waiting for calibrator thread to end");
				 System::Threading::Thread::Sleep(5);
			 }
			 // now abort the calibration thread and join it to the current one
			 this->myThreadShell.myThread->Abort();
			 this->myThreadShell.myThread->Join();
			 this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		}
	}
};
}

