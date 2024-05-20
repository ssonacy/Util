#include "stdafx.h"
#include "Invoke.h"
#include "Thread.h"
#include "MemoryUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

namespace Invoke
{
	struct Entry
	{
		Entry() = default;

		Entry( int Index , Invoke::CallbackType Callback ) : m_Index( Index ) , m_Callback(Callback) {}

		int m_Index = -1;
		Invoke::CallbackType	m_Callback;
	};

	namespace
	{
		HWND	_main_wnd = NULL;
		CThread	_invoke_thread;
		HANDLE  _queue_semaphore = NULL;

		SyncList< Invoke::Entry > _func_list;
	}
	
	unsigned int __stdcall InvokeThreadCaller(void*)
	{
		while ( !_invoke_thread.IsReqStatus( ThreadReq::TERMINATING ) )
		{
			DWORD WaitRet = WaitForSingleObjectEx( _queue_semaphore , INFINITE , TRUE );
			if ( WaitRet != WAIT_OBJECT_0 ) return -1;
			
			Invoke::Entry Item;
			if( !_func_list.PopFront( Item ) ) continue;
			
			Invoke::Repeat Ret = (Invoke::Repeat)SendMessage( _main_wnd , WM_INVOKE_CALL_TIMER , (WPARAM)&Item.m_Callback , 0 );
			if ( Invoke::Again == Ret )
			{
				_func_list.PushBack( Item );
				ReleaseSemaphore( _queue_semaphore , 1 , NULL );
			}
		}
		return 0;
	}

	BOOL Init( HWND h )
	{
		_queue_semaphore = CreateSemaphore( NULL , 0 , LONG_MAX , NULL );
		if ( !_queue_semaphore ) return FALSE;

		_main_wnd = h;
		
		return _invoke_thread.Start( InvokeThreadCaller , NULL , FALSE );
	}

	BOOL Delete( int Index )
	{
		if ( _func_list.Count() <= 0 ) return FALSE;

		int Item = _func_list.Delete( [Index]( const Invoke::Entry& Item ) { return Item.m_Index == Index; });

		return ( Item > 0 );
	}

	void Release()
	{
		CLOSE_HANDLE( _queue_semaphore );
		_main_wnd = NULL;
		_func_list.Clear();
		_invoke_thread.Exit( 0 );
	}

	int Add( Invoke::CallbackType Func )
	{
		if ( !_main_wnd ) return FALSE;

		int Index = _func_list.Count();

		_func_list.PushBack( Entry( Index , Func ) );
		ReleaseSemaphore( _queue_semaphore , 1 , NULL );

		return Index;
	}
};