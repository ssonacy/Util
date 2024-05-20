#pragma once

using Second = int;

namespace Time
{
	CTime	AddSec( const CTime& Now , int Sec );
	Second  Subtract( const CTime& lhs , const CTime& rhs );
	Second  SubtractFromNow( const CTime& rhs );

	CString GetNowFileName( TCHAR DateStep , TCHAR BetweenStep ,TCHAR TimeStep );
	CString GetFileName( const CTime& Time , const CString& Ext );
	CString GetNowDateTimeString( CTime Now = CTime::GetCurrentTime() );
};