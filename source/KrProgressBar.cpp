#include "KrProgressBar.h"
#include "KrCore.h"
namespace KrUI
{
	KrProgressBar::KrProgressBar()
	{
		m_ForeColor = m_BorderColor;
		std::lock_guard<std::mutex> locker(m_PercentageMutex);
		m_Percentage = 0;
	}

	void KrProgressBar::SetForeColor(Gdiplus::Color c) 
	{
		m_ForeColor = c;
	}

	Gdiplus::Color KrProgressBar::GetForeColor()
	{
		return m_ForeColor;
	}

	void KrProgressBar::SetPercentage(unsigned int Percentage)
	{
		if (Percentage > 100)Percentage = 100;
		std::lock_guard<std::mutex> locker(m_PercentageMutex);
		m_Percentage = Percentage;
		//TODO
		if (m_pKrWindow != nullptr) m_pKrWindow->UpdateUI(this);
	}

	unsigned int KrProgressBar::GetPercentage()
	{
		std::lock_guard<std::mutex> locker(m_PercentageMutex);
		return m_Percentage;
	}

	void KrProgressBar::Update()
	{
		m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_BgColor), 0, 0, GetWidth(), GetHeight());

		m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_ForeColor), 0, 0, GetWidth()*m_Percentage / 100, GetHeight());

		m_pGraphics->DrawRectangle(&Gdiplus::Pen(m_BorderColor), 0, 0, GetWidth() - 1, GetHeight() - 1);
		KrUIBase::Update();
	}
}// !namespace KrUI