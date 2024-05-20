#pragma once

#include <afxbutton.h>

class CMFCCheckButton : public CMFCButton
{
public:

	CMFCCheckButton() : m_bChecked(FALSE) {}
	
	void SetCheck( COLORREF Color , BOOL Check )
	{
		SetFaceColor( Color );
		m_bChecked = Check;
	}

	void Toggle()
	{
		BOOL IsCheck = IsChecked();
		SetCheck( IsCheck ? BtnColor::Uncheck : BtnColor::Check , !IsCheck );
	}

	inline BOOL IsChecked() const { return m_bChecked; }

private:

	BOOL m_bChecked;
};

