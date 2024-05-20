#include "stdafx.h"
#include "FileSystemUtil.h"
#include <filesystem>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

namespace File
{
	DWORD Write( LPCTSTR path , LPBYTE pData , int Size , DWORD* ErrorCode )
	{
		HandlePtr handle = GetHandle( path );
		if ( handle.Get() == INVALID_HANDLE_VALUE )
		{
			if ( ErrorCode ) *ErrorCode = GetLastError();
			return 0;
		}

		return Write( handle.Get() , pData , Size , ErrorCode );
	}

	DWORD Write( HANDLE h , LPBYTE pData , int Size , DWORD* ErrorCode )
	{
		DWORD written_byte = 0;
		if ( !::WriteFile( h , pData , Size , &written_byte , NULL ) )
		{
			if ( ErrorCode ) *ErrorCode = GetLastError();
			return 0;
		}

		return written_byte;
	}

	DWORD WriteLn( LPCTSTR path , LPBYTE pData , int Size , DWORD* ErrorCode )
	{
		HandlePtr handle = GetHandle( path );
		if ( handle.Get() == INVALID_HANDLE_VALUE )
		{
			if ( ErrorCode ) *ErrorCode = GetLastError();
			return 0;
		}

		return WriteLn( handle.Get() , pData , Size , ErrorCode );	
	}

	DWORD WriteLn( HANDLE h , LPBYTE pData , int Size , DWORD* ErrorCode )
	{
		SetFilePointer( h , 0 , NULL , FILE_END );
		DWORD Written = Write( h , pData , Size , ErrorCode );
		if ( Written <= 0 )
		{
			if ( ErrorCode ) *ErrorCode = GetLastError();
			return 0;
		}

		return Written;
	}

	CharPtr Read( HANDLE h , DWORD NullCharSize , DWORD* ErrorCode , DWORD* ReadSize )
	{
		DWORD FileSize  = ::GetFileSize( h , NULL );
		DWORD read_byte = 0;

		CharPtr Buffer( new CHAR[FileSize + NullCharSize]{ 0 , } );
		if ( !::ReadFile( h , (LPVOID)Buffer.Get() , FileSize , &read_byte , NULL ) )
		{
			if ( ErrorCode ) *ErrorCode = GetLastError();

			return CharPtr(NULL);
		}

		if ( ErrorCode ) *ErrorCode = GetLastError();
		if ( ReadSize  ) *ReadSize  = read_byte;

		return std::move(Buffer);
	}

	FileBuffer Read( LPCTSTR path , DWORD* ErrorCode )
	{
		HandlePtr handle = GetHandle( path );
		if ( handle.Get() == INVALID_HANDLE_VALUE )
		{
			if ( ErrorCode ) *ErrorCode = GetLastError();
			return FileBuffer(NULL,0);
		}

		DWORD FileSize = ::GetFileSize( handle.Get() , NULL );
		ArrayPtr<BYTE> BufferPtr( new BYTE[FileSize] { 0 , } );

		DWORD ReadByte = 0;
		if ( !::ReadFile( handle.Get() , (LPVOID)BufferPtr.Get() , FileSize , &ReadByte , NULL ) )
		{
			if ( ErrorCode ) *ErrorCode = GetLastError();

			return FileBuffer(NULL,0);
		}
		
		return FileBuffer( BufferPtr.Reset(NULL) , ReadByte );
	}

	HandlePtr GetHandle( LPCTSTR path )
	{
		return HandlePtr( CreateFile( path , GENERIC_READ|GENERIC_WRITE , FILE_SHARE_READ | FILE_SHARE_WRITE , NULL , OPEN_ALWAYS , FILE_ATTRIBUTE_NORMAL , NULL ) );
	}

	BOOL Delete( LPCTSTR FilePath )
	{
		return ::DeleteFile( FilePath );
	}

	BOOL  ChageName( LPCTSTR FilePath , LPCTSTR NewFilePath , BOOL FirstDeleteNewFilePath )
	{
		if ( FirstDeleteNewFilePath ) 
			Delete(NewFilePath);

		return MoveFile( FilePath , NewFilePath );
	}

	BOOL IsExist( LPCTSTR path , HandlePtr* Result )
	{
		WIN32_FIND_DATA FileInfo = { 0 , };

		HANDLE Searching = FindFirstFile( path , &FileInfo );
		if ( Searching == INVALID_HANDLE_VALUE  ) return FALSE;
	
		FindClose( Searching );

		if ( Result )
			*Result = std::move( File::GetHandle( path ) );

		return TRUE;
	}

	FileSize GetSize( LPCTSTR FilePath )
	{
		HandlePtr handle = GetHandle( FilePath );
		if ( handle.Get() == INVALID_HANDLE_VALUE ) return 0;		

		DWORD High = 0;
		DWORD Low  = ::GetFileSize( handle.Get() , &High );

		FileSize Ret = High;

		return (Ret << 32) | Low;
	}

};

namespace USB
{
	CString GetLastDriverName( DWORD* Error )
	{
		TCHAR Driver[MAX_PATH] = { 0 , };
        if ( GetLogicalDriveStrings( MAX_PATH , Driver ) <= 0 )
        {
            if ( Error ) *Error = GetLastError();
            return CString();
        }

        HighOrderVector<CString> Tokens = Str::Tokenizer( Driver , _T('\0') );
		if ( Tokens.empty() ) return _T("");

        HighOrderVector<CString>::iterator Ret = std::find_if( Tokens.begin() , Tokens.end() , []( const CString& Driver )
        {
            return ( GetDriveType( Driver ) == DRIVE_REMOVABLE );
        });

        return Ret == Tokens.end() ? _T("") : (*Ret);
	}
};