#include<windows>


class KrWindow
{
	private:
		LPCTSTR m_lpWindowName;//�������� 
		HWND m_hwnd=NULL;//���ھ�� 
		RECT m_rect;//���ھ��� 
		DWORD m_dwStyle;//���ڷ�� 
	public:
		LPCTSTR GetWindowName();//��ȡ�������� 
		void SetWindowName(LPCTSTR lpWindowName);//���ô������� 
		HWND GetHWND();//��ȡ���ھ�� 
		RECT* GetRect();//��ȡ���ھ��� 
		void SetRect(RECT* pRect); //���ô��ھ��� 
 		void SetStyle(DWORD dwStyle);//���ô��ڷ�� 
 		bool Create();//������ʵ���� 
 		int GetX();//
 		int GetY();//
 		int GetWidth();//
 		int GetHeight;//
 		void SetX(int x);//
 		void SetY(int y);//
 		void SetWidth(int width);//
 		void SetHeight(int height);//
}



