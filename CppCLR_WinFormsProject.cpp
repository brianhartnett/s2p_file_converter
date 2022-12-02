#include "pch.h"
#include "Form1.h"
#include <stdio.h>


extern "C" {
#include "Fileinfo.h"
#include "s2p_get_data.h"
#include "s2p_create_file.h"
}

using namespace System;
using namespace System::Windows::Forms;



[STAThread]
int main()
{
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false);
  Application::Run(gcnew CppCLRWinFormsProject::Form1());
  return 0;
}