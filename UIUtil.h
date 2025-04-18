#pragma once

enum BtnColor { Uncheck = RGB(240,240,240) , Check = RGB(153,153,255) };

namespace UI
{
	float	GetFloat( CWnd* pParent , int ID );

	double  GetDouble( CWnd* pParent , int ID );
	void	SetDouble( CWnd* pParent , int ID , double Value , int Point );

	CString GetString( CWnd* pParent , int ID );
	void    SetString( CWnd* pParent , int ID , const CString& Value );

	int		GetInt( CWnd* pParent , int ID );
	void    SetInt( CWnd* pParent , int ID , int Value );

	void	SetEditCursorPos( CWnd* pParent , int ID , int Pos );
	void	SetEditCursorLastPos( CWnd* pParent , int ID );

	BOOL IsCheck( CWnd* pParent , int ID );
	void SetCheck( CWnd* pParent , int ID , BOOL Check );

	void Enable( CWnd* pParent, int ID );
	void Enable( CWnd* pParent, std::initializer_list<int> IDs );

	void Disable( CWnd* pParent, int ID );
	void Disable( CWnd* pParent, std::initializer_list<int> IDs );
	
	BOOL IsEmpty( CWnd* pParent, int ID );
	BOOL IsEmpty( CWnd* pParent , std::initializer_list<int> Controls );

	CString CompactPrePath( CWnd* pParent , int ID , const CString& Path );
	CString CompactMidPath( CWnd* pParent , int ID , const CString& Path );
	CString CompactSuffPath( CWnd* pParent , int ID , const CString& Path );

	// 자식 컨트롤 Rect값을 부모의 기준 상대 Rect값으로 변환해서 리턴
	CRect GetRelativeRect( CWnd* pParent , int ChildID );

	CRect GetClientRect( CWnd* pParent, int ID );
	CRect GetWindowRect( CWnd* pParent, int ID );
};