#include "stdafx.h"
#include "FolderUtil.h"

namespace FolderUtil
{
	CString GetFullDirectoryPath( BOOL LastSlash )
	{
		TCHAR exe_path[MAX_PATH] = { 0 , };
		::GetModuleFileName( NULL , exe_path , MAX_PATH );
		PathRemoveFileSpec(exe_path);

		if ( LastSlash ) PathAddBackslash(exe_path);

		return CString( exe_path );
	}
	void CreateFolder( const CString& FolderPath )
	{
		SHCreateDirectoryEx( NULL , (LPCTSTR)FolderPath , NULL );
	}

	BOOL ExistFolder( LPCTSTR FolerPath )
	{
		return PathFileExists(FolerPath);
	}

	namespace Private
	{
		int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
		{
			if ( uMsg == BFFM_INITIALIZED )
				SendMessage( hwnd , BFFM_SETSELECTION , TRUE , lpData );

			return 0;
		}
	};

	CString ShowFolderSelectDialog( HWND Parent , LPCTSTR Title , LPCTSTR FirstFolderPath )
	{
		BROWSEINFO  BrInfo = { 0 , };
		TCHAR pszPathname[MAX_PATH] = { 0 , };
		TCHAR FirstFolderPathBuffer[MAX_PATH] = { 0 , };
		
		CString FirstFolder = !FirstFolderPath ? FolderUtil::GetFullDirectoryPath() : FirstFolderPath;
		_tcscpy_s( FirstFolderPathBuffer , MAX_PATH , (LPCTSTR)FirstFolder );

		BrInfo.hwndOwner	  = Parent;
		BrInfo.pszDisplayName = pszPathname;
		BrInfo.lpszTitle	  = Title;
		BrInfo.ulFlags		  = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
		BrInfo.lpfn			  = Private::BrowseCallbackProc;
		BrInfo.lParam		  = (LPARAM)(LPCTSTR)FirstFolderPathBuffer;

		LPITEMIDLIST pidlBrowse = ::SHBrowseForFolder( &BrInfo );
		if ( !pidlBrowse ) return _T("");

		TCHAR SelectedPath[MAX_PATH] = { 0 , };
		SHGetPathFromIDList( pidlBrowse , SelectedPath );
		CoTaskMemFree( pidlBrowse );
		
		return SelectedPath;
	}

	int ShowFileSelectDialog( BOOL SingleSelect , LPCTSTR Filter , CStringArray& SelectedFile )
	{
		CFileDialog dlg( TRUE , NULL , NULL , 
						SingleSelect ? OFN_HIDEREADONLY : OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT , 
						!Filter ? _T("All Files(*.*)|*.*||") : Filter , NULL , 0 , FALSE  );

		if ( IDOK != dlg.DoModal() ) return 0;

		for ( POSITION pos = dlg.GetStartPosition() ; pos != NULL ; ) 
			SelectedFile.Add( dlg.GetNextPathName(pos) );
	
		return (int)SelectedFile.GetCount();
	}

	int CopyFolderToFolder( CString SrcFolder , CString DestFolder , LPCTSTR Title )
	{
		if ( SrcFolder.IsEmpty() || DestFolder.IsEmpty() ) return FALSE;
    
		// SHFileOperation �Լ����� ���� �� ������ �����Ҷ��� ���ϰ�� �������� �� ���ڰ� 2�� �����ؾ� �Ѵ�.
		SrcFolder.AppendChar( _T('\0') );
		DestFolder.AppendChar( _T('\0') );

		SHFILEOPSTRUCT shfo = { 0 , };

		shfo.hwnd   = AfxGetMainWnd()->m_hWnd;
		shfo.wFunc  = FO_COPY;
		shfo.pTo    = DestFolder;
		shfo.pFrom  = SrcFolder;
		shfo.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_RENAMEONCOLLISION;

		shfo.lpszProgressTitle = Title;

		return SHFileOperation( &shfo );  // zero is success
	}

	void CreateFolder( const CString& FolderPath , BOOL FirstDeleteFolder )
	{
		if ( FirstDeleteFolder )
			DeleteFolder( FolderPath );

		SHCreateDirectoryEx( NULL , (LPCTSTR)FolderPath , NULL );
	}

	void  DeleteFolder( const CString& FolerPath )
	{
		CFileFind Finder;
		BOOL Working = Finder.FindFile( FolerPath + _T("\\*.*") );
		while (Working) 
		{
			Working = Finder.FindNextFile();
			if ( Finder.IsDots() ) continue;

			CString FilePath = Finder.GetFilePath();
			if (Finder.IsDirectory())  DeleteFolder(FilePath);
			else					   DeleteFile(FilePath);
		}
		Finder.Close();
		RemoveDirectory(FolerPath);
	}

	BOOL Search( CString DirPath , const CString& Ext , SearchFunction Func )
	{
		TCHAR LastCh = DirPath.GetAt( DirPath.GetLength() - 1 );
		if ( LastCh != _T('\\') ) DirPath.AppendChar( _T('\\') );

		if ( Ext.IsEmpty() ) DirPath += _T("*.*");
		else				 DirPath += _T("*.") + Ext;
		
		WIN32_FIND_DATA Finder = { 0 , };
		HANDLE hFind = FindFirstFile( DirPath , &Finder );
		DWORD LastError = GetLastError();
		
		// FindFirstFile �Լ��� INVALID_HANDLE_VALUE(-1)�� ���� �ϴ� ���� �ΰ���.
		// 1. FindFirstFile �Լ� ȣ�� ��ü�� ����.
		// 2. ã������ ���� ����.
		// �ΰ��� ��쿡 ���� �к��� GetLastError ���ϰ��� �߰������� Ȯ�� �ʿ�.
		// 2���� ��� GetLastError �Լ��� ERROR_FILE_NOT_FOUND(2) ����.
		if ( hFind == INVALID_HANDLE_VALUE ) return FALSE;		// 1��, 1���� ��� �Լ� ȣ�� ����
		if ( LastError == ERROR_FILE_NOT_FOUND ) return TRUE;	// 2��, 2���� ��� �Լ� ȣ�� ����
		
		do
		{
			if ( !Func( Finder ) ) break;

		} while ( FindNextFile( hFind , &Finder ) );

		FindClose(hFind);

		return TRUE;
	}
};