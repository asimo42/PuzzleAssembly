/*
	This form allows the user to select old data for display. It finds what dates are available for data based on the entered 
	username and game, and the expected location of the data. The form will return the selected player, game, and dates (not the data). 
*/

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
	/// Summary for selectOldResultsForm
	/// </summary>
	public ref class selectOldResultsForm : public System::Windows::Forms::Form
	{
	public:
		selectOldResultsForm(void)
		{
			InitializeComponent();
			this->initialGame = "ex. KNOBPUZZLE1";
			this->initialPlayer = "ex. Caleb";
			this->selectedDates = gcnew array<System::String^>(0);
			this->selectedGame = "";
			this->selectedPlayer = "";
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~selectOldResultsForm()
		{
			if (components)
			{
				delete components;
			}
		}

	public: System::String^ initialPlayer;
	public: System::String^ initialGame;
	public: System::String^ selectedPlayer;
	public: System::String^ selectedGame;

	private: array<System::String^>^ availablePlayers;
	public: array<System::String^>^ selectedDates;

	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::ComboBox^  playerComboBox;
	private: System::Windows::Forms::ComboBox^  gameComboBox;
	private: System::Windows::Forms::ListBox^  dateListBox;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  okButton;
	private: System::Windows::Forms::Button^  cancelButton;


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
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->playerComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->gameComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->dateListBox = (gcnew System::Windows::Forms::ListBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->okButton = (gcnew System::Windows::Forms::Button());
			this->cancelButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(27, 77);
			this->label1->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(87, 29);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Player:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(27, 160);
			this->label2->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(84, 29);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Game:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(355, 87);
			this->label3->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(97, 29);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Date(s):";
			// 
			// playerComboBox
			// 
			this->playerComboBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->playerComboBox->FormattingEnabled = true;
			this->playerComboBox->Location = System::Drawing::Point(32, 122);
			this->playerComboBox->Margin = System::Windows::Forms::Padding(6);
			this->playerComboBox->Name = L"playerComboBox";
			this->playerComboBox->Size = System::Drawing::Size(294, 32);
			this->playerComboBox->TabIndex = 3;

			this->playerComboBox->TextChanged += gcnew System::EventHandler(this, &selectOldResultsForm::playerComboBox_TextChanged);
			this->playerComboBox->Click += gcnew System::EventHandler(this, &selectOldResultsForm::playerComboBox_Click);
			// 
			// gameComboBox
			// 
			this->gameComboBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->gameComboBox->FormattingEnabled = true;
			this->gameComboBox->Location = System::Drawing::Point(32, 202);
			this->gameComboBox->Margin = System::Windows::Forms::Padding(6);
			this->gameComboBox->Name = L"gameComboBox";
			this->gameComboBox->Size = System::Drawing::Size(291, 32);
			this->gameComboBox->TabIndex = 4;
			this->gameComboBox->DropDown += gcnew System::EventHandler(this, &selectOldResultsForm::gameComboBox_DropDown);
			this->gameComboBox->TextChanged += gcnew System::EventHandler(this, &selectOldResultsForm::gameComboBox_TextChanged);
			this->gameComboBox->Click += gcnew System::EventHandler(this, &selectOldResultsForm::gameComboBox_Click);
			// 
			// dateListBox
			// 
			this->dateListBox->FormattingEnabled = true;
			this->dateListBox->ItemHeight = 24;
			this->dateListBox->Location = System::Drawing::Point(461, 87);
			this->dateListBox->Name = L"dateListBox";
			this->dateListBox->SelectionMode = System::Windows::Forms::SelectionMode::MultiExtended;
			this->dateListBox->Size = System::Drawing::Size(309, 148);
			this->dateListBox->TabIndex = 6;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(28, 13);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(560, 24);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Please select a player and game. Available dates will be provided.";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(32, 41);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(360, 18);
			this->label5->TabIndex = 8;
			this->label5->Text = L"*Mutiple dates may be selected by holding Shift or Ctrl";
			// 
			// okButton
			// 
			this->okButton->Location = System::Drawing::Point(261, 267);
			this->okButton->Name = L"okButton";
			this->okButton->Size = System::Drawing::Size(115, 41);
			this->okButton->TabIndex = 9;
			this->okButton->Text = L"OK";
			this->okButton->UseVisualStyleBackColor = true;
			this->okButton->Click += gcnew System::EventHandler(this, &selectOldResultsForm::okButton_Click);
			// 
			// cancelButton
			// 
			this->cancelButton->Location = System::Drawing::Point(382, 267);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(111, 41);
			this->cancelButton->TabIndex = 10;
			this->cancelButton->Text = L"Cancel";
			this->cancelButton->UseVisualStyleBackColor = true;
			this->cancelButton->Click += gcnew System::EventHandler(this, &selectOldResultsForm::cancelButton_Click);
			// 
			// selectOldResultsForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(807, 320);
			this->Controls->Add(this->cancelButton);
			this->Controls->Add(this->okButton);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->dateListBox);
			this->Controls->Add(this->gameComboBox);
			this->Controls->Add(this->playerComboBox);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Margin = System::Windows::Forms::Padding(6);
			this->Name = L"selectOldResultsForm";
			this->Text = L"Load Records";
			this->Load += gcnew System::EventHandler(this, &selectOldResultsForm::selectOldResultsForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// this will run the first time the form opens up; when the parent code calls ShowDialog()
	private: System::Void selectOldResultsForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 // current player and current game should have been passed into this form; autopopulate the relevent textboxes with them
				 this->playerComboBox->Text = this->initialPlayer;
				 this->gameComboBox->Text = this->initialGame;

				 // find all of the available patients and save them for the drop down menu
				 array<System::String^>^ patientNames = System::IO::Directory::GetDirectories( Constants::RESULTS_DIRECTORY );
				 for (int i = 0; i < patientNames->Length; i++) {
					 patientNames[i] = System::IO::Path::GetFileNameWithoutExtension(patientNames[i]);
				 }
				 this->availablePlayers = patientNames;
				 playerComboBox->Items->AddRange(availablePlayers);

				 // find possible dates for the current user and game
				 findDatesFromUserAndGame();

			 }

private: System::Void playerComboBox_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void gameComboBox_Click(System::Object^  sender, System::EventArgs^  e) {
		 }

// if user clicks, okay, pull selected data from boxes and return dialogresult::Ok
private: System::Void okButton_Click(System::Object^  sender, System::EventArgs^  e) {

			 // if a date hasn't been selected, alert user and return
			 if (this->dateListBox->SelectedItems->Count == 0) {
				 System::Windows::Forms::MessageBox::Show("Please select Date(s)");
				 return;
			 }

			 // pull player name, game, and dates from text boxes and store as public variables
			 selectedPlayer = this->playerComboBox->Text;
			 selectedGame = this->gameComboBox->Text;
			 // need to convert datelistbox type to Strings
			 System::Windows::Forms::ListBox::SelectedObjectCollection^ collection = this->dateListBox->SelectedItems;
			 selectedDates = gcnew array<System::String^>(collection->Count);
			 for (int i = 0; i < collection->Count; i++) {
				 System::String^ txt = dateListBox->GetItemText(collection[i]);
				 selectedDates[i] = txt;
			 }

			 // return dialogresult OK. Form should now close.
			 this->DialogResult = System::Windows::Forms::DialogResult::OK;
		 }

// if user clicks cancel, return dialogresult::Cancel, which will close the form
private: System::Void cancelButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		 }

		 // find all files for the selected user, return their paths as strings
private: array<System::String^>^ findFileNamesFromUser() {

			 System::String^ player = playerComboBox->Text;
			 System::String^ filePath = Constants::RESULTS_DIRECTORY + player;
			 
			 // find all files in selected user's folder, if the folder exists
			 array<System::String^>^ fileNames = gcnew array<System::String^>(0);
			 if (System::IO::Directory::Exists(filePath)) {
				fileNames = System::IO::Directory::GetFiles( filePath );
			 }
			 else if (!System::IO::Directory::Exists(filePath)) {
				 return fileNames; 
			 }
			 // cut the paths and extensions off 
			 for (int i = 0; i < fileNames->Length; i++) {
			 		 fileNames[i] = System::IO::Path::GetFileNameWithoutExtension(fileNames[i]);
			 }
			 return fileNames;
		 }

private: System::Void findDatesFromUserAndGame() {

			 // clear out all old dates in box
			 dateListBox->Items->Clear();

			 System::String^ player = playerComboBox->Text;
			 System::String^ game = gameComboBox->Text;

			// find all file names for user
			array<System::String^>^ fileNames = findFileNamesFromUser();
			if (fileNames->Length == 0 ) { return; }

			System::String^ delimStr = "_";
			array<Char>^ delimiter = delimStr->ToCharArray( );

			 // Parse each file name for game and date
			 for each (System::String^ file in fileNames) {
				 array<System::String^>^ tokens = file->Split(delimiter);
				 System::String^ gameToken = tokens[1];

				 // if the game doesn't match, move on
				 if (!gameToken->Equals(game)) { continue; }
				 System::String^ dateStr = tokens[3] + " " + tokens[4] + " " + tokens[2];
				 dateListBox->Items->Add(dateStr);
			 }
		 }

		 // if user uses the dropdown for the games, find the games for the given user and add to dropdown
private: System::Void gameComboBox_DropDown(System::Object^  sender, System::EventArgs^  e) {

			 // clear contents of drop down
			 gameComboBox->Items->Clear();

			array<System::String^>^ fileNames = findFileNamesFromUser();

			System::String^ delimStr = "_";
			array<Char>^ delimiter = delimStr->ToCharArray( );

			// now parse each one for game and date
			 for each (System::String^ file in fileNames) {
				 array<System::String^>^ tokens = file->Split(delimiter);
				 System::String^ game = tokens[1];
				 // now add game to drop down menu if it's not already there
				 if (!gameComboBox->Items->Contains(game)) {
					 gameComboBox->Items->Add(game);
				 }
			 }
		 }

// if user changes text in player box, recalculate possible games and dates
private: System::Void playerComboBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 // if player changed, reset dates to empty
			 dateListBox->Items->Clear();

			 // then refill dates if the game is present
			 findDatesFromUserAndGame();
		 }

// if user changes text in game box, recalculate possible games and dates
private: System::Void gameComboBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 // if game changed, reset dates to empty
			 dateListBox->Items->Clear();

			 // then refill dates if the player is present
			 findDatesFromUserAndGame();
		 }
};
}
