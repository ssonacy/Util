#include "stdafx.h"
#include "UIUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

namespace UIUtil
{
	float GetFloat( CWnd* pParent , int ID )
	{
		TCHAR Buffer[64] = { 0 , };
		pParent->GetDlgItemText( ID , Buffer , _countof(Buffer) );
		return (float)_ttof(Buffer);
	}

	double  GetDouble( CWnd* pParent , int ID )
	{
		TCHAR Buffer[64] = { 0 , };
		pParent->GetDlgItemText( ID , Buffer , _countof(Buffer) );
		return _ttof(Buffer);
	}

	int GetInt( CWnd* pParent , int ID )
	{
		return (int)pParent->GetDlgItemInt( ID );
	}

	CString GetString( CWnd* pParent , int ID )
	{
		TCHAR Buffer[512] = { 0 , };
		pParent->GetDlgItemText( ID , Buffer , _countof(Buffer) );
		return CString( Buffer );
	}

	BOOL IsCheck( CWnd* pParent , int ID )
	{
		return ((CButton*)pParent->GetDlgItem( ID ))->GetCheck() == BST_CHECKED;
	}

	void SetCheck( CWnd* pParent , int ID , BOOL Check )
	{
		((CButton*)pParent->GetDlgItem( ID ))->SetCheck( Check ? BST_CHECKED : BST_UNCHECKED );
	}

	CRect GetRelativeRect( CWnd* pParent , int ChildID )
	{
		CRect ChildRect;

		CWnd* pChildCtrl = pParent->GetDlgItem( ChildID );
		pChildCtrl->GetClientRect( &ChildRect );
		pChildCtrl->ClientToScreen( &ChildRect );
		pParent->ScreenToClient( &ChildRect );
		
		return ChildRect;
	}
};