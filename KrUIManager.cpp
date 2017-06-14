#include<KrUIManager.h>
//��Ϣת������ 
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}




bool KrUIManager::Initialize(HINSTANCE hInstance)
{
	m_hInstance=hInstance;
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc;
	wc.hInstance	 = m_hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = GetWindowClassName();
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); 
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);
	
	if(!RegisterClassEx(&wc))
	{
		return false;
	}
	
	return true;
}


KrWindow* KrUIManager::CreateWindow(LPCTSTR lpWindowName,int x,int y,int width,int height,DWORD dwStyle)
{
	KrWindow* pKrWindow=new KrWindow;
	if(!pKrWindow) return false;
	pKrWindow->SetWindowName(lpWindowName);
	RECT rect;
	rect.left  =x;
	rect.top   =y;
	rect.right =x + width;
	rect.bottom=y + height;
	pKrWindow->SetRect(&rect);
	pKrWindow->SetStyle(dwStyle);
	m_WndList.push_back(pKrWindow);
	return pKrWindow;
}


KrWindow* CreateWindow(LPCTSTR lpWindowName,int x,int y,int width,int height)
{
	return CreateWindow(lpWindowName,x,y,width,height,WS_BORDER);
}


LPCTSTR KrUIManager::GetWindowClassName()
{
	return m_lpWindowClassName;
}

	

