#include<list>
#include<windows>



class KrUIManager
{
	public:
		bool      Initialize(HINSTANCE hInstance);//ui��������ʼ�� 
		KrWindow* AddWindow(LPCTSTR lpWindowName,int x,int y,int width,int height,DWORD dwStyle);//��Ӵ��� 
		KrWindow* AddWindow(LPCTSTR lpWindowName,int x,int y,int width,int height);//��Ӵ��� 
		LPCTSTR   GetWindowClassName();//��ȡ�������� 
		HINSTANCE GetHINSTANCE();//��ȡ����ʵ�� 
		void      CreateWindow(); 
		void      MsgLoop();
	private:
		WNDCLASSEX      m_wc; //������ 
		LPCTSTR         m_lpWindowClassName="KrUI";//���� 
		HINSTANCE       m_hInstance;//ʵ����� 
		list<KrWindow*> m_WndList;//�����б� 
	
}


