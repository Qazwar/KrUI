#include "KrCore.h"
using namespace KrUI;
KrUIManager* pUI = KrUIManager::GetpKrUIManager();
/*typedef LRESULT(*MSGFUNC)(void* pObject, WPARAM wParam, LPARAM lParam);*/

LRESULT OnBtnDown(void* pObject, WPARAM wParam, LPARAM lParam)
{
	((KrArea*)pObject)->GetWindow()->Destroy();
	return 0;
}



//��ں���
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	pUI->Initialize(hInstance);//��ʼ��
	KrWindow* pWnd = pUI->AddWindow(L"caption", 400, 300, 500, 400);//��Ӵ���
	pWnd->Show();//��ʾ����
	KrControl* pA=pWnd->AddControl(Area, L"Caption", 0, 0, pWnd->GetWidth(),30);
	((KrArea*)pA)->Show();
	//pA->RegMsg(WM_LBUTTONDOWN, OnBtnDown);
	return pUI->MessageLoop();//������Ϣѭ��
}