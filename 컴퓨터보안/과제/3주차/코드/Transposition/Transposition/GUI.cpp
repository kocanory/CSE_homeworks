#include "GUI.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

void main() {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Transposition::GUI form;	// 프로젝트내 GUI 파일 선언 
	Application::Run(% form); //GUI 실행
}