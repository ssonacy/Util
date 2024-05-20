#pragma once

typedef unsigned (__stdcall * ThreadProcType) (void *);

enum class ThreadReq
{
	NONE,		 // 초기값
	WORKING,	 // 작업을 요청할때
	SLEEP,		 // Sleep을 요청할때
	TERMINATING, // 종료를 요청할때
};

enum class ThreadRes
{
	NONE,		// 초기값
	WORKING,	// 작업 중일때
	SLEEPING,	// Sleep이 되었을때
	TERMINATED,	// 스레드가 종료 중이거나 종료 되었을때
};

class CThread
{
public:

	CThread() = default;
	virtual ~CThread();

	BOOL Start( ThreadProcType pFunctionProc , void* pParm , BOOL Suspend );
	void Exit( DWORD WaitTick );

	void Suspend( DWORD dwSleepTick = INFINITE );
	void Resume();
	
	inline BOOL		 IsValid()		const { return m_hThread != NULL;	}
	inline ThreadRes GetResStatus() const { return m_CurResponse;		}

	inline BOOL IsResStatus( ThreadRes Res ) const { return m_CurResponse == Res; }
	inline BOOL IsReqStatus( ThreadReq Req ) const { return m_CurRequest == Req;  }

	inline HANDLE GetHandle() const { return m_hThread; }

private:

	static unsigned int __stdcall ThreadFunStub( void* param );
		unsigned int ThreadFun();

	static void __stdcall WakeUpFn( ULONG_PTR ) { /* do nothing */ }

private:

	ThreadReq m_CurRequest	= ThreadReq::NONE;  // Thread 에게 요청시에 대입한다.
	ThreadRes m_CurResponse	= ThreadRes::NONE; // Thread 의 현재 상태 값이다.

	HANDLE m_hThread = NULL;	// 스레드 핸들

	ThreadProcType	m_pFun  = NULL;	// 호출할 함수 포인터 주소
	void*			m_pParm = NULL;	// 호출할 함수의 추가 파라미터

	DWORD m_dwSleepTick = 0;	// REQUEST_SLEEP 요청을 받았을때 얼마만큼 대기 할것인지를 결정하는 변수
};

namespace ThreadUtil
{
	// Thread 에 해당 하는 스레드가 현재 어느 주소에 존재하는 명령어를 실행중인지 리턴.
	DWORD64	GetProgramCounter( HANDLE Thread );

	// Thread가 현제 수행하고 있는 코드의 위치를 EqualCount 만큼 비교해서 동일하면 리턴 TRUE (WaitTick 후에 타임아웃실패 FALSE )
	BOOL WaitForThreadAtAddress( HANDLE Thread , int EqualCount , ULONGLONG WaitTick );

	// Thread의 현재 콜 스택에 FuncName이 존재하면 TRUE 그렇치 않거나 오류 상태면 FALSE
	BOOL HasCallStack( HANDLE Thread , const CStringA& FuncName );
};