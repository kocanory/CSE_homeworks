#include "GUI.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

void main() {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Transposition::GUI form;	// ������Ʈ�� GUI ���� ���� 
	Application::Run(% form); //GUI ����
}