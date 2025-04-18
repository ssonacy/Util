#include "stdafx.h"
#include "UtilCommon.h"
#include "Invoke.h"
#include "Thread.h"
#include "MemoryUtil.h"
#include "SyncContainer.h"
#include "TimeUtil.h"
#include <Windows.h>
#include <unordered_map>

JobEvent::JobEvent( HANDLE hEvent )  : m_hEvent( hEvent ) {}
JobEvent::JobEvent( JobEvent&& rhs ) noexcept : m_hEvent( rhs.Reset() ) {}
JobEvent::~JobEvent() { CLOSE_HANDLE( m_hEvent ); }

HANDLE JobEvent::Reset()
{
	HANDLE h = m_hEvent;
	m_hEvent = NULL;
	return h;
}

BOOL JobEvent::Wait( DWORD WaitTick , DWORD* LastError )
{
	if ( !m_hEvent ) 
	{
		if ( LastError ) *LastError = ERROR_INVALID_HANDLE;
		return FALSE;
	}

	DWORD Ret = WaitForSingleObject( m_hEvent , WaitTick );
	if ( LastError ) *LastError = GetLastError();

	return ( Ret == WAIT_OBJECT_0 );
}

namespace Job
{
	BOOL WaitAll( std::initializer_list<JobEventRef> JobList , BOOL AllComplete , DWORD WaitTick , DWORD* LastError )
	{
		DWORD Count = (DWORD)JobList.size();
		if ( Count <= 0 )
		{
			if  ( LastError ) *LastError = ERROR_INVALID_HANDLE;
			return FALSE;
		}

		std::vector<HANDLE> Handles;
		Handles.reserve( Count );

		std::for_each( JobList.begin() , JobList.end() , [&Handles]( const JobEventRef& rhs ) 
		{
			Handles.push_back( rhs.get().GetHandle() );
		});

		DWORD Ret = WaitForMultipleObjects( Count , Handles.data() , AllComplete , WaitTick );
		if ( LastError ) *LastError = GetLastError();

		return (WAIT_OBJECT_0 <= Ret) && (Ret <= Count - 1);
	}
}

namespace Invoke
{
	namespace UI
	{
		namespace Private
		{
			HWND _main_wnd = NULL;
			SyncList< Invoke::Entry > _func_list;

			CThread	_invoke_ui_thread;

			BOOL Send( HWND h , Invoke::Entry* pEntry )
			{				
				__try
				{
					return (BOOL)SendMessage( h , WM_UI_INVOKE_CALL , (WPARAM)pEntry , 0 );
				}
				__except( EXCEPTION_EXECUTE_HANDLER ) {}

				return FALSE;
			}

			unsigned int __stdcall InvokeUIThreadCaller(void*)
			{
				while ( !Private::_invoke_ui_thread.IsReqStatus( ThreadReq::TERMINATING ) )
				{	
					Sleep( 1 );

					if ( Private::_func_list.IsEmpty() ) CONTINUE_SLEEP( 100 );

					Invoke::Entry Item;
					if ( !_func_list.PopFront( Item ) ) CONTINUE_SLEEP( 100 );

					if ( GetTickCount() - Item.m_LastCallTick < Item.m_IntervalTick ) CONTINUE( _func_list.PushBack( Item ) );

					if ( !Send( Private::_main_wnd , &Item ) )
					{
						SetEvent( Item.m_Finish );
						CLOSE_HANDLE( Item.m_Finish );
						continue;
					}

					Item.m_LastCallTick = GetTickCount();
					_func_list.PushBack( Item );
				}
				return 0;
			}
		};

		BOOL Init( HWND h )
		{
			Private::_main_wnd = h;
		
			return Private::_invoke_ui_thread.Start( Private::InvokeUIThreadCaller , NULL , FALSE );
		}

		void Release()
		{
			Private::_main_wnd = NULL;
			Private::_func_list.Clear();
			Private::_invoke_ui_thread.Exit( 0 );
		}

		JobEvent Once( Invoke::Call Func )
		{
			Invoke::Entry NewEntry = Invoke::Entry::CreateOnce( Func );

			HANDLE Copyed = NULL;
			DuplicateHandle( GetCurrentProcess() , NewEntry.m_Finish , 
							 GetCurrentProcess() , &Copyed , 0 , FALSE , DUPLICATE_SAME_ACCESS );

			Private::_func_list.PushBack( NewEntry );

			return JobEvent(Copyed);
		}

		JobEvent Repeat( DWORD Interval , Invoke::Recall Func )
		{
			Invoke::Entry NewEntry = Invoke::Entry::CreateRepeat( Interval , Func );

			HANDLE Copyed = NULL;
			DuplicateHandle( GetCurrentProcess() , NewEntry.m_Finish , 
							 GetCurrentProcess() , &Copyed , 0 , FALSE , DUPLICATE_SAME_ACCESS );

			Private::_func_list.PushBack( NewEntry );

			return JobEvent(Copyed);
		}
	};

	namespace Worker
	{
		enum class Req
		{
			None,		 // 초기값
			CallAgin,	 // 호출 요청
			Finish,		 // 호출끝남을 알림
		};

		enum class Res
		{
			None,		// 초기값
			CallDone,	// Req::CallAgin 응답
		};

		enum class CallbackType
		{
			Once,		// 1회성 호출
			Recall,		// 콜백 함수에서의 리턴값에 따라서 재호출
			LongTerm,	// 콜백을 호출한 스레드 폴의 스레드를 오래동안 선점
		};

		struct Job
		{
			Req _req = Req::CallAgin;
			Res _res = Res::None;

			PTP_WORK _work = NULL;

			Invoke::Entry* _pEntry = NULL;
		};

		namespace Private
		{
			SyncList< Job* > _work_entry_list;

			CThread _work_process_thread;

			unsigned int __stdcall WorkProcessThreadFunc( void* p )
			{
				while ( !_work_process_thread.IsReqStatus( ThreadReq::TERMINATING ) )
				{
					Sleep( 1 );

					_work_entry_list.Delete( []( const Job* pcValue )
					{
						Job*			pJob = (Job*)pcValue;
						Invoke::Entry*	pEntry = pJob->_pEntry;

						if ( pJob->_req == Req::Finish )
						{
							ObjPtr<Job>				JobPtr( pJob );
							ObjPtr<Invoke::Entry>	EntryPtr( pEntry );

							SetEvent( pEntry->m_Finish );
							CLOSE_HANDLE( pEntry->m_Finish );

							RETURN_V( CloseThreadpoolWork( pJob->_work ) , TRUE );
						}

						if ( pJob->_req != Req::CallAgin || pJob->_res == Res::CallDone ) return FALSE;
						
						DWORD LastCallTick = pEntry->m_LastCallTick;
						DWORD IntervalTick = pEntry->m_IntervalTick;

						if ( GetTickCount() - LastCallTick > IntervalTick )
						{
							pJob->_res = Res::CallDone;
							pEntry->m_LastCallTick = GetTickCount();

							SubmitThreadpoolWork( pJob->_work );
						}
						
						return FALSE;
					});
				}

				return 0;
			}

			void __stdcall CallbackStub( PTP_CALLBACK_INSTANCE Instance , PVOID Context , PTP_WORK Work )
			{
				Worker::Job*	pJob		= (Worker::Job*)Context;
				Invoke::Entry*	pEntry		= pJob->_pEntry;
				BOOL			Recallable	= pEntry->m_IsRecall;

				__try
				{
					if ( Recallable )
					{
						if ( !pEntry->m_Recallback() ) RETURN( pJob->_req = Req::Finish );
					}
					else
					{
						pEntry->m_Callback();
					}
				}
				__except( EXCEPTION_EXECUTE_HANDLER ) {}

				pJob->_req = Recallable ? Req::CallAgin : Req::Finish;
				pJob->_res = Res::None;
			}

			void __stdcall LongCallbackStub( PTP_CALLBACK_INSTANCE Instance , PVOID Context , PTP_WORK Work )
			{
				CallbackMayRunLong( Instance );

				Worker::Job* pJob = (Worker::Job*)Context;

				__try
				{
					pJob->_pEntry->m_Callback();
				}
				__except( EXCEPTION_EXECUTE_HANDLER ) {}
				
				pJob->_req = Req::Finish;
				pJob->_res = Res::None;
			}

			JobEvent CreateThreadPoolCallback( CallbackType Type , void* Callback , DWORD IntervalTick )
			{
				Invoke::Entry* pEntry = NULL;
				if ( Type == CallbackType::Recall )	pEntry = Invoke::Entry::AllocRepeat( IntervalTick , *(Invoke::Recall*)Callback );
				else							    pEntry = Invoke::Entry::AllocOnce( *(Invoke::Call*)Callback );

				Job* pJob = new Job { Req::CallAgin , Res::None , NULL , pEntry };
				if ( Type == CallbackType::LongTerm ) pJob->_work = CreateThreadpoolWork( Private::LongCallbackStub , pJob , NULL );
				else								  pJob->_work = CreateThreadpoolWork( Private::CallbackStub , pJob , NULL );

				HANDLE Copyed = NULL;
				DuplicateHandle( GetCurrentProcess() , pEntry->m_Finish , 
								 GetCurrentProcess() , &Copyed , 0 , FALSE , DUPLICATE_SAME_ACCESS );

				Private::_work_entry_list.PushBack( pJob );

				return JobEvent(Copyed);
			}
		};

		void Init()
		{
			if ( Private::_work_process_thread.IsValid() ) return;

			Private::_work_process_thread.Start( Private::WorkProcessThreadFunc , NULL , FALSE );
		}

		void Release()
		{
			Private::_work_process_thread.Exit( INFINITE );

			ENTER( Private::_work_entry_list )
			{
				typename std::list<Job*>::iterator cur = Private::_work_entry_list.Begin();
				typename std::list<Job*>::iterator end = Private::_work_entry_list.End();

				for ( ; cur != end ; ++cur )
				{
					Job*		   pJob = (*cur);
					Invoke::Entry* pEntry = pJob->_pEntry;

					WaitForThreadpoolWorkCallbacks( pJob->_work , TRUE );
					CloseThreadpoolWork( pJob->_work );
					
					delete pEntry;
					delete pJob;
				}

				Private::_work_entry_list.Clear();
			}
		}

		JobEvent Once( Invoke::Call Func )
		{
			return Private::CreateThreadPoolCallback( CallbackType::Once , &Func , 0 );
		}

		JobEvent Repeat( DWORD Interval , Invoke::Recall Func )
		{
			return Private::CreateThreadPoolCallback( CallbackType::Recall , &Func , Interval );
		}

		JobEvent LongTerm( Invoke::Call Func )
		{
			return Private::CreateThreadPoolCallback( CallbackType::LongTerm , &Func , 0 );
		}
	};
};