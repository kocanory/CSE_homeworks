#include "GUI.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

void main() {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	BruteForceAttack::GUI form;	// Project1 - ���� ������Ʈ �̸�
	Application::Run(% form);
}