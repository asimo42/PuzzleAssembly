/*
	This form displays results either from the current session (default) or from loaded data. 
	Loaded data is pulled in via a selectOldResultsForm.
*/

#include "selectOldResultsForm.h"
#include "Functions.h"
#pragma once

namespace ConsoleApplication4 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for displayResultsForm
	/// </summary>
	public ref class displayResultsForm : public System::Windows::Forms::Form
	{
	public:
		displayResultsForm(void)
		{
			InitializeComponent();
			this->currentGame = "Unknown";
			this->currentPlayer = "Unknown";
			this->filesToBeDisplayed = gcnew List<System::String^>();
			this->recordKeeper = gcnew ScoreKeeping();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~displayResultsForm()
		{
			if (components)
			{
				delete components;
			}
		}

	public: System::String^ currentPlayer;
	public: System::String^ currentGame;
	public: ScoreKeeping^ recordKeeper;
	private: List<System::String^>^ filesToBeDisplayed;

	private: System::Windows::Forms::Button^  displayOldDataButton;
	private: System::Windows::Forms::Button^  doneButton;
	private: System::Windows::Forms::Label^  todaysSessionLabel;
	private: System::Windows::Forms::Label^  numGamesPlayedLabel;

	private: System::Data::DataSet^  myDataSet;
	private: System::Windows::Forms::TextBox^  mainTextBox;


	public: 

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
			this->displayOldDataButton = (gcnew System::Windows::Forms::Button());
			this->doneButton = (gcnew System::Windows::Forms::Button());
			this->todaysSessionLabel = (gcnew System::Windows::Forms::Label());
			this->numGamesPlayedLabel = (gcnew System::Windows::Forms::Label());
			this->myDataSet = (gcnew System::Data::DataSet());
			this->mainTextBox = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->myDataSet))->BeginInit();
			this->SuspendLayout();
			// 
			// displayOldDataButton
			// 
			this->displayOldDataButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->displayOldDataButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->displayOldDataButton->Location = System::Drawing::Point(1, 466);
			this->displayOldDataButton->Name = L"displayOldDataButton";
			this->displayOldDataButton->Size = System::Drawing::Size(231, 43);
			this->displayOldDataButton->TabIndex = 0;
			this->displayOldDataButton->Text = L"Look at old data";
			this->displayOldDataButton->UseVisualStyleBackColor = true;
			this->displayOldDataButton->Click += gcnew System::EventHandler(this, &displayResultsForm::displayOldDataButton_Click);
			// 
			// doneButton
			// 
			this->doneButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->doneButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->doneButton->Location = System::Drawing::Point(329, 466);
			this->doneButton->Name = L"doneButton";
			this->doneButton->Size = System::Drawing::Size(223, 43);
			this->doneButton->TabIndex = 1;
			this->doneButton->Text = L"Done";
			this->doneButton->UseVisualStyleBackColor = true;
			this->doneButton->Click += gcnew System::EventHandler(this, &displayResultsForm::doneButton_Click);
			// 
			// todaysSessionLabel
			// 
			this->todaysSessionLabel->AutoSize = true;
			this->todaysSessionLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->todaysSessionLabel->Location = System::Drawing::Point(13, 13);
			this->todaysSessionLabel->Name = L"todaysSessionLabel";
			this->todaysSessionLabel->Size = System::Drawing::Size(272, 25);
			this->todaysSessionLabel->TabIndex = 2;
			this->todaysSessionLabel->Text = L"Results of Today\'s Session";
			// 
			// numGamesPlayedLabel
			// 
			this->numGamesPlayedLabel->AutoSize = true;
			this->numGamesPlayedLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->numGamesPlayedLabel->Location = System::Drawing::Point(18, 42);
			this->numGamesPlayedLabel->Name = L"numGamesPlayedLabel";
			this->numGamesPlayedLabel->Size = System::Drawing::Size(173, 24);
			this->numGamesPlayedLabel->TabIndex = 3;
			this->numGamesPlayedLabel->Text = L"# of games played: ";
			// 
			// myDataSet
			// 
			this->myDataSet->DataSetName = L"NewDataSet";
			// 
			// mainTextBox
			// 
			this->mainTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->mainTextBox->Location = System::Drawing::Point(1, 69);
			this->mainTextBox->Multiline = true;
			this->mainTextBox->Name = L"mainTextBox";
			this->mainTextBox->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->mainTextBox->Size = System::Drawing::Size(551, 391);
			this->mainTextBox->TabIndex = 4;
			// 
			// displayResultsForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(552, 509);
			this->Controls->Add(this->mainTextBox);
			this->Controls->Add(this->numGamesPlayedLabel);
			this->Controls->Add(this->todaysSessionLabel);
			this->Controls->Add(this->doneButton);
			this->Controls->Add(this->displayOldDataButton);
			this->Name = L"displayResultsForm";
			this->Text = L"Performance";
			this->Load += gcnew System::EventHandler(this, &displayResultsForm::displayResultsForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->myDataSet))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// handle user clicking "look at old data"
	private: System::Void displayOldDataButton_Click(System::Object^  sender, System::EventArgs^  e) {

				 // create form to select old records
				 selectOldResultsForm^ oldResultsForm = gcnew selectOldResultsForm();
				 // load form with current player and game and launch
				 oldResultsForm->initialGame = this->currentGame;
				 oldResultsForm->initialPlayer = this->currentPlayer;
			     System::Windows::Forms::DialogResult dialogResult = oldResultsForm->ShowDialog(); 

				 System::String^ selectedUser = "";
				 System::String^ selectedGame = "";
				 array<System::String^>^ selectedDates = gcnew array<System::String^>(0);

				 // if the user selected OK on the form, then pull the selected player name, game, and dates
				 if (dialogResult == System::Windows::Forms::DialogResult::OK) {
					 selectedUser = oldResultsForm->selectedPlayer;
					 selectedGame = oldResultsForm->selectedGame;
					 selectedDates = oldResultsForm->selectedDates;
					 // if no dates were chosen, return
					 if (selectedDates->Length == 0) {
						 Console::WriteLine("displayResultsForm::displayOldDataButton_Click(): no dates were chosen");
						 return;
					 }
					 this->currentGame = selectedGame;
					 this->currentPlayer = selectedUser;
				 }
				 // if user hit cancel or there was an error, go ahead and return
				 else if (dialogResult != System::Windows::Forms::DialogResult::OK) {
					Console::WriteLine("displayResultsForm::displayOldDataButton_Click(): user cancelled");
					 return;
				 }
				 // find all of the files we need to pull based on selected user, game, and dates
				 List<System::String^>^ filesNeeded = findRecordFiles(selectedUser, selectedGame, selectedDates);

				 displayFiles(filesNeeded);
			 }

	// if the user has selected old files, display their contents in the text box
private: void displayFiles(List<System::String^>^ files) {
  				  System::String^ resultString = "";

				  // pull the contents of each file
				  for each(System::String^ file in files) {
					  array<System::String^>^ contents = getStringArrayFromFile(file);
					  if (contents[0]->Equals("ERROR")) {
						  continue;
					  }
					  for each (System::String^ line in contents) {
						  resultString = resultString + line + Environment::NewLine;
					  }
				  }
				  // display the loaded data
				  mainTextBox->Text = resultString;
				  todaysSessionLabel->Text = "Showing results for " + currentPlayer;
				  numGamesPlayedLabel->Text = currentGame;

			 }

			 // when the form loads up for the first time, build score display
	private: System::Void displayResultsForm_Load(System::Object^  sender, System::EventArgs^  e) {

				 int numberOfGames = 0;

				 // Pull result string from each game played this session
				 System::String^ displayString = "";
				 for (int i = this->recordKeeper->individualGamesList->Count -1; i >= 0; i--)   {
					 GamePlayedData^ game = this->recordKeeper->individualGamesList[i]; 
					 System::String^ tmpString = game->writeOut();
					 if (!tmpString->Contains("Error")) {
						 displayString = displayString + tmpString + Environment::NewLine;
						 numberOfGames++; // keep track of number of games completed
					 }
				 }
				 numGamesPlayedLabel->Text = "# of Games Played: " + numberOfGames;
				 mainTextBox->Text = displayString;
			 }

// if user clicks 'Done', leave form
private: System::Void doneButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->DialogResult = System::Windows::Forms::DialogResult::OK;
		 }
};
}
