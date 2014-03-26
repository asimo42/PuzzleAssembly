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
			this->initialGame = "Unknown";
			this->initialPlayer = "Unknown";
			this->filesToBeDisplayed = gcnew List<System::String^>();
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

	public: System::String^ initialPlayer;
	public: System::String^ initialGame;
	private: List<System::String^>^ filesToBeDisplayed;
	private: System::Windows::Forms::Button^  displayOldDataButton;
	private: System::Windows::Forms::Button^  doneButton;
	private: System::Windows::Forms::Label^  todaysSessionLabel;
	private: System::Windows::Forms::Label^  numGamesPlayedLabel;
	private: System::Windows::Forms::DataGridView^  dataGridView;
	private: System::Data::DataSet^  myDataSet;

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
			this->dataGridView = (gcnew System::Windows::Forms::DataGridView());
			this->myDataSet = (gcnew System::Data::DataSet());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView))->BeginInit();
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
			this->doneButton->Location = System::Drawing::Point(399, 466);
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
			// dataGridView
			// 
			this->dataGridView->AllowUserToAddRows = false;
			this->dataGridView->AllowUserToDeleteRows = false;
			this->dataGridView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView->Location = System::Drawing::Point(1, 70);
			this->dataGridView->Name = L"dataGridView";
			this->dataGridView->ReadOnly = true;
			this->dataGridView->Size = System::Drawing::Size(621, 398);
			this->dataGridView->TabIndex = 4;
			// 
			// myDataSet
			// 
			this->myDataSet->DataSetName = L"NewDataSet";
			// 
			// displayResultsForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(622, 509);
			this->Controls->Add(this->dataGridView);
			this->Controls->Add(this->numGamesPlayedLabel);
			this->Controls->Add(this->todaysSessionLabel);
			this->Controls->Add(this->doneButton);
			this->Controls->Add(this->displayOldDataButton);
			this->Name = L"displayResultsForm";
			this->Text = L"Performance";
			this->Load += gcnew System::EventHandler(this, &displayResultsForm::displayResultsForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->myDataSet))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void displayOldDataButton_Click(System::Object^  sender, System::EventArgs^  e) {

				 // create form to select old records
				 selectOldResultsForm^ oldResultsForm = gcnew selectOldResultsForm();
				 // load form with current player and game and launch
				 oldResultsForm->initialGame = this->initialGame;
				 oldResultsForm->initialPlayer = this->initialPlayer;
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
					 MessageBox::Show("Results: User : " + selectedUser + ",  Game: " + selectedGame + ",  dates: " + selectedDates[0]);
				 }
				 // if user hit cancel or there was an error, go ahead and return
				 else if (dialogResult != System::Windows::Forms::DialogResult::OK) {
					 return;
				 }

				 // find all of the files we need to pull based on selected user, game, and dates
				 List<System::String^>^ filesNeeded = findRecordFiles(selectedUser, selectedGame, selectedDates);
				 this->filesToBeDisplayed = filesNeeded;

			 }

			 // when the form loads up, build score display
	private: System::Void displayResultsForm_Load(System::Object^  sender, System::EventArgs^  e) {
				//SetupLayout();
				SetupDataGridView();
				PopulateDataGridView();
			 }

//void MakeNodeTable()	
//	{
//		System::Data::DataTable^ myDataTable = gcnew DataTable("PerformanceData");
//		DataColumn^ myDataColumn;
//		DataRow^ myDataRow;
// 
//		// Create new DataColumns, set DataTypes, ColumnNames and add to DataTable.    
//		myDataColumn = gcnew DataColumn();
//		myDataColumn->DataType = System::Type::GetType("System.String");
//		myDataColumn->ColumnName = "Node";
//		// Add the Column to the DataColumnCollection.
//		myDataTable->Columns->Add(myDataColumn);
// 
//		myDataColumn = gcnew DataColumn();
//		myDataColumn->DataType = System::Type::GetType("System.String");
//		myDataColumn->ColumnName = "X";
//		myDataColumn->AutoIncrement = false;
//		myDataColumn->Caption = "X";
//		myDataColumn->ReadOnly = false;
//		myDataTable->Columns->Add(myDataColumn);
//
//		myDataColumn = gcnew DataColumn();
//		myDataColumn->DataType = System::Type::GetType("System.String");
//		myDataColumn->ColumnName = "Y";
//		myDataColumn->Caption = "Y";
//		myDataColumn->ReadOnly = false;
//		myDataTable->Columns->Add(myDataColumn);
//
//		myDataColumn = gcnew DataColumn();
//		myDataColumn->DataType = System::Type::GetType("System.String");
//		myDataColumn->ColumnName = "Z";
//		myDataColumn->AutoIncrement = false;
//		myDataColumn->Caption = "Z";
//		myDataColumn->ReadOnly = false;
//		myDataColumn->Unique = false;
//		myDataTable->Columns->Add(myDataColumn);
//
//		myDataSet = gcnew DataSet();
//		// Add the new DataTable to the DataSet.
//		myDataSet->Tables->Add(myDataTable);
// 
//		//int numbernodes = Vars.GetNumNodes();
//		//// load data to datatable
//		//for (int i = 0; i< numbernodes; i++){
//		//   myDataRow = myDataTable->NewRow();
//		//   int node = Vars.GetNodeFromNodeArray(i); 
//		//   myDataRow["Node"] = node;
//		//   myDataRow["X"] = Vars.GetXFromNode(node);
//		//   myDataRow["Y"] = Vars.GetYFromNode(node);
//		//   myDataRow["Z"] = Vars.GetZFromNode(node); 
//		//   myDataTable->Rows->Add(myDataRow);
//		//}
//		dataGridView->DataSource = myDataSet; // dataset
//		dataGridView->DataMember = "PerformanceTable"; // table name you need to show
//	}


private: void SetupDataGridView()
    {
        this->Controls->Add(dataGridView);

        dataGridView->ColumnCount = 3;

        dataGridView->ColumnHeadersDefaultCellStyle->BackColor = System::Drawing::Color::Navy;
        dataGridView->ColumnHeadersDefaultCellStyle->ForeColor = System::Drawing::Color::White;
        dataGridView->ColumnHeadersDefaultCellStyle->Font =
            gcnew System::Drawing::Font(dataGridView->Font, System::Drawing::FontStyle::Bold);

        dataGridView->Name = "dataGridView";
        dataGridView->AutoSizeRowsMode =
            DataGridViewAutoSizeRowsMode::DisplayedCellsExceptHeaders;
        dataGridView->ColumnHeadersBorderStyle =
            DataGridViewHeaderBorderStyle::Single;
        dataGridView->CellBorderStyle = DataGridViewCellBorderStyle::Single;
        dataGridView->GridColor = Color::Navy;
        dataGridView->RowHeadersVisible = false;
		dataGridView->ColumnHeadersVisible = false;

        dataGridView->Columns[0]->Name = "Piece";
        dataGridView->Columns[1]->Name = "Placed in _ seconds";
        dataGridView->Columns[2]->Name = "Placed _ seconds into game";

		dataGridView->Columns[0]->Width = 0.3333*dataGridView->Width;
		dataGridView->Columns[1]->Width = 0.3333*dataGridView->Width;
		dataGridView->Columns[2]->Width = 0.3333*dataGridView->Width;

        //dataGridView->Columns[4]->DefaultCellStyle->Font =
        //    gcnew System::Drawing::Font(dataGridView->DefaultCellStyle->Font, FontStyle::Italic);

        dataGridView->SelectionMode =
            DataGridViewSelectionMode::FullRowSelect;
        dataGridView->MultiSelect = false;

    }



private: void PopulateDataGridView()
    {
		//for each (System::String^ file in fileList) {

		// find string contents of file
		// deconstruct string contents to rebuild gamePlayed^ instance (basically reverse the printout)
		// construct row strings from gamePlayed^ instance

	//resultString = "Game : " + this->gameName + "\r\n";
	//System::String^ tim = this->timeStarted.ToString("MMMM dd yyyy HH:mm");
	//resultString = resultString + "Time Started : " + tim + "\r\n";
	//resultString = resultString + "Time for Completion (s): " + this->timeForCompletion + "\r\n";
	//resultString = resultString + "Average Time Between Pieces: " + this->avgTimeBetweenPieces + "\r\n\n";
	//for (int i = 0; i < this->orderOfPiecesPlayed->Count; i++) 
	//{ 
	//	System::String^ val1 = "Piece : " + this->orderOfPiecesPlayed[i] + "\r\n";
	//	System::String^ val2 = "         Time of Placement (s) :    " + this->timesOfPlacement[i] + "\r\n";
	//	System::String^ val3 = "         Time it Took to Place (s) : " + this->timeBetweenPlacements[i] + "\r\n";
	//	resultString = resultString + System::String::Format("{0}{1}{2}", val1, val2, val3);
	//	//resultString = resultString + "Piece : " + this->orderOfPiecesPlayed[i] + 
	//	//	"       Time of Placement (s) : " + this->timesOfPlacement[i] + "\n       Time it Took to Place (s) : " + this->timeBetweenPlacements[i] + "\n";
	//}

		// can pull kid name from file

		// pull all strings from input file
		System::String^ inputFile = "C:/";
		if (!System::IO::File::Exists(inputFile)) {
			// if can't find calibrated file, then use default file instead
			Console::WriteLine("displayResultsForm.h::PopulateDataGridView(): - Could not find data file" + inputFile);
			return;
		}

		// pull all strings from file
		array<System::String^>^ stringArray = getStringArrayFromFile(inputFile);
		if (stringArray == nullptr || stringArray[0]->Equals("ERROR")) {
			MessageBox::Show("displayResultsForm.h::PopulateDataGridView(): -Could not pull strings from data file " + inputFile);
			return;
		}

		System::String^ line = stringArray[0];
		System::String^ gameName = "";
		System::String^ playerName = "";
		System::String^ timeForCompletion;
		System::String^ averageTimeForPieces;
		System::String^ month;
		System::String^ year;
		System::String^ day;
		System::String^ tim;
		List<System::String^>^ pieceNames = gcnew List<System::String^>();
		List<System::String^>^ timesToPlace = gcnew List<System::String^>();
		List<System::String^>^ timesOfPlacement = gcnew List<System::String^>();

		int index = 0;
		while(!line->Contains("----") && index < stringArray->Length) {
			line = stringArray[index++]; 
			Console::WriteLine(line);
			if (line->Contains("Game:")) {
				array<System::String^>^ tokens = line->Split();
				gameName = tokens[-1];
			}
			if (line->Contains("Player:") ) {
				array<System::String^>^ tokens = line->Split();
				playerName = tokens[-1];
			}
			if (line->Contains("Time for Completion (s):")) {
				array<System::String^>^ tokens = line->Split();
				timeForCompletion = tokens[-1];
			}
			if (line->Contains("Average Time")) {
				array<System::String^>^ tokens = line->Split();
				averageTimeForPieces = tokens[-1];
			}
			if (line->Contains("Time Started:")) {
				array<System::String^>^ tokens = line->Split();
				tim = tokens[-1];
				year = tokens[-2];
				day = tokens[-3];
				month = tokens[-4];
			}
			if (line->Contains("Piece")) {
				// pull piece name
				array<System::String^>^ tokens = line->Split();
				pieceNames->Add(tokens[-1]);
				// move ot next line and pull time of placement
				line = stringArray[index++]; 
				tokens = line->Split();
				timesOfPlacement->Add(tokens[-1]);
				// move to next line and pull time to place
				line = stringArray[index++]; 
				tokens = line->Split();
				timesToPlace->Add(tokens[-1]);
			}
		}



        array<System::String^>^ row0 = { "Time Started : ", "Day Month Year HH:MM am/pm", ""};
        array<System::String^>^ row1 = { "Player : ", "Gretel", ""};
        array<System::String^>^ row2 = { "Game : ", "KNOBPUZZLE", ""};
        array<System::String^>^ row3 = { "Time Taken : ", "None yet", ""};
        array<System::String^>^ row4 = { "Piece : ", "Placed in _ seconds", "Placed _ seconds into game" };
        array<System::String^>^ row5 = { "Triangle", "9", "85"};
        array<System::String^>^ row6 = { "Pentagon", "13", "105"};

	    


		// add all rows into data grid view
        dataGridView->Rows->Add(row0);
        dataGridView->Rows->Add(row1);
        dataGridView->Rows->Add(row2);
        dataGridView->Rows->Add(row3);
        dataGridView->Rows->Add(row4);
        dataGridView->Rows->Add(row5);
        dataGridView->Rows->Add(row6);


		// customize colors header rows
		for (int i = 0; i < 4; i++) {   // for 4 header rowsrows
			for (int j = 0; j < 3; j++) { // for 3 columns
				// bold and navy
				dataGridView->Rows[i]->Cells[j]->Style->ForeColor = System::Drawing::Color::Navy;
				dataGridView->Rows[i]->Cells[j]->Style->Font = gcnew System::Drawing::Font(dataGridView->Font, System::Drawing::FontStyle::Bold);
			}
		}
		// customize color/background for piece description row
		for (int j = 0; j < 3; j++) {
			// for the header row of 'piece, time placed, etc' bold with colored background
			dataGridView->Rows[4]->Cells[j]->Style->Font = gcnew System::Drawing::Font(dataGridView->Font, System::Drawing::FontStyle::Bold);
			dataGridView->Rows[4]->Cells[j]->Style->BackColor = System::Drawing::Color::AntiqueWhite;
		}


        dataGridView->Columns[0]->DisplayIndex = 3;
        dataGridView->Columns[1]->DisplayIndex = 4;
        dataGridView->Columns[2]->DisplayIndex = 0;
        dataGridView->Columns[3]->DisplayIndex = 1;
        dataGridView->Columns[4]->DisplayIndex = 2;

		//remove all selection highlighting
		dataGridView->SelectedRows->Clear();
    }


private: System::Void doneButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->DialogResult = System::Windows::Forms::DialogResult::OK;
		 }
};
}
