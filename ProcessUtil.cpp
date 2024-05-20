#include "stdafx.h"
#include "ProcessUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

namespace ProcessUtil
{
	namespace 
	{
		HighOrderList<HWND> _HWNDList;
	};

	HandlePtr Run( LPCTSTR WorkingDirectory , LPCTSTR OnlyExeName , DWORD* ErrorCode )
	{
		CString FullPath;
		FullPath.Format( _T("%s%s") , WorkingDirectory , OnlyExeName );

		TCHAR Path[MAX_PATH] = { 0 , };
		StringCchCopy( Path , _countof(Path) , (LPCTSTR)FullPath );

		STARTUPINFO si = { 0 , };
		si.cb = sizeof(STARTUPINFO);

		PROCESS_INFORMATION pi = { 0 , };

		BOOL  Ret = CreateProcess( NULL , Path , NULL , NULL , FALSE , NORMAL_PRIORITY_CLASS , 
								   NULL , WorkingDirectory , &si , &pi );
		DWORD LastError = GetLastError();

		if ( !Ret )
		{
			if ( ErrorCode ) *ErrorCode = LastError;

			return HandlePtr( NULL );
		}

		CloseHandle( pi.hThread );

		return HandlePtr( pi.hProcess );
	}

	BOOL EnumerateProcess( EnumProcessFunction Func )
	{
		HandlePtr SnapPtr( CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS , 0 ) );
		if ( SnapPtr.Get() == INVALID_HANDLE_VALUE ) return FALSE;

		PROCESSENTRY32 Cur = { 0 , };
		Cur.dwSize = sizeof( PROCESSENTRY32 );
		if ( !Process32First( SnapPtr.Get() , &Cur ) ) return FALSE;

		do
		{
			// 호출자가 넘겨준 함수가 FALSE을 반환할때 까지 프로세스 나열을 계속 한다.
			if ( !Func( Cur ) ) return TRUE;

		} while( Process32Next( SnapPtr.Get() , &Cur ) );

		return TRUE;
	}

	BOOL __stdcall EnumHWNDFunction( HWND h , LPARAM l )
	{
		DWORD lpdwProcessId = 0;
		GetWindowThreadProcessId( h , &lpdwProcessId );
		if( lpdwProcessId == l )
			_HWNDList.push_back( h );

		return TRUE;
	}

	HighOrderList<HWND> PIDToHWNDs( DWORD ProcessID )
	{
		_HWNDList.clear();
		EnumWindows( EnumHWNDFunction , ProcessID );
		return _HWNDList;
	}

};