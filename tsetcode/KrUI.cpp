// KrUI.cpp : ����Ӧ�ó������ڵ㡣
//typedef LRESULT(*MSGPROC) (KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam);
#include "stdafx.h"
#include "KrUI.h"
#include "source/KrCore.h"
#include <windows.h>
using namespace KrUI;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	KrUIManager* p = KrUI::KrUIManager::GetpKrUIManager();
	if (!p->Initialize(hInstance))return 0;
	KrWindow* pw = p->AddWindow(L"��ӭʹ��KrUI", 100, 100,500,300);
	pw->Show();
	KrButton* pb = dynamic_cast<KrButton*>(pw->AddControl(KrButton_t, L"Button1", 70, 135, 100, 25));
	pb->Show();
	KrButton* pb1 = dynamic_cast<KrButton*>(pw->AddControl(KrButton_t, L"Button2", 300, 135, 100, 25));
	pb1->Show();
	KrLabel* pl1 = dynamic_cast<KrLabel*>(pw->AddControl(KrLabel_t, L"��8�� VBA������Ƹ�����һ������VBA��VBA�༭�������������ԡ��������¼����û�������ؼ�", 70, 160, 150, 150));
	pl1->Show();
	return p->MessageLoop();
}
