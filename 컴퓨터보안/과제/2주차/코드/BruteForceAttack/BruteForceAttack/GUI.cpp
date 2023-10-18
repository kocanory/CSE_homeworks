#include "GUI.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

void main() {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	BruteForceAttack::GUI form;	// Project1 - 본인 프로젝트 이름
	Application::Run(% form);
}