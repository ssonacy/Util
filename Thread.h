#pragma once

typedef unsigned (__stdcall * ThreadProcType) (void *);

enum class ThreadReq
{
	NONE,		 // �ʱⰪ
	WORKING,	 // �۾��� ��û�Ҷ�
	SLEEP,		 // Sleep�� ��û�Ҷ�
	TERMINATING, // ���Ḧ ��û�Ҷ�
};

enum class ThreadRes
{
	NONE,		// �ʱⰪ
	WORKING,	// �۾� ���϶�
	SLEEPING,	// Sleep�� �Ǿ�����
	TERMINATED,	// �����尡 ���� ���̰ų� ���� �Ǿ�����
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

	ThreadReq m_CurRequest	= ThreadReq::NONE;  // Thread ���� ��û�ÿ� �����Ѵ�.
	ThreadRes m_CurResponse	= ThreadRes::NONE; // Thread �� ���� ���� ���̴�.

	HANDLE m_hThread = NULL;	// ������ �ڵ�

	ThreadProcType	m_pFun  = NULL;	// ȣ���� �Լ� ������ �ּ�
	void*			m_pParm = NULL;	// ȣ���� �Լ��� �߰� �Ķ����

	DWORD m_dwSleepTick = 0;	// REQUEST_SLEEP ��û�� �޾����� �󸶸�ŭ ��� �Ұ������� �����ϴ� ����
};

namespace ThreadUtil
{
	// Thread �� �ش� �ϴ� �����尡 ���� ��� �ּҿ� �����ϴ� ��ɾ ���������� ����.
	DWORD64	GetProgramCounter( HANDLE Thread );

	// Thread�� ���� �����ϰ� �ִ� �ڵ��� ��ġ�� EqualCount ��ŭ ���ؼ� �����ϸ� ���� TRUE (WaitTick �Ŀ� Ÿ�Ӿƿ����� FALSE )
	BOOL WaitForThreadAtAddress( HANDLE Thread , int EqualCount , ULONGLONG WaitTick );

	// Thread�� ���� �� ���ÿ� FuncName�� �����ϸ� TRUE �׷�ġ �ʰų� ���� ���¸� FALSE
	BOOL HasCallStack( HANDLE Thread , const CStringA& FuncName );
};