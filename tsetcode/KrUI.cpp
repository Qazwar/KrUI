#include "source/KrCore.h"
KrUI::KrUIManager* pUM = KrUI::KrUIManager::GetpKrUIManager();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!pUM->Initialize(hInstance)) return 0;//��ʺ��
	KrUI::KrWindow* pWnd = pUM->AddWindow(L"�ⲻ��һ������", 100, 100, 350, 200);//��Ӵ���
	KrUI::KrButton* pBtn = dynamic_cast<KrUI::KrButton*>(pWnd->AddControl(KrUI::KrUIType::KrButton_t, L"��Ų��ǰ�ť", 100, 50, 150, 25));
	KrUI::KrEdit* pEdit = dynamic_cast<KrUI::KrEdit*>(pWnd->AddControl(KrUI::KrUIType::KrEdit_t, L"һ�����������߰˾�ʮ", 100, 100, 200, 25));
	KrUI::KrProgressBar* pProgressBar = dynamic_cast<KrUI::KrProgressBar*>(pWnd->AddControl(KrUI::KrUIType::KrProgressBar_t, L"", 100, 150, 200, 20));
	pProgressBar->SetPercentage(100);
	return pUM->MessageLoop();
}