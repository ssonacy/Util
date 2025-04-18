#ifndef _UTIL_COMMON_H_
#define _UTIL_COMMON_H_

#define Alert           	   AfxMessageBox
#define YesNo(MESSAGE)         Alert( MESSAGE , MB_OKCANCEL )          

#define RETURN(FUNC)				do { FUNC; return;   } while(0)
#define RETURN_V(FUNC,VALUE)		do { FUNC; return VALUE; } while(0)
#define RETURN_MSG(MESSAGE)		    RETURN( Alert( MESSAGE ) )
#define CONTINUE(FUNC)				{ FUNC; continue; }
#define CONTINUE_SLEEP( TICK )		{ Sleep(TICK); continue; }
#define BREAK(FUNC)				    { FUNC; break;	   }

#define IS_ODD(X)				((X)&1)
#define IS_EVEN(X)				(!IS_ODD((X)))

#define _USE_MATH_DEFINES
#include <math.h> // FFTW 라이브러리에서 사용함
#include <complex>

#include <strsafe.h>
#include "FontManager.h"
#include "MinidumpHelp.h"
#include "SyncContainer.h"
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
#include "Serial.h"
#include "Color.h"
#include "ColorStatic.h"
#include "./chartCtrl/Chart/ChartCtrl.h"
#include "./chartCtrl/ColourPicker/ColourPicker.h"
#include "./chartCtrl/Chart/ChartLineSerie.h"

#endif // _UTIL_COMMON_H_