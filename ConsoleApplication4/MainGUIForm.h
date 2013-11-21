#include <Windows.h>
#include "stdafx.h"
#include <WinBase.h>
#include <WinUser.h>
#using <System.dll>
#include <stdlib.h>
#include  <stdio.h>
#include <vcclr.h>
#include "GameBoard.h"
#include "PuzzlePiece.h"
#include "TrackedPiece.h"
#include "HandleVariables.h"
#include "Functions.h"

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
			this->Vars.InitializeFlags();
			//
			//TODO: Add the constructor code here
			//
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




	private: System::Windows::Forms::Button^  stopGameButton;
	public: bool gameRunning;
	private: System::Windows::Forms::TextBox^  textBox1;
	public: 
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Button^  statsButton;

	private: HandleVariables Vars;

	protected: 

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
			this->components = (gcnew System::ComponentModel::Container());
			this->runGameButton = (gcnew System::Windows::Forms::Button());
			this->stopGameButton = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->statsButton = (gcnew System::Windows::Forms::Button());
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
			// stopGameButton
			// 
			this->stopGameButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->stopGameButton->Location = System::Drawing::Point(370, 140);
			this->stopGameButton->Name = L"stopGameButton";
			this->stopGameButton->Size = System::Drawing::Size(194, 69);
			this->stopGameButton->TabIndex = 5;
			this->stopGameButton->Text = L"Stop Game";
			this->stopGameButton->UseVisualStyleBackColor = true;
			this->stopGameButton->Visible = false;
			this->stopGameButton->Click += gcnew System::EventHandler(this, &MainGUIForm::stopGameButton_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(30, 72);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(190, 20);
			this->textBox1->TabIndex = 6;
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
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MainGUIForm::timer1_Tick);
			// 
			// statsButton
			// 
			this->statsButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->statsButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.25F));
			this->statsButton->Location = System::Drawing::Point(23, 243);
			this->statsButton->Name = L"statsButton";
			this->statsButton->Size = System::Drawing::Size(212, 61);
			this->statsButton->TabIndex = 8;
			this->statsButton->Text = L"Stats";
			this->statsButton->UseVisualStyleBackColor = true;
			this->statsButton->Click += gcnew System::EventHandler(this, &MainGUIForm::statsButton_Click);
			// 
			// MainGUIForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(568, 308);
			this->Controls->Add(this->statsButton);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->stopGameButton);
			this->Controls->Add(this->runGameButton);
			this->Name = L"MainGUIForm";
			this->Text = L"Puzzle Assembly Assistant";
			this->Load += gcnew System::EventHandler(this, &MainGUIForm::MainGUIForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void runGameButton_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->gameRunning = true;
			 this->runGameButton->Visible = false;
			 this->stopGameButton->Visible = true;
			 System::String^ CodeString = this->textBox1->Text;
			 System::String^ puzzleType = searchPuzzleType(CodeString);
			 //GameBaseClass^ puzzle = gcnew GameBaseClass();
			 if (puzzleType->Equals("KnobPuzzle")) {
				 KnobPuzzle^ puzzle = gcnew KnobPuzzle(CodeString);
				 MessageBox::Show(Vars.JunkLine);
				 initializeOpenCV( Vars.returnHandle(), puzzle);
			 }
			 else if (puzzleType->Equals("BlockPuzzle")) {
				 //BlockPuzzle^ puzzle = gcnew BlockPuzzle(CodeString);
				 //etc...
			 }
		 }


		 // NOTE ALSO NEED A PAUSE BUTTON
private: System::Void stopGameButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 // add a STOP command to flags
			 this->gameRunning = false;
			 this->runGameButton->Visible = true;
			 this->stopGameButton->Visible = false;
		 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {

		 }
private: System::Void statsButton_Click(System::Object^  sender, System::EventArgs^  e) {

		 }

};
}
