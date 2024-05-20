#pragma once

#include "HighOrderContainer.h"

namespace Str // String Util
{
	CStringW ToStringW( int Value );
	CStringW ToStringW( float Value );
	CStringW ToStringW( float Value , int Point );
	CStringW ToStringW( double Value );
	CStringW ToStringW( double Value , int Point );

	CStringA ToStringA( int Value );
	CStringA ToStringA( float Value );
	CStringA ToStringA( float Value , int Point );
	CStringA ToStringA( double Value );
	CStringA ToStringA( double Value , int Point );

	int		ToInt( LPCTSTR Str );
	double	ToDouble( LPCTSTR Str );

	HighOrderVector<CStringW> TokenizerW( const CStringW& Str , WCHAR Step );
	HighOrderVector<CStringA> TokenizerA( const CStringA& Str , CHAR Step );

	HighOrderVector<CStringW> TokenizerW( const CStringW& Str , const CStringW& Step );
	HighOrderVector<CStringA> TokenizerA( const CStringA& Str , const CStringA& Step );

	int		HexToIntW( WCHAR Hex );
	int		HexToIntA( CHAR Hex );
	int		HexToIntW( CStringW Hex );
	int		HexToIntA( CStringA Hex );

	CString IntToHex( int Value , int MinimumLen );
	CString ByteToHex( const BYTE* pSrc , int Size );

	BOOL HasPrefixW( const CStringW& String , const CStringW& Prefix );
	BOOL HasSuffixW( const CStringW& String , const CStringW& Suffix );

	BOOL HasPrefixA( const CStringA& String , const CStringA& Prefix );
	BOOL HasSuffixA( const CStringA& String , const CStringA& Suffix );

	CStringA _A( LPCSTR Format , ... );
	CStringW _W( LPCWSTR Format , ... );
};

#define STR_W   Str::_W
#define STR_A	Str::_A

#ifdef _UNICODE
		#define ToString	ToStringW
		#define HasPrefix	HasPrefixW
		#define HasSuffix	HasSuffixW
		#define HexToInt	HexToIntW
		#define Tokenizer	TokenizerW
		#define STR			STR_W
#elif
		#define ToString	ToStringA
		#define HasPrefix	HasPrefixA
		#define HasSuffix	HasSuffixA
		#define HexToInt	HexToIntA
		#define Tokenizer	TokenizerA
		#define STR			STR_A
#endif // _UNICODE

class HexString
{
public:

	HexString() = default;
	HexString( const CString& Hex ) : m_Hex(Hex) {}
	HexString( int Value , int Length ) : m_Hex( Str::IntToHex( Value , Length) ) {}
	~HexString() = default;

	inline void SetHexString( const CString& Hex ) { m_Hex = Hex; }

	int		 ToInt()	const	{ return Str::HexToInt( m_Hex ); }
	CString  ToString() const	{ return m_Hex; }

private:

	CString m_Hex;
};