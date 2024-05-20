#include "stdafx.h"
#include "CompleteEvent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

CompleteEvent::CompleteEvent() : m_CompletePtr( CreateEvent( NULL , TRUE , FALSE , NULL ) ) {}

void CompleteEvent::Init()
{
	if ( m_CompletePtr.Get() )
	{
		HANDLE h = m_CompletePtr.Reset( NULL );
		SetEvent( h );
		CloseHandle( h );
	}

	m_CompletePtr.Reset( CreateEvent( NULL , TRUE , FALSE , NULL ) );
}

BOOL CompleteEvent::IsDone()
{
	return WaitComplete( 0 );
}

BOOL CompleteEvent::WaitComplete( DWORD WaitTick )
{
	return WaitForSingleObject( m_CompletePtr.Get() , WaitTick ) == WAIT_OBJECT_0;
}

BOOL CompleteEvent::Signal()
{
	return SetEvent( m_CompletePtr.Get() );
}
//-----------------------------------------------------------------
CS::CS()  
{ 
	InitializeCriticalSectionAndSpinCount( &_cs , 3000 ); 
	m_bInit = TRUE;
}

CS::CS( CS&& r )
{
	_cs		= r._cs;
	m_bInit = TRUE;

	r.m_bInit = FALSE;
}

CS::~CS() 
{ 
	if ( !m_bInit ) return;

	DeleteCriticalSection( &_cs );
}
//-----------------------------------------------------------------