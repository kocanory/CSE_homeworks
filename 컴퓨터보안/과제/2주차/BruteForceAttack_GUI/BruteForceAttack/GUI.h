#include "code.h"

#pragma once
    
namespace BruteForceAttack {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	std::vector<std::string> character_set; //�н����带 �����ϱ� ���� ����
	bool Number = false, Alpha = false, Special = false;
	//������ ������ �������� �Ǻ��ϱ� ���� �÷���

	/// <summary>
	/// GUI�� ���� ����Դϴ�.
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	public:
		GUI(void)
		{
			InitializeComponent();
			CheckForIllegalCrossThreadCalls = false;
			textBox1->Select(textBox1->Text->Length, 0);
			textBox1->ScrollToCaret();
			textBox1->WordWrap = true;
			//
			//TODO: ������ �ڵ带 ���⿡ �߰��մϴ�.
			//
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
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::CheckBox^ checkBox2;
	private: System::Windows::Forms::CheckBox^ checkBox3;
	private: System::Windows::Forms::Button^ button3;

	protected:

	private:
		/// <summary>
		/// �ʼ� �����̳� �����Դϴ�.
		/// </summary>
		System::ComponentModel::Container^ components;

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
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(476, 37);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(163, 93);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Generate Passwords";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &GUI::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(476, 185);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(163, 93);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Start Cracking";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &GUI::button2_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(53, 185);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(354, 205);
			this->textBox1->TabIndex = 2;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &GUI::textBox1_TextChanged);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(88, 76);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(69, 16);
			this->checkBox1->TabIndex = 3;
			this->checkBox1->Text = L"Number";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &GUI::checkBox1_CheckedChanged);
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(192, 76);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(56, 16);
			this->checkBox2->TabIndex = 4;
			this->checkBox2->Text = L"Alpha";
			this->checkBox2->UseVisualStyleBackColor = true;
			this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &GUI::checkBox2_CheckedChanged);
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(302, 76);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(66, 16);
			this->checkBox3->TabIndex = 5;
			this->checkBox3->Text = L"Special";
			this->checkBox3->UseVisualStyleBackColor = true;
			this->checkBox3->CheckedChanged += gcnew System::EventHandler(this, &GUI::checkBox3_CheckedChanged);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(476, 297);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(163, 93);
			this->button3->TabIndex = 6;
			this->button3->Text = L"Exit";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &GUI::button3_Click);
			// 
			// GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(736, 525);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->checkBox3);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"GUI";
			this->Text = L"Brute Force Attack";
			this->Load += gcnew System::EventHandler(this, &GUI::GUI_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		BruteForce b;
		character_set.clear(); //�н����尡 ����� ���� �ʱ�ȭ
		character_set = b.Make_password(Number, Alpha, Special, textBox1);
		//������ ������ �°� �н����� ����
	}

	private: void run()
	{
		BruteForce b;
		b.Attack(character_set, textBox1);	//�н����� ���� ����
	}
	
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		textBox1->Text = "";	//GUI�� ����ϱ� ���� ����
		if (character_set.size() != 0)	System::Threading::Tasks::Task::Factory->StartNew(gcnew Action(this, &GUI::run));
			//�����带 ����Ͽ� �������� ���� �н����尡 �����ɶ����� GUI�� ����� �� �ֵ��� ó��
		else textBox1->AppendText("You don't have passwords");
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	Number = !(Number); //���� ���� �÷��� �� ����
}
	private: System::Void checkBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	Alpha = !(Alpha); //���ĺ� ���� �÷��� �� ����
}
	private: System::Void checkBox3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	Special = !(Special); //Ư������ ���� �÷��� �� ����
}

	private: void exit_program(){
		exit(1); //���α׷� ����
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {

		System::Threading::Tasks::Task::Factory->StartNew(gcnew Action(this, &GUI::exit_program));
		//�����带 ����Ͽ� ��ٷ� ���α׷��� ������ �� �ֵ��� ó�� 
}
	private: System::Void GUI_Load(System::Object^ sender, System::EventArgs^ e) {
}
	};
}