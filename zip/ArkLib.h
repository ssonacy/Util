////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
///                                      Ark Library Wrapper class
/// 
/// @author   parkkh
/// @date     Thursday, January 07, 2010  11:18:16 AM
/// 
/// Copyright(C) 2008-2021 Bandisoft, All rights reserved.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _ARK_LIB_H_
#define _ARK_LIB_H_

#include "Ark.h"

#ifdef _M_ARM64
#	ifdef _DEBUG
#		define ARK_DLL_FILE_NAME				_T("ark.a64.debug.dll")
#		define ARK_LGPLDLL_FILE_NAME			_T("ark.a64.lgpl.debug.dll")
#	else
#		define ARK_DLL_FILE_NAME				_T("ark.a64.dll")
#		define ARK_LGPLDLL_FILE_NAME			_T("ark.a64.lgpl.dll")
#	endif
#	define ARK_DLL_RELEASE_FILE_NAME			_T("ark.a64.dll")
#	define ARK_LGPLDLL_RELEASE_FILE_NAME		_T("ark.a64.lgpl.dll")
#elif defined(_WIN64)
#	ifdef _DEBUG
#		define ARK_DLL_FILE_NAME				_T("ark.x64.debug.dll")
#		define ARK_LGPLDLL_FILE_NAME			_T("ark.x64.lgpl.debug.dll")
#	else
#		define ARK_DLL_FILE_NAME				_T("ark.x64.dll")
#		define ARK_LGPLDLL_FILE_NAME			_T("ark.x64.lgpl.dll")
#	endif
#	define ARK_DLL_RELEASE_FILE_NAME			_T("ark.x64.dll")
#	define ARK_LGPLDLL_RELEASE_FILE_NAME		_T("ark.x64.lgpl.dll")
#elif defined(_WIN32)
#	ifdef _DEBUG
#		define ARK_DLL_FILE_NAME				_T("ark.x86.debug.dll")
#		define ARK_LGPLDLL_FILE_NAME			_T("ark.x86.lgpl.debug.dll")
#	else
#		define ARK_DLL_FILE_NAME				_T("ark.x86.dll")
#		define ARK_LGPLDLL_FILE_NAME			_T("ark.x86.lgpl.dll")
#	endif
#	define ARK_DLL_RELEASE_FILE_NAME			_T("ark.x86.dll")
#	define ARK_LGPLDLL_RELEASE_FILE_NAME		_T("ark.x86.lgpl.dll")
#endif

#ifndef _WIN32
#	ifdef __APPLE__
#		ifdef __arm64__
#			ifdef _DEBUG
#				define ARK_DLL_FILE_NAME		"ark.a64.debug.dylib"
#				define ARK_LGPLDLL_FILE_NAME	"ark.a64.lgpl.debug.dylib"
#			else
#				define ARK_DLL_FILE_NAME		"ark.a64.dylib"
#				define ARK_LGPLDLL_FILE_NAME	"ark.a64.lgpl.dylib"
#			endif
#			define ARK_DLL_RELEASE_FILE_NAME	"ark.a64.dylib"
#			define ARK_LGPLDLL_RELEASE_FILE_NAME "ark.a64.lgpl.dylib"
#		else
#			ifdef _DEBUG
#				define ARK_DLL_FILE_NAME		"ark.x64.debug.dylib"
#				define ARK_LGPLDLL_FILE_NAME	"ark.x64.lgpl.debug.dylib"
#			else
#				define ARK_DLL_FILE_NAME		"ark.x64.dylib"
#				define ARK_LGPLDLL_FILE_NAME	"ark.x64.lgpl.dylib"
#			endif
#			define ARK_DLL_RELEASE_FILE_NAME	"ark.x64.dylib"
#			define ARK_LGPLDLL_RELEASE_FILE_NAME "ark.x64.lgpl.dylib"
#		endif
#	else
#		if defined(__aarch64__)
#			ifdef _DEBUG
#				define ARK_DLL_FILE_NAME		"ark.a64.debug.so"
#				define ARK_LGPLDLL_FILE_NAME	"ark.a64.lgpl.debug.so"
#			else
#				define ARK_DLL_FILE_NAME		"ark.a64.so"
#				define ARK_LGPLDLL_FILE_NAME	"ark.a64.lgpl.so"
#			endif
#			define ARK_DLL_RELEASE_FILE_NAME	"ark.a64.so"
#			define ARK_LGPLDLL_RELEASE_FILE_NAME "ark.a64.lgpl.so"
#		elif defined(__x86_64__) || defined(__ia64__) || defined(_M_AMD64) || defined(_M_IA64) || defined(_WIN64) || defined(__alpha__) || defined(__s390__)
#			ifdef _DEBUG
#				define ARK_DLL_FILE_NAME		"ark.x64.debug.so"
#				define ARK_LGPLDLL_FILE_NAME	"ark.x64.lgpl.debug.so"
#			else
#				define ARK_DLL_FILE_NAME		"ark.x64.so"
#				define ARK_LGPLDLL_FILE_NAME	"ark.x64.lgpl.so"
#			endif
#			define ARK_DLL_RELEASE_FILE_NAME	"ark.x64.so"
#			define ARK_LGPLDLL_RELEASE_FILE_NAME "ark.x64.lgpl.so"
#		else
#			ifdef _DEBUG
#				define ARK_DLL_FILE_NAME		"ark.x86.debug.so"
#				define ARK_LGPLDLL_FILE_NAME	"ark.x86.lgpl.debug.so"
#			else
#				define ARK_DLL_FILE_NAME		"ark.x86.so"
#				define ARK_LGPLDLL_FILE_NAME	"ark.x86.lgpl.so"
#			endif
#			define ARK_DLL_RELEASE_FILE_NAME	 "ark.x86.so"
#			define ARK_LGPLDLL_RELEASE_FILE_NAME "ark.x86.lgpl.so"
#		endif
#	endif // __APPLE__
#endif	// _WIN32

#ifdef __APPLE__
#	ifdef _DEBUG
#		define ARK_DLL_FILE_NAME_UNI			"ark.uni.debug.dylib"
#		define ARK_LGPLDLL_FILE_NAME_UNI		"ark.uni.lgpl.debug.dylib"
#	else
#		define ARK_DLL_FILE_NAME_UNI			"ark.uni.dylib"
#		define ARK_LGPLDLL_FILE_NAME_UNI		"ark.uni.lgpl.dylib"
#	endif
#	ifdef _ARK_UNI
#		undef ARK_DLL_FILE_NAME
#		undef ARK_LGPLDLL_FILE_NAME
#		define ARK_DLL_FILE_NAME				ARK_DLL_FILE_NAME_UNI
#		define ARK_LGPLDLL_FILE_NAME			ARK_LGPLDLL_FILE_NAME_UNI
#	endif
#endif



#define ARK_EXPORTED_FUNCTION_NAME				"CreateArk"
#define ARKCOMPRESSOR_EXPORTED_FUNCTION_NAME	"CreateArkCompressor"

#ifndef _WIN32
#	include <dlfcn.h>
#	define HMODULE	void*
#	define LoadLibrary(name)					dlopen(name, RTLD_NOW | RTLD_GLOBAL)
#	define GetProcAddress(handle, func)			dlsym(handle, func)
#	define FreeLibrary(handle)					dlclose(handle)
#	include <string>
#endif

#ifdef _WIN32
#	define ARK_CDECL		__cdecl
#else
#	define ARK_CDECL
#endif


#ifndef _INC_TCHAR
#	ifdef _UNICODE
#		define _T(x)		L##x
#	else
#		define _T(x)		x
#	endif
#endif

#ifdef _UNICODE
	typedef  const wchar_t* LPCTSTR;
#else
	typedef  const char* LPCTSTR;
#endif

typedef IArk*			(ARK_CDECL *LPCREATEARK)(UINT32 version);
typedef IArkCompressor* (ARK_CDECL *LPCREATEARKCOMPRESSOR)(UINT32 version);

#ifndef ASSERT
#   include <stdio.h>
#	define ASSERT(x)	printf("Assert at %s %d\n", __FILE__, __LINE__)
#endif


class CArkLib : public IArk
{
public :
	CArkLib()
	{
		m_hDll = NULL;
		m_pCreateArk = NULL;
		m_pCreateArkCompressor = NULL;
		m_pArk = NULL;
	}

	virtual ~CArkLib()
	{
		Destroy();
	}

#ifndef _ARK_STATIC
	// .dll 로 사용하는 경우
	ARKERR	 Create(LPCTSTR szDllPathName, LPCSTR id, LPCSTR key)
	{
		if(m_hDll) {ASSERT(0); return ARKERR_ALREADY_DLL_CREATED;}

		m_hDll = LoadLibrary(szDllPathName);
		if(m_hDll==NULL)
		{
			#ifdef _WIN32
			const DWORD err = ::GetLastError();(err);
			#else
			#ifdef _DEBUG
			printf("Load %s failed.(Reason: '%s')\n", szDllPathName, dlerror());
			#endif
			#endif
			ASSERT(0);
			return ARKERR_LOADLIBRARY_FAILED;
		}

		m_pCreateArk = (LPCREATEARK)GetProcAddress(m_hDll, ARK_EXPORTED_FUNCTION_NAME);
		m_pCreateArkCompressor = (LPCREATEARKCOMPRESSOR)GetProcAddress(m_hDll, ARKCOMPRESSOR_EXPORTED_FUNCTION_NAME);

		if(m_pCreateArk==NULL)
		{
			#ifndef _WIN32
			printf("dlsym() failed.(Reason: '%s')\n", dlerror());
			#endif

			ASSERT(0);
			FreeLibrary(m_hDll);
			m_hDll = NULL;
			return ARKERR_GETPROCADDRESS_FAILED;
		}

		m_pArk = (m_pCreateArk)(ARK_LIBRARY_VERSION);
		if(m_pArk==NULL)
		{
			ASSERT(0);
			FreeLibrary(m_hDll);
			m_hDll = NULL;
			return ARKERR_INVALID_VERSION;
		}

		// Verify license
		if (id && key && id[0] && key[0])
		{
			const BOOL32 verified = m_pArk->Verify(id, key);
			if (verified == FALSE) return ARKERR_VERIFY_FAILED;
		}

		return ARKERR_NOERR;
	}
#endif	// not _ARK_STATIC

	IArkCompressor* CreateCompressor()
	{
#ifdef _ARK_STATIC
		return CreateArkCompressorLib(ARK_LIBRARY_VERSION);
#else
		return m_pCreateArkCompressor ? m_pCreateArkCompressor(ARK_LIBRARY_VERSION) : NULL;
#endif
	}

	IArk* CreateDecompressor(LPCSTR id, LPCSTR key)
	{
#ifdef _ARK_STATIC
		IArk* ark = CreateArkLib(ARK_LIBRARY_VERSION);
#else
		IArk* ark = m_pCreateArk ? m_pCreateArk(ARK_LIBRARY_VERSION) : NULL;
#endif
		if(ark)
			ark->Verify(id, key);
		return ark;
	}


	IArk*			GetIArk()
	{
		return m_pArk;
	}

#ifdef _ARK_STATIC
	// .lib 로 사용하는 경우
	ARKERR	 CreateLib(LPCSTR id, LPCSTR key)
	{
		m_pArk = CreateArkLib(ARK_LIBRARY_VERSION);
		if(m_pArk==NULL)
		{
			ASSERT(0);
			return ARKERR_INVALID_VERSION;
		}
		// Verify license
		BOOL verified = m_pArk->Verify(id, key);
		return ARKERR_NOERR;
	}
#endif

	BOOL32	IsCreated()
	{
		return m_pArk ? TRUE : FALSE;
	}

	void	Destroy()
	{
		if(m_pArk)
			m_pArk->Release();
		m_pArk = NULL;
		m_pCreateArk = NULL;
#ifndef _ARK_STATIC
		if(m_hDll) FreeLibrary(m_hDll);
		m_hDll = NULL;
#endif
	}

public :				// IArk
	ARKMETHOD(void)				Release() 
	{
		Destroy();
	}
	ARKMETHOD(BOOL32)				Verify(LPCSTR id, LPCSTR key) 
	{
		return m_pArk ? m_pArk->Verify(id, key) : FALSE;
	}

#ifndef _WIN32
	// posix 용 std::string 인터페이스
	ARKMETHOD(BOOL32)	Open(std::string name, std::string pass){ return Open(name.c_str(), pass.c_str()); }
	ARKMETHOD(BOOL32)	Open(std::string name, const char* pass){ return Open(name.c_str(), pass); }
	ARKMETHOD(BOOL32)	ExtractOneTo(int index,std::string dest){ return ExtractOneTo(index, dest.c_str()); };
	ARKMETHOD(BOOL32)	ExtractAllTo(std::string dest)			{ return ExtractAllTo(dest.c_str()); };
	ARKMETHOD(BOOL32)	ExtractMultiFileTo(std::string dest)	{ return ExtractMultiFileTo(dest.c_str()); }
	ARKMETHOD(ARK_FF)	CheckFormat(std::string name) const	{ return CheckFormat(name.c_str()); }
#endif


	ARKMETHOD(BOOL32)  			Open(LPCSTR  filePath, LPCSTR password=NULL)
	{
		return m_pArk ? m_pArk->Open(filePath, password) : FALSE;
	}
	ARKMETHOD(BOOL32)  			Open(LPCWSTR filePath, LPCWSTR password=NULL)
	{
		return m_pArk ? m_pArk->Open(filePath, password) : FALSE;
	}
	ARKMETHOD(BOOL32)			Open(ARKBYTE* src, int srcLen, LPCWSTR password=NULL)
	{
		return m_pArk ? m_pArk->Open(src, srcLen, password) : FALSE;
	}
	ARKMETHOD(BOOL32)  			Open(IArkSimpleInStream* srcStream, LPCWSTR password=NULL)
	{
		return m_pArk ? m_pArk->Open(srcStream, password) : FALSE;
	}

	ARKMETHOD(void)				Close()
	{
		if(m_pArk) m_pArk->Close();
	}

	ARKMETHOD(BOOL32)			TestArchive()
	{
		return m_pArk ? m_pArk->TestArchive() : FALSE;
	}

	ARKMETHOD(ARK_FF)  			CheckFormat(LPCSTR  filePath) const
	{
		return  m_pArk ? m_pArk->CheckFormat(filePath) : ARK_FF_UNKNOWN;
	}
	ARKMETHOD(ARK_FF)  			CheckFormat(LPCWSTR filePath) const
	{
		return  m_pArk ? m_pArk->CheckFormat(filePath) : ARK_FF_UNKNOWN;
	}
	ARKMETHOD(ARK_FF)  			CheckFormat(const unsigned char* buffer, size_t bufLen) const
	{
		return  m_pArk ? m_pArk->CheckFormat(buffer, bufLen) : ARK_FF_UNKNOWN;
	}

	ARKMETHOD(void)				SetPassword(LPCSTR password)
	{
		if(m_pArk) m_pArk->SetPassword(password);
	}
	ARKMETHOD(void)				SetPassword(LPCWSTR password)
	{
		if(m_pArk) m_pArk->SetPassword(password);
	}

	ARKMETHOD(int)				GetFileItemCount() const
	{
		return m_pArk ? m_pArk->GetFileItemCount() : 0;
	}

	ARKMETHOD(const SArkFileItem*)	GetFileItem(int index) const
	{
		return m_pArk ? m_pArk->GetFileItem(index) : NULL;
	}

	ARKMETHOD(ARK_FF)			GetFileFormat() const
	{
		return m_pArk ? m_pArk->GetFileFormat() : ARK_FF_UNKNOWN;
	}

	ARKMETHOD(BOOL32)			IsBrokenArchive() const
	{
		return m_pArk ? m_pArk->IsBrokenArchive() : FALSE;
	}

	ARKMETHOD(BOOL32)			IsEncryptedArchive() const
	{
		return m_pArk ? m_pArk->IsEncryptedArchive() : FALSE;
	}

	ARKMETHOD(BOOL32)			IsSolidArchive() const
	{
		return m_pArk ? m_pArk->IsSolidArchive() : FALSE;
	}

	ARKMETHOD(BOOL32)			IsOpened() const
	{
		return m_pArk ? m_pArk->IsOpened() : FALSE;
	}

	ARKMETHOD(BOOL32)			IsEditable() const
	{
		return m_pArk ? m_pArk->IsEditable() : FALSE;
	}

	ARKMETHOD(BOOL32)			ExtractAllTo(LPCSTR szDestPath, LPCWSTR path2remove = NULL)
	{
		return m_pArk ? m_pArk->ExtractAllTo(szDestPath, path2remove) : FALSE;
	}

	ARKMETHOD(BOOL32)			ExtractAllTo(LPCWSTR szDestPath, LPCWSTR path2remove = NULL)
	{
		return m_pArk ? m_pArk->ExtractAllTo(szDestPath, path2remove) : FALSE;
	}

	ARKMETHOD(BOOL32)			ExtractAllTo(IArkSimpleOutStream* pOutStream, LPCWSTR path2remove = NULL)
	{
		return m_pArk ? m_pArk->ExtractAllTo(pOutStream, path2remove) : FALSE;
	}

	ARKMETHOD(BOOL32)			ExtractOneTo(int index, LPCSTR szDestPath)
	{
		return m_pArk ? m_pArk->ExtractOneTo(index, szDestPath) : FALSE;
	}

	ARKMETHOD(BOOL32)			ExtractOneTo(int index, LPCWSTR szDestPath)
	{
		return m_pArk ? m_pArk->ExtractOneTo(index, szDestPath) : FALSE;
	}

	ARKMETHOD(BOOL32)			ExtractOneTo(int index, IArkSimpleOutStream* pOutStream)
	{
		return m_pArk ? m_pArk->ExtractOneTo(index, pOutStream) : FALSE;
	}
	ARKMETHOD(BOOL32)			ExtractOneTo(int index, ARKBYTE* outBuf, int outBufLen)
	{
		return m_pArk ? m_pArk->ExtractOneTo(index, outBuf, outBufLen) : FALSE;
	}
	ARKMETHOD(BOOL32)			ExtractOneAs(int index, LPCWSTR filePathName, WCHAR* resultPathName, int resultPathNameLen)
	{
		return m_pArk ? m_pArk->ExtractOneAs(index, filePathName, resultPathName, resultPathNameLen) : FALSE;
	}


	ARKMETHOD(BOOL32)			AddIndex2ExtractList(int nIndex)
	{
		return m_pArk ? m_pArk->AddIndex2ExtractList(nIndex) : FALSE;
	}

	ARKMETHOD(void)				ClearExtractList()
	{
		if(m_pArk) m_pArk->ClearExtractList();
	}

	ARKMETHOD(int)				GetExtractListCount() const
	{
		return m_pArk ? m_pArk->GetExtractListCount() : 0;
	}

	ARKMETHOD(BOOL32)			ExtractMultiFileTo(LPCSTR szDestPath)
	{
		return m_pArk ? m_pArk->ExtractMultiFileTo(szDestPath) : FALSE;
	}
	ARKMETHOD(BOOL32)			ExtractMultiFileTo(LPCWSTR szDestPath, LPCWSTR szPath2Remove=NULL)
	{
		return m_pArk ? m_pArk->ExtractMultiFileTo(szDestPath, szPath2Remove) : FALSE;
	}
	ARKMETHOD(BOOL32)			ExtractMultiFileTo(IArkSimpleOutStream* pOutStream)
	{
		return m_pArk ? m_pArk->ExtractMultiFileTo(pOutStream) : FALSE;
	}


	ARKMETHOD(BOOL32)			SetEvent(IArkEvent* pProgress)
	{
		return m_pArk ? m_pArk->SetEvent(pProgress) : FALSE;
	}

	ARKMETHOD(ARKERR)			GetLastError() const
	{
		return m_pArk ? m_pArk->GetLastError() : ARKERR_LIBRARY_NOT_LOADED ;
	}
	ARKMETHOD(UINT32)			GetLastSystemError() const 
	{
		return m_pArk ? m_pArk->GetLastSystemError() : 0 ;
	}

	ARKMETHOD(void)				SetCodePage(SArkCodepage cp)
	{
		if(m_pArk) m_pArk->SetCodePage(cp);
	}

	ARKMETHOD(LPCWSTR)			EncryptionMethod2Str(ARK_ENCRYPTION_METHOD method) const
	{
		return m_pArk ? m_pArk->EncryptionMethod2Str(method) : NULL;
	}

	ARKMETHOD(LPCWSTR)			CompressionMethod2Str(ARK_COMPRESSION_METHOD method) const
	{
		return m_pArk ? m_pArk->CompressionMethod2Str(method) : NULL;
	}

	ARKMETHOD(LPCWSTR)			FileFormat2Str(ARK_FF ff) const
	{
		return m_pArk ? m_pArk->FileFormat2Str(ff) : NULL;
	}

	ARKMETHOD(void)				SetProps(const SArkProps& props)
	{
		if(m_pArk) m_pArk->SetProps(props);
	}

	ARKMETHOD(INT64)			GetArchiveFileSize() const
	{
		return m_pArk ? m_pArk->GetArchiveFileSize() : 0;
	}
	ARKMETHOD(INT64)			GetArchiveStartPos() const 
	{
		return m_pArk ? m_pArk->GetArchiveStartPos() : 0;
	}

	ARKMETHOD(LPCWSTR)			GetFilePathName() const
	{
		return m_pArk ? m_pArk->GetFilePathName() : NULL;
	}
	ARKMETHOD(int)				FindIndex(LPCWSTR szFileNameW, LPCSTR szFileNameA, BOOL32 bCaseSensitive) const
	{
		return m_pArk ? m_pArk->FindIndex(szFileNameW, szFileNameA, bCaseSensitive) : -1;
	}

	ARKMETHOD(LPCWSTR)			GetArchiveComment() const
	{
		return m_pArk ?m_pArk->GetArchiveComment() : NULL;
	}

	ARKMETHOD(ARK_MULTIVOL_STYLE) GetMultivolStyle() const
	{
		return m_pArk ?m_pArk->GetMultivolStyle() : ARK_MULTIVOL_STYLE_NONE;
	}

	ARKMETHOD(size_t)			GetMultivolCount() const
	{
		return m_pArk ?m_pArk->GetMultivolCount() : 0;
	}

	ARKMETHOD(LPCWSTR)			GetMultivolFilePathName(size_t volume) const
	{
		return m_pArk ?m_pArk->GetMultivolFilePathName(volume) : NULL;
	}

	//ARKMETHOD(BOOL32)			DetectCurrentArchivesCodepage(SArkDetectCodepage& dcp) const
	//{
	//	return m_pArk ?m_pArk->DetectCurrentArchivesCodepage(dcp) : FALSE;
	//}

	ARKMETHOD(BOOL32)			ChangeCurrentArchivesCodepage(int codePage)
	{
		return m_pArk ? m_pArk->ChangeCurrentArchivesCodepage(codePage) : FALSE;
	}

	ARKMETHOD(BOOL32)			LoadArkLGPL(const char* pathName)
	{
		return m_pArk ? m_pArk->LoadArkLGPL(pathName) : FALSE;
	}
	ARKMETHOD(BOOL32)			LoadArkLGPL(const wchar_t* pathName)
	{
		return m_pArk ? m_pArk->LoadArkLGPL(pathName) : FALSE;
	}
	ARKMETHOD(BOOL32)			UnloadArkLGPL()
	{
		return m_pArk ? m_pArk->UnloadArkLGPL() : FALSE;
	}

	ARKMETHOD(BOOL32)  			ChangeArkFileName(const SArkFileItem* item, const wchar_t* newFileName)
	{
		return  m_pArk ? m_pArk->ChangeArkFileName(item, newFileName) : 0;
	}

	ARKMETHOD(UINT32)  			_CheckCRC32(LPCWSTR filePath)
	{
		return  m_pArk ? m_pArk->_CheckCRC32(filePath) : 0;
	}

	//////////////////////////
	// undocumented 
	/*
	ARKMETHOD(LPCWSTR)			_GetAlias()
	{
		return m_pArk ? m_pArk->_GetAlias() : NULL;
	}

	ARKMETHOD(void)				_SetAlias(LPCWSTR szAlias)
	{
		if(m_pArk) m_pArk->_SetAlias(szAlias);
	}

	ARKMETHOD(const void*)		_GetBondFileInfo()
	{
		return m_pArk ? m_pArk->_GetBondFileInfo() : 0;
	}

	ARKMETHOD(void)				_SetUserKey(void* key)
	{
		if(m_pArk) m_pArk->_SetUserKey(key);
	}


	ARKMETHOD(void*)			_GetExtractor()
	{
		return  m_pArk ? m_pArk->_GetExtractor(): NULL;
	}
	ARKMETHOD(void*)			_GetInStream()
	{
		return  m_pArk ? m_pArk->_GetInStream(): NULL;
	}
	ARKMETHOD(BOOL32)			_ReadRawArchiveData(INT64 offset, ARKBYTE* buf, int length)
	{
		return  m_pArk ? m_pArk->_ReadRawArchiveData(offset, buf, length) : FALSE;
	}

	ARKMETHOD(void)				_Test()
	{
		if(m_pArk) m_pArk->_Test();
	}
	*/

public :
	HMODULE					m_hDll;
	LPCREATEARK				m_pCreateArk;
	LPCREATEARKCOMPRESSOR	m_pCreateArkCompressor;
	IArk*					m_pArk;
};


#endif // _ARK_LIB_H_

