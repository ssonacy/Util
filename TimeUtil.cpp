#include "stdafx.h"
#include "TimeUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

namespace Time
{
	CTime AddSec( const CTime& Now , int Sec )
	{
		return CTime( Now + CTimeSpan( 0 , 0 , 0 , Sec ) );
	}

	Second Subtract( const CTime& lhs , const CTime& rhs )
	{
		CTimeSpan rest = lhs - rhs;
		return (Second)rest.GetTotalSeconds();
	}
	
	Second  SubtractFromNow( const CTime& rhs )
	{
		return Subtract( CTime::GetCurrentTime() , rhs );
	}

	CString GetNowFileName( TCHAR DateStep , TCHAR BetweenStep ,TCHAR TimeStep )
	{
		SYSTEMTIME st = { 0 , };
		GetLocalTime( &st );

		CString DateTimeString;
		DateTimeString.Format( _T("%04d%c%02d%c%02d%c%02d%c%02d%c%02d%c%03d"), 
			st.wYear , DateStep , st.wMonth , DateStep , st.wDay ,
			BetweenStep ,
			st.wHour , TimeStep , st.wMinute , TimeStep , st.wSecond , TimeStep , st.wMilliseconds );

		return DateTimeString;
	}

	CString GetFileName( const CTime& Time , const CString& Ext )
	{
		return Time.Format( _T("%Y_%m_%d_%H_%M_%S") ) + _T(".") + Ext;
	}

	CString GetNowDateTimeString( CTime Now )
	{
		return Now.Format( _T("%H:%M:%S") );
	}
};