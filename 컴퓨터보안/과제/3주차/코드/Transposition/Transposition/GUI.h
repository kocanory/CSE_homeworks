#pragma once
#include "code.h"

namespace Transposition {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// GUI�� ���� ����Դϴ�.
	/// </summary>
	
	TranspositionCiper trans;
	
	public ref class GUI : public System::Windows::Forms::Form
	{
	public:
		GUI(void)
		{
			InitializeComponent();
			//
			//TODO: ������ �ڵ带 ���⿡ �߰��մϴ�.
			//

			CheckForIllegalCrossThreadCalls = false;
		}

	protected:
		/// <summary>
		/// ��� ���� ��� ���ҽ��� �����մϴ�.
		/// </summary>
		~GUI()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button3;
	protected:

	private:
		/// <summary>
		/// �ʼ� �����̳� �����Դϴ�.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����̳� ������ �ʿ��� �޼����Դϴ�. 
		/// �� �޼����� ������ �ڵ� ������� �������� ������.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(42, 47);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(143, 97);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Transposition Encrypt";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &GUI::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(251, 47);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(143, 97);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Transposition Decrypt";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &GUI::button2_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(42, 178);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(553, 226);
			this->textBox1->TabIndex = 3;
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &GUI::textBox1_TextChanged);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(452, 47);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(143, 97);
			this->button3->TabIndex = 4;
			this->button3->Text = L"Autumatic Run";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &GUI::button3_Click);
			// 
			// GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(640, 457);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"GUI";
			this->Text = L"Transposition Ciper";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		trans.createSentense();
		textBox1->Text = "<Created Random Sentense!>" + Environment::NewLine;
		textBox1->AppendText(trans.getSentense() + Environment::NewLine + Environment::NewLine);

		trans.encrypt();
		textBox1->AppendText("<Encrypt Transposition Ciper!>" + Environment::NewLine);
		textBox1->AppendText(trans.getSentense() + Environment::NewLine + Environment::NewLine);
	}

	private: void run()
	{
		trans.decrypt(textBox1);
	}

	private: void all_run()
	{
		trans.run(textBox1);
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		
		if (!trans.check_decrypted())
		{
			textBox1->AppendText("<Decrypt Transposition Ciper!>" + Environment::NewLine);
			System::Threading::Tasks::Task::Factory->StartNew(gcnew Action(this, &GUI::run));
		}
		else
			textBox1->AppendText("<Decrypted>" + Environment::NewLine);
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Threading::Tasks::Task::Factory->StartNew(gcnew Action(this, &GUI::all_run));
	}
};
}
