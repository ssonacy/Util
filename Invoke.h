#pragma once
#include <functional>

// UI 스레드가 아닌 스레드에서 UI 스레드로 작업을 요청할때 사용하는 함수
namespace Invoke
{
	enum Repeat
	{
		Done , // Invoke 호출 큐에서 제거, 제거된 함수는 다시 호출 안됨. 1회성
		Again  // Invoke 호출 큐에서 제거 하지 않음. 다시 호출됨.
	};
	
	using CallbackType = std::function<Invoke::Repeat(void*)>;

	BOOL Init( HWND h );
	void ClearJob();

	BOOL Delete( int Index );
	void Release();

	int Add( Invoke::CallbackType Func );
};

#define DECLARE_INVOKE()	LRESULT OnInvoke(WPARAM W,LPARAM) \
							{ \
								__try { \
									Invoke::CallbackType* pFunc = (Invoke::CallbackType*)W; \
									return (LRESULT)(*pFunc)(this); \
								} \
								__except( EXCEPTION_EXECUTE_HANDLER ){} \
									return (LRESULT)Invoke::Done; \
							}

#define WM_INVOKE_CALL_TIMER (WM_USER+7182)
#define ON_INVOKE()			 ON_MESSAGE(WM_INVOKE_CALL_TIMER,OnInvoke)