#pragma once
#include <functional>

// UI �����尡 �ƴ� �����忡�� UI ������� �۾��� ��û�Ҷ� ����ϴ� �Լ�
namespace Invoke
{
	enum Repeat
	{
		Done , // Invoke ȣ�� ť���� ����, ���ŵ� �Լ��� �ٽ� ȣ�� �ȵ�. 1ȸ��
		Again  // Invoke ȣ�� ť���� ���� ���� ����. �ٽ� ȣ���.
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