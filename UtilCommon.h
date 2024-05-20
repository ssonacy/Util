#pragma once

#define RETURN(F)			{ F; return;   }
#define RETURN_V(F,V)		{ F; return V; }
#define CONTINUE(F)			{ F; continue; }
#define BREAK(F)			{ F; break;	   }

#define IS_ODD(X)			((X)&1)
#define IS_EVEN(X)			(!IS_ODD(X))

#include <strsafe.h>
#include "MinidumpHelp.h"
#include "SyncObject.h"
#include "Invoke.h"
#include "HighOrderContainer.h"
#include "StringUtil.h"
#include "IniFile.h"
#include "UIUtil.h"
#include "MemoryUtil.h"
#include "ProcessUtil.h"
#include "TimeUtil.h"
#include "FileSystemUtil.h"
#include "FolderUtil.h"
#include "Log.h"
#include "Thread.h"
#include "MFCCheckButton.h"
#include "SystemUtil.h"
#include "SocketDefine.h"
#include "ServerSocket.h"
#include "ClientSocket.h"
#include "NetworkUtil.h"
#include "Serial.h"
#include "ValueEncode.h"
#include "CompleteEvent.h"
#include ".\\zip\Ark.h"
#include ".\\zip\ArkLib.h"



