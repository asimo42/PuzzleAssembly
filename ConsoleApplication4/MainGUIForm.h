#include <Windows.h>
#include "stdafx.h"
#include <WinBase.h>
#include <WinUser.h>
#using <System.dll>
#include <stdlib.h>
#include  <stdio.h>
#include <vcclr.h>
#include "Functions.h"
#include "CalibrationMainPrompt.h"

#pragma once

namespace PuzzleAssembly {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainGUIForm
	/// </summary>
	public ref class MainGUIForm : public System::Windows::Forms::Form
	{
	public:
		MainGUIForm(void)
		{
			InitializeComponent();
			this->gameRunning = false;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainGUIForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  runGameButton;

	//private: System::Windows::Forms::Button^  stopGameButton;
	public: bool gameRunning;
	private: System::Windows::Forms::TextBox^  textBox1;
	public: 
	private: System::Windows::Forms::Label^  label1;
	private: System::ComponentModel::IContainer^  components;
	private: HandleVariables Vars;
	private: System::Windows::Forms::Button^  scoresButton;
	private: System::Windows::Forms::Button^  calibrateButton;
	private: System::Windows::Forms::Button^  loadButton;

	private: ScoreKeeping ScoreKeeper;


	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->runGameButton = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->scoresButton = (gcnew System::Windows::Forms::Button());
			this->calibrateButton = (gcnew System::Windows::Forms::Button());
			this->loadButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// runGameButton
			// 
			this->runGameButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->runGameButton->Location = System::Drawing::Point(370, 234);
			this->runGameButton->Name = L"runGameButton";
			this->runGameButton->Size = System::Drawing::Size(195, 71);
			this->runGameButton->TabIndex = 0;
			this->runGameButton->Text = L"Run Game";
			this->runGameButton->UseVisualStyleBackColor = true;
			this->runGameButton->Click += gcnew System::EventHandler(this, &MainGUIForm::runGameButton_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(30, 72);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(190, 20);
			this->textBox1->TabIndex = 6;
			this->textBox1->Text = L"KNOBPUZZLE";
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MainGUIForm::textBox1_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(31, 55);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(63, 13);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Game Code";
			// 
			// scoresButton
			// 
			this->scoresButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->scoresButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->scoresButton->Location = System::Drawing::Point(16, 237);
			this->scoresButton->Name = L"scoresButton";
			this->scoresButton->Size = System::Drawing::Size(203, 67);
			this->scoresButton->TabIndex = 8;
			this->scoresButton->Text = L"Performance / Progress";
			this->scoresButton->UseVisualStyleBackColor = true;
			this->scoresButton->Click += gcnew System::EventHandler(this, &MainGUIForm::scoresButton_Click);
			// 
			// calibrateButton
			// 
			this->calibrateButton->Enabled = false;
			this->calibrateButton->Location = System::Drawing::Point(237, 237);
			this->calibrateButton->Name = L"calibrateButton";
			this->calibrateButton->Size = System::Drawing::Size(75, 23);
			this->calibrateButton->TabIndex = 9;
			this->calibrateButton->Text = L"Calibrate";
			this->calibrateButton->UseVisualStyleBackColor = true;
			this->calibrateButton->Click += gcnew System::EventHandler(this, &MainGUIForm::calibrateButton_Click);
			// 
			// loadButton
			// 
			this->loadButton->Enabled = false;
			this->loadButton->Location = System::Drawing::Point(218, 72);
			this->loadButton->Name = L"loadButton";
			this->loadButton->Size = System::Drawing::Size(75, 23);
			this->loadButton->TabIndex = 10;
			this->loadButton->Text = L"Load";
			this->loadButton->UseVisualStyleBackColor = true;
			this->loadButton->Click += gcnew System::EventHandler(this, &MainGUIForm::loadButton_Click);
			// 
			// MainGUIForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(568, 308);
			this->Controls->Add(this->loadButton);
			this->Controls->Add(this->calibrateButton);
			this->Controls->Add(this->scoresButton);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->runGameButton);
			this->Name = L"MainGUIForm";
			this->Text = L"Puzzle Assembly Assistant";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void runGameButton_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->gameRunning = true;
			 this->runGameButton->Visible = false;
			 //this->stopGameButton->Visible = true;
			 System::String^ CodeString = this->textBox1->Text;
			 System::String^ puzzleType = searchPuzzleType(CodeString);
			 //KNOB PUZZLE IS STILL HARDCODED - WILL NEED TO MAKE CHANGES TO RELEVANT CLASSES

			 // load up puzzle class and start tracking
			 if (puzzleType->Equals("KnobPuzzle")) {   
				 KnobPuzzle^ puzzle = gcnew KnobPuzzle(CodeString);
				 initializeTracking( Vars.returnHandle(), puzzle, ScoreKeeper.returnHandle());
			 }
			 else if (puzzleType->Equals("BlockPuzzle")) {
				 //etc...
			 }

			 this->runGameButton->Visible = true;
		 }


		 // NOTE ALSO NEED A PAUSE BUTTON
//private: System::Void stopGameButton_Click(System::Object^  sender, System::EventArgs^  e) {
//			 this->gameRunning = false;
//			 this->runGameButton->Visible = true;
//			 this->stopGameButton->Visible = false;
//		 }


private: System::Void scoresButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 // scores should probably be a tabbed display, e.g. this session's games, Progress to-date
			 // we'll keep it a simple message box for now - We'll want a scrolling form later
			System::String^ results = ScoreKeeper.showFinalResults();
			MessageBox::Show(results);
		 }
private: System::Void calibrateButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 // this should go in loadButton_Click eventually
			 System::String^ CodeString = this->textBox1->Text;
			 System::String^ puzzleType = searchPuzzleType(CodeString);
			 // load up puzzle class and start tracking
			KnobPuzzle^ puzzle = gcnew KnobPuzzle(CodeString);
			 ConsoleApplication4::CalibrationMainPrompt^ calibForm = gcnew ConsoleApplication4::CalibrationMainPrompt();
			 calibForm->puzzle = puzzle;
			 if (calibForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				 MessageBox::Show("You're done with calibration!");
			 }
			 // set up calibration form
			 // pass off puzzle piece info
		 }

private: System::Void loadButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->calibrateButton->Enabled = true;
		 }

private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (textBox1->Text->Length == 0) {
				 this->loadButton->Enabled = false;
			 }
			 else {
				 this->loadButton->Enabled = true; 
			 }
		 }
};
}
