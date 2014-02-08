#include <Windows.h>
#include "stdafx.h"
#include <WinBase.h>
#include <WinUser.h>
#using <System.dll>
#include <stdlib.h>
#include  <stdio.h>
#include <vcclr.h>
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
	/// Summary for ColorCalibrationForm
	/// </summary>
	public ref class ColorCalibrationForm : public System::Windows::Forms::Form
	{
	public:
		ColorCalibrationForm(void)
		{
			InitializeComponent();
			this->puzzle = gcnew KnobPuzzle();
			this->pieceIndex = 0;
			this->piece = gcnew PuzzlePiece();
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
	private: System::Windows::Forms::Label^  label1;
	public: 
	private: System::Windows::Forms::Label^  label2;

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
			// ColorCalibrationForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(444, 286);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->okButton);
			this->Name = L"ColorCalibrationForm";
			this->Text = L"Calibrate Colors";
			this->Load += gcnew System::EventHandler(this, &ColorCalibrationForm::ColorCalibrationForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ColorCalibrationForm_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void okButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (this->pieceIndex >= this->puzzle->getPieceList()->Count) {
					 this->DialogResult = System::Windows::Forms::DialogResult::OK;
					 return;
				 }
				 this->piece = this->puzzle->getPieceList()[this->pieceIndex];
				 MessageBox::Show(this->piece->getName());
				 // go to next piece
				 this->pieceIndex++;
			 }
};
}
