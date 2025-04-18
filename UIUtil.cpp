#include "stdafx.h"
#include "UIUtil.h"
#include <initializer_list>

namespace UI
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

	void SetDouble( CWnd* pParent , int ID , double Value , int Point )
	{
		pParent->SetDlgItemText( ID , Str::ToString( Value , Point ) );
	}

	int GetInt( CWnd* pParent , int ID )
	{
		return (int)pParent->GetDlgItemInt( ID );
	}

	void SetInt( CWnd* pParent , int ID , int Value )
	{
		pParent->SetDlgItemInt( ID , Value );
	}

	CString GetString( CWnd* pParent , int ID )
	{
		TCHAR Buffer[512] = { 0 , };
		pParent->GetDlgItemText( ID , Buffer , _countof(Buffer) );
		return CString( Buffer );
	}

	void SetString( CWnd* pParent , int ID , const CString& Value )
	{
		pParent->SetDlgItemText( ID , Value );
	}

	BOOL IsCheck( CWnd* pParent , int ID )
	{
		return ((CButton*)pParent->GetDlgItem( ID ))->GetCheck() == BST_CHECKED;
	}

	void SetCheck( CWnd* pParent , int ID , BOOL Check )
	{
		((CButton*)pParent->GetDlgItem( ID ))->SetCheck( Check ? BST_CHECKED : BST_UNCHECKED );
	}

	void SetEditCursorPos( CWnd* pParent , int ID , int Pos )
	{
		CEdit* pEdit = (CEdit*)pParent->GetDlgItem( ID );
		pEdit->SetSel( Pos , Pos );
	}

	void SetEditCursorLastPos( CWnd* pParent , int ID )
	{
		SetEditCursorPos( pParent , ID , pParent->GetDlgItem( ID )->GetWindowTextLength() );
	}

	void Enable( CWnd* pParent , int ID )
	{
		pParent->GetDlgItem( ID )->EnableWindow( TRUE );
	}

	void Enable( CWnd* pParent , std::initializer_list<int> IDs )
	{
		typename std::initializer_list<int>::const_iterator cur = IDs.begin();
		typename std::initializer_list<int>::const_iterator end = IDs.end();

		for ( ; cur != end ; ++cur ) UI::Enable( pParent , (*cur) );
	}

	void Disable( CWnd* pParent , int ID )
	{
		pParent->GetDlgItem( ID )->EnableWindow( FALSE );
	}

	void Disable( CWnd* pParent , std::initializer_list<int> IDs )
	{
		typename std::initializer_list<int>::const_iterator cur = IDs.begin();
		typename std::initializer_list<int>::const_iterator end = IDs.end();

		for ( ; cur != end ; ++cur ) UI::Disable( pParent , (*cur) );
	}

	BOOL IsEmpty( CWnd* pParent, int ID )
	{
		return UI::GetString( pParent , ID ).IsEmpty();
	}

	BOOL IsEmpty( CWnd* pParent , std::initializer_list<int> Controls )
	{
		typename std::initializer_list<int>::iterator cur = Controls.begin();
		typename std::initializer_list<int>::iterator end = Controls.end();

		for ( ; cur != end ; ++cur ) 
		{
			if ( IsEmpty( pParent , (*cur) ) ) return TRUE;
		}

		return FALSE;
	}

	CString CompactPrePath( CWnd* pParent , int ID , const CString& Path )
	{
		CWnd* pWnd = pParent->GetDlgItem(ID);
		CRect Rect = UI::GetClientRect( pParent , ID );

		CDC*	pDC		  = pWnd->GetDC();
		CString strResult = Path;

		CSize size = pDC->GetTextExtent(strResult);
		while ( size.cx > Rect.Width() && strResult.GetLength() > 4 )
		{
			strResult = _T("...") + strResult.Right( strResult.GetLength() - 4 );
			size	  = pDC->GetTextExtent(strResult);
		}

		pWnd->ReleaseDC(pDC);
		return strResult;
	}

	CString CompactMidPath( CWnd* pParent , int ID , const CString& Path )
	{
		CWnd* pWnd = pParent->GetDlgItem(ID);
		CRect Rect = UI::GetClientRect( pParent , ID );

		CDC*	pDC		  = pWnd->GetDC();
		CString strResult = Path;

		PathCompactPath( pDC->GetSafeHdc() , strResult.GetBuffer(MAX_PATH) , Rect.Width() );
		strResult.ReleaseBuffer();

		pWnd->ReleaseDC(pDC);
		return strResult;
	}

	CString CompactSuffPath( CWnd* pParent , int ID , const CString& Path )
	{
		CWnd* pWnd = pParent->GetDlgItem(ID);
		CRect Rect = UI::GetClientRect( pParent , ID );

		CDC*	pDC		  = pWnd->GetDC();
		CString strResult = Path;

		CSize size = pDC->GetTextExtent( _T("A") );
		PathCompactPathEx( strResult.GetBuffer(MAX_PATH) , Path , Rect.Width() / size.cx, 0 );
		strResult.ReleaseBuffer();

		pWnd->ReleaseDC(pDC);
		return strResult;
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

	CRect GetClientRect( CWnd* pParent, int ID )
	{
		CRect Rect;
		pParent->GetDlgItem( ID )->GetClientRect( &Rect );

		return Rect;
	}

	CRect GetWindowRect( CWnd* pParent, int ID )
	{
		CRect Rect;
		pParent->GetDlgItem( ID )->GetWindowRect( &Rect );

		return Rect;
	}
};