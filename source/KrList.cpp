/*********************************************************
Author:MilesYang
Mail:1961464399@qq.com
CurrentTime:2018-4-13
FileName:KrList.cpp
*********************************************************/

#include "KrList.h"
#include "KrCore.h"
namespace KrUI
{
	KrList::KrList()
	{
		m_Position = 0;
		m_TotalHeight = 0;
		m_MouseWheelDelta = 10;
		m_ScrollBarRect.Width = 20;
		m_bMultiSelectable = false;
		m_MouseHoverItem = -1;
		m_MouseDownOnScrollBarPos = -1;
		m_FontColor = Gdiplus::Color::Black;
		m_StringFormat.SetAlignment(Gdiplus::StringAlignment::StringAlignmentNear);
		m_StringFormat.SetLineAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
	}

	void KrList::SetPosition(int position)
	{
		if (position < 0)
		{
			m_Position = 0;
		}
		else if (position > static_cast<int>(m_TotalHeight - GetHeight()))
		{
			m_Position = m_TotalHeight - GetHeight();
		}
		else
		{
			m_Position = position;
		}
		//TODO
		if (m_pKrWindow != nullptr)m_pKrWindow->UpdateUI(this);
	}

	void KrList::SetMultiSelectable(bool bMultiSelectable)
	{
		m_bMultiSelectable = bMultiSelectable;
		//m_SelectedItems.clear();
	}
	std::vector<KrUI::KrListItem> KrList::GetSelectedItems() const
{
		std::vector<KrListItem> kls;
		for (auto& li : m_ListItems)
		{
			if (li.m_bSelected)
			{
				kls.push_back(li);
			}
		}
		return kls;
	}

	LRESULT KrList::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		switch (Message)
		{
		case WM_LBUTTONDOWN:
			//如果鼠标按下时在列表内，就把当前选中的项目设置为鼠标停留在的那一项
			if ((static_cast<int>(m_pKrWindow->m_ptMouse.x) >= static_cast<int>(GetX()) && static_cast<int>(m_pKrWindow->m_ptMouse.y) >= static_cast<int>(GetY()) &&
				static_cast<int>(m_pKrWindow->m_ptMouse.x) < static_cast<int>(GetX() + GetWidth() - m_ScrollBarRect.Width) && static_cast<int>(m_pKrWindow->m_ptMouse.y) <= static_cast<int>(GetY() + GetHeight())))
			{
				if (m_bMultiSelectable)
				{
					// 					bool bExsited = false;
					// 					auto it = m_SelectedItems.begin();
					// 					while (it != m_SelectedItems.end())
					// 					{
					// 						if (*it == m_MouseHoverItem)
					// 						{
					// 							it = m_SelectedItems.erase(it);
					// 							bExsited = true;
					// 							//TODO
					// 							if (m_pKrWindow != nullptr)m_pKrWindow->UpdateUI(this);
					// 							break;
					// 						}
					// 						else
					// 						{
					// 							++it;
					// 						}
					// 					}
					// 
					// 					if (!bExsited)
					// 					{
					// 						m_SelectedItems.push_back(m_MouseHoverItem);
					// 						//TODO
					// 						if (m_pKrWindow != nullptr)m_pKrWindow->UpdateUI(this);
					// 					}
					if (m_MouseHoverItem != -1)
					{
						m_ListItems[m_MouseHoverItem].m_bSelected = !m_ListItems[m_MouseHoverItem].m_bSelected;
					}
				}
				else
				{
					// 					m_SelectedItems.clear();
					// 					m_SelectedItems.push_back(m_MouseHoverItem);
					for (auto& li : m_ListItems)
					{
						li.m_bSelected = false;
					}
					if (m_MouseHoverItem < m_ListItems.size())m_ListItems[m_MouseHoverItem].m_bSelected = true;
				}
				if (m_pKrWindow != nullptr)m_pKrWindow->UpdateUI(this);
				CallMsgProc(KM_LISTITEMCLICK, wParam, lParam);
			}
			//如果鼠标按下时在滚动条上，就保存鼠标和滚送条顶部的相对位置
			if (static_cast<int>(m_pKrWindow->m_ptMouse.x) >= static_cast<int>(GetX() + GetWidth() - m_ScrollBarRect.Width) &&
				static_cast<int>(m_pKrWindow->m_ptMouse.y) >= static_cast<int>(GetY() + m_ScrollBarRect.Y) &&
				static_cast<int>(m_pKrWindow->m_ptMouse.x) <= static_cast<int>(GetX() + GetWidth()) &&
				static_cast<int>(m_pKrWindow->m_ptMouse.y) <= static_cast<int>(GetY() + m_ScrollBarRect.GetBottom()))
				m_MouseDownOnScrollBarPos = m_pKrWindow->m_ptMouse.y - GetY() - m_ScrollBarRect.GetTop();
			break;
		case WM_MOUSEMOVE:
			//如果鼠标按在滚动条上时，根据相对位置设置列表的显示位置
			if (m_MouseDownOnScrollBarPos != -1)
			{
				//m_ScrollBarRect.Y = (GetHeight() - m_ScrollBarRect.Height)*static_cast<float>(m_Position) / (m_TotalHeight - GetHeight());
				//解以上方程得：
				SetPosition(static_cast<int>((m_pKrWindow->m_ptMouse.y - m_MouseDownOnScrollBarPos - GetY())*
					(static_cast<float>(m_TotalHeight) - GetHeight()) / (GetHeight() - m_ScrollBarRect.Height)));
			}
			break;
		case WM_MOUSEWHEEL:
			//如果鼠标滚动时在列表区域内，就设置显示位置是增加或减少
			if (!(static_cast<int>(m_pKrWindow->m_ptMouse.x) >= static_cast<int>(GetX()) && static_cast<int>(m_pKrWindow->m_ptMouse.y) >= static_cast<int>(GetY()) &&
				static_cast<int>(m_pKrWindow->m_ptMouse.x) <= static_cast<int>(GetX() + GetWidth()) && static_cast<int>(m_pKrWindow->m_ptMouse.y) <= static_cast<int>(GetY() + GetHeight())))break;
			if (static_cast<int>(wParam) > 0)
			{
				if (m_Position > 0)SetPosition(m_Position - m_MouseWheelDelta);
			}
			else
			{
				if (m_TotalHeight - m_Position >= GetHeight())SetPosition(m_Position + m_MouseWheelDelta);
			}
			break;
		case WM_LBUTTONUP:
			if (m_MouseDownOnScrollBarPos != -1)
			{
				m_MouseDownOnScrollBarPos = -1;
				//TODO
				if (m_pKrWindow != nullptr)m_pKrWindow->UpdateUI(this);
			}
			break;
		case WM_TIMER:
			int current_total = 0, start_position = 0;
			m_MouseHoverItem = -1;
			for (unsigned int i = 0; i < m_ListItems.size(); i++)
			{
				//确定开始项
				if (static_cast<int>(m_Position) >= current_total && m_Position <= (current_total + m_ListItems[i].m_Height))
				{
					start_position = current_total - m_Position;
				}
				//确定鼠标停留项
				if (m_pKrWindow->m_ptMouse.x >= static_cast<int>(GetX()) && m_pKrWindow->m_ptMouse.y >= static_cast<int>(GetY()) &&
					m_pKrWindow->m_ptMouse.x <= static_cast<int>(GetX() + GetWidth()) && m_pKrWindow->m_ptMouse.y <= static_cast<int>(GetY() + GetHeight()) &&
					static_cast<int>(m_pKrWindow->m_ptMouse.y - GetY()) >= static_cast<int>(current_total - m_Position) &&
					static_cast<int>(m_pKrWindow->m_ptMouse.y - GetY()) <= static_cast<int>(current_total - m_Position + m_ListItems[i].m_Height) &&
					static_cast<int>(m_pKrWindow->m_ptMouse.x - GetX()) <= static_cast<int>(GetWidth() - m_ScrollBarRect.Width))
					m_MouseHoverItem = i;
				//确定结束项
				int end_position = m_Position + GetHeight();
				if (end_position >= current_total && end_position <= static_cast<int>(current_total + m_ListItems[i].m_Height))
				{
					break;//找到结束项直接退出循环
				}
				current_total += m_ListItems[i].m_Height;
			}
			break;
		}
		return KrUIBase::HandleMessage(Message, wParam, lParam);
	}

	int KrList::AddItem(std::wstring wStr, int nIndex /* = -1 */, unsigned int nHeight /* = 35*/)
	{
		if (nIndex == -1)
		{
			while (nIndex == -1)
			{
				nIndex = abs(rand());
				for (auto& li : m_ListItems)
				{
					if (li.m_Index == nIndex) nIndex = -1;
				}
			}
			m_ListItems.push_back(KrListItem(wStr, nIndex, nHeight));
			m_TotalHeight += nHeight;
			this->ItemChange();
			return nIndex;
		}

		for (auto& li : m_ListItems)
		{
			if (li.m_Index == nIndex)return -1;
		}
		m_ListItems.push_back(KrListItem(wStr, nIndex, nHeight));
		m_TotalHeight += nHeight;
		this->ItemChange();
		return nIndex;
	}

	int KrList::RemoveItem(std::wstring wStr)
	{
		int ret = 0;
		auto it = m_ListItems.begin();
		while (it != m_ListItems.end())
		{
			if (it->m_ItemName == wStr)
			{
				m_TotalHeight -= it->m_Height;
				it = m_ListItems.erase(it);
				if (m_Position > m_TotalHeight - GetHeight())SetPosition(m_TotalHeight - GetHeight());
				++ret;
			}
			else
			{
				++it;
			}
		}
		this->ItemChange();
		return ret;
	}

	void KrList::SelectAllItems(bool b)
	{
		if (b&&m_bMultiSelectable)
		{
			for (auto& li : m_ListItems)
			{
				li.m_bSelected = true;
			}
		}
		else if (!b)
		{
			for (auto& li : m_ListItems)
			{
				li.m_bSelected = false;
			}
		}
		m_pKrWindow->UpdateUI(this);
	}

	bool KrList::RemoveItem(int nIndex)
	{
		auto it = m_ListItems.begin();
		while (it != m_ListItems.end())
		{
			if (it->m_Index == nIndex)
			{
				//从列表项中删除
				m_TotalHeight -= it->m_Height;
				if (m_Position > m_TotalHeight - GetHeight())SetPosition(m_TotalHeight - GetHeight());
				it = m_ListItems.erase(it);
				this->ItemChange();
				return true;
			}
			else
			{
				++it;
			}
		}
		return false;
	}
	void KrList::ItemChange()
	{
		if (m_pKrWindow != nullptr)m_pKrWindow->UpdateUI();
	}

	void KrList::DrawItem(unsigned int item_index, int start_position)
	{
		//如果这一项处于鼠标停留或者选中状态时，画淡蓝色背景

		if (m_ListItems[item_index].m_bSelected)m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color(196, 218, 242)), 0, start_position, GetWidth() - m_ScrollBarRect.Width, m_ListItems[item_index].m_Height);
		//画文字内容
		m_pGraphics->DrawString(m_ListItems[item_index].m_ItemName.c_str(), -1, m_pFont, Gdiplus::RectF(static_cast<Gdiplus::REAL>(10),
			static_cast<Gdiplus::REAL>(start_position), static_cast<Gdiplus::REAL>(GetWidth() - m_ScrollBarRect.Width), static_cast<Gdiplus::REAL>(m_ListItems[item_index].m_Height)),
			&m_StringFormat, &Gdiplus::SolidBrush(m_FontColor));
		//画边框
		m_pGraphics->DrawRectangle(&Gdiplus::Pen(m_BorderColor), 0, start_position, GetWidth() - m_ScrollBarRect.Width, m_ListItems[item_index].m_Height);
	}

	void KrList::Update()
	{
		m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_BgColor), 0, 0, GetWidth(), GetHeight());
		if (m_ListItems.size() != 0)
		{
			//计算需要画哪些项：
			//m_Position = 0;
			int current_total = 0, start_item = -1, end_item = -1, start_position = 0;
			m_MouseHoverItem = -1;
			for (unsigned int i = 0; i < m_ListItems.size(); i++)
			{
				//确定开始项
				if (static_cast<int>(m_Position) >= current_total && m_Position <= (current_total + m_ListItems[i].m_Height))
				{
					start_item = i;
					start_position = current_total - m_Position;
				}
				//确定鼠标停留项
// 				if (m_pKrWindow->m_ptMouse.x >= static_cast<int>(GetX()) && m_pKrWindow->m_ptMouse.y >= static_cast<int>(GetY()) &&
// 					m_pKrWindow->m_ptMouse.x <= static_cast<int>(GetX() + GetWidth()) && m_pKrWindow->m_ptMouse.y <= static_cast<int>(GetY() + GetHeight()) &&
// 					static_cast<int>(m_pKrWindow->m_ptMouse.y - GetY()) >= static_cast<int>(current_total - m_Position) &&
// 					static_cast<int>(m_pKrWindow->m_ptMouse.y - GetY()) <= static_cast<int>(current_total - m_Position + m_ListItems[i].m_Height) &&
// 					static_cast<int>(m_pKrWindow->m_ptMouse.x - GetX()) <= static_cast<int>(GetWidth() - m_ScrollBarRect.Width))
// 					m_MouseHoverItem = i;
				//确定结束项
				int end_position = m_Position + GetHeight();
				if (end_position >= current_total && end_position <= static_cast<int>(current_total + m_ListItems[i].m_Height))
				{
					end_item = i;
					break;//找到结束项直接退出循环
				}
				current_total += m_ListItems[i].m_Height;
			}
			//如果未找到最后一项即从开始位置画到末尾
			if (end_item = -1)end_item = m_ListItems.size() - 1;
			for (int i = start_item; i <= end_item; i++)
			{
				this->DrawItem(i, start_position);

				//下一次画的位置增加
				start_position += m_ListItems[i].m_Height;
			}
		}
		//画列表项和滚动条分界线
		m_pGraphics->DrawLine(&Gdiplus::Pen(m_BorderColor, 1), Gdiplus::Point(GetWidth() - m_ScrollBarRect.Width, 0), Gdiplus::Point(GetWidth() - m_ScrollBarRect.Width, GetHeight()));
		//根据显示位置设置滚动条的矩形
		if (m_TotalHeight > GetHeight())
		{
			m_ScrollBarRect.Height = static_cast<int>(GetHeight()*static_cast<float>(GetHeight()) / m_TotalHeight);
			m_ScrollBarRect.X = GetWidth() - m_ScrollBarRect.Width + 1;
			m_ScrollBarRect.Y = static_cast<int>((GetHeight() - m_ScrollBarRect.Height)*static_cast<float>(m_Position) / (m_TotalHeight - GetHeight()));
		}
		else
		{
			m_ScrollBarRect.Height = GetHeight();
			m_ScrollBarRect.X = GetWidth() - m_ScrollBarRect.Width + 1;
			m_ScrollBarRect.Y = 0;
		}
		//画滚动条
		m_pGraphics->FillRectangle(
			//正处于按下状态时，画深灰色，否则画浅灰色
			(m_MouseDownOnScrollBarPos != -1) ?
			&Gdiplus::SolidBrush(Gdiplus::Color(150, 150, 150)) :
			&Gdiplus::SolidBrush(Gdiplus::Color(200, 200, 200)), m_ScrollBarRect);
		//画列表边框
		m_pGraphics->DrawRectangle(&Gdiplus::Pen(m_BorderColor, 2), 1, 1, GetWidth() - 2, GetHeight() - 2);
		KrUIBase::Update();
	}
}