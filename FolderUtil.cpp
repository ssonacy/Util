#include "stdafx.h"
#include "FolderUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

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

	int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
	{
		switch (uMsg) 
		{    
		case BFFM_INITIALIZED:
			{
				if ( lpData )
					SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
			}
			break;
		}
		return 0;
	}

	CString ShowFolderSelectDialog( HWND Parent , LPCTSTR Title , LPCTSTR FirstFolderPath )
	{
		BROWSEINFO  BrInfo = { 0 , };
		TCHAR		pszPathname[MAX_PATH] = { 0 , };
	
		BrInfo.hwndOwner	  = Parent;
		BrInfo.pszDisplayName = pszPathname;
		BrInfo.lpszTitle	  = Title;
		BrInfo.ulFlags		  = BIF_RETURNONLYFSDIRS;
		BrInfo.lpfn			  = BrowseCallbackProc;
		BrInfo.lParam		  = (LPARAM)FirstFolderPath;

		LPITEMIDLIST pidlBrowse = ::SHBrowseForFolder( &BrInfo );

		if ( pidlBrowse )
			SHGetPathFromIDList( pidlBrowse , pszPathname );
    
		return pszPathname;
	}

	int ShowFileSelectDialog( BOOL SingleSelect , LPCTSTR Filter , CStringArray& SelectedFile )
	{
		CFileDialog dlg( TRUE , NULL , NULL , 
						SingleSelect ? OFN_HIDEREADONLY : OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT , 
						!Filter ? _T("All Files(*.*)|*.*||") : Filter  );

		if ( IDOK != dlg.DoModal() ) return 0;

		for ( POSITION pos = dlg.GetStartPosition() ; pos != NULL ; ) 
			SelectedFile.Add( dlg.GetNextPathName(pos) );
	
		return (int)SelectedFile.GetCount();
	}

	int CopyFolderToFolder( CString SrcFolder , CString DestFolder , LPCTSTR Title )
	{
		if ( SrcFolder.IsEmpty() || DestFolder.IsEmpty() ) return FALSE;
    
		// SHFileOperation 함수에서 파일 및 폴더를 삭제할때는 파일경로 마지막에 널 문자가 2번 존재해야 한다.
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

		if ( ExistFolder( FolderPath ) ) return;

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

		HANDLE hFind	 = FindFirstFile( DirPath , &Finder );
		DWORD  LastError = GetLastError();
		
		if ( hFind == INVALID_HANDLE_VALUE ) return FALSE;

		do
		{
			if ( !Func( Finder ) ) break;

		} while ( FindNextFile( hFind , &Finder ) );

		FindClose(hFind);

		return TRUE;
	}
};