#include "KrEdit.h"

namespace KrUI
{
	void KrEdit::SetText(std::wstring str)
	{
		m_strText = str;
	}

	std::wstring KrEdit::GetText()
	{
		return m_strText;
	}

	LRESULT KrEdit::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		if (m_pKrWindow->GetFocusedCtrl()==this)
		{
			switch (Message)
			{
			case WM_CHAR:
				if (wParam >= 32 && wParam <= 126)//�ַ�
				{
					m_strText += static_cast<char>(wParam);
				}
				else if (wParam == 8 & m_strText.size() != 0)//�˸�
				{
					m_strText.pop_back();
				}
				break;
			}
		}
		return KrUIBase::HandleMessage(Message, wParam, lParam);
	}

	void KrEdit::UpdateDc()
	{
		m_Time += TIMER_INTERVAL;
		if (m_Time >= 500)
		{
			m_bShowCursor = !m_bShowCursor;
			m_Time = 0;
		}
		//��������ɫ:
		m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_BgColor), 0, 0, GetWidth(), GetHeight());
		//����������:
			//TODO������
		m_pGraphics->DrawString((m_strText + (m_bShowCursor&&m_pKrWindow->GetFocusedCtrl() == this ? L"��" : L"")).c_str(), -1,
			m_pFont, Gdiplus::RectF(5, 0, GetWidth(), GetHeight()), &m_StringFormat, &Gdiplus::SolidBrush(m_FontColor));
		//���߿�:
		if ((m_bMouseIn && !m_bMouseDown) && m_ButtonStatus != mouse_hover)
		{
			m_ButtonStatus = mouse_hover;
		}
		else if (((!m_bMouseDown) && (!m_bMouseIn)) && m_ButtonStatus != mouse_leave)
		{
			m_ButtonStatus = mouse_leave;
		}
		else if (m_bMouseDown && (m_ButtonStatus != mouse_down))
		{
			m_ButtonStatus = mouse_down;
		}																		// Color(21,131,221)������ƶ����ı�����ʱ�߿����ɫ
		m_pGraphics->DrawRectangle(&Gdiplus::Pen((m_ButtonStatus == mouse_leave ? m_BorderColor : Gdiplus::Color(21, 131, 221))),
			0, 0, GetWidth() - 1, GetHeight() - 1);
		//��������Mmp��
		m_pKrWindow->GetBmpGraphics()->DrawImage(m_pBmp, GetX(), GetY(), GetWidth(), GetHeight());
	}
	KrEdit::KrEdit()
	{
		m_BgColor = Gdiplus::Color::White;
		m_BorderColor = Gdiplus::Color(170, 170, 170);
		m_FontColor = Gdiplus::Color::Black;
		m_StringFormat.SetAlignment(Gdiplus::StringAlignmentNear);
		m_StringFormat.SetFormatFlags(Gdiplus::StringFormatFlags::StringFormatFlagsNoWrap);
		m_hCursor = LoadCursor(nullptr, IDC_IBEAM);//��������������ʽ
	}
}// !KrUI