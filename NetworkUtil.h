#pragma once
#include "HighOrderContainer.h"

namespace NetUtil
{
	BOOL Init();
	void Release();

	HighOrderVector<CStringA> GetIPAddress( int* ErrorCode = NULL );
};