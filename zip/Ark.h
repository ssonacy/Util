////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
///                                      Ark Library v7
/// 
/// @author   parkkh
/// @date     Tuesday, December 22, 2009  9:22:23 AM
/// 
/// Copyright(C) 2008-2022 Bandisoft, All rights reserved.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _ARK_H_
#define _ARK_H_

#define ARK_LIBRARY_VERSION								(0x20230308)		// ArkLibrary 버전 (Ark.h 와 ArkXX.dll 파일의 버전이 동일한지 여부 판단용)

enum ARKERR																	// 에러코드
{
	ARKERR_NOERR										= 0x00000000,		// 오류 없음
	ARKERR_START										= 0xa0000000,
	ARKERR_CANT_OPEN_FILE								= 0xa0000001,		// 파일 열기 실패
	ARKERR_CANT_READ_SIG								= 0xa0000002,		// signature 읽기 실패
	ARKERR_AT_READ_CONTAINER_HEADER						= 0xa0000003,		// 컨테이너 헤더가 손상되었음
	ARKERR_INVALID_FILENAME_LENGTH						= 0xa0000004,		// (압축 파일 내부의)파일명 길이에 문제가 있음
	ARKERR_READ_FILE_NAME_FAILED						= 0xa0000005,		// 파일이름 읽기 실패
	ARKERR_INVALID_EXTRAFIELD_LENGTH					= 0xa0000006,		// extra field 읽기
	ARKERR_READ_EXTRAFILED_FAILED						= 0xa0000007,		// extra field 읽기 실패
	ARKERR_CANT_READ_CENTRAL_DIRECTORY_STRUCTURE		= 0xa0000008,		// (zip) Central Directory 정보를 읽는데 실패하였음
	ARKERR_INVALID_FILENAME_SIZE						= 0xa0000009,		// 파일명 길이 정보가 잘못되었음
	ARKERR_INVALID_EXTRAFIELD_SIZE						= 0xa0000010,		// (zip) ExtraField 정보 길이가 잘못되었음
	ARKERR_INVALID_FILECOMMENT_SIZE						= 0xa0000011,		// Comment 정보 길이가 잘못되었음
	ARKERR_CANT_READ_CONTAINER_HEADER					= 0xa0000012,		// 컨테이너의 헤더에 문제가 있음
	ARKERR_MEM_ALLOC_FAILED								= 0xa0000013,		// 메모리 할당 실패
	ARKERR_CANT_READ_DATA								= 0xa0000015,		// 압축 데이터 읽기 실패
	ARKERR_INFLATE_FAILED								= 0xa0000016,		// Inflate 함수 호출중 에러 발생
	ARKERR_USER_ABORT_OR_CANCEL							= 0xa0000017,		// 사용자 중지  //ARKERR_USER_ABORTED = 0xa0000017,
	ARKERR_INVALID_FILE_CRC								= 0xa0000018,		// 압축 해제후 CRC 에러 발생
	ARKERR_UNKNOWN_COMPRESSION_METHOD					= 0xa0000019,		// 모르는(혹은 지원하지 않는) 압축방식
	ARKERR_PASSWD_NOT_SET								= 0xa0000020,		// 암호걸린 파일인데 암호가 지정되지 않았음
	ARKERR_INVALID_PASSWD								= 0xa0000021,		// 암호가 틀렸음
	ARKERR_WRITE_FAIL									= 0xa0000030,		// 파일 쓰다가 실패
	ARKERR_CANT_OPEN_DEST_FILE							= 0xa0000031,		// 대상 파일을 만들 수 없음
	ARKERR_BZIP2_ERROR									= 0xa0000032,		// BZIP2 압축해제중 에러 발생
	ARKERR_INVALID_DEST_PATH							= 0xa0000033,		// 경로명에 ../ 이 포함된 경우, 대상 경로에 접근이 불가능한 경우
	ARKERR_CANT_CREATE_FOLDER							= 0xa0000034,		// 경로 생성 실패
	ARKERR_DATA_CORRUPTED								= 0xa0000035,		// 압축푸는데 데이터가 손상됨 or RAR 분할 압축파일의 뒷부분이 없음
	ARKERR_CANT_OPEN_FILE_TO_WRITE						= 0xa0000036,		// 쓰기용으로 파일 열기 실패
	ARKERR_INVALID_INDEX								= 0xa0000037,		// 압축풀 대상의 index 파라미터가 잘못됨
	ARKERR_CANT_READ_CODEC_HEADER						= 0xa0000038,		// 압축 코덱의 헤더를 읽는데 에러
	ARKERR_CANT_INITIALIZE_CODEC						= 0xa0000039,		// 코덱 초기화 실패
	ARKERR_LZMA_ERROR									= 0xa0000040,		// LZMA 압축 해제중 에러 발생
	ARKERR_PPMD_ERROR									= 0xa0000041,		// ppmd 에러
	ARKERR_CANT_SET_OUT_FILE_SIZE						= 0xa0000042,		// 출력파일의 SetSize() 실패
	ARKERR_NOT_MATCH_FILE_SIZE							= 0xa0000043,		// 압축을 푼 파일 크기가 맞지 않음
	ARKERR_NOT_A_FIRST_VOLUME_FILE						= 0xa0000044,		// 분할 압축파일중 첫번째 파일이 아님
	ARKERR_NOT_OPENED									= 0xa0000045,		// 파일이 열려있지 않음
	ARKERR_NOT_SUPPORTED_ENCRYPTION_METHOD				= 0xa0000046,		// 지원하지 않는 암호 방식
	ARKERR_INTERNAL										= 0xa0000047,		// 내부 에러
	ARKERR_NOT_SUPPORTED_FILEFORMAT						= 0xa0000048,		// 지원하지 않는 파일 포맷
	ARKERR_UNKNOWN_FILEFORMAT							= 0xa0000049,		// 압축파일이 아니거나 모르는 파일 포맷
	ARKERR_FILENAME_EXCED_RANGE							= 0xa0000050,		// 경로명이 너무 길어서 파일이나 폴더를 만들 수 없음
	ARKERR_LZ_ERROR										= 0xa0000052,		// lz 에러
	ARKERR_NOTIMPL										= 0xa0000053,		// not implemented
	ARKERR_DISK_FULL									= 0xa0000054,		// 파일 쓰다가 실패
	ARKERR_FILE_TRUNCATED								= 0xa0000055,		// 파일의 뒷부분이 잘렸음
	ARKERR_CANT_DO_THAT_WHILE_WORKING					= 0xa0000056,		// 압축 해제 작업중에는 파일을 열거나 닫을 수 없음
	ARKERR_CANNOT_FIND_NEXT_VOLUME						= 0xa0000057,		// 분할 압축된 파일의 다음 파일을 찾을 수 없음
	ARKERR_NOT_ARCHIVE_FILE								= 0xa0000058,		// 압축파일이 아님 (Open() 호출시 명백히 압축파일이 아닌 경우 발생)
	ARKERR_USER_SKIP									= 0xa0000059,		// 덮어쓰기 물어보는 창에서 사용자가 건너띄기를 선택하였음
	ARKERR_INVALID_PASSWD_OR_BROKEN_ARCHIVE				= 0xa0000060,		// 암호가 틀리거나 파일이 손상되었음 (rar 포맷, zip 포맷중 1바이트 체크섬만 동일한 파일)
	ARKERR_ZIP_LAST_VOL_ONLY							= 0xa0000061,		// 분할 zip 인데 마지막 zip 파일만 열려고 했음
	ARKERR_ACCESS_DENIED_TO_DEST_PATH					= 0xa0000062,		// 대상 폴더에 대해서 쓰기 권한이 없음
	ARKERR_NOT_ENOUGH_MEMORY							= 0xa0000063,		// 메모리가 부족함
	ARKERR_NOT_ENOUGH_MEMORY_LZMA_ENCODE				= 0xa0000064,		// LZMA 압축중 메모리가 부족함
	ARKERR_CANT_OPEN_SHARING_VIOLATION					= 0xa0000065,		// 파일이 잠겨있어서 열 수 없음 (ERROR_SHARING_VIOLATION, WIN32 전용)
	ARKERR_CANT_OPEN_ERROR_LOCK_VIOLATION				= 0xa0000066,		// 파일이 잠겨있어서 열 수 없음 (ERROR_LOCK_VIOLATION, WIN32 전용)
	ARKERR_CANT_LOAD_UNACE								= 0xa0000067,		// unace32.exe 혹은 unacev2.dll 파일을 로드할 수 없음 (WIN32 전용)
	ARKERR_NOT_SUPPORTED_OPERATION						= 0xa0000068,		// 지원하지 않는 작동입니다. (ACE 파일을 IArkSimpleOutStream 를 이용해 압축해제할 경우 발생)
	ARKERR_CANT_CONVERT_FILENAME						= 0xa0000069,		// 파일명이 잘못되어서 유니코드 파일명으로 바꿀 수 없음(posix 환경에서 iconv 사용시 코드페이지가 잘못된 경우 사용할 수 없는 문자 때문에 발생)
	ARKERR_TOO_LONG_FILE_NAME							= 0xa0000070,		// 파일명이 너무 길어서 처리할 수 없음
	ARKERR_TOO_LONG_FILE_NAME_AND_TRUNCATED				= 0xa0000071,		// 파일명이 너무 길어서 뒷부분이 잘렸습니다.
	ARKERR_TOO_MANY_FILE_COUNT							= 0xa0000072,		// 파일 개수가 너무 길어서 처리할 수 없음
	ARKERR_CANT_OPEN_SRC_FILE_TO_COPY					= 0xa0000073,		// 파일을 복사하기 위한 원본 파일을 열 수 없음 (rar5 redirect 처리용)
	ARKERR_INVALID_COMPRESSED_SIZE						= 0xa0000074,		// 압축된 크기가 잘못되었음(음수임)
	ARKERR_CANT_START_THREAD							= 0xa0000075,		// 스레드 시작 실패
	ARKERR_NEED_ADMIN_PRIVILEGE_TO_MAKE_SYMLINK			= 0xa0000076,		// 심볼릭 링크를 만들기 위해서 관리자 권한이 필요함
	ARKERR_CANT_MAKE_SYMLINK							= 0xa0000077,		// 심볼릭 링크를 만들 수 없음
	ARKERR_SYMLINK_NOT_SUPPORTED						= 0xa0000078,		// 심볼릭 링크 생성을 지원하지 않습니다
	//ARKERR_USER_CANCEL								= 0xa0000079,		// 사용자가 취소했음 - ARKERR_USER_ABORT_OR_CANCEL 에러코드로 통합
	ARKERR_CANT_RENAME_ARCHIVE							= 0xa0000080,		// 분할 압축시 RenameFile 실패
	ARKERR_RECURSIVE_FILE_ITEM							= 0xa0000081,		// 파일 아이템 정보가 리커시브하게 얽혀있다 2019/3/26 추가
	ARKERR_RESOURCEFORK_TOO_BIG							= 0xa0000082,		// 리소스 포크 파일이 너무 크다.
	ARKERR_RESOURCEFORK_INVALIDFILE						= 0xa0000083,		// 리소스 포크 파일이 손상됨
	ARKERR_RESOURCEFORK_WRITEFAILED						= 0xa0000084,		// 리소스 포크 정보 쓰기 실패

	ARKERR_CORRUPTED_FILE								= 0xa0000100,		// 파일이 손상되었음
	ARKERR_INVALID_FILE									= 0xa0000101,		// 포맷이 다르다
	ARKERR_CANT_READ_FILE								= 0xa0000102,		// 파일을 읽을 수 없음

	ARKERR_INVALID_VERSION								= 0xa0000200,		// 헤더파일과 dll 의 버전이 맞지 않음
	ARKERR_ENCRYPTED_BOND_FILE							= 0xa0000201,		// 압축 해제 불가(암호화된 bond 파일임)

	ARKERR_7ZERR_BROKEN_ARCHIVE							= 0xa0000300,		// 7z.dll 으로 열때 에러가 발생(깨진파일)
	ARKERR_LOAD_7Z_DLL_FAILED							= 0xa0000301,		// 7z.dll 여는중 에러 발생

																			// [압축할 때만 발생하는 에러]
	ARKERR_CANT_CREATE_FILE								= 0xa0000401,		// 파일을 쓰기용으로 생성하지 못함
	ARKERR_INIT_NOT_CALLED								= 0xa0000402,		// Init() 함수가 호출되지 않았음
	ARKERR_INVALID_PARAM								= 0xa0000403,		// 잘못된 파라미터로 호출하였음
	ARKERR_CANT_OPEN_INPUT_SFX							= 0xa0000404,		// SFX 파일을 열지 못함
	ARKERR_SFX_SIZE_OVER_4GB							= 0xa0000405,		// SFX 파일의 크기가 4GB를 넘었음
	ARKERR_CANT_LOAD_ARKLGPL							= 0xa0000406,		// ArkXXLgpl.dll 파일을 열지 못함
	ARKERR_CANT_STORE_FILE_SIZE_OVER_4GB				= 0xa0000407,		// 파일 크기가 4GB를 넘어서 저장할 수 없음
	ARKERR_SFX_NOT_SUPPORTED_FORMAT						= 0xa0000408,		// SFX 를 지원하지 않는 포맷인데 sfxPathName 이 지정되었음
	ARKERR_TOO_SMALL_SPLIT_SIZE							= 0xa0000409,		// SPLIT 크기가 너무 작다(SFX STUB보다 작다)
	ARKERR_NOFILE_TO_ARCHIVE							= 0xa0000410,		// 압축할 파일이 없음
	ARKERR_TOOMANYFILE_TO_ARCHIVE						= 0xa0000411,		// 압축할 파일이 너무 많음
	ARKERR_FILE_NOT_EXIST								= 0xa0000412,		// 압축 파라미터로 넘어온 파일이 존재하지 않음
	ARKERR_DUPE_FILE_NAME								= 0xa0000413,		// 이미 동일한 파일명이 있음(AddFileItem()/AddFileItem2()에서만 발생)
	ARKERR_CANNOT_GET_FILEINFO_TO_COMPRESS				= 0xa0000414,		// 압축할 파일에 대한 정보를 가져올 수 없음 (AddFileItem()/AddFileItem2() 에서만 발생)

	ARKERR_STAT_FAILED									= 0xa0000501,		// Unix 전용 에러 - 파일에 대한 stat 실패
	ARKERR_REPAIR_EMPTY									= 0xa0000601,		// Repair 에러 - 원본 파일에 아무런 내용이 없음
	ARKERR_CANNOT_DUPE_FILEHANDLE						= 0xa0000602,		// 파일 핸들 복사 실패

	ARKERR_ALREADY_DLL_CREATED							= 0xa0000902,		// (CArkLib) 이미 ARK DLL 파일을 로드하였음
	ARKERR_LOADLIBRARY_FAILED							= 0xa0000903,		// (CArkLib) LoadLibrary() 호출 실패
	ARKERR_GETPROCADDRESS_FAILED						= 0xa0000904,		// (CArkLib) GetProcAddress() 호출 실패
	ARKERR_LIBRARY_NOT_LOADED							= 0xa0000906,		// (CArkLib) 라이브러리를 로드하지 않았거나 로드하는데 실패하였음
	ARKERR_VERIFY_FAILED								= 0xa0000907,		// (CArkLib) Verify() 호출이 실패하였음. 
	ARKERR_INVALID_DLL_SIG								= 0xa0000908,		// (CArkLib) 잘못된 DLL 이미지

	ARKERR_WARN_LOCKED_FILE_OPENED_TO_COMPR				= 0xa0001000,		// 경고 - 압축 하려는 파일이 잠겨있음
	ARKERR_LAST
};


// ARK FILE FORMAT
enum ARK_FF
{
	ARK_FF_ZIP,								// zip, zipx
	ARK_FF_ZIP_LASTVOLONLY,					// 분할 zip 파일의 마지막 볼륨 (파일이 하나만 존재할 경우)
	ARK_FF_ZIP_BANDIZIP_SFX,				// 반디집 sfx 
	ARK_FF_ALZ,
	ARK_FF_ALZ_SECONDVOL,					// 분할 alz 파일의 2번째 이후 압축파일
	ARK_FF_LZH,
	ARK_FF_RAR,
	ARK_FF_RAR_SECONDVOL,					// 분할 RAR 파일의 2번째 이후 압축파일
	ARK_FF_RAR5,
	ARK_FF_RAR5_SECONDVOL,
	ARK_FF_7Z,
	ARK_FF_7ZSPLIT,							// 7z 파일의 뒷부분이 잘렸고 확장자가 .001 인 파일 (.7z.001 ~ .7z.NNN)
	ARK_FF_7ZBROKEN,						// 7z 파일의 뒷부분이 잘렸거나 헤더가 손상된 파일
	ARK_FF_TAR,
	ARK_FF_CAB,
	ARK_FF_CAB_NOTFIRSTVOL,					// 
	ARK_FF_ISO,								// iso, joliet
	ARK_FF_IMG,								// clone cd img (img, ccd)
	ARK_FF_UDF,
	//ARK_FF_UDFBROKEN,						// 뒷부분이 잘린 UDF 
	ARK_FF_SPLIT,							// 확장자가 .001 인 파일 (.001 ~ .NNN)
	ARK_FF_BOND,							// hv3
	ARK_FF_GZ,
	ARK_FF_BZ2,
	ARK_FF_LZMA,
	ARK_FF_BH,								// blakhole (not blackhole)
	ARK_FF_EGG,
	ARK_FF_EGG_NOTFIRSTVOL,					// 분할 압축의 첫번째 볼륨이 아닌 파일
	ARK_FF_XZ,
	ARK_FF_WIM,								// raw 만 사용하는 wim
	ARK_FF_WIM_COMPRESSED,					// 압축된 wim, Windows 에서만 지원
	ARK_FF_Z,								// .Z (unix compress)
	ARK_FF_ARJ,								// arj 
	ARK_FF_BAMSFX,							// 밤톨이 sfx
	ARK_FF_BAMSFX_NOTFIRSTVOL,				// 
	ARK_FF_TGZ,								// .tar.gz
	ARK_FF_TBZ,								// .tar.bz2
	ARK_FF_J2J,								// .j2j
	ARK_FF_J2JBROKEN,						// 뒷부분이 잘린 j2j
	ARK_FF_K2K,								// .k2k
	ARK_FF_NSIS,							// nsis exe
	ARK_FF_ISZ,								// EZBSystems(UltraISO) ZIPPED ISO
	ARK_FF_BIN,								// CD Image
	ARK_FF_AESCRYPT,						// AESCrypt (v0, v1, v2)
	ARK_FF_COMPOUND,						// MSI, XLS, PPT, DOC ...
	ARK_FF_LZIP,							// LZIP
	ARK_FF_ARC,								// ARC(FreeArc 말고.. 예전 Arc)
	ARK_FF_ZPAQ,							// ZPAQ
	ARK_FF_ZPAQENC,							// ZPAQ(Encrypted)
	ARK_FF_ACE,								// ACE
	ARK_FF_ZSTD,							// Zstandard
	ARK_FF_BROTLI,							// BROTLI
	ARK_FF_DAA,								// DAA
	ARK_FF_UU,								// UU (UUE)
	ARK_FF_XXE,								// XXE
	ARK_FF_PEA,								// PEA
	ARK_FF_ASAR,							// ASAR

	ARK_FF_UNKNOWN				= 0x00ff,	// 알 수 없는 파일 포맷

	ARK_FF_UNSUPPORTED_FIRST	= 0x0100,	// 지원하지 않는 압축파일 포맷
	ARK_FF_SIT					= 0x0100,	// sit
	ARK_FF_BPE					= 0x0101,	// bpe
	ARK_FF_PAE					= 0x0104,	// PowerArchiver Encryption
	ARK_FF_XEF					= 0x0105,	// Winace Encryption
	ARK_FF_MBR					= 0x0107,	// MBR
	ARK_FF_SQUASH				= 0x0108,	// SQUASH
	ARK_FF_FREEARC				= 0x0109,	// FreeArc
	ARK_FF_XAR					= 0x010a,	// XAR
	ARK_FF_DMG					= 0x010b,	// DMG
	ARK_FF_DEB					= 0x010c,	// DEB
	ARK_FF_UNSUPPORTED_LAST		= 0x01FF,

	ARK_FF_NOTARCHIVE_FIRST		= 0x0200,	// 명백히 압축파일이 아닌 파일 (실행파일, 이미지파일 등등..)
	ARK_FF_NULL					= 0x0201,	// 파일의 앞부분이 전부 0 으로 채워져 있는 파일
	ARK_FF_RIFF					= 0x0202,	// avi, wav
	ARK_FF_EXE					= 0x0203,	// sfx 가 아닌 일반 PE 실행파일
	ARK_FF_HTML					= 0x0204,	// HTML(정확하지는 않음)
	ARK_FF_JPG					= 0x0205,	// 
	ARK_FF_PNG					= 0x0206,	// 
	ARK_FF_GIF					= 0x0207,	// 
	ARK_FF_OGGS					= 0x0208,	// OggS
	ARK_FF_MATROSKA				= 0x0209,	// MKV
	ARK_FF_PDF					= 0x020a,	// PDF
	ARK_FF_MP4					= 0x020b,	// MP4 
	ARK_FF_NOTARCHIVE_LAST		= 0x020b,
};

// 암호화 방식
enum ARK_ENCRYPTION_METHOD
{
	ARK_ENCRYPTION_METHOD_NONE				= 0x00,
	ARK_ENCRYPTION_METHOD_ZIP				= 0x01,	// ZipCrypto
	ARK_ENCRYPTION_METHOD_AES128			= 0x02,	// zip
	ARK_ENCRYPTION_METHOD_AES192			= 0x03,	
	ARK_ENCRYPTION_METHOD_AES256			= 0x04,
											
	ARK_ENCRYPTION_METHOD_EGG_ZIP			= 0x05,	// EGG 포맷에서 사용
	ARK_ENCRYPTION_METHOD_EGG_AES128		= 0x06,
	ARK_ENCRYPTION_METHOD_EGG_AES256		= 0x07,
	ARK_ENCRYPTION_METHOD_EGG_LEA128		= 0x08,
	ARK_ENCRYPTION_METHOD_EGG_LEA256		= 0x09,

	ARK_ENCRYPTION_METHOD_RAR				= 0x10,	// RAR 암호 방식
	ARK_ENCRYPTION_METHOD_ACE				= 0x11,	// ACE 암호
	ARK_ENCRYPTION_METHOD_AESCRYPT			= 0x12,	// AesCrypt 암호(AES256)

	ARK_ENCRYPTION_METHOD_ETC				= 0x99,	

	ARK_ENCRYPTION_METHOD_NOTSUPPORTED_FIRST= 0x100,// Not supported encryption method
	ARK_ENCRYPTION_METHOD_GARBLE,					// ARJ 암호 방식
	ARK_ENCRYPTION_METHOD_DES,
	ARK_ENCRYPTION_METHOD_RC2,
	ARK_ENCRYPTION_METHOD_3DES168,
	ARK_ENCRYPTION_METHOD_3DES112,
	ARK_ENCRYPTION_METHOD_PKAES128,
	ARK_ENCRYPTION_METHOD_PKAES192,
	ARK_ENCRYPTION_METHOD_PKAES256,
	ARK_ENCRYPTION_METHOD_RC2_2,
	ARK_ENCRYPTION_METHOD_BLOWFISH,
	ARK_ENCRYPTION_METHOD_TWOFISH,
	ARK_ENCRYPTION_METHOD_RC4,
	ARK_ENCRYPTION_METHOD_UNKNOWN,
};

// 압축 방식
enum ARK_COMPRESSION_METHOD
{
	/////////////////////////////////////////////////////////////////
	// zip 에서 사용하는것들, zip 포맷에 정의된 값과 동일하다.
	// (http://www.pkware.com/documents/casestudies/APPNOTE.TXT 참고)
	ARK_COMPRESSION_METHOD_STORE		=	0,
	ARK_COMPRESSION_METHOD_SHRINK		=	1,
	ARK_COMPRESSION_METHOD_REDUCE1		=	2,
	ARK_COMPRESSION_METHOD_REDUCE2		=	3,
	ARK_COMPRESSION_METHOD_REDUCE3		=	4,
	ARK_COMPRESSION_METHOD_REDUCE4		=	5,
	ARK_COMPRESSION_METHOD_IMPLODE		=	6,
	ARK_COMPRESSION_METHOD_DEFLATE		=	8,

	ARK_COMPRESSION_METHOD_DEFLATE64	=	9,
	ARK_COMPRESSION_METHOD_BZIP2		=	12,
	ARK_COMPRESSION_METHOD_LZMA			=	14,		// zipx, 7zip ...
	ARK_COMPRESSION_METHOD_22			=	22,		// UNKNOWN ZIP METHOD 22(FORZA)
	ARK_COMPRESSION_METHOD_REFERENCE	=	92,		// zipx https://www.winzip.com/en/support/compression-methods/
	ARK_COMPRESSION_METHOD_ZSTD			=	93,		// zipx
	ARK_COMPRESSION_METHOD_PACKMP3		=	94,		// zipx
	ARK_COMPRESSION_METHOD_XZ			=	95,		// zipx
	ARK_COMPRESSION_METHOD_JPEG			=	96,		// zipx
	ARK_COMPRESSION_METHOD_WAVPACK		=	97,		// zipx
	ARK_COMPRESSION_METHOD_PPMD			=	98,		// zipx, 7zip
	ARK_COMPRESSION_METHOD_AES			=	99,		// aes 로 암호화된 zip 파일. 실제 압축 방법은 다른곳에 저장된다.
	// 
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	// ETC
	ARK_COMPRESSION_METHOD_FUSE			=	300,	// bh 에서 사용 
	ARK_COMPRESSION_METHOD_FUSE6		=	301,	// bh 에서 사용 
	ARK_COMPRESSION_METHOD_AZO			=	302,	// egg 에서 사용
	ARK_COMPRESSION_METHOD_COMPRESS		=	303,	// .Z 에서 사용

	ARK_COMPRESSION_METHOD_RAR15		=	400,	// RAR 1.5
	ARK_COMPRESSION_METHOD_RAR20		=	401,	// RAR 2.X
	ARK_COMPRESSION_METHOD_RAR26		=	402,	// RAR 2.X & 2GB 이상
	ARK_COMPRESSION_METHOD_RAR29		=	403,	// RAR 3.X
	ARK_COMPRESSION_METHOD_RAR36		=	404,	// RAR 3.X alternative hash
	ARK_COMPRESSION_METHOD_RAR50		=	405,	// RAR 5.0
	//ARK_COMPRESSION_METHOD_REDIR		=	406,	// Redirect (RAR5)
	ARK_COMPRESSION_METHOD_COPY			=	407,	// COPY (RAR5)

	ARK_COMPRESSION_METHOD_MSZIP		=	500,	// CAB
	ARK_COMPRESSION_METHOD_LHA			=	501,	// lzh
	ARK_COMPRESSION_METHOD_LZMA2		=	502,	// 7z
	ARK_COMPRESSION_METHOD_BCJ			=	503,	// 7z
	ARK_COMPRESSION_METHOD_BCJ2			=	504,	// 7z
	ARK_COMPRESSION_METHOD_LZX			=	505,	// CAB
	ARK_COMPRESSION_METHOD_LZXWIM		=	506,	// wim
	ARK_COMPRESSION_METHOD_OBDEFLATE	=	508,	// Obfuscated deflate (alz)
	ARK_COMPRESSION_METHOD_DELTA		=	509,	// 7z
	ARK_COMPRESSION_METHOD_XPRESS		=	510,	// wim - xpress
	ARK_COMPRESSION_METHOD_SWAP2		=	511,	// SWAP2
	ARK_COMPRESSION_METHOD_SWAP4		=	512,	// SWAP4
	ARK_COMPRESSION_METHOD_ARM			=	513,	// ARM
	ARK_COMPRESSION_METHOD_ARMT			=	514,	// ARMT
	ARK_COMPRESSION_METHOD_IA64			=	515,	// IA64
	ARK_COMPRESSION_METHOD_PPC			=	516,	// PPC
	ARK_COMPRESSION_METHOD_SPARC		=	517,	// SPARC
	ARK_COMPRESSION_METHOD_LZMS			=	518,	// LZMS(WIM)

	ARK_COMPRESSION_METHOD_LH0			=	600,	// -lh0-
	ARK_COMPRESSION_METHOD_LH1			=	601,	// -lh1-
	ARK_COMPRESSION_METHOD_LH2			=	602,	// -lh2-
	ARK_COMPRESSION_METHOD_LH3			=	603,	// -lh3-
	ARK_COMPRESSION_METHOD_LH4			=	604,	// -lh4-
	ARK_COMPRESSION_METHOD_LH5			=	605,	// -lh5-
	ARK_COMPRESSION_METHOD_LH6			=	606,	// -lh6-
	ARK_COMPRESSION_METHOD_LH7			=	607,	// -lh7-
	ARK_COMPRESSION_METHOD_LZS			=	608,	// -lzs-
	ARK_COMPRESSION_METHOD_LZHLZ5		=	609,	// -lz5-
	ARK_COMPRESSION_METHOD_LZHLZ4		=	610,	// -lz4-
	ARK_COMPRESSION_METHOD_LHD			=	611,	// -lhd-
	ARK_COMPRESSION_METHOD_PM0			=	612,	// -pm0-
	ARK_COMPRESSION_METHOD_PM2			=	613,	// -pm2-
	ARK_COMPRESSION_METHOD_PM1			=	614,	// -pm1-

	ARK_COMPRESSION_METHOD_LZX15		=	715,	// LZX (WINDOW SIZE 15bit)
	ARK_COMPRESSION_METHOD_LZX16		=	716,	// 
	ARK_COMPRESSION_METHOD_LZX17		=	717,	// 
	ARK_COMPRESSION_METHOD_LZX18		=	718,	// 
	ARK_COMPRESSION_METHOD_LZX19		=	719,	// 
	ARK_COMPRESSION_METHOD_LZX20		=	720,	// 
	ARK_COMPRESSION_METHOD_LZX21		=	721,	// LZX (WINDOW SIZE 21bit)

	ARK_COMPRESSION_METHOD_QUANTUM10	=	810,	// QTMD(WINDOW SIZE 10bit)
	ARK_COMPRESSION_METHOD_QUANTUM11	=	811,	//
	ARK_COMPRESSION_METHOD_QUANTUM12	=	812,	//
	ARK_COMPRESSION_METHOD_QUANTUM13	=	813,	//
	ARK_COMPRESSION_METHOD_QUANTUM14	=	814,	//
	ARK_COMPRESSION_METHOD_QUANTUM15	=	815,	//
	ARK_COMPRESSION_METHOD_QUANTUM16	=	816,	//
	ARK_COMPRESSION_METHOD_QUANTUM17	=	817,	//
	ARK_COMPRESSION_METHOD_QUANTUM18	=	818,	//
	ARK_COMPRESSION_METHOD_QUANTUM19	=	819,	//
	ARK_COMPRESSION_METHOD_QUANTUM20	=	820,	//
	ARK_COMPRESSION_METHOD_QUANTUM21	=	821,	// QTMD(WINDOW SIZE 21bit)

	ARK_COMPRESSION_METHOD_ARJ1			=	901,	// Arj Method 1
	ARK_COMPRESSION_METHOD_ARJ2			=	902,	//            2
	ARK_COMPRESSION_METHOD_ARJ3			=	903,	//            3
	ARK_COMPRESSION_METHOD_ARJ4			=	904,	//            4

	ARK_COMPRESSION_METHOD_ACELZ77		=	910,	// ace lz77
	ARK_COMPRESSION_METHOD_ACEBLOCKED	=	911,	// ace v20
	//ARK_COMPRESSION_METHOD_ACE		=	912,	// ace 최신?

	ARK_COMPRESSION_METHOD_GRZIP		=	1000,	// FreeARC
	ARK_COMPRESSION_METHOD_4x4			=	1001,
	ARK_COMPRESSION_METHOD_DISPACK		=	1002,
	ARK_COMPRESSION_METHOD_PMM			=	1003,
	ARK_COMPRESSION_METHOD_LZ4B			=	1004,
	ARK_COMPRESSION_METHOD_LZP			=	1005,
	ARK_COMPRESSION_METHOD_MM			=	1006,
	ARK_COMPRESSION_METHOD_REP			=	1007,
	ARK_COMPRESSION_METHOD_TORNADO		=	1008,
	ARK_COMPRESSION_METHOD_TTA			=	1009,
	ARK_COMPRESSION_METHOD_DICT			=	1010,
	ARK_COMPRESSION_METHOD_CRC			=	1011,
	ARK_COMPRESSION_METHOD_FAKE			=	1012,

	ARK_COMPRESSION_METHOD_ARC1			=	1101,	// Arc
	ARK_COMPRESSION_METHOD_ARC2			=	1102,
	ARK_COMPRESSION_METHOD_ARC3			=	1103,
	ARK_COMPRESSION_METHOD_ARC4			=	1104,
	ARK_COMPRESSION_METHOD_ARC5			=	1105,
	ARK_COMPRESSION_METHOD_ARC6			=	1106,
	ARK_COMPRESSION_METHOD_ARC7			=	1107,
	ARK_COMPRESSION_METHOD_ARC8			=	1108,
	ARK_COMPRESSION_METHOD_ARC9			=	1109,

	ARK_COMPRESSION_METHOD_SPARSE		=	1110,	// tar
	ARK_COMPRESSION_METHOD_UU			=	1111,	// UU

	ARK_COMPRESSION_METHOD_BROTLI		=	2001,	// brotli
	ARK_COMPRESSION_METHOD_LZ4_			=	2002,	// https://lz4.github.io/lz4/
	ARK_COMPRESSION_METHOD_LZ5_			=	2003,
	ARK_COMPRESSION_METHOD_LIZARD		=	2004,

	ARK_COMPRESSION_METHOD_ZPAQ			=	3000,	// ZPAQ

	// 
	/////////////////////////////////////////////////////////////////

	ARK_COMPRESSION_METHOD_UNKNOWN		=	9999,	// unknown
};

// 분할 압축 스타일
enum ARK_MULTIVOL_STYLE
{
	ARK_MULTIVOL_STYLE_NONE,			// 분할 압축파일이 아님
	ARK_MULTIVOL_STYLE_001,				// 7zip 의 001, 002, .. 스타일
	ARK_MULTIVOL_STYLE_WINZIP,			// winzip 스타일  (z01, z02 ..... zip)
	ARK_MULTIVOL_STYLE_ZIPX,			// winzip zipx 스타일  (zx01, zx02 ..... zipx)
	ARK_MULTIVOL_STYLE_ALZ,				// alzip 의 alz, a00, a01, a02, .. 스타일
	ARK_MULTIVOL_STYLE_EGG,				// vol1.egg vol2.egg vol3.egg ... 스타일
	ARK_MULTIVOL_STYLE_RAR,				// part1.rar part2.rar ... 스타일
	ARK_MULTIVOL_STYLE_R00,				// .rar .r00 .r01 스타일
	ARK_MULTIVOL_STYLE_RAR5,			// part1.rar (RAR5)
	ARK_MULTIVOL_STYLE_ARJ,				// .arj .a01 .a02 스타일
	ARK_MULTIVOL_STYLE_BAMSFX,			// 밤톨이 sfx (exe, .002 .003 ...)
	ARK_MULTIVOL_STYLE_BDZSFX,			// 반디집 SFX (exe, .e01 .e02 ...)
	ARK_MULTIVOL_STYLE_CAB,				// 분할 cab 파일
	ARK_MULTIVOL_STYLE_ISZ0,			// 분할 ISZ 파일 (isz, i01, i02... )
	ARK_MULTIVOL_STYLE_ISZ1,			// 분할 ISZ 파일 (part01.isz, part02.isz...)
	ARK_MULTIVOL_STYLE_ISZ2,			// 분할 ISZ 파일 (part001.isz, part002.isz...)
	ARK_MULTIVOL_STYLE_IOO,				// 분할 ISO 파일 (i00, i01, i02... )
	ARK_MULTIVOL_STYLE_ACE,				// 분할 ACE 파일 (ace, c00, c01... )
	ARK_MULTIVOL_STYLE_HAOZIP,			// HAOZIP 분할 ZIP ( .haozip01.zip, .haozip02.zip, ...)
	ARK_MULTIVOL_STYLE_PEA,				// PEAZIP 분할 (.000001.pea, .000002.pea, ...)
	//ARK_MULTIVOL_STYLE_ZPAQ,			// 분할 ZPAQ  ( filename*.zpaq)
};


// 파일 속성
#define ARK_FILEATTR					unsigned int
#define ARK_FILEATTR_NONE				0x000
#define ARK_FILEATTR_READONLY			0x001	// FILE_ATTRIBUTE_READONLY
#define ARK_FILEATTR_HIDDEN				0x002	// FILE_ATTRIBUTE_HIDDEN
#define ARK_FILEATTR_SYSTEM				0x004	// FILE_ATTRIBUTE_SYSTEM
#define ARK_FILEATTR_DIRECTORY			0x010	// FILE_ATTRIBUTE_DIRECTORY
#define ARK_FILEATTR_FILE				0x020	// FILE_ATTRIBUTE_ARCHIVE
#define ARK_FILEATTR_SYMLINK			0x400	// FILE_ATTRIBUTE_REPARSE_POINT
#define ARK_FILEATTR_ALL				(ARK_FILEATTR_SYMLINK|ARK_FILEATTR_FILE|ARK_FILEATTR_DIRECTORY|ARK_FILEATTR_SYSTEM|ARK_FILEATTR_HIDDEN|ARK_FILEATTR_READONLY)

// 코드 페이지
#define ARK_CP_UNKNOWN					-1		// 코드페이지가 정의 안된 경우 사용
#define ARK_CP_ACP						0		// == CP_ACP
#define ARK_CP_OEM						1		// == CP_OEMCP
#define ARK_CP_KOR						949		// EUC-KR, CP949 
#define ARK_CP_JPN						932		// SHIFT-JIS, CP932
#define ARK_CP_UTF8						65001	// == CP_UTF8
#define ARK_CP_UTF8_MAC					65002	// 맥용 utf8 코드 페이지


// 기타 정의
#define ARK_FILESIZE_UNKNOWN			(0xffffffffffffffffLL)	// 파일 크기를 알 수 없을때 사용되는 값

// for SWIFT 
#ifdef __cplusplus

// WIN32 이외의 시스템일 경우 기본 타입 정의
#ifndef _WIN32
	#define FALSE               0
	#define TRUE                1
	typedef char				CHAR;
	typedef wchar_t				WCHAR;
	typedef unsigned int		UINT32;
	typedef unsigned long long	UINT64;
	typedef int					INT32;
	typedef const char*			LPCSTR;
	typedef const wchar_t*		LPCWSTR;
#endif

// BOOL 대신 BOOL32 를 사용한다.
typedef int				BOOL32;
typedef unsigned char   ARKBYTE;



#ifndef PURE
#	define PURE                = 0
#endif

#ifdef _WIN32
	typedef signed __int64      INT64;
	#define WINAPI				__stdcall
#else
	typedef signed long long	INT64;
	#define WINAPI				
	#define THREAD_PRIORITY_NORMAL 0
#endif

// Use OS's default packing
#if !defined (__APPLE__) && !defined(__clang__)
#	pragma pack()
#endif

// 인터페이스 메써드 타입 정의
#define ARKMETHOD(type)	virtual type WINAPI

#define ARK_TIME_T			INT64					// time_t 와 동일
struct SArkFileTime									// FILETIME(ntfs)과 동일
{
	UINT32 dwLowDateTime;
	UINT32 dwHighDateTime;
};
struct SArkNtfsFileTimes							// NTSF 파일 시간 정보
{
	SArkFileTime	mtime;							// 마지막 수정 시간
	SArkFileTime	ctime;							// 파일을 생성한 시간
	SArkFileTime	atime;							// 마지막으로 파일에 접근한 시간
};
#define ARK_NOBODY	(-1)							// undefined UID, GID 
struct SArkUnixAttr									// UNIX 파일 시스템 속성
{
	SArkUnixAttr()
	{
		mtime = ctime = atime = 0;
		uid = gid = ARK_NOBODY;
		mode = 0;
	}
	ARK_TIME_T		mtime;							// 마지막 수정 시간
	ARK_TIME_T		ctime;							// 파일을 생성한 시간
	ARK_TIME_T		atime;							// 마지막으로 파일에 접근한 시간
	INT32			uid;							// Unix user ID, ARK_NOBODY 이면 undefined
	INT32			gid;							// Unix group ID, ARK_NOBODY 이면 undefined
	UINT32			mode;							// 파일 모드
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일 아이템 정보
//
struct SArkFileItem
{
	//CHAR*					fileName;				// fileName은 더이상 제공되지 않습니다. fileNameW 만 사용하세요.
	WCHAR*					fileNameW;				// 압축파일에 저장된 파일명 (이 이름은 폴더 경로명도 포함한다)
	WCHAR*					fileCommentW;
	ARK_TIME_T				fileTime;				// last modified(write) time
	INT64					compressedSize;			// 파일의 압축된 크기. 정보가 없으면 -1(ARK_FILESIZE_UNKNOWN)
	INT64					uncompressedSize;		// 파일의 압축해제된 크기. 정보가 없으면 -1(ARK_FILESIZE_UNKNOWN)
	ARK_ENCRYPTION_METHOD	encryptionMethod;
	ARK_FILEATTR			attrib;					// 아이템의 속성
	UINT32					crc32;
	ARK_COMPRESSION_METHOD	compressionMethod;
	SArkNtfsFileTimes*		ntfsFileTimes;			// NTFS 파일 시간 정보. 압축파일에 NTFS 파일정보가 없으면 NULL임
	BOOL32					isUnicodeFileName;		// 유니코드를 지원하는 압축포맷을 통해서 가져온 파일 이름인가? (즉, fileNameW를 100% 믿을 수 있는가)
	SArkUnixAttr*			unixAttr;				// 유닉스 기반의 파일 시스템에서 압축된 경우 유닉스 관련 속성. 관련 속성이 없거나 지원하지 않으면 NULL 임

	BOOL32					IsFolder() const { return attrib & ARK_FILEATTR_DIRECTORY ? TRUE : FALSE;}
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 압축 및 압축 해제 진행 상황 정보
//
struct SArkProgressInfo
{
	void Init1()
	{
		fCurPercent = 0;
		fTotPercent = 0;
		bCompleting = 0;
		fCompletingPercent = 0;
		_processed = 0;
	}
	float		fCurPercent;		// 현재 파일의 압축 해제 진행률(%)
	float		fTotPercent;		// 전체 파일의 압축 해제 진행률(%)
	BOOL32		bCompleting;		// 마무리 중인가?
	float		fCompletingPercent;	// 마무리 중일때 진행률(%)
	int			_processed;			// undocumented - do not use
};

enum ZIP_OPEN_STRATEGY				// ZIP 파일 열기 전략
{
	ZIP_OPEN_STRATEGY_DEFAULT,		// 기본 방법
	ZIP_OPEN_STRATEGY_USESIZEINFO_IF_CENTRALOFFSETINVALID,	// 센트럴 헤더 옵셋 정보에 문제가 있으면 센트럴 헤더 크기 정보로 센트럴 헤더 위치를 찾기
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IArk 속성 설정 (압축풀때)
//
struct SArkProps
{
	SArkProps() { Init(); }
	void Init()
	{
		arkFlags = 0;
		bPrintAssert = TRUE;
		bTreatTGZAsSolidArchive = FALSE;
		bTreatTBZAsSolidArchive = FALSE;
		bAzoSupport = TRUE;
		bTreatUnixZipFileNameAsUTF8 = FALSE;
		bConvertNFD2NFCWhenMacOS = FALSE;
		bIgnoreMacOSXMetaFolder = TRUE;
		bUseLongPathName = FALSE;
		bShortenPathNameWhenTooLong = FALSE;
		//bOpenArchiveWithShareDelete = FALSE;
		dwReadFileShareMode = 1;	// == FILE_SHARE_READ
		bUseRAR5QuickOpen = FALSE;
		bEnableRecoveryModeOpen = FALSE;
		bDeleteOutFileWhenUserCancel = FALSE;
		zipProcessSymbolicLink = TRUE;
		zipProcessStreamingZip = TRUE;
		tarForceUTF8FileName = FALSE;
		zipIgnoreAppleResourceFork = FALSE;
		zipApplyResourceFork2File = FALSE;
		useThreadFileWrite = TRUE;
		copyZoneIdentifierADS = TRUE;
		zipOpenStrategy = ZIP_OPEN_STRATEGY_DEFAULT;
		udfProcessSymLink = TRUE;
		useSetEndofFile2OutFile = TRUE;
		openAllSplitVolume = FALSE;
		setFoldertimeAfterExtraction = FALSE;
		useParallelExtraction = FALSE;
		parallelExtThreadCount = 0;
		sevenZipLzmaExtNumThreads = 0;
		_diableAssert_ = FALSE;
	}
	void InitPosix()
	{
		Init();
		zipProcessSymbolicLink = TRUE;
		bShortenPathNameWhenTooLong = TRUE;
	}
	UINT64	arkFlags;						// 각종 flags
	BOOL32	bPrintAssert;					// ASSERT 발생시 stdout 에 출력 여부 결정(posix 전용)
	BOOL32	bTreatTGZAsSolidArchive;		// TGZ 파일을 솔리드 압축된 파일처럼 처리하기
	BOOL32	bTreatTBZAsSolidArchive;		// TBZ 파일을 솔리드 압축된 파일처럼 처리하기
	BOOL32	bAzoSupport;					// azo 알고리즘 지원 여부
	BOOL32	bTreatUnixZipFileNameAsUTF8;	// zip 파일이 unix 에서 압축된 경우 무조건 utf8 코드페이지 처리
	BOOL32	bConvertNFD2NFCWhenMacOS;		// MAC OS 에서 압축한 파일일 경우 NFD를 NFC로 자동 변환
	BOOL32	bIgnoreMacOSXMetaFolder;		// zip 포맷의 __MACOSX/ 폴더를 무시한다.
	BOOL32	bUseLongPathName;				// 경로명이 260자가 넘어도 파일이나 폴더를 생성하기(Win32 전용)
	BOOL32	bShortenPathNameWhenTooLong;	// 파일/폴더명이 255자 넘으면 이름 길이를 줄여서 풀기
	//BOOL32	bOpenArchiveWithShareDelete;	// 압축파일 열때 FILE_SHARE_DELETE 속성으로 열기(Win32 전용)
	UINT32	dwReadFileShareMode;			// 압축파일 열때 CreateFile 에 전달될 dwShareMode 값
	BOOL32	bUseRAR5QuickOpen;				// RAR5 포맷의 QuickOpen 정보 사용하기
	BOOL32	bEnableRecoveryModeOpen;		// 손상된 압축 파일인 경우, 복구모드로 열어보기
	BOOL32	bDeleteOutFileWhenUserCancel;	// 사용자 취소시 압축 풀던 파일 삭제하기
	BOOL32	zipProcessSymbolicLink;			// ZIP 포맷 - SymbolicLink 일 경우 심볼릭 링크 처리
	BOOL32	zipProcessStreamingZip;			// ZIP 포맷 - 4GB 넘는 스트리밍 ZIP 일 경우, Open() 하면서 파일 목록을 가져올때 로컬 헤더의 위치가 정상적인지 확인 과정을 거친다.
	BOOL32	tarForceUTF8FileName;			// TAR 포맷 - 무조건 파일명에 UTF8 코드페이지 사용
	BOOL32	zipIgnoreAppleResourceFork;		// 맥에서 생성된 "._" 로 시작되는 리소스 포크 파일 무시하고 파일 목록에 추가 안함
	BOOL32	zipApplyResourceFork2File;		// 맥에서 생성된 "._" 로 시작되는 리소스 포크 파일을 압축 해제 시 파일에 써준다
	BOOL32	useThreadFileWrite;				// 파일 쓰기할 때 멀티 스레드를 사용한다.
	BOOL32	copyZoneIdentifierADS;			// 압축을 풀 때, 압축 파일의 Zone.Identifier Alternate Data Stream 을 압축 푼 파일에도 복사해서 저장한다.(Widows 전용)
	ZIP_OPEN_STRATEGY	zipOpenStrategy;	// ZIP 파일의 헤더를 분석할 때 사용할 전략
	BOOL32	udfProcessSymLink;				// UDF 포맷 - SymbolicLink 일 경우 심볼릭 링크 처리 
	BOOL32	useSetEndofFile2OutFile;		// 출력 파일에 SetEndOfFile() 사용
	BOOL32	openAllSplitVolume;				// 분할 압축된 파일된 파일의 2번째 이후의 파일도 단독으로 열기
	BOOL32	setFoldertimeAfterExtraction;	// 압축 해제가 완료된 다음 폴더의 시간을 다시한번 설정합니다.
	BOOL32	useParallelExtraction;			// 병렬 압축 해제 사용 (지원하는 포맷에 한하여)
	UINT32	parallelExtThreadCount;			// 멀티 스레드를 지원하는 압축 해제 시 사용할 스레드 개수. 0 이면 자동.
	UINT32	sevenZipLzmaExtNumThreads;		// 7Z 포맷의 LZMA2 압축 해제 시 사용할 스레드 개수. 0 이면 자동
	BOOL32  _diableAssert_;					// 디버그 ASSERT 처리
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 압축 해제 진행 상황
//
enum ARK_OVERWRITE_MODE					// 파일 덮어쓰기 질문에 대한 사용자 대답
{
	ARK_OVERWRITE_MODE_OVERWRITE,
	ARK_OVERWRITE_MODE_SKIP, 
	ARK_OVERWRITE_MODE_RENAME,
	ARK_OVERWRITE_MODE_QUIT,
};
enum ARK_PASSWORD_RET					// 파일 암호 질문에 대한 사용자 대답
{
	ARK_PASSWORD_RET_OK,				// 사용자 OK
	ARK_PASSWORD_RET_CANCEL,			// 사용자 취소
	ARK_PASSWORD_RET_UNDEF,				// 사용자에게 물어보지 않음
};
enum ARK_PASSWORD_ASKTYPE				// OnAskPassword() 호출 이유
{
	ARK_PASSWORD_ASKTYPE_PASSWDNOTSET,	// 암호가 지정되지 않았음
	ARK_PASSWORD_ASKTYPE_INVALIDPASSWD,	// 기존에 지정된 암호가 틀렸음
};
struct ISetStr
{
	ARKMETHOD(void)			Set(LPCWSTR str) PURE;
};

struct IArkEvent
{
	ARKMETHOD(void)			OnOpeningMultivolArchive(LPCSTR archivePathNameA, LPCWSTR archivePathNameW, int archiveVol, BOOL32& bStop) PURE;
	ARKMETHOD(void)			OnOpening(const SArkFileItem* pFileItem, float progress, BOOL32& bStop) PURE;

	ARKMETHOD(void)			OnStartFile(const SArkFileItem* pFileItem, BOOL32& bStopCurrent, BOOL32& bStopAll, int index, LPCWSTR itemFullPathName, ISetStr* changeFullPathName) PURE;
	ARKMETHOD(void)			OnProgressFile(const SArkProgressInfo* pProgressInfo, BOOL32& bStopCurrent, BOOL32& bStopAll) PURE;
	ARKMETHOD(void)			OnCompleteFile(const SArkProgressInfo* pProgressInfo, ARKERR nErr) PURE;

	ARKMETHOD(void)			OnError(ARKERR nErr, const SArkFileItem* pFileItem, BOOL32 bIsWarning, BOOL32& bStopAll) PURE;
	ARKMETHOD(void)			OnMultiVolumeFileChanged(LPCWSTR szPathFileName) PURE;

	ARKMETHOD(void)			OnAskOverwrite(const SArkFileItem* pFileItem, LPCWSTR szLocalPathName, ARK_OVERWRITE_MODE& overwrite, ISetStr* changeLocalPathName) PURE;
	ARKMETHOD(void)			OnAskPassword(const SArkFileItem* pFileItem, ARK_PASSWORD_ASKTYPE askType, ARK_PASSWORD_RET& ret, ISetStr* setPasswd) PURE;
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 압축파일 출력 스트림
//
struct IArkSimpleOutStream
{
	ARKMETHOD(BOOL32)		Open(LPCWSTR szPathName) PURE;
	ARKMETHOD(BOOL32)		SetSize(INT64 nSize) PURE;
	ARKMETHOD(BOOL32)		Write(const void* lpBuffer, UINT32 nNumberOfBytesToWrite) PURE;
	ARKMETHOD(BOOL32)		Close() PURE;
	ARKMETHOD(BOOL32)		CreateFolder(LPCWSTR szPathName) PURE;
	ARKMETHOD(INT64)		SetPos(INT64 pos) PURE;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 압축파일 입력 스트림
//
struct IArkSimpleInStream
{
	ARKMETHOD(BOOL32)		Read(void* lpBuffer, UINT32 nNumberOfBytesToRead, UINT32* lpNumberOfBytesRead) PURE;
	ARKMETHOD(INT64)		SetPos(INT64 pos) PURE;
	ARKMETHOD(INT64)		GetPos() const PURE;
	ARKMETHOD(INT64)		GetSize() PURE;
	ARKMETHOD(BOOL32)		Close() PURE;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MBCS 처리용 코드페이지
//
struct SArkCodepage
{
	SArkCodepage(){Init();}
	void Init()
	{
		#ifdef _WIN32
		  fileSystem = ARK_CP_ACP;
		#else
		  fileSystem = ARK_CP_UTF8;	// POSIX 는 파일시스템에 보통 UTF8 코드페이지 사용
		#endif
		fileName = ARK_CP_OEM;		// ZIP 포맷은 DOS 호환으로 ACP 대신 OEM 을 사용한다.
		comment = ARK_CP_ACP;
		password = ARK_CP_ACP;
	}
	int		fileSystem;				// 파일 시스템을 통해 압축파일을 열 때 사용하는 코드페이지. 보통 CP_ACP
	int		fileName;				// 압축파일 내부의 파일명을 처리할 때 사용하는 코드페이지. 보통 CP_OEM
	int		comment;				// 압축파일 내부의 코멘트를 처리할 때 사용하는 코드페이지. 보통 CP_ACP
	int		password;				// MBCS 암호를 처리할 때 사용하는 코드페이지. 보통 CP_ACP
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 압축파일의 압축 해제 인터페이스
//
struct IArk
{
	ARKMETHOD(void)					Release() PURE;
	ARKMETHOD(BOOL32)				Verify(LPCSTR id, LPCSTR key) PURE;
									
	ARKMETHOD(BOOL32)  				Open(LPCSTR  filePath, LPCSTR password) PURE; 
	ARKMETHOD(BOOL32)  				Open(LPCWSTR filePath, LPCWSTR password) PURE; 
	ARKMETHOD(BOOL32)				Open(ARKBYTE* src, int srcLen, LPCWSTR password) PURE;
	ARKMETHOD(BOOL32)  				Open(IArkSimpleInStream* srcStream, LPCWSTR password) PURE; 
	ARKMETHOD(void)					Close() PURE;
	ARKMETHOD(BOOL32)  				TestArchive() PURE; 

	ARKMETHOD(ARK_FF)  				CheckFormat(LPCSTR  filePath) const PURE; 
	ARKMETHOD(ARK_FF)  				CheckFormat(LPCWSTR filePath) const PURE; 
	ARKMETHOD(ARK_FF)  				CheckFormat(const unsigned char* buffer, size_t bufLen) const PURE;

	ARKMETHOD(void)					SetPassword(LPCSTR password) PURE;
	ARKMETHOD(void)					SetPassword(LPCWSTR password) PURE;
	ARKMETHOD(int)					GetFileItemCount() const PURE;
	ARKMETHOD(const SArkFileItem*)	GetFileItem(int index) const PURE;
	ARKMETHOD(ARK_FF)				GetFileFormat() const PURE;
	ARKMETHOD(BOOL32)				IsBrokenArchive() const PURE;
	ARKMETHOD(BOOL32)				IsEncryptedArchive() const PURE;
	ARKMETHOD(BOOL32)				IsSolidArchive() const PURE;
	ARKMETHOD(BOOL32)				IsOpened() const PURE;
	ARKMETHOD(BOOL32)				IsEditable() const PURE;

	ARKMETHOD(BOOL32)				ExtractAllTo(LPCSTR folderPath, LPCWSTR path2remove) PURE;		// 전체 파일 풀기
	ARKMETHOD(BOOL32)				ExtractAllTo(LPCWSTR folderPath, LPCWSTR path2remove) PURE;
	ARKMETHOD(BOOL32)				ExtractAllTo(IArkSimpleOutStream* outStream, LPCWSTR path2remove) PURE;

	ARKMETHOD(BOOL32)				ExtractOneTo(int index, LPCWSTR folderPath) PURE;				// 파일 하나 풀기
	ARKMETHOD(BOOL32)				ExtractOneTo(int index, LPCSTR folderPath) PURE;
	ARKMETHOD(BOOL32)				ExtractOneTo(int index, IArkSimpleOutStream* outStream) PURE;
	ARKMETHOD(BOOL32)				ExtractOneTo(int index, ARKBYTE* outBuf, int outBufLen) PURE;
	ARKMETHOD(BOOL32)				ExtractOneAs(int index, LPCWSTR filePathName, WCHAR* resultPathName, int resultPathNameLen) PURE;			// 파일명을 지정해서 파일 하나 풀기

	ARKMETHOD(BOOL32)				AddIndex2ExtractList(int index) PURE;						// 압축풀 파일 인덱스를 목록에 추가
	ARKMETHOD(void)					ClearExtractList() PURE;									// 압축풀 파일 목록 삭제하기
	ARKMETHOD(int)					GetExtractListCount() const PURE;							// 압축풀 파일 목록의 개수
	ARKMETHOD(BOOL32)				ExtractMultiFileTo(LPCSTR szDestPath) PURE;					// 몇개 파일 풀기
	ARKMETHOD(BOOL32)				ExtractMultiFileTo(LPCWSTR szDestPath, LPCWSTR szPath2Remove=NULL) PURE;
	ARKMETHOD(BOOL32)				ExtractMultiFileTo(IArkSimpleOutStream* outStream) PURE;

	ARKMETHOD(BOOL32)				SetEvent(IArkEvent* pEvent) PURE;
	ARKMETHOD(ARKERR)				GetLastError() const PURE;
	ARKMETHOD(UINT32)				GetLastSystemError() const PURE;
	ARKMETHOD(void)					SetCodePage(SArkCodepage cp) PURE;

	ARKMETHOD(LPCWSTR)				EncryptionMethod2Str(ARK_ENCRYPTION_METHOD method) const PURE;
	ARKMETHOD(LPCWSTR)				CompressionMethod2Str(ARK_COMPRESSION_METHOD method) const PURE;
	ARKMETHOD(LPCWSTR)				FileFormat2Str(ARK_FF ff) const PURE;

	ARKMETHOD(void)					SetProps(const SArkProps& props) PURE;
	ARKMETHOD(INT64)				GetArchiveFileSize() const PURE;
	ARKMETHOD(INT64)				GetArchiveStartPos() const PURE;
	ARKMETHOD(LPCWSTR)				GetFilePathName() const PURE;
	ARKMETHOD(int)					FindIndex(LPCWSTR szFileNameW, LPCSTR szFileNameA, BOOL32 bCaseSensitive) const PURE;
	ARKMETHOD(LPCWSTR)				GetArchiveComment() const PURE;

	ARKMETHOD(ARK_MULTIVOL_STYLE)	GetMultivolStyle() const PURE;
	ARKMETHOD(size_t)				GetMultivolCount() const PURE;
	ARKMETHOD(LPCWSTR)				GetMultivolFilePathName(size_t volume) const PURE;

	//ARKMETHOD(BOOL32)				DetectCurrentArchivesCodepage(SArkDetectCodepage& dcp) const PURE;
	ARKMETHOD(BOOL32)				ChangeCurrentArchivesCodepage(int codePage) PURE;

	ARKMETHOD(BOOL32)				LoadArkLGPL(const char* pathName) PURE;
	ARKMETHOD(BOOL32)				LoadArkLGPL(const wchar_t* pathName) PURE;
	ARKMETHOD(BOOL32)				UnloadArkLGPL() PURE;

	ARKMETHOD(BOOL32)				ChangeArkFileName(const SArkFileItem* item, const wchar_t* newFileName) PURE;

	ARKMETHOD(UINT32)  				_CheckCRC32(LPCWSTR filePath) PURE;

};


/////////////////////////////////////////////////////////
//
// IArkCompressor 속성 설정
//
enum ARK_ZIPOS
{
	ARK_ZIPOS_UNKNOWN = -1,
	ARK_ZIPOS_DOS = 0,
	ARK_ZIPOS_UNIX = 3,
};
struct SArkCompProps
{
	SArkCompProps(){Init();}
	void Init()
	{
		ff = ARK_FF_ZIP;
		deleteArchiveWhenFailed = TRUE;
		saveNTFSTime = FALSE;
		streamOutput = FALSE;
		compressionMethod = ARK_COMPRESSION_METHOD_DEFLATE;
		encryptionMethod = ARK_ENCRYPTION_METHOD_ZIP;
		compressionLevel = -1;							// -1 은 Z_DEFAULT_COMPRESSION
		splitSize = 0;
		forceZip64 = FALSE;
		useDosTime2PasswordCheck = TRUE;
		sfxPathName = NULL;
		forceUtf8FileNameZip = FALSE;
		saveInfozipUnicodePath = TRUE;
		saveUnixExtendedTimeStamp = FALSE;
		forceUtf8FileNameTar = FALSE;
		forceUtf8Comment = FALSE;
		utf8FileNameIfNeeded = TRUE;
		bypassWhenUncompressible = FALSE;
		lzmaEncodeThreadCount = 2;
		enableMultithreadDeflate = FALSE;
		deflateEncodeThreadCount = 0;
		deflateUseZopfli = FALSE;
		_7zCompressHeader = TRUE;
		_7zEncryptHeader = FALSE;
		_7zSolidBlockSize = ARK_FILESIZE_UNKNOWN;
		lzma2NumBlockThreads = -1;
		threadPriority = THREAD_PRIORITY_NORMAL;
		lzma2AutoReduceThreadCount = TRUE;
		sortItemBeforeArchive = TRUE;
		convertNFD2NFC = FALSE;
		zipProcessSymbolicLink = FALSE;
		zipOSwhenUTF8 = zipOS = ARK_ZIPOS_DOS;
		caseSensitive = FALSE;
		tarProcessSymbolicLink = FALSE;
		tarProcessHardLink = FALSE;
		openWritableSrcFile = FALSE;
		_showDebugMessages_ = FALSE;
		_diableAssert_ = FALSE;
		_repairMode_ = FALSE;
	}
	void InitPosix(ARK_ZIPOS zipTarget)
	{
		Init();
		forceUtf8FileNameTar = TRUE;
		saveUnixExtendedTimeStamp = TRUE;
		convertNFD2NFC = TRUE;
		tarProcessSymbolicLink = TRUE;
		tarProcessHardLink = TRUE;

		zipOS = zipTarget;
		zipOSwhenUTF8 = ARK_ZIPOS_UNIX;
		if (zipTarget == ARK_ZIPOS_DOS)
		{
			// 기본 파일명은 MBCS + 확장필드에 유니코드 저장
			forceUtf8FileNameZip = FALSE;
			saveInfozipUnicodePath = TRUE;
		}
		else if (zipTarget == ARK_ZIPOS_UNIX)
		{
			// 기본 파일명을 유니코드로 저장
			forceUtf8FileNameZip = TRUE;
			saveInfozipUnicodePath = FALSE;
		}

	}
	ARK_FF					ff;							// 파일 포맷 ARK_FF_ZIP, ARK_FF_TAR, ARK_FF_TGZ, ARK_FF_7Z, ARK_FF_LZH, ARK_FF_XZ, ARK_FF_GZ, ARK_FF_ISO
	BOOL32					deleteArchiveWhenFailed;	// 압축중 에러 발생시 생성된 파일 삭제하기
	BOOL32					saveNTFSTime;				// ZIP - ntfs 시간 저장 여부
	BOOL32					streamOutput;				// ZIP - stream 형태로 저장 - 이 값이 TRUE 일 경우 열지 못하는 프로그램이 너무 많음.
	ARK_COMPRESSION_METHOD	compressionMethod;			// 압축 방식 ( ARK_COMPRESSION_METHOD_STORE, ARK_COMPRESSION_METHOD_DEFLATE, ARK_COMPRESSION_METHOD_LZMA )
	ARK_ENCRYPTION_METHOD	encryptionMethod;			// 파일에 암호를 걸 경우 사용할 암호 방식 ( ARK_ENCRYPTION_METHOD_ZIP, ARK_ENCRYPTION_METHOD_AES256 만 유효)
	int						compressionLevel;			// 압축 레벨 ( Z_NO_COMPRESSION, Z_BEST_SPEED ~ Z_BEST_COMPRESSION )
	INT64					splitSize;					// 분할 압축 크기 (bytes,  0 이면 분할 압축 안함)
	BOOL32					forceZip64;					// ZIP - 강제로 zip64 정보 저장
	BOOL32					useDosTime2PasswordCheck;	// ZIP - 암호 체크 데이터를 crc 대신 dostime 을 사용한다. (사용시 압축 속도 향상)
	LPCWSTR					sfxPathName;				// SFX - sfx를 만들경우 sfx 파일경로명. NULL 이면 사용하지 않음.
	BOOL32					forceUtf8FileNameZip;		// ZIP - zip 포맷의 기본 파일명을 항상 utf8 로 저장
	BOOL32					forceUtf8FileNameTar;		// TAR - tar/tgz 포맷의 파일명을 항상 utf8 로 저장
	BOOL32					forceUtf8Comment;			// ZIP - 압축파일 설명을 utf8 로 저장 (다른 프로그램과 호환되지 않음)
	BOOL32					utf8FileNameIfNeeded;		// ZIP - 파일명에 유니코드가 포함되어 있을 경우 utf8 로 저장
	BOOL32					saveInfozipUnicodePath;		// ZIP - 파일명에 ASCII 이외의 문자가 포함된 경우 extra field 에 info-zip unicode path 정보 저장
	BOOL32					saveUnixExtendedTimeStamp;	// ZIP - EXTRA FIELD 에 UNIX TIME 과 UID, GID 를 저장한다.
	BOOL32					bypassWhenUncompressible;	// ZIP - 압축중 압축이 안될경우 그냥 bypass
	int						lzmaEncodeThreadCount;		// 7Z/ZIPX - LZMA 압축시 스레드 카운트. 1~2
	BOOL32					enableMultithreadDeflate;	// ZIP - Deflate 압축시 멀티 스레드 사용
	int						deflateEncodeThreadCount;	// ZIP - Deflate 압축시 사용할 스레드 개수. 0 이면 시스템 개수만큼
	BOOL32					deflateUseZopfli;			// ZIP - Deflate 압축시 zopfli 사용

	BOOL32					_7zCompressHeader;			// 7zip 압축시 헤더를 압축할 것인가?
	BOOL32					_7zEncryptHeader;			// 7zip 압축시 헤더를 암호화 할 것인가? (암호 지정시)
	INT64					_7zSolidBlockSize;			// 7zip 압축할 때 솔리드 블럭 크기. 0 이면 솔리드 사용 안함. -1 이면 전체 솔리드
	int						lzma2NumBlockThreads;		// lzma2 압축시 스레드 개수, 0 이면 시스템 개수만큼
	int						threadPriority;				// 멀티코어를 이용해서 압축시 스레드 우선 순위
	BOOL32					lzma2AutoReduceThreadCount;	// lzma2 압축시 시스템의 메모리가 부족한 경우 자동으로 스레드 숫자 감소시키기
	BOOL32					sortItemBeforeArchive;		// 압축하기 전에 아이템을 경로명으로 소트하여 저장하기(현재 zip포맷만 지원)
	BOOL32					convertNFD2NFC;				// 압축 포맷에 저장될 파일명을 NFD 에서 NFC 로 변환하기
	ARK_ZIPOS				zipOS;						// ZIP - ZIP 포맷 생성시 헤더에 저장될 생성 OS 종류
	ARK_ZIPOS				zipOSwhenUTF8;				// ZIP - ZIP 포맷 생성시 파일명이 강제로 UTF8 로 변환될때 헤더에 사용할 OS 종류
	BOOL32					zipProcessSymbolicLink;		// ZIP - 압축 대상이 심볼릭 링크인 경우, 원본 파일 대신 심볼릭 링크 정보만 저장
	BOOL32					caseSensitive;				// 압축할 파일의 목록을 관리할 때 대소문자를 구분할지 여부를 지정한다. 기본값은 FALSE
	BOOL32					tarProcessSymbolicLink;		// TAR - 압축 대상이 심볼릭 링크인 경우, 원본 파일 대신 심볼릭 링크 정보만 저장
	BOOL32					tarProcessHardLink;			// TAR - 압축 대상이 하드 링크인 경우, 원본 파일 대신 하드 링크 정보만 저장
	BOOL32					openWritableSrcFile;		// 압축하려는 파일이 쓰기 가능한 상태로 열려있어도 압축하기. Win32 전용
	BOOL32					_showDebugMessages_;		// 내부 디버그 메시지 출력하기 - 내부 디버깅용. 사용하지 마셈
	BOOL32					_diableAssert_;				// 디버그 ASSERT 처리
	BOOL32					_repairMode_;				// 압축파일 복구 모드
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 압축파일 만들기 인터페이스
//
struct IArkCompressor
{
	ARKMETHOD(void)			Release() PURE;												// 객체 해제

	ARKMETHOD(void)			Init() PURE;												// 초기화 (새로운 압축파일 생성 시작)
	ARKMETHOD(void)			SetCodePage(SArkCodepage cp) PURE;
	ARKMETHOD(void)			SetEvent(IArkEvent* pEvent) PURE;							// 반드시 Init() 호출후 매번 호출해야 한다.
	ARKMETHOD(BOOL32)		SetProps(SArkCompProps& props, const ARKBYTE* password, int pwLen) PURE;// CreateArchive() 호출전에만 호출하면 언제 호출해도 상관없고, 한번 호출하면 끝
	ARKMETHOD(BOOL32)		SetProps7z(SArkCompProps& props, LPCWSTR password) PURE;

	ARKMETHOD(BOOL32)		AddFileItem(LPCWSTR szSrcPathName, LPCWSTR szTargetPathName, BOOL32 overwrite, LPCWSTR szFileComment = NULL, INT64 fileSize = -1) PURE;
	ARKMETHOD(BOOL32)		AddFileItem2(LPCWSTR szSrcPathName, LPCWSTR szTargetPathName, BOOL32 overwrite, BOOL32 caseSensitive, LPCWSTR szFileComment = NULL) PURE;

	ARKMETHOD(int)			FindFileItemIndex2Add(LPCWSTR szTargetPathName) PURE;						// 기존 목록에 존재하는지 확인한다.
	ARKMETHOD(int)			FindFileItemIndex2Add2(LPCWSTR szTargetPathName, BOOL32 caseSensitive) PURE;
	ARKMETHOD(BOOL32)		GetFileItemInfo(int index, INT64& fileSize, ARK_TIME_T& fileTime) PURE;		// 목록에 있는 파일의 정보 가져오기
	ARKMETHOD(INT64)		GetTotalFileSize2Archive() PURE;
	ARKMETHOD(BOOL32)		CreateArchive(LPCWSTR szPathName, LPCWSTR szArchiveComment=NULL) PURE;
	ARKMETHOD(ARKERR)		GetLastError() const PURE;

	ARKMETHOD(BOOL32)		SetArchiveFile(IArk* pArchive) PURE;						// 원본 파일 세팅 
	ARKMETHOD(BOOL32)		RenameItem(int index, LPCWSTR szPathName) PURE;				// SetArchiveFile() 로 지정한 파일의 이름을 바꾼다.
	ARKMETHOD(BOOL32)		DeleteItem(int index) PURE;									// SetArchiveFile() 로 지정한 파일을 삭제한다.

};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IArk, IArkCompressor 객체를 생성합니다. SDKVersion 파라미터는 ARK_LIBRARY_VERSION 을 넘기면 됩니다.
//

#ifdef _WIN32
extern "C" __declspec(dllexport) IArk*				__cdecl	CreateArk(UINT32 SDKVersion);
extern "C" __declspec(dllexport) IArkCompressor*	__cdecl CreateArkCompressor(UINT32 SDKVersion);
extern "C" IArkCompressor*							__cdecl	CreateArkCompressorLib(UINT32 SDKVersion);
extern "C" IArk*									__cdecl	CreateArkLib(UINT32 SDKVersion);
#else
extern "C" IArkCompressor*							CreateArkCompressorLib(UINT32 SDKVersion);
extern "C" IArk*									CreateArkLib(UINT32 SDKVersion);
#endif

#endif	// __cplusplus

#endif	// _ARK_H_
