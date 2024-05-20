#include "stdafx.h"
#include "Thread.h"
#include <process.h>
#include <dbghelp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

CThread::~CThread()
{
	try
	{
		Exit( INFINITE );
	}
	catch(...) { /*Do Noting*/ }
}

unsigned int __stdcall CThread::ThreadFunStub( void* param )
{
	CThread* this_ = (CThread*)param;
	return this_->ThreadFun();
}

unsigned int CThread::ThreadFun()
{
	if ( !m_pFun ) return -1;

	while ( m_CurRequest != ThreadReq::TERMINATING )
	{
		if ( m_CurRequest == ThreadReq::SLEEP )
		{
			m_CurResponse = ThreadRes::SLEEPING;
			SleepEx( m_dwSleepTick , TRUE );
		}
		else if ( m_CurRequest == ThreadReq::WORKING )
		{
			m_CurResponse = ThreadRes::WORKING;
			m_pFun( m_pParm );
		}
	}

	m_CurResponse = ThreadRes::TERMINATED;

	return 0;
}

BOOL CThread::Start( ThreadProcType pFunctionProc , void* pParm , BOOL Suspend )
{
	if ( !pFunctionProc ) return FALSE;

	Exit( INFINITE );

	m_pFun  = pFunctionProc;
	m_pParm = pParm;
	
	if ( Suspend )
	{
		m_CurRequest = ThreadReq::SLEEP;
		m_dwSleepTick = INFINITE;
	}
	else
	{
		m_CurRequest = ThreadReq::WORKING;
	}

	DWORD ThreadId = 0;
	m_hThread = (HANDLE)_beginthreadex( NULL , 0 , ThreadFunStub , this , 0 , (unsigned int*)&ThreadId );

	return m_hThread != NULL;
}

void CThread::Exit( DWORD WaitTick )
{
	if ( !m_hThread ) return;

	m_CurRequest = ThreadReq::TERMINATING;
	QueueUserAPC( CThread::WakeUpFn , m_hThread ,  NULL );

	WaitForSingleObject( m_hThread , WaitTick );

	CLOSE_HANDLE( m_hThread );
	m_pParm = NULL;
}

void CThread::Suspend( DWORD dwSleepTick )
{
    // dh.kim 2019-03-12 11:34:52 : 이미 Req::Terminating 요청이 있었다면 무시한다.
    if ( m_CurRequest == ThreadReq::TERMINATING ) return;

	m_CurRequest  = ThreadReq::SLEEP;
	m_dwSleepTick = dwSleepTick;
}

void CThread::Resume()
{
    // dh.kim 2019-03-12 11:34:52 : 이미 Req::Terminating 요청이 있었다면 무시한다.
    if ( m_CurRequest == ThreadReq::TERMINATING || !m_hThread ) return;

	m_CurRequest  = ThreadReq::WORKING;
	m_dwSleepTick = 0;

	QueueUserAPC( CThread::WakeUpFn , m_hThread ,  NULL );
}

namespace ThreadUtil
{
	DWORD64	GetProgramCounter( HANDLE Thread )
	{
		CONTEXT Context = { 0 , };
		Context.ContextFlags = CONTEXT_CONTROL;

		if ( !GetThreadContext( Thread , &Context ) ) return -1;

		return Context.Rip;
	}

	BOOL WaitForThreadAtAddress( HANDLE Thread , int EqualCount , ULONGLONG WaitTick )
	{
		ULONGLONG Begin = GetTickCount64();

		do 
		{
			for ( int i = 1 ; i <= EqualCount ; ++i )
			{
				DWORD64 IP1 = GetProgramCounter( Thread );
				Sleep(0);
				DWORD64 IP2 = GetProgramCounter( Thread );

				if ( IP1 != IP2 ) break;
				if ( i == EqualCount ) return TRUE;
			}

		} while ( GetTickCount64() - Begin < WaitTick );

		return FALSE;
	}

	BOOL HasCallStack( HANDLE Thread , const CStringA& FuncName )
	{	
		CONTEXT Context = { 0 , };
		Context.ContextFlags = CONTEXT_FULL;

		if ( !GetThreadContext( Thread , &Context ) ) return FALSE;

		STACKFRAME	StackFrame  = { 0 , };
		DWORD		MachineType = 0;

		StackFrame.AddrPC.Mode = AddrModeFlat;
		StackFrame.AddrStack.Mode = AddrModeFlat;
		StackFrame.AddrFrame.Mode = AddrModeFlat;

#if defined(_M_X64) || defined(_M_AMD64)
		MachineType = IMAGE_FILE_MACHINE_AMD64;
		StackFrame.AddrPC.Offset = Context.Rip;
		StackFrame.AddrStack.Offset = Context.Rsp;
		StackFrame.AddrFrame.Offset = Context.Rbp;
#elif defined(_M_IX86)
		MachineType = IMAGE_FILE_MACHINE_I386;
		StackFrame.AddrPC.Offset = Context.Eip;
		StackFrame.AddrStack.Offset = Context.Esp;
		StackFrame.AddrFrame.Offset = Context.Ebp;
#endif

		if ( !SymInitialize( GetCurrentProcess() , NULL , TRUE ) ) return FALSE;

		while ( StackWalk( MachineType , GetCurrentProcess() , Thread , &StackFrame , &Context , NULL , SymFunctionTableAccess , SymGetModuleBase , NULL ) )
		{
			DWORD64 Address = StackFrame.AddrPC.Offset;
			if (Address == 0) break;

			char symbolBuffer[sizeof(IMAGEHLP_SYMBOL) + 256] = { 0 , };
			PIMAGEHLP_SYMBOL Symbol = (PIMAGEHLP_SYMBOL)symbolBuffer;
			Symbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL);
			Symbol->MaxNameLength = 256;

			DWORD64 SymbolDisplacement = 0;
			if ( !SymGetSymFromAddr( GetCurrentProcess() , Address , &SymbolDisplacement , Symbol ) ) continue;
			
			if ( FuncName == Symbol->Name )
			{
				SymCleanup( GetCurrentProcess() );
				return TRUE;
			}
		}
		
		SymCleanup( GetCurrentProcess() );
		return FALSE;
	}
};