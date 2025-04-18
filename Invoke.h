#pragma once
#include <functional>

class JobEvent
{
public:

	explicit JobEvent( HANDLE hEvent );
	JobEvent( JobEvent&& rhs ) noexcept;
	~JobEvent();

	BOOL Wait( DWORD WaitTick , DWORD* LastError = NULL );

	HANDLE GetHandle() const { return m_hEvent; }

private:
	
	HANDLE Reset();

	JobEvent( const JobEvent& rhs )			   = delete;
	JobEvent& operator=( JobEvent&& rhs )	   = delete;
	JobEvent& operator=( const JobEvent& rhs ) = delete;

private:

	HANDLE m_hEvent = NULL;
};

using JobEventRef = std::reference_wrapper<JobEvent>;

namespace Job
{
	BOOL WaitAll( std::initializer_list<JobEventRef> JobList , BOOL AllComplete , DWORD WaitTick , DWORD* LastError = NULL );
};

// UI 또는 다른 스레드(스레드풀) 에게 작업을 위임할때 사용하는 기능
namespace Invoke
{
	using Recall = std::function<BOOL()>;
	using Call   = std::function<void()>;
	
	struct Entry
	{
		DWORD m_IntervalTick = 0;
		DWORD m_LastCallTick = 0;

		BOOL  m_IsRecall = FALSE;

		Invoke::Call	m_Callback;
		Invoke::Recall	m_Recallback;

		HANDLE	m_Finish = NULL;

		static Invoke::Entry CreateOnce( Invoke::Call Callback )
		{
			return Invoke::Entry { 0 , 0 ,  FALSE , Callback , Invoke::Recall() , CreateEvent( NULL , FALSE , FALSE , NULL ) };
		}

		static Invoke::Entry CreateRepeat( DWORD Interval , Invoke::Recall Callback )
		{
			return Invoke::Entry { Interval , 0 , TRUE , Invoke::Call() , Callback , CreateEvent( NULL , FALSE , FALSE , NULL ) };
		}

		static Invoke::Entry* AllocOnce( Invoke::Call Callback )
		{
			return new Invoke::Entry{ Invoke::Entry::CreateOnce( Callback ) };
		}

		static Invoke::Entry* AllocRepeat( DWORD Interval , Invoke::Recall Callback )
		{
			return new Invoke::Entry{ Invoke::Entry::CreateRepeat( Interval , Callback ) };
		}
	};

	namespace UI
	{
		BOOL Init( HWND h );
		void Release();

		JobEvent Once( Invoke::Call Func );
		JobEvent Repeat( DWORD Interval , Invoke::Recall Func );
	};

	namespace Worker
	{
		void Init();
		void Release();

		JobEvent Once( Invoke::Call Func );
		JobEvent Repeat( DWORD Interval , Invoke::Recall Func );
		JobEvent LongTerm( Invoke::Call Func );
	};
};

#define DECLARE_UI_INVOKE()		LRESULT OnUIInvoke(WPARAM W,LPARAM){\
									__try {\
										Invoke::Entry* pEntry = (Invoke::Entry*)W;\
										if ( pEntry->m_Recallback ) return pEntry->m_Recallback();\
										else					    RETURN_V( pEntry->m_Callback() , FALSE );\
									}\
									__except( EXCEPTION_EXECUTE_HANDLER ){}\
										return (LRESULT)FALSE;}\

#define WM_UI_INVOKE_CALL  (WM_USER+7182)
#define ON_UI_INVOKE()	   ON_MESSAGE(WM_UI_INVOKE_CALL,OnUIInvoke)


#define WORK_1		Invoke::Worker::Once 
#define WORK_N		Invoke::Worker::Repeat

#define UI_1		Invoke::UI::Once
#define UI_N		Invoke::UI::Repeat
