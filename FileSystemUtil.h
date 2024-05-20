#pragma once
#include <utility>

using FileBuffer = std::pair<LPBYTE,DWORD>;
using FileSize   = __int64;

namespace File
{
	DWORD Write( HANDLE h , LPBYTE pData , int Size , DWORD* ErrorCode );
	DWORD Write( LPCTSTR path , LPBYTE pData , int Size , DWORD* ErrorCode );
	DWORD WriteLn( HANDLE h , LPBYTE pData , int Size , DWORD* ErrorCode );
	DWORD WriteLn( LPCTSTR path , LPBYTE pData , int Size , DWORD* ErrorCode );

	CharPtr    Read( HANDLE h , DWORD NullCharSize , DWORD* ErrorCode , DWORD* ReadSize );
	FileBuffer Read( LPCTSTR path , DWORD* ErrorCode );
	HandlePtr  GetHandle( LPCTSTR path );
		
	BOOL    Delete( LPCTSTR FilePath );
	BOOL    ChageName( LPCTSTR FilePath , LPCTSTR NewFilePath , BOOL FirstDeleteNewFilePath );

	BOOL IsExist( LPCTSTR path , HandlePtr* Result );

	FileSize GetSize( LPCTSTR FilePath );
};

namespace USB
{
	CString GetLastDriverName( DWORD* Error );
};