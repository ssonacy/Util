#pragma once

#define MAX_BUFFER_SIZE  (1024*4)
#define INVALID_PORT_NUM (-1)

class  CSerial
{
public:
	
	CSerial();
	~CSerial();

	BOOL OpenPort( int Port , DWORD dwBaud , BYTE byData , BYTE byStop , BYTE byParity , DWORD& LastError );
	void ClosePort();				

	DWORD Send( const BYTE* pBuff , DWORD Size );
	DWORD Read( BYTE* pBuff , DWORD nToRead );

	DWORD SendAndRead( const BYTE* pSend , DWORD SendSize , BYTE* ResBuffer , DWORD ResBufferSize , DWORD WaitTick = 100 );

	inline BOOL IsConnected()	const { return GetComPortNum() != INVALID_PORT_NUM; }
	inline int  GetComPortNum()	const { return m_ComPort;							}

private:

	CRITICAL_SECTION m_cs;

	OVERLAPPED	m_osRead;							 // ��Ʈ ���� Overlapped structure
	OVERLAPPED  m_osWrite;							 // ��Ʈ ���� Overlapped structure

	HANDLE		m_hComm		 = INVALID_HANDLE_VALUE; // ��� ��Ʈ ���� �ڵ�
	int			m_ComPort    = INVALID_PORT_NUM;	 // ���� ����� ����Ʈ ��ȣ( INVALID_PORT_NUM(-1) �� ���� ���°� �ƴϴ� )
};