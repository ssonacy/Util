#pragma once

enum BtnColor { Uncheck = RGB(240,240,240) , Check = RGB(153,153,255) };

namespace UIUtil
{
	float	GetFloat( CWnd* pParent , int ID );
	double  GetDouble( CWnd* pParent , int ID );
	int		GetInt( CWnd* pParent , int ID );
	CString GetString( CWnd* pParent , int ID );

	BOOL IsCheck( CWnd* pParent , int ID );
	void SetCheck( CWnd* pParent , int ID , BOOL Check );

	// �ڽ� ��Ʈ�� Rect���� �θ��� ���� ��� Rect������ ��ȯ�ؼ� ����
	CRect GetRelativeRect( CWnd* pParent , int ChildID );
};