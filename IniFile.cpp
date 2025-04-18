
#include "stdafx.h"
#include "IniFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CIniFile

CIniFile::CIniFile(LPCTSTR	strIniFileName,		// [in] new file name
				UINT		iMaxStringLength)	// [in] max length of a string that can be wtritten/read to/from the INI file by this instance
				: m_MAXSTRLEN(iMaxStringLength)
{
	SetIniFileName(strIniFileName);
}


CIniFile::~CIniFile()
{
}

/////////////////////////////////////////////////////////////////////////////
// CIniFile operations

// PURPOSE: Get the name of the INI file.
CString	CIniFile::GetIniFileName()
{
	return m_strFileName;
}

// PURPOSE: Set the name of the INI file.
void
CIniFile::SetIniFileName(LPCTSTR lpIniFileName)	// [in] new file name
{
	m_strFileName = lpIniFileName;
}

// PURPOSE: Get the status of the ini file.  
//			This can be used, for example, to check the existence of the file.
BOOL
CIniFile::GetStatus(CFileStatus& rStatus)	// [out] A reference to a user-supplied CFileStatus structure that will receive the status information.
{
	BOOL bRetVal = FALSE;
	bRetVal = CFile::GetStatus(m_strFileName, rStatus);
	return bRetVal;
}


// PURPOSE:			Create a new section.
// NOTE:	If the INI file doesn't exist, this method creates it.
//			::WritePrivateProfileSection() can create keys with duplicate names.  That can be viewed asa bug,
BOOL		// TRUE, if the API function call was successful.  FALSE, if there was an error.  To get extended error information, call ::GetLastError(). 
CIniFile::WriteSection(LPCTSTR lpSection,	// [in] name of the new section
						LPCTSTR lpData)		// [in] for the new section.  See help for the ::WritePrivateProfileSection(...) function.
{
	BOOL bRetVal = FALSE;
	bRetVal = ::WritePrivateProfileSection(lpSection, lpData, m_strFileName);
	return bRetVal;
}

// PURPOSE:	Write string data to the INI file
BOOL		// TRUE, if the API function call was successful.  FALSE, if there was an error.  To get extended error information, call ::GetLastError(). 
CIniFile::WriteString(LPCTSTR lpSection,	// [in] section
						LPCTSTR lpKey,		// [in] key. If key with this name doesn't exist, it's created.
						LPCTSTR lpString)	// [in] String to be written into the file.  If this parameter is NULL, the key pointed to by the lpKeyName parameter is deleted.
{
	ASSERT(lpString == NULL || _tcslen(lpString) < m_MAXSTRLEN);
	return ::WritePrivateProfileString(lpSection, lpKey, lpString, m_strFileName);
}

// PURPOSE:	Write an integer (signed) to the INI file
BOOL		// TRUE, if the API function call was successful.  FALSE, if there was an error.  To get extended error information, call ::GetLastError(). 
CIniFile::WriteNumber(LPCTSTR lpSection, 	// [in] section name
						LPCTSTR lpKey, 		// [in] key name
						INT iValue)			// [in] integer value to be written to the INI file
{
	CString	str;
	str.Format(_T("%d"), iValue);
	return WriteString(lpSection, lpKey, str);
}

// PRUPOSE: Write the data into the specified key in the INI file.
BOOL		// TRUE, if the API function call was successful.  FALSE, if there was an error.  To get extended error information, call ::GetLastError(). 
CIniFile::WriteStruct(LPCTSTR lpSection,	// [in] pointer to section name
						LPCTSTR lpKey,		// [in] pointer to key name
						LPVOID lpStruct,	// [in] pointer to buffer that contains data to add
						UINT iSizeStruct)	// [in] size, in bytes, of the buffer
{
	BOOL bRetVal = FALSE;
	bRetVal = ::WritePrivateProfileStruct(lpSection, lpKey, lpStruct, iSizeStruct, m_strFileName);
	return bRetVal;
}

// PURPOSE:	Write a float to the INI file.
BOOL		// TRUE, if the API function call was successful.  FALSE, if there was an error.  To get extended error information, call ::GetLastError(). 
CIniFile::WriteNumber(LPCTSTR	lpSection,	// [in] section name
						LPCTSTR	lpKey,		// [in] key name
						FLOAT		fValue)	// [in] floating point value to be written to the INI file
{
	CString	str;
	str.Format(_T("%f"), fValue);
	return WriteString(lpSection, lpKey, str);
}

BOOL CIniFile::WriteNumber(LPCTSTR lpSection, LPCTSTR lpKey, DOUBLE Value)
{
	CString	str;
	str.Format(_T("%f"), Value);
	return WriteString(lpSection, lpKey, str);
}

// PURPOSE:	Remove a key from a specified section.
BOOL
CIniFile::RemoveKey(LPCTSTR lpSection,		// [in] section name
					LPCTSTR lpKey)			// [in] key name
{
	return WriteString(lpSection, lpKey, NULL);
}


// PURPOSE:	Read an integer to the INI file.
// NOTE:	The MSDN article on ::GetPrivateProfileInt(...) says: "If the value of the key is less than zero, the return value is zero."
//			However, ::GetPrivateProfileInt returns negative integers just fine.
INT
CIniFile::GetInt(LPCTSTR lpSection,			// [in] section name
				LPCTSTR lpKey,				// [in] key name
				const INT iDefaultValue)	// [in] default value, which is returned, if the key is not found
{
	INT iRet = (INT)::GetPrivateProfileInt(lpSection, lpKey, iDefaultValue, m_strFileName);
	// ::GetLastError() is of no use here, because ::GetPrivateProfileInt() doesn't set an error-code.
	return iRet;
}

// PURPOSE:	Read a string from the INI file.
BOOL		// TRUE, if successful.  FALSE otherwise.
CIniFile::GetString(LPCTSTR lpSection,		// [in] section name
					LPCTSTR lpKey,			// [in] key name
					CString& strRet,		// [out] CString that receives the tring from the INI file
					LPCTSTR lpDefault)		// [in] default string, which is copied into strRet, if the key is not found.  NOTE: this pointer can't be NULL.
{
	ASSERT(lpDefault != NULL);
	ASSERT(_tcslen(lpDefault) < m_MAXSTRLEN);
	return CIniFile::GetString(lpSection, lpKey, strRet, lpDefault, m_MAXSTRLEN);
}

CString CIniFile::GetString(LPCTSTR lpSection, LPCTSTR lpKey)
{
	CString Ret;
	GetString( lpSection , lpKey , Ret , _T("") );
	return Ret;
}

// PURPOSE:	Read a string from the INI file. (Helper function.)
// NOTE:	The calling code should check if strRet == lpDefault.
BOOL		// TRUE, if API call successful (incl. the case, when strRet == lpDefault).  
			// FALSE otherwise (incl. memory exception
CIniFile::GetString(LPCTSTR lpSection,		// [in] section name
					LPCTSTR lpKey,			// [in] key name
					CString& strRet,		// [out] CString that receives the tring from the INI file
					LPCTSTR lpDefault,		// [in] default string, which is copied into strRet, if the key is not found.  NOTE: this pointer can't be NULL. 
					const DWORD iSize)		// [in] buffer size
{
	LPTSTR pBuffer;
	TRY
	{
		pBuffer = strRet.GetBuffer(iSize);
	}
		CATCH(CMemoryException, pExc)	// GetBuffer() can throw a memory exceprion
	{
		THROW(pExc);				// rethrow
		return FALSE;
	}
	END_CATCH

	memcpy(pBuffer + iSize - 2, "xx", 2);	// initialize the last 2 characters on the buffer with something other than \0
	DWORD iRet = ::GetPrivateProfileString(lpSection, lpKey, lpDefault, pBuffer, iSize, m_strFileName);
	ASSERT(iRet < iSize);
	BOOL bRet = (memcmp(pBuffer + iSize - 2, "\0\0", 2) != 0);	// check the last 2 characters of the buffer.
	strRet.ReleaseBuffer();
	return bRet;
}

// PURPOSE:	Read an integer to the INI file.
FLOAT
CIniFile::GetFloat(LPCTSTR lpSection,		// [in] section name
					LPCTSTR lpKey,			// [in] key name
					const FLOAT fDefaultValue) // [in] default value, which is returned, if the key is not found, or if there's a memory exception
{
	return (FLOAT)GetDouble( lpSection , lpKey , fDefaultValue );
}

FLOAT CIniFile::GetFloat(LPCTSTR lpSection, LPCTSTR lpKey, FLOAT fDefaultValue, INT iPrecision)
{
	return (FLOAT)GetDouble(lpSection, lpKey, fDefaultValue, iPrecision );
}
DOUBLE  CIniFile::GetDouble(LPCTSTR lpSection, LPCTSTR lpKey, DOUBLE fDefaultValue)
{
	const int MAXFLOATDIGS = 512;
	CString strRet, strDefault;
	strDefault.Format(_T("%f"), fDefaultValue);
	BOOL bRet = CIniFile::GetString(lpSection, lpKey, strRet, strDefault, MAXFLOATDIGS);
	return bRet ? _ttof(strRet) : fDefaultValue;
}
DOUBLE  CIniFile::GetDouble(LPCTSTR lpSection, LPCTSTR lpKey, DOUBLE fDefaultValue, INT iPrecision)
{
	int MAXFLOATDIGS = 512;

	CString PrecisionDigit;
	PrecisionDigit.Format(_T("%d"), iPrecision);

	CString FormatString;
	FormatString.Append(_T("%."));
	FormatString.Append(PrecisionDigit);
	FormatString.AppendChar(_T('f'));

	DOUBLE retValue = GetDouble(lpSection, lpKey, fDefaultValue);

	CString ret;
	ret.Format(FormatString, retValue);
	return _ttof(ret);
}
// PURPOSE:	Read a struct from the INI file
BOOL
CIniFile::GetStruct(LPCTSTR lpSection,		// [in] section name 		  
					LPCTSTR lpKey, 			// [in]	key name	  
					LPVOID	lpRetStruct,	// [out] pointer to thye return buffer
					const UINT iSizeStruct) // [in] size of the return buffer
{
	ASSERT(lpRetStruct != NULL);
	ASSERT(iSizeStruct > 0);
	return ::GetPrivateProfileStruct(lpSection, lpKey, lpRetStruct, iSizeStruct, m_strFileName);
}

// PURPOSE:	Get the list of section names from the INI file.
void
CIniFile::GetSectionNames(CStringList& lstSectionNames)	// [out] array of section name strings
{
	// Get the section names through an API function call.
	LPTSTR lpRetBuff = new TCHAR[m_MAXSTRLEN] { 0 , };
	DWORD iRetVal = GetPrivateProfileSectionNames(lpRetBuff, m_MAXSTRLEN, m_strFileName);

	// Parse out the individual names and store them in the list
	for ( LPCTSTR p = lpRetBuff; *p != _T('\0') ; p += _tcslen(p) + 1)
	{
		lstSectionNames.AddTail(p);
	}
	delete[] lpRetBuff;
}
