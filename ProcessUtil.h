#pragma once

#include <TlHelp32.h>
#include <functional>

using EnumProcessFunction = std::function<BOOL(const PROCESSENTRY32&)>;
using EnumModuleFunction  = std::function<BOOL(const MODULEENTRY32&)>;

namespace ProcessUtil
{
	HandlePtr Run( LPCTSTR WorkingDirectory , LPCTSTR ExeNameWithArg , DWORD* ErrorCode );

	HighOrderList<HWND> PIDToHWNDs( DWORD ProcessID );
};