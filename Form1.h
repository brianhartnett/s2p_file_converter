#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>


extern "C" {
#include "Fileinfo.h"
#include "s2p_get_data.h"
#include "s2p_create_file.h"
#include "c:/cprogrammingcourse/master/src/dbg.h"

}




namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Runtime::InteropServices;




	public ref class Form1 : public System::Windows::Forms::Form
	{
	//Declare variables for filename and description
	String^ fileName;
	String^ description;


	private: System::Windows::Forms::PictureBox^ pictureBox1;
		   

	public:
		Form1(void)
		{
			InitializeComponent();

		}

	protected:

		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	
	private: System::Windows::Forms::TextBox^ tbDescription;
	private: System::Windows::Forms::Button^ btnOpen;
	protected:

	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Button^ btnEnter;
	private: System::Windows::Forms::Label^ label1;




	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->tbDescription = (gcnew System::Windows::Forms::TextBox());
			this->btnOpen = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->btnEnter = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// tbDescription
			// 
			this->tbDescription->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tbDescription->Location = System::Drawing::Point(12, 246);
			this->tbDescription->MaxLength = 70;
			this->tbDescription->Name = L"tbDescription";
			this->tbDescription->Size = System::Drawing::Size(570, 20);
			this->tbDescription->TabIndex = 0;
			// 
			// btnOpen
			// 
			this->btnOpen->Location = System::Drawing::Point(232, 162);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(103, 46);
			this->btnOpen->TabIndex = 1;
			this->btnOpen->Text = L"Select Input File";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &Form1::btnOpen_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// btnEnter
			// 
			this->btnEnter->Location = System::Drawing::Point(168, 332);
			this->btnEnter->Name = L"btnEnter";
			this->btnEnter->Size = System::Drawing::Size(237, 78);
			this->btnEnter->TabIndex = 2;
			this->btnEnter->Text = L"Submit";
			this->btnEnter->UseVisualStyleBackColor = true;
			this->btnEnter->Click += gcnew System::EventHandler(this, &Form1::btnEnter_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 230);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(89, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Enter description:";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox1->Location = System::Drawing::Point(105, 31);
			this->pictureBox1->Image = Image::FromFile(L"C:\\CProgrammingCourse\\W3Resources\\LetUsCHomework\\CppCLR_WinFormsProject3\\sunlord2.bmp");
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(371, 105);
			this->pictureBox1->TabIndex = 4;
			this->pictureBox1->TabStop = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(594, 444);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->btnEnter);
			this->Controls->Add(this->btnOpen);
			this->Controls->Add(this->tbDescription);
			this->Icon = gcnew System::Drawing::Icon(L"C:\\CProgrammingCourse\\W3Resources\\LetUsCHomework\\CppCLR_WinFormsProject3\\sl.ico");
			this->Name = L"Form1";
			this->Text = L"Brian\'s s2p Converter";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnOpen_Click(System::Object^ sender, System::EventArgs^ e) {
		
		//Get input csv file thru file dialog box and store in fileName
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
		//Dialog box settings
		openFileDialog1->InitialDirectory = "c:\\";
		openFileDialog1->Filter = "csv files (*.csv)|*.csv";
		openFileDialog1->FilterIndex = 2;
		openFileDialog1->RestoreDirectory = true;

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
				fileName = openFileDialog1->FileName;		
		}
	}
private: System::Void btnEnter_Click(System::Object^ sender, System::EventArgs^ e) {
	
	struct Fileinfo header[1];
	struct FreqPoint point[202];

	//Get file name and description and add the header struct

	description = tbDescription->Text;

	char* description_text = (char*)(void*)Marshal::StringToHGlobalAnsi(description);
	strcpy(header[0].description, description_text);
	
	char* fileName_text = (char*)(void*)Marshal::StringToHGlobalAnsi(fileName);
	strcpy(header[0].filename, fileName_text);
	
	/*String^ lDescription = gcnew String(header[0].description);*/

	//myStream = File::Open(fileName, FileMode::Open, FileAccess::ReadWrite);
	//StreamWriter^ sw = gcnew StreamWriter(myStream);
	//sw->WriteLine("This is my first line");
	//sw->WriteLine("This is my second line");
	//sw->WriteLine(description);
	//sw->Close();

	//Run C program to pull data from .csv file
	s2p_get_data(header, point);

	//Run C program to export data to .s2p file
	s2p_create_file(header, point);


	MessageBox::Show("COMPLETE: s2p file created in the same directory as this program.");
	Application::Exit();
}
};
}
