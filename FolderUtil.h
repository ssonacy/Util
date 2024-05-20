#pragma once

#include <functional>

// SearchFunction �Լ��� TRUE ���� �ϸ� ���� ã�⸦ ��� �����ϸ�, FALSE �����ϸ� �ߴܵȴ�.
using SearchFunction = std::function<BOOL(const WIN32_FIND_DATA&)>;

namespace FolderUtil
{
	CString GetFullDirectoryPath( BOOL LastSlash = TRUE );
	void    CreateFolder( const CString& FolderPath , BOOL FirstDeleteFolder );
	BOOL	ExistFolder( LPCTSTR FolerPath );

	CString ShowFolderSelectDialog( HWND Parent , LPCTSTR Title , LPCTSTR FirstFolderPath );
	int		ShowFileSelectDialog( BOOL SingleSelect , LPCTSTR Filter , CStringArray& SelectedFile );
	int     CopyFolderToFolder( CString SrcFolder , CString DestFolder , LPCTSTR Title );
	void    CreateFolder( const CString& FolderPath , BOOL FirstDeleteFolder );
	void    DeleteFolder( const CString& FolerPath);

	BOOL Search( CString DirPath , const CString& Ext , SearchFunction Func );
};