#include "KrUIManager.h"
#include "KrWindow.h"

using namespace KrUI;
KrUIManager* pUI = KrUIManager::GetpKrUIManager();
/*typedef LRESULT(*MSGFUNC)(void* pObject, WPARAM wParam, LPARAM lParam);*/

LRESULT OnBtnUP(void* pObject, WPARAM wParam, LPARAM lParam)
{
	::MessageBox(NULL, L"LBTNUP", L"MsgGetted", MB_OK);//
	return 0;
}

//��ں���
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	pUI->Initialize(hInstance);//��ʼ��
	KrWindow* pWnd = pUI->AddWindow(L"caption", 400, 300, 500, 400);//��Ӵ���
	pWnd->Show();//��ʾ����
	pWnd->RegMsg(WM_LBUTTONUP, OnBtnUP);//��Ϣע��
	return pUI->MessageLoop();//������Ϣѭ��
}