#pragma once

#include <windows.h>
#include <list>
#include <map>
#include <vector>
#include <set>
#include <functional>
#include "MemoryUtil.h"

class BeginCriticalSectionWarp
{
private:

	inline BeginCriticalSectionWarp() = default;
	inline BeginCriticalSectionWarp(CRITICAL_SECTION* cs) { EnterCriticalSection(cs); }
};

class EndCriticalSectionWarp
{
private:

	inline EndCriticalSectionWarp() = default;
	inline EndCriticalSectionWarp(CRITICAL_SECTION* cs) { LeaveCriticalSection(cs); }
};

template < typename T,
	template< typename T, typename ALLOC = std::allocator<T> >
	class CON >
class SyncObject : private BeginCriticalSectionWarp , 
				   private CON<T> , 
				   private EndCriticalSectionWarp
{
public:

	SyncObject()
	{ 
		InitializeCriticalSectionAndSpinCount(&m_NowUse, 3000); 
	}

	~SyncObject()
	{ 
		DeleteCriticalSection(&m_NowUse);
	}

	template<typename R>
	SyncObject(R&& rhs) : BeginCriticalSectionWarp(&rhs.m_NowUse),
						  CON<T>(std::forward<R>(rhs)) ,
						  EndCriticalSectionWarp(&rhs.m_NowUse)
	{
		InitializeCriticalSectionAndSpinCount(&m_NowUse, 3000);
	}

	SyncObject( std::initializer_list<T> list ) : CON<T>(list)
	{
		InitializeCriticalSectionAndSpinCount(&m_NowUse, 3000);
	}

	template<typename R>
	SyncObject& operator=(R && rhs)
	{
		CSPtr obj(m_NowUse);

		rhs.Enter();
		CON<T>::operator=(std::forward<R>(rhs));
		rhs.Leave();

		return (*this);
	}

	template<typename U>
	void PushBack( U&& Data )
	{
		CSPtr obj(m_NowUse);

		push_back( std::forward<U>( Data ) );
	}

	void PushArray( T* Src , int Size )
	{
		CSPtr obj(m_NowUse);

		assign(Src, Src + Size);
	}

	void PushFront(const T& Data)
	{
		CSPtr obj(m_NowUse);

		push_front(Data);
	}

	BOOL PopBack(T& t)
	{
		CSPtr obj(m_NowUse);

		if ( Count() <= 0 ) return FALSE;

		t = Back();
		pop_back();

		return TRUE;
	}

	BOOL PopFront(T& t)
	{
		CSPtr obj(m_NowUse);

		if ( Count() <= 0 ) return FALSE;

		t = std::move( Front() );
		pop_front();

		return TRUE;
	}

	T& Front()
	{
		CSPtr obj(m_NowUse);

		return front();
	}

	T& Back()
	{
		CSPtr obj(m_NowUse);

		return back();
	}

	int Count()
	{
		CSPtr obj(m_NowUse);

		return (int)size();
	}

	BOOL FindValue( const T& t )
	{
		return FindByFunc( [&]( const T& v ) { return v == t; });
	}

	template< typename F >
	BOOL FindByFunc( F f )
	{
		CSPtr obj(m_NowUse);

		auto result = std::find_if( begin() , end() , f );

		return result != end();
	}

	void ForEach( std::function<void(const T&)> Function )
	{
		CSPtr obj(m_NowUse);

		std::for_each( begin() , end() , Function );
	}

	void Delete(T& t)
	{
		CSPtr obj(m_NowUse);

		remove( t );	
	}

	// 요소 중에서 함수객체 리턴값이 TRUE인 객체들을 삭제
	int Delete( std::function<BOOL(const T&)> Func )
	{
		CSPtr obj(m_NowUse);

		int Count = 0;

		typename CON<T>::iterator cur = this->begin();
		typename CON<T>::iterator end = this->end();

		while ( cur != end )
		{
			if ( Func( (*cur) ) ) 
			{
				cur = erase(cur);
				++Count;
			}
			else
			{
				++cur;
			}
		}

		return Count;
	}

	void Clear()
	{
		CSPtr obj(m_NowUse);

		clear();
	}
	
	inline void Enter() { EnterCriticalSection(&m_NowUse); }
	inline void Leave() { LeaveCriticalSection(&m_NowUse); }

private:

	CRITICAL_SECTION m_NowUse;
};

// SyncMap은 SyncObject를 상속받아서 구현할수 없는 템플릿 파리미터를 가지고 있다.
template< typename KEY , typename VALUE >
class SyncMap :	private BeginCriticalSectionWarp , 
				private std::map<KEY,VALUE> ,
				private EndCriticalSectionWarp
{
public:

	SyncMap()
	{
		InitializeCriticalSectionAndSpinCount(&m_NowUse , 3000);
	}

	~SyncMap()
	{
		DeleteCriticalSection(&m_NowUse);
		clear();
	}

	template<typename R>
	SyncMap(R&& rhs) : BeginCriticalSectionWarp(&rhs.m_NowUse),
					   std::map<KEY,VALUE>(std::forward<R>(rhs)) ,
					   EndCriticalSectionWarp(&rhs.m_NowUse)
	{
		InitializeCriticalSectionAndSpinCount(&m_NowUse, 3000);
	}

	BOOL Has(const KEY& k)
	{
		CSPtr obj(m_NowUse);

		std::map< KEY , VALUE >::iterator result = find(k);
		return (result != end());
	}

	VALUE& Get(const KEY& k)
	{
		CSPtr obj(m_NowUse);

		std::map< KEY, VALUE >::iterator result = find(k);

		return result->second;
	}

	void Set( const KEY& k , VALUE&& v )
	{
		CSPtr obj(m_NowUse);

		insert( std::make_pair( k , std::forward<VALUE>(v) ) );
	}

	inline void SetNoSync( const KEY& k , const VALUE& v)
	{
		m_map[k] = v;
	}

	int Count() const
	{
		CSPtr obj(m_NowUse);

		return (int)size();
	}

	BOOL Delete(const KEY& k)
	{
		CSPtr obj(m_NowUse);

		std::map< KEY , VALUE >::iterator result = find(k);

		if ( result == end() ) return false;

		erase( result );

		return true;
	}

	void Clear()
	{
		CSPtr obj(m_NowUse);

		clear();
	}

	inline VALUE& operator[]( const KEY& k ) { return Get( k ); }

	inline void Enter() { EnterCriticalSection(&m_NowUse); }
	inline void Leave() { LeaveCriticalSection(&m_NowUse); }

private:

	CRITICAL_SECTION m_NowUse;
};

template<typename T>
using SyncList = SyncObject<T,std::list>;

template<typename T>
using SyncVector = SyncObject<T,std::vector>;

template<typename T>
class Variable
{
public:

	Variable() = default;
	~Variable() = default;

	T& Get( const CString& Key )
	{
		if ( !m_Map.Has( Key ) ) 
			m_Map.Set( Key , T() );
			
		return m_Map.Get( Key );
	}

	void Reset( const CString& Key )
	{
		if ( !m_Map.Has( Key ) ) return;

		m_Map.Get( Key ) = T();
	}

private:

	Variable( Variable&& r ) = delete;
	Variable( const Variable& r ) = delete;

private:

	SyncMap< CString , T > m_Map;
};