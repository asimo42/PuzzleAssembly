/* 
	This form is the main GUI by which the user starts and stops games. This is also the 'entry-point' of the program. 
	All callbacks for users selecting items on the main GUI are handled here. 
	The 'global' class variables here hold information that is consistent through different 'phases' of the program;
	e.g. a knobpuzzle loaded here can be transfered to calibration, or to a running game, etc, and all game results are stored
	in these variables. This is because this is the only form/class that never closes or ends throughout a session. 
*/
#include <Windows.h>
#include "stdafx.h"
#include <WinBase.h>
#include <WinUser.h>
#using <System.dll>
#include <stdlib.h>
#include  <stdio.h>
#include <vcclr.h>
#include "Functions.h"
#include "displayResultsForm.h"
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

			// initialize all the status variables and the knobpuzzle class
			turnAllButtonsOnExceptStop();
			this->gameRunning = false;
			this->calibrating = false;
			this->sessionDataSaved = false;
			this->puzzleComboBox->Text = "KNOBPUZZLE1";			// REMOVE FOR FINAL VERSION
			this->currentPuzzle = gcnew KnobPuzzle();
			this->ScoreKeeper = gcnew ScoreKeeping();

			//see if the results directory for the patient results data exists yet. If not, create it. 
			if (!System::IO::Directory::Exists(Constants::RESULTS_DIRECTORY)) {
				// * I don't know how to error check this yet.
				System::IO::Directory::CreateDirectory(Constants::RESULTS_DIRECTORY);
				Console::WriteLine("MainGuiForm.h::Initialize(): Created results directory " + Constants::RESULTS_DIRECTORY);
			}
			else {
				Console::WriteLine("MainGuiForm.h::Initialize(): Results Directory found: " + Constants::RESULTS_DIRECTORY);
			}
			//******

			// For me, CameraPrefs folder is located 2 folders above the consolepplication4.exe file
//			System::String^ cameraExecutablePath = System::Windows::Forms::Application::StartupPath + "/../../CameraPrefs/CameraPrefs.exe";
			//System::String^ cameraExecutablePath = "C:\\CameraPrefs\\CameraPrefs.exe";
			//MessageBox::Show("Attempting to run : " + cameraExecutablePath);
			//if (System::IO::File::Exists(cameraExecutablePath)) {
			//	MessageBox::Show("Executable file found");
			//	System::Diagnostics::Process^ process = System::Diagnostics::Process::Start(cameraExecutablePath);
			//}
			//else {
			//	MessageBox::Show("Can't find CameraPrefs.exe. Please change my file path in MainGUIForm.h :: MainGUIform(void)");
			//}


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

	// My Variables
	public: bool gameRunning;
	public: bool calibrating;
	public: bool sessionDataSaved;

	private: System::Windows::Forms::Label^  label1;
	private: System::ComponentModel::IContainer^  components;
	private: KnobPuzzle^ currentPuzzle;
	private: ScoreKeeping^ ScoreKeeper;

	// Visual Studio's GUI stuff
	private: System::Windows::Forms::Button^  runGameButton;
	private: System::Windows::Forms::Button^  scoresButton;
	private: System::Windows::Forms::Button^  calibrateButton;

	private: System::Windows::Forms::Button^  stopGameButton;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::HelpProvider^  helpProvider1;
	private: System::Windows::Forms::CheckBox^  level1CheckBox;
	private: System::Windows::Forms::CheckBox^  level2CheckBox;
	private: System::Windows::Forms::CheckBox^  level3CheckBox;
	private: System::Windows::Forms::Button^  levelDescriptionsButton;

	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::ComboBox^  playerNameComboBox;

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::ComboBox^  puzzleComboBox;
	private: System::Windows::Forms::Button^  helpButton;
	private: System::Windows::Forms::Label^  label4;

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->scoresButton = (gcnew System::Windows::Forms::Button());
			this->calibrateButton = (gcnew System::Windows::Forms::Button());
			this->stopGameButton = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->helpProvider1 = (gcnew System::Windows::Forms::HelpProvider());
			this->level1CheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->level2CheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->level3CheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->levelDescriptionsButton = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->playerNameComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->puzzleComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->helpButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// runGameButton
			// 
			this->runGameButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->runGameButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->runGameButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->runGameButton->Location = System::Drawing::Point(597, 278);
			this->runGameButton->Name = L"runGameButton";
			this->runGameButton->Size = System::Drawing::Size(247, 142);
			this->runGameButton->TabIndex = 0;
			this->runGameButton->Text = L"Run Game";
			this->runGameButton->UseVisualStyleBackColor = true;
			this->runGameButton->Click += gcnew System::EventHandler(this, &MainGUIForm::runGameButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(17, 157);
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
			this->scoresButton->Location = System::Drawing::Point(12, 306);
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
			this->calibrateButton->Location = System::Drawing::Point(316, 306);
			this->calibrateButton->Name = L"calibrateButton";
			this->calibrateButton->Size = System::Drawing::Size(256, 114);
			this->calibrateButton->TabIndex = 9;
			this->calibrateButton->Text = L"Calibrate";
			this->calibrateButton->UseVisualStyleBackColor = true;
			this->calibrateButton->Click += gcnew System::EventHandler(this, &MainGUIForm::calibrateButton_Click);
			// 
			// stopGameButton
			// 
			this->stopGameButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->stopGameButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->stopGameButton->Enabled = false;
			this->stopGameButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->stopGameButton->Location = System::Drawing::Point(597, 94);
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
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(168, 162);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(225, 18);
			this->label3->TabIndex = 13;
			this->label3->Text = L"please enter exactly as it appears";

			// 
			// level1CheckBox
			// 
			this->level1CheckBox->AutoSize = true;
			this->level1CheckBox->Checked = true;
			this->level1CheckBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->level1CheckBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->level1CheckBox->Location = System::Drawing::Point(171, 255);
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
			this->level2CheckBox->Location = System::Drawing::Point(260, 257);
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
			this->level3CheckBox->Location = System::Drawing::Point(373, 257);
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
			this->levelDescriptionsButton->Location = System::Drawing::Point(456, 250);
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
			this->label4->Location = System::Drawing::Point(13, 257);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(152, 24);
			this->label4->TabIndex = 18;
			this->label4->Text = L"Level of Difficulty:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(22, 74);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(181, 29);
			this->label5->TabIndex = 20;
			this->label5->Text = L"Who\'s Playing\?:";
			// 
			// playerNameComboBox
			// 
			this->playerNameComboBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->playerNameComboBox->FormattingEnabled = true;
			this->playerNameComboBox->Location = System::Drawing::Point(27, 106);
			this->playerNameComboBox->Name = L"playerNameComboBox";
			this->playerNameComboBox->Size = System::Drawing::Size(357, 32);
			this->playerNameComboBox->TabIndex = 21;
			this->playerNameComboBox->Text = L"<enter name>";
			this->playerNameComboBox->Click += gcnew System::EventHandler(this, &MainGUIForm::playerNameComboBox_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(385, 109);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(174, 32);
			this->label6->TabIndex = 22;
			this->label6->Text = L"* Enter new name or choose\r\n   from dropdown list";
			// 
			// puzzleComboBox
			// 
			this->puzzleComboBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->puzzleComboBox->FormattingEnabled = true;
			this->puzzleComboBox->Location = System::Drawing::Point(32, 193);
			this->puzzleComboBox->Name = L"puzzleComboBox";
			this->puzzleComboBox->Size = System::Drawing::Size(357, 37);
			this->puzzleComboBox->TabIndex = 23;
			this->puzzleComboBox->Text = L"<enter game>";
			this->puzzleComboBox->Click += gcnew System::EventHandler(this, &MainGUIForm::puzzleComboBox_Click);
			// 
			// helpButton
			// 
			this->helpButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->helpButton->Location = System::Drawing::Point(816, 12);
			this->helpButton->Name = L"helpButton";
			this->helpButton->Size = System::Drawing::Size(26, 25);
			this->helpButton->TabIndex = 24;
			this->helpButton->Text = L"\?";
			this->helpButton->UseVisualStyleBackColor = true;
			this->helpButton->Click += gcnew System::EventHandler(this, &MainGUIForm::helpButton_Click);
			// 
			// MainGUIForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Beige;
			this->ClientSize = System::Drawing::Size(854, 432);
			this->Controls->Add(this->helpButton);
			this->Controls->Add(this->puzzleComboBox);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->playerNameComboBox);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->levelDescriptionsButton);
			this->Controls->Add(this->level3CheckBox);
			this->Controls->Add(this->level2CheckBox);
			this->Controls->Add(this->level1CheckBox);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->stopGameButton);
			this->Controls->Add(this->calibrateButton);
			this->Controls->Add(this->scoresButton);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->runGameButton);
			this->Name = L"MainGUIForm";
			this->Text = L"Puzzle Assembly Assistant";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainGUIForm::MainGUIForm_FormClosing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

// User hits 'Run Game'
private: System::Void runGameButton_Click(System::Object^  sender, System::EventArgs^  e) {
	
			 // Lock down thread while loading puzzle, so that only one thread is accessing it (I'm not actually sure this is doing anything)
			 HANDLE myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "runGameButton_Click : loading game");
			 WaitForSingleObject(myMutex, INFINITE);

			 System::String^ userName = playerNameComboBox->Text->ToLower();
			 // if player is not recognized, ask if want to save new player, then do so. 
			 if (!playerNameComboBox->Items->Contains(userName) && !userName->Equals("") && !userName->Equals("<enter name>")) 
			 {
				 System::String^ messageString = "Do you want to save new user " + userName + "?";
				 System::Windows::Forms::DialogResult result = MessageBox::Show(messageString, "Warning", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
				 // if user says yes, save the settings to the hardcoded location (user doesn't select)
				 if(result == System::Windows::Forms::DialogResult::Yes)
				 {
					 // create the results directory
					 System::String^ fileStr = Constants::RESULTS_DIRECTORY + userName;
					 System::IO::Directory::CreateDirectory(fileStr);	
					 Console::WriteLine("MainGuiForm.h::runGameButton_Click(): Created results directory " + fileStr);
					 // refill the player drop down to include the new name
					 playerNameComboBox->Items->Clear();
					 array<System::String^>^ patientNames = findPatientNames();
					 playerNameComboBox->Items->AddRange(patientNames);
				 }
				 // if user says no, then return. 
				 else if (result == System::Windows::Forms::DialogResult::No) {
					 MessageBox::Show("Please select a valid username and try running again.");
					 return;
				 }
			 }
			 // if no player has been entered, return
			 else if (userName->Equals("") || userName->Equals("<enter name>"))  {
				 MessageBox::Show("Please enter a username and try running again!");
				 return;
			 }

			 // load up puzzle if not already loaded (make sure it's the same puzzle that the user has entered in the text box too). 
			 if (!this->currentPuzzle->checkIsInitialized(this->getCodeStringFromGUI())) {
				 Console::WriteLine("MainGUIForm.h : runGameButton_Click() : Loading Puzzle");

				 // load the puzzle from the given code
				 int success = this->loadPuzzleFromCode();

				 // if loading was unsuccessful, alert user and cancel running game
				 if (success == -1) {
					 System::Windows::Forms::MessageBox::Show("Error loading puzzle. \nPlease check code string");
					 Console::WriteLine("MainGUIForm.h : runGameButton_Click() : Error loading puzzle. Please check code string");
 		 			 ReleaseMutex(myMutex);
					 return;
				 }
			 }

			 // reload the level of difficulty in case it's changed
			 this->currentPuzzle->setLevelOfDifficulty(this->getLevelOfDifficulty());
			 if (this->currentPuzzle->getLevelOfDifficulty() == -1) {
					 Console::WriteLine("MainGUIForm.h : runGameButton_Click() : Error loading puzzle. Please check code string");
 		 			 ReleaseMutex(myMutex);
					 return;
			 }
			 // Set global difficulty level
			 Globals::difficultylevel = this->getLevelOfDifficulty();

			 // release lock
		 	 ReleaseMutex(myMutex);

			 // MAY WANT A COMPREHENSIVE ERROR CHECK within KnobPuzzle, for a one line check

			 // Turn on 'Stop' button and turn off the other buttons for while game is running
			 this->gameRunning = true;
			 turnAllButtonsOff();
			 this->stopGameButton->Enabled = true;

			 // now start the game by initializing the tracking. Pass in the puzzle. It will return the game stats for that game
			 GamePlayedData^ gameResults = initializeTracking( this->currentPuzzle, userName);
			 
			 //add new game results to the ScoreKeeper
			 this->ScoreKeeper->AddNewGame(gameResults);

			 // reset the 'endgame' variable in KnobPuzzle (in case it was set by StopButtonClick)
			 this->currentPuzzle->resetEndGame();

			 // Turn off 'Stop' button, and enable all other buttons
			 turnAllButtonsOnExceptStop();

			 this->gameRunning = false;
		 }
//----------------------------------------------------------------------------------------------------------
// User stops game before it ends naturally
private: System::Void stopGameButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 // if game isn't running, then return ( this shouldn't be able to happen)
			 if (!gameRunning) {
				 return;
			 }

			 // tell KnobPuzzle to end; RunTracking will see the change in this variable and end. 
			 this->currentPuzzle->setEndGame();		
			 this->gameRunning = false; // set gameRunning to false (for main gui)
		 }

//----------------------------------------------------------------------------------------------------------
// User clicks the "Performance" button
private: System::Void scoresButton_Click(System::Object^  sender, System::EventArgs^  e) {

			 // set up the form to display the results, and load it with the necessary data
			ConsoleApplication4::displayResultsForm^ displayResults = gcnew ConsoleApplication4::displayResultsForm();
			displayResults->currentPlayer = this->playerNameComboBox->Text->ToLower();
			displayResults->currentGame = this->puzzleComboBox->Text;
			displayResults->recordKeeper = this->ScoreKeeper;
			// show it as a dialog, so that it pulls focus and ends when the user clicks ok or cancel.
			System::Windows::Forms::DialogResult dialogResult = displayResults->ShowDialog(); 

		 }

//----------------------------------------------------------------------------------------------------------
// mini function to disable all buttons on the main GUI
private: System::Void turnAllButtonsOff() {
			 this->runGameButton->Enabled = false;
			 this->calibrateButton->Enabled = false;
			 this->scoresButton->Enabled = false;
			 this->stopGameButton->Enabled = false;
		 }

// mini function to enable all buttons except the stop button (this is used whenever a game is running)
private: System::Void turnAllButtonsOnExceptStop() {
			 this->runGameButton->Enabled = true;
			 this->calibrateButton->Enabled = true;
			 this->scoresButton->Enabled = true;
			 this->stopGameButton->Enabled = false;
		 }
//----------------------------------------------------------------------------------------------------------
// Handle a user clicking the "Calibrate" button
private: System::Void calibrateButton_Click(System::Object^  sender, System::EventArgs^  e) {

			 // Lock down thread for entire calibration process to minimize conflicts. I don't know if this does anything
			 HANDLE myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "calibrateButton_Click : loading and calibrating");
			 WaitForSingleObject(myMutex, INFINITE);

			 // load up puzzle if not already loaded (compare current KnobPuzzle to the combobox input)
			 if (!this->currentPuzzle->checkIsInitialized(this->getCodeStringFromGUI())) {
				 //MessageBox::Show("Loading Puzzle");
				 System::Console::WriteLine("MainGUIForm.h : calibrateButton_Click() : Loading Puzzle");
				 int success = this->loadPuzzleFromCode();
				 if (success == -1) {
					 System::Console::WriteLine("MainGUIForm.h : calibrateButton_Click() : Error loading puzzle. \nPlease check code string");
 		 			 ReleaseMutex(myMutex);
					 return;
				 }
			 }

			 // all buttons off while calibrating
			 turnAllButtonsOff();
			 this->calibrating = true;

			 // create new calibration main form and pass it the puzzle. User will now enter the calibration process
			 ConsoleApplication4::CalibrationMainPrompt^ calibForm = gcnew ConsoleApplication4::CalibrationMainPrompt();
			 calibForm->puzzle = this->currentPuzzle;

			 // show the form and wait until the calibration form has exited. 
			 System::Windows::Forms::DialogResult dialogResult = calibForm->ShowDialog(); 

			 this->calibrating = false;
  		 	 ReleaseMutex(myMutex);

			 // if DialogResult is OK, then calibration has been completed successfully (or should)
			 if (dialogResult == System::Windows::Forms::DialogResult::OK) {
				 MessageBox::Show("You're done with calibration!");
				 delete calibForm;
			 }


			 // if DialogResult was Cancel (user exited prematurely, or there was an error)
			 // then cancel the calibration and reload all of the old calibration data
			 else if (dialogResult == System::Windows::Forms::DialogResult::Cancel) {
				 delete calibForm;
				// reload old data into current puzzle
				 MessageBox::Show("Re-Loading old puzzle data");
				 System::Console::WriteLine("MainGUIForm.h : calibrateButton_Click() : ReLoading old Puzzle data");
				 int success = this->loadPuzzleFromCode();
				 if (success == -1) {
					 System::Console::WriteLine("MainGUIForm.h : calibrateButton_Click() : Error reLoading puzzle. \nPlease check code string");
					 turnAllButtonsOnExceptStop();
					 return;
				 }
				 // no point in continuing to next stage (saving settings) so return
				turnAllButtonsOnExceptStop();
				return;
			 }

			 // color and location info should be embedded now in this->currentPuzzle, which should be passed to tracking initializer

			 // ask user if they want to save settings
			 System::Windows::Forms::DialogResult result = MessageBox::Show("Do you want to save calibration settings for future sessions?", "Warning", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Warning);

			 // if user says yes, save the settings to the hardcoded location (user doesn't select)
			 if(result == System::Windows::Forms::DialogResult::Yes)
			 {
				 Console::WriteLine("Saving Settings");
    			 int success = this->currentPuzzle->SaveCalibrationSettings();
				 if (success != 0) {
					MessageBox::Show("Error: Failed to save settings. Calibrated values will be used for this session only.");
					Console::WriteLine("Mainguiform::CalibrateButton_Click() : Failed to save settings. Calibrated values not saved for future use.");
				 }
			 }

			 // Otherwise, cancel
			 else if(result == System::Windows::Forms::DialogResult::No || result == System::Windows::Forms::DialogResult::Cancel)
			 {
			   Console::WriteLine("Mainguiform::CalibrateButton_Click() : Not saving settings.");
			 }

			 // turn buttons back on
			 turnAllButtonsOnExceptStop();
			 return;
		 }


//----------------------------------------------------------------------------------------------------------
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {

			 // if puzzle code box is blank, de-enable all buttons (because there is obviously no game to play)
			 if (this->puzzleComboBox->Text->Length == 0) {
				 this->calibrateButton->Enabled = false;
				 this->runGameButton->Enabled = false;
			 }

			 // otherwise enable load and run button (assumes a game has been entered)
			 else {
				 this->calibrateButton->Enabled = true;
				 this->runGameButton->Enabled = true;
			 }
		 }


//----------------------------------------------------------------------------------------------------------
// take code from input textbox and load puzzle from it (Should I have this take a string argument?)
private: int loadPuzzleFromCode() {

			 int success = 0;

			 // make sure the user has properly selected a level of difficulty
			 int level = this->getLevelOfDifficulty();
			 if ( level == -1) {
				 MessageBox::Show("Please select a level of difficulty");
				 return -1;
			 }
			 // load level of difficulty to puzzle
			 else { this->currentPuzzle->setLevelOfDifficulty(level); }

			 // pull puzzle name from GUI
			 System::String^ CodeString = this->getCodeStringFromGUI();
			 System::String^ puzzleType = searchPuzzleType(CodeString);
			 //KNOB PUZZLE IS STILL HARDCODED HERE- WILL NEED TO GO THROUGH ALL CODE IF YOU WANT TO ADD NEW GAME TYPES

			 // load up puzzle class. If unsuccessful, will return -1
			 if (puzzleType->Equals("KnobPuzzle")) {   
				 // reset the knob puzzle just to be sure everything is cleared correctly
				 this->currentPuzzle = gcnew KnobPuzzle();
				 success = this->currentPuzzle->setGame(CodeString); // this function will load up all puzzle data
			 }

			 // check if loading was successful
			 if (success != 0) {
				 //MessageBox::Show("MainGUIForm.h : loadPuzzleFromCode(): error loading knob puzzle from code");
				 System::Console::WriteLine("MainGUIForm.h : loadPuzzleFromCode(): error loading knob puzzle from code");
				 return success;
			 }

			 return success;
}


//----------------------------------------------------------------------------------------------------------
// Handle the form closing via X button
private: System::Void MainGUIForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {

			 // if game is running, need to end the game before we can quit
			 if (this->gameRunning) {
				 this->currentPuzzle->setEndGame();		
			 }
			 // if currently calibrating, just don't let the form close. User must close out of calibration first.
			 if (this->calibrating) {
				 Console::WriteLine("MainGUIForm.h: MainGUIForm_FormClosing(): attempted to exit main gui during calibration. Cancelled exit.");
				 e->Cancel = true;
			 } 
}

//----------------------------------------------------------------------------------------------------------
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

// display a little messagebox describing the difference between the levels of difficulty
private: System::Void levelDescriptionsButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 System::String^ tmp = "Levels of Difficulty: \n\nEasy: Flash piece being moved, dim all other pieces, then turn off all other pieces\
								   \nMedium: Flash piece being moved, dim all other pieces \n\nHard: Only flashes piece being moved";
			 MessageBox::Show(tmp);
		 }

//----------------------------------------------------------------------------------------------------------
// mini function that pulls the game code from the GUI (isolated in case text input method changes
private: System::String^ getCodeStringFromGUI() {
			 System::String^ resultString = this->puzzleComboBox->Text;
			 return resultString;
		 }

//----------------------------------------------------------------------------------------------------------
// mini function that pulls the level of difficulty from the GUI
private: int getLevelOfDifficulty() {
			int level = -1; // boxes aren't properly checked, will return error (-1)
			if (level1CheckBox->Checked == true) { return 1; }
			else if (level2CheckBox->Checked == true) { return 2; }
			else if (level3CheckBox->Checked == true) { return 3; }
			return level;
		 }

//----------------------------------------------------------------------------------------------------------
// handle user clicking on the username text box. Generates drop down menu options
private: System::Void playerNameComboBox_Click(System::Object^  sender, System::EventArgs^  e) {

			 // This will be called the first time the box is clicked (when the initial prompt <enter name> is still displayed)
			 if (playerNameComboBox->Text->Equals("<enter name>")) {

				 // get rid of <enter name> prompt
				 playerNameComboBox->Text = "";
			 }
			 playerNameComboBox->Items->Clear();
			 // find add list of kids that currently have records to drop down list. Each kid should have their own folder in the patient results mother-folder
			 array<System::String^>^ patientNames = findPatientNames();
			 playerNameComboBox->Items->AddRange(patientNames);
		 }

//=---------------------------------------------------------------------------------------------------------
private: array<System::String^>^ findPatientNames() {
			 // find add list of kids that currently have records to drop down list. Each kid should have their own folder in the patient results mother-folder
			 array<System::String^>^ patientNames = System::IO::Directory::GetDirectories( Constants::RESULTS_DIRECTORY );
			 for (int i = 0; i < patientNames->Length; i++) {
				patientNames[i] = System::IO::Path::GetFileNameWithoutExtension(patientNames[i]);
			 }
			 return patientNames;
		}
//----------------------------------------------------------------------------------------------------------
// handle user clicking on the game text box. Generates drop down menu options
private: System::Void puzzleComboBox_Click(System::Object^  sender, System::EventArgs^  e) {

			 // This will be called the first time the box is clicked (when the initial prompt <enter name> is still displayed)
			 if (puzzleComboBox->Text->Equals("<enter game>") || puzzleComboBox->Text->Equals("KNOBPUZZLE1")) { //CHANGEME

				 // get rid of <enter name> prompt
				 puzzleComboBox->Text = "";

				 // clear out current drop down items
				 puzzleComboBox->Items->Clear();

				 // find all files that contain the word "KNOBPUZZLE"
				 array<System::String^>^ fileNames = System::IO::Directory::GetFiles( Constants::GAME_INPUT_DIRECTORY );
				 List<System::String^>^ matches = gcnew List<System::String^>();
				 for (int i = 0; i < fileNames->Length; i++) {
					 System::String^ tmp = System::IO::Path::GetFileNameWithoutExtension(fileNames[i]);
					 // find knobpuzzle files, and pull the name from them
					 if (tmp->Contains("KNOBPUZZLE")) {   /// CHANGE THIS ONCE I CREATE A FOLDER FOR GAME INPUTS
						System::String^ delimStr = "_";
						array<Char>^ delimiter = delimStr->ToCharArray();
					    array<System::String^>^ tokens = tmp->Split(delimiter);
						tmp = tokens[0];
						if (!matches->Contains(tmp)) {
							matches->Add(tmp);
						}
					 }
				 }
				 // Now need to convert list back to an array
				 array<System::String^>^ result = gcnew array<System::String^>(matches->Count);
				 for (int i = 0; i < matches->Count; i++) {
					 result[i] = matches[i];
				 }

				 // add puzzles to drop down list
				 puzzleComboBox->Items->AddRange(result);
			 }
		 }

//----------------------------------------------------------------------------------------------------------
// handle user clicking the help button
private: System::Void helpButton_Click(System::Object^  sender, System::EventArgs^  e) {
			
			 System::String^ fileName = Constants::HELP_FILE;

			 // make sure help file exists and has content
			 checkOrCreateFile(fileName); 
			 array<System::String^>^ fileStrings = getStringArrayFromFile(fileName);
			 if (fileStrings->Length == 0) {
				 MessageBox::Show("Error: can't find help information :(");
				 return;
			 }
			 if (fileStrings[0]->Equals("Error")) {
				 MessageBox::Show("Error: can't find help information :(");
				 return;
			 }

			 // now open up the help file in notepad
			System::Diagnostics::Process::Start("notepad.exe", fileName);

		 }

};
}
