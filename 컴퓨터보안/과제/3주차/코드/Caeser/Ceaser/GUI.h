#pragma once

#include "code.h"

using namespace std;



namespace Caeser {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	CaeserCiper caeser;
	/// <summary>
	/// GUI에 대한 요약입니다.
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	public:
		GUI(void)
		{
			InitializeComponent();
			//
			//TODO: 생성자 코드를 여기에 추가합니다.
			//

			CheckForIllegalCrossThreadCalls = false;
		}

	protected:
		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
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
		/// 필수 디자이너 변수입니다.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 디자이너 지원에 필요한 메서드입니다. 
		/// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
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
			this->button1->Location = System::Drawing::Point(71, 50);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(125, 89);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Caeser Encrypt";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &GUI::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(256, 50);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(125, 89);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Caeser Decrypt";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &GUI::button2_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(71, 189);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(488, 234);
			this->textBox1->TabIndex = 2;
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(434, 50);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(125, 89);
			this->button3->TabIndex = 3;
			this->button3->Text = L"Automatic Run";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &GUI::button3_Click);
			// 
			// GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(640, 435);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"GUI";
			this->Text = L"Caeser Ciper";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		caeser.createSentense();
		textBox1->Text = "<Created Random Sentense!>" + Environment::NewLine;
		
		textBox1->AppendText(caeser.getSentense() + Environment::NewLine + Environment::NewLine);
		
		caeser.encrypt();
		textBox1->AppendText("<Encrypt Caeser Ciper!>" + Environment::NewLine);

		textBox1->AppendText(caeser.getSentense() + Environment::NewLine + Environment::NewLine);
	}

	private: void run()
	{
		caeser.decrypt(textBox1);
	}

	private: void all_run()
	{
		caeser.run(textBox1);
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!caeser.check_decrypted())
		{
			textBox1->AppendText("<Decrypt Caeser Ciper!>" + Environment::NewLine);
			System::Threading::Tasks::Task::Factory->StartNew(gcnew Action(this, &GUI::run));
		}
		else
			textBox1->AppendText("<Decrypted!>" + Environment::NewLine);
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Threading::Tasks::Task::Factory->StartNew(gcnew Action(this, &GUI::all_run));
	}
};
}
