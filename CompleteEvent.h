#pragma once
#include "MemoryUtil.h"

class CompleteEvent
{
public:

	CompleteEvent();
	~CompleteEvent() = default;
	
	void Init();

	BOOL IsDone();
	BOOL WaitComplete( DWORD WaitTick );

	BOOL Signal();

private:

	CompleteEvent( CompleteEvent&& rhs ) = delete;
	CompleteEvent( const CompleteEvent& rhs ) = delete;

	CompleteEvent& operator=( const CompleteEvent& rhs ) = delete;
	CompleteEvent& operator=( CompleteEvent&& rhs ) = delete;

private:

	EventHandlePtr m_CompletePtr = NULL;
};
//-----------------------------------------------------------------
class CS
{
public:

	CS();
	CS( CS&& r );
	~CS();

	inline CSPtr Obj() { return CSPtr( _cs ); }

private:

	CS( const CS& r ) = delete;
	CS& operator=( const CS& ) = delete;

private:

	BOOL m_bInit = FALSE; // 해당 CS 객체가 초기화가 완료 되었는지 판단 변수
	CRITICAL_SECTION _cs;
};
//-----------------------------------------------------------------