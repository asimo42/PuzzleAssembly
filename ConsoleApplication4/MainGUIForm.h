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
#include "RunTracking.h"

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

			// ** THESE ARE INITIALIZED FOR TESTING PURPOSES ONLY - REMOVE FOR FINAL VERSION
			this->loadButton->Enabled = true;
			this->calibrateButton->Enabled = true;
			this->runGameButton->Enabled = true;
			//******

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

	public: bool gameRunning;
	private: System::Windows::Forms::TextBox^  textBox1;
	public: 
	private: System::Windows::Forms::Label^  label1;
	private: System::ComponentModel::IContainer^  components;
	private: KnobPuzzle currentPuzzle;
	//private: ThreadShell myThreadShell;
	//private: RunTracking* runTracking;
	private: System::Windows::Forms::Button^  scoresButton;
	private: System::Windows::Forms::Button^  calibrateButton;
	private: System::Windows::Forms::Button^  loadButton;
	private: System::Windows::Forms::Button^  stopGameButton;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::HelpProvider^  helpProvider1;
	private: System::Windows::Forms::CheckBox^  level1CheckBox;
	private: System::Windows::Forms::CheckBox^  level2CheckBox;
	private: System::Windows::Forms::CheckBox^  level3CheckBox;
	private: System::Windows::Forms::Button^  levelDescriptionsButton;

	private: System::Windows::Forms::Label^  label4;

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
			this->stopGameButton = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->helpProvider1 = (gcnew System::Windows::Forms::HelpProvider());
			this->level1CheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->level2CheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->level3CheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->levelDescriptionsButton = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// runGameButton
			// 
			this->runGameButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->runGameButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->runGameButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->runGameButton->Location = System::Drawing::Point(597, 207);
			this->runGameButton->Name = L"runGameButton";
			this->runGameButton->Size = System::Drawing::Size(247, 142);
			this->runGameButton->TabIndex = 0;
			this->runGameButton->Text = L"Run Game";
			this->runGameButton->UseVisualStyleBackColor = true;
			this->runGameButton->Click += gcnew System::EventHandler(this, &MainGUIForm::runGameButton_Click);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(17, 141);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(350, 38);
			this->textBox1->TabIndex = 6;
			this->textBox1->Text = L"KNOBPUZZLE1";
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MainGUIForm::textBox1_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 113);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(132, 25);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Game Code:";
			// 
			// scoresButton
			// 
			this->scoresButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->scoresButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->scoresButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->scoresButton->Location = System::Drawing::Point(12, 235);
			this->scoresButton->Name = L"scoresButton";
			this->scoresButton->Size = System::Drawing::Size(277, 114);
			this->scoresButton->TabIndex = 8;
			this->scoresButton->Text = L"Performance";
			this->scoresButton->UseVisualStyleBackColor = true;
			this->scoresButton->Click += gcnew System::EventHandler(this, &MainGUIForm::scoresButton_Click);
			// 
			// calibrateButton
			// 
			this->calibrateButton->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->calibrateButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->calibrateButton->Enabled = false;
			this->calibrateButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->calibrateButton->Location = System::Drawing::Point(322, 235);
			this->calibrateButton->Name = L"calibrateButton";
			this->calibrateButton->Size = System::Drawing::Size(256, 114);
			this->calibrateButton->TabIndex = 9;
			this->calibrateButton->Text = L"Calibrate";
			this->calibrateButton->UseVisualStyleBackColor = true;
			this->calibrateButton->Click += gcnew System::EventHandler(this, &MainGUIForm::calibrateButton_Click);
			// 
			// loadButton
			// 
			this->loadButton->Enabled = false;
			this->loadButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->loadButton->Location = System::Drawing::Point(368, 141);
			this->loadButton->Name = L"loadButton";
			this->loadButton->Size = System::Drawing::Size(172, 38);
			this->loadButton->TabIndex = 10;
			this->loadButton->Text = L"Load";
			this->loadButton->UseVisualStyleBackColor = true;
			this->loadButton->Click += gcnew System::EventHandler(this, &MainGUIForm::loadButton_Click);
			// 
			// stopGameButton
			// 
			this->stopGameButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->stopGameButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->stopGameButton->Enabled = false;
			this->stopGameButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->stopGameButton->Location = System::Drawing::Point(595, 40);
			this->stopGameButton->Name = L"stopGameButton";
			this->stopGameButton->Size = System::Drawing::Size(247, 139);
			this->stopGameButton->TabIndex = 11;
			this->stopGameButton->Text = L"Stop Game";
			this->stopGameButton->UseVisualStyleBackColor = true;
			this->stopGameButton->Click += gcnew System::EventHandler(this, &MainGUIForm::stopGameButton_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(12, 21);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(474, 29);
			this->label2->TabIndex = 12;
			this->label2->Text = L"Welcome to the Puzzle Assembly Assistant!";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(42, 65);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(472, 24);
			this->label3->TabIndex = 13;
			this->label3->Text = L"Please enter a game code below (exactly as it appears)";
			// 
			// level1CheckBox
			// 
			this->level1CheckBox->AutoSize = true;
			this->level1CheckBox->Checked = true;
			this->level1CheckBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->level1CheckBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->level1CheckBox->Location = System::Drawing::Point(166, 190);
			this->level1CheckBox->Name = L"level1CheckBox";
			this->level1CheckBox->Size = System::Drawing::Size(79, 29);
			this->level1CheckBox->TabIndex = 14;
			this->level1CheckBox->Text = L"Easy";
			this->level1CheckBox->UseVisualStyleBackColor = true;
			this->level1CheckBox->CheckedChanged += gcnew System::EventHandler(this, &MainGUIForm::level1CheckBox_CheckedChanged);
			// 
			// level2CheckBox
			// 
			this->level2CheckBox->AutoSize = true;
			this->level2CheckBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->level2CheckBox->Location = System::Drawing::Point(255, 192);
			this->level2CheckBox->Name = L"level2CheckBox";
			this->level2CheckBox->Size = System::Drawing::Size(107, 29);
			this->level2CheckBox->TabIndex = 15;
			this->level2CheckBox->Text = L"Medium";
			this->level2CheckBox->UseVisualStyleBackColor = true;
			this->level2CheckBox->CheckedChanged += gcnew System::EventHandler(this, &MainGUIForm::level2CheckBox_CheckedChanged);
			// 
			// level3CheckBox
			// 
			this->level3CheckBox->AutoSize = true;
			this->level3CheckBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->level3CheckBox->Location = System::Drawing::Point(368, 192);
			this->level3CheckBox->Name = L"level3CheckBox";
			this->level3CheckBox->Size = System::Drawing::Size(77, 29);
			this->level3CheckBox->TabIndex = 16;
			this->level3CheckBox->Text = L"Hard";
			this->level3CheckBox->UseVisualStyleBackColor = true;
			this->level3CheckBox->CheckedChanged += gcnew System::EventHandler(this, &MainGUIForm::level3CheckBox_CheckedChanged);
			// 
			// levelDescriptionsButton
			// 
			this->levelDescriptionsButton->BackColor = System::Drawing::Color::Linen;
			this->levelDescriptionsButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->levelDescriptionsButton->Location = System::Drawing::Point(451, 185);
			this->levelDescriptionsButton->Name = L"levelDescriptionsButton";
			this->levelDescriptionsButton->Size = System::Drawing::Size(127, 44);
			this->levelDescriptionsButton->TabIndex = 17;
			this->levelDescriptionsButton->Text = L"Descriptions...";
			this->levelDescriptionsButton->UseVisualStyleBackColor = false;
			this->levelDescriptionsButton->Click += gcnew System::EventHandler(this, &MainGUIForm::levelDescriptionsButton_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(8, 192);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(152, 24);
			this->label4->TabIndex = 18;
			this->label4->Text = L"Level of Difficulty:";
			// 
			// MainGUIForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Beige;
			this->ClientSize = System::Drawing::Size(854, 353);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->levelDescriptionsButton);
			this->Controls->Add(this->level3CheckBox);
			this->Controls->Add(this->level2CheckBox);
			this->Controls->Add(this->level1CheckBox);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->stopGameButton);
			this->Controls->Add(this->loadButton);
			this->Controls->Add(this->calibrateButton);
			this->Controls->Add(this->scoresButton);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->runGameButton);
			this->HelpButton = true;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MainGUIForm";
			this->Text = L"Puzzle Assembly Assistant";
			this->HelpButtonClicked += gcnew System::ComponentModel::CancelEventHandler(this, &MainGUIForm::MainGUIForm_HelpButtonClicked);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void runGameButton_Click(System::Object^  sender, System::EventArgs^  e) {
	
			 HANDLE myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "runGameButton_Click : loading game");

			 // load up puzzle if not already loaded. 
			 if (!this->currentPuzzle.checkIsInitialized(this->textBox1->Text)) {
				 MessageBox::Show("Loading Puzzle");
				 Console::WriteLine("MainGUIForm.h : runGameButton_Click() : Loading Puzzle");
				 int success = this->loadPuzzleFromCode();
				 // if loading was unsuccessful, alert user and cancel running game
				 if (success == -1) {
					 System::Windows::Forms::MessageBox::Show("Error loading puzzle. \nPlease check code string");
					 Console::WriteLine("MainGUIForm.h : runGameButton_Click() : Error loading puzzle. \nPlease check code string");
					 return;
				 }
			 }

		 	ReleaseMutex(myMutex);

			 //MAY WANT A COMPREHENSIVE ERROR CHECK within KnobPuzzle, for a one line check

			 this->gameRunning = true;
			 this->runGameButton->Enabled = false;
			 this->loadButton->Enabled = false;
			 this->calibrateButton->Enabled = false;
			 this->scoresButton->Enabled = false;
			 this->stopGameButton->Enabled = true;

			 // now start the tracking
			 initializeTracking( this->currentPuzzle.returnHandle(), ScoreKeeper.returnHandle());

			 this->runGameButton->Enabled = true;
			 this->stopGameButton->Enabled = false;
			 this->loadButton->Enabled = true;
			 this->calibrateButton->Enabled = true;
			 this->scoresButton->Enabled = true;

		 }
//----------------------------------------------------------------------------------------------------------
// User stops game before it ends naturally
private: System::Void stopGameButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->gameRunning = false;

			 // tell KnobPuzlze to end; RunTracking will see this and end. 
			 this->currentPuzzle.setEndGame();				

		 }

//----------------------------------------------------------------------------------------------------------
private: System::Void scoresButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 // scores should probably be a tabbed display, e.g. this session's games, Progress to-date
			 // we'll keep it a simple message box for now - We'll want a scrolling form later
			System::String^ results = ScoreKeeper.showFinalResults();
			MessageBox::Show(results);
		 }

//----------------------------------------------------------------------------------------------------------
private: System::Void calibrateButton_Click(System::Object^  sender, System::EventArgs^  e) {

			 HANDLE myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "runGameButton_Click : loading game");

			 // load up puzzle if not already loaded (compare current KnobPuzzle to the textbox input)
			 if (!this->currentPuzzle.checkIsInitialized(this->textBox1->Text)) {
				 MessageBox::Show("Loading Puzzle");
				 System::Console::WriteLine("MainGUIForm.h : calibrateButton_Click() : Loading Puzzle");
				 int success = this->loadPuzzleFromCode();
				 if (success == -1) {
					 System::Console::WriteLine("MainGUIForm.h : calibrateButton_Click() : Error loading puzzle. \nPlease check code string");
					 return;
				 }
			 }

			 // create new calibration main form and pass it the puzzle
			 ConsoleApplication4::CalibrationMainPrompt^ calibForm = gcnew ConsoleApplication4::CalibrationMainPrompt();
			 calibForm->puzzle = this->currentPuzzle.returnHandle();

			 // wait until the calibration form has exited. 
			 if (calibForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				 MessageBox::Show("You're done with calibration!");
			 }
			 else if (calibForm->ShowDialog() == System::Windows::Forms::DialogResult::Cancel) {
				// reload old data into current puzzle
				 MessageBox::Show("Re-Loading Puzzle data");
				 System::Console::WriteLine("MainGUIForm.h : calibrateButton_Click() : ReLoading Puzzle");
				 int success = this->loadPuzzleFromCode();
				 if (success == -1) {
					 System::Console::WriteLine("MainGUIForm.h : calibrateButton_Click() : Error reLoading puzzle. \nPlease check code string");
					 return;
				 }
			 }

			 // color and location info should be embedded now in this->currentPuzzle, which should be passed to tracking initializer

			 System::Windows::Forms::DialogResult result = MessageBox::Show("Do you want to save calibration settings for future sessions?", "Warning", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Warning);
			 // if user selects that they want to save the settings, save the settings
			 if(result == System::Windows::Forms::DialogResult::Yes)
			 {
				 Console::WriteLine("Saving Settings");
    			 int success = this->currentPuzzle.SaveCalibrationSettings();
				 if (success != 0) {
					MessageBox::Show("Error: Failed to save settings. Calibrated values will be used for this session only.");
					Console::WriteLine("Error: Failed to save settings. Calibrated values will be used for this session only.");
				 }
			 }

			 // Otherwise, cancel
			 else if(result == System::Windows::Forms::DialogResult::No || result == System::Windows::Forms::DialogResult::Cancel)
			 {
			   Console::WriteLine("Not saving settings");
			 }

 		 	ReleaseMutex(myMutex);

			 return;
		 }

//----------------------------------------------------------------------------------------------------------
private: System::Void loadButton_Click(System::Object^  sender, System::EventArgs^  e) {

			 // load puzzle from puzzle code box text and enable calibrate/run buttons.
			 this->calibrateButton->Enabled = true;
			 this->runGameButton->Enabled = true;
			 int success = this->loadPuzzleFromCode();
			 if (success == -1) {
				 System::Console::WriteLine("MainGUIForm.h : loadButton_Click(): Error loading puzzle. \nPlease check code string");
				 return;
			 }
			 // disable load button - to signify puzzle successfully loaded
			 this->loadButton->Enabled = false;

		 }

//----------------------------------------------------------------------------------------------------------
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {

			 // if puzzle code box is blank, de-enable all buttons
			 if (textBox1->Text->Length == 0) {
				 this->loadButton->Enabled = false;
				 this->calibrateButton->Enabled = false;
				 this->runGameButton->Enabled = false;
			 }
			 // otherwise enable load and run button
			 else {
				 this->loadButton->Enabled = true; 
				 this->calibrateButton->Enabled = true;
				 this->runGameButton->Enabled = true;
			 }
		 }

//----------------------------------------------------------------------------------------------------------
// take code from input textbox and load puzzle from it
private: int loadPuzzleFromCode() {

			 int success = 0;

			 // make sure the user has selected a level of difficulty
			 if (!level1CheckBox->Checked == true && !level2CheckBox->Checked == true && ! !level3CheckBox->Checked == true) {
				 MessageBox::Show("Please select a level of difficulty");
				 return -1;
			 }

			 System::String^ CodeString = this->textBox1->Text;
			 System::String^ puzzleType = searchPuzzleType(CodeString);
			 //KNOB PUZZLE IS STILL HARDCODED - WILL NEED TO GO THROUGH ALL CODE IF YOU WANT TO ADD NEW GAME TYPES

			 // load up puzzle class. If unsuccessful, will return -1
			 if (puzzleType->Equals("KnobPuzzle")) {   
				 success = this->currentPuzzle.setGame(CodeString);
			 }

			 // check if loading was successful
			 if (success != 0) {
				 //MessageBox::Show("MainGUIForm.h : loadPuzzleFromCode(): error loading knob puzzle from code");
				 System::Console::WriteLine("MainGUIForm.h : loadPuzzleFromCode(): error loading knob puzzle from code");
				 return success;
			 }
			 // load level of difficulty to puzzle
			 if (level1CheckBox->Checked == true) {
				 this->currentPuzzle.setLevelOfDifficulty(1);
			 }
			 if (level2CheckBox->Checked == true) {
				 this->currentPuzzle.setLevelOfDifficulty(2);
			 }
			 if (level3CheckBox->Checked == true) {
				 this->currentPuzzle.setLevelOfDifficulty(3);
			 }

			 // test code for importing drawing info::
			 //int Xpos = this->currentPuzzle.getPieceList()[0]->getShapePointX();
			 //int Ypos = this->currentPuzzle.getPieceList()[0]->getShapePointY();
			 //System::String^ name = this->currentPuzzle.getPieceList()[0]->getName();
			 //System::String^ str = "Shape Drawing location for Piece: " + name + " : XPos = " + Xpos + "  Ypos = " + Ypos;
			 //System::Windows::Forms::MessageBox::Show(str);
			 // :: end test code

			 return success;
		 }
private: System::Void MainGUIForm_HelpButtonClicked(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 MessageBox::Show("You Clicked the Help Button! Help functionality under construction.");
		 }

// if user selects a level of difficulty box, set that box to check and uncheck the other difficulty boxes. 
private: System::Void level2CheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (level2CheckBox->Checked == true) { 
				 level1CheckBox->Checked = false;
				 level3CheckBox->Checked = false;	
			 }
		
		 }
private: System::Void level3CheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (level3CheckBox->Checked == true) { 
				 level1CheckBox->Checked = false;
				 level2CheckBox->Checked = false;	
			 }
	
		 }
private: System::Void level1CheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (level1CheckBox->Checked == true) { 
				level2CheckBox->Checked = false;
				level3CheckBox->Checked = false;	
			 }
	
		 }
private: System::Void levelDescriptionsButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 System::String^ tmp = "Levels of Difficulty: \nEasy:   \n\nMedium: \n\nHard: ";
			 MessageBox::Show(tmp);
		 }
};
}
