#pragma once
#include "MemoryUtil.h"

struct CritialSectionCtor  { inline void operator()(CRITICAL_SECTION& cs) const { EnterCriticalSection(&cs); } };
struct CritialSectionDtor  { inline void operator()(CRITICAL_SECTION& cs) const { LeaveCriticalSection(&cs); } };

struct SRCtor { inline void operator()(SRWLOCK& srw) { AcquireSRWLockShared( &srw ); } };
struct SRDtor { inline void operator()(SRWLOCK& srw) { ReleaseSRWLockShared( &srw ); } };
struct SWCtor { inline void operator()(SRWLOCK& srw) { AcquireSRWLockExclusive( &srw ); } };
struct SWDtor { inline void operator()(SRWLOCK& srw) { ReleaseSRWLockExclusive( &srw ); } };

using CSPtr = RAII<CRITICAL_SECTION&,CritialSectionDtor,CritialSectionCtor>;
using SRPtr = RAII<SRWLOCK&,SRDtor,SRCtor>;
using SWPtr = RAII<SRWLOCK&,SWDtor,SWCtor>;
