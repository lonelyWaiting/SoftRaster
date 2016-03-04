#include "PCH.h"
#include "Timer.h"

using namespace Sand;

Timer::Timer() :
	m_SecondsPerCount( 0.0f ) ,
	m_DeltaTime( -1.0f ) ,
	m_BaseTime( 0 ) ,
	m_PrevTime( 0 ) ,
	m_CurrTime( 0 ) ,
	m_bUseFixedTimeStep( false ) ,
	m_FixedTimeStep( 0.0f )
{
	__int64 countsPerSec;
	QueryPerformanceFrequency( ( LARGE_INTEGER* )&countsPerSec );
	m_SecondsPerCount = 1.0f / ( double )countsPerSec;

	Reset();
}

Timer::~Timer()
{

}

void Timer::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter( ( LARGE_INTEGER* )&currTime );

	m_BaseTime = currTime;
	m_PrevTime = currTime;
}

void Timer::Update()
{
	__int64 currTime;
	QueryPerformanceCounter( ( LARGE_INTEGER* )&currTime );
	m_CurrTime = currTime;

	// 计算两帧的时间差
	m_DeltaTime = ( m_CurrTime - m_PrevTime )*m_SecondsPerCount;

	m_PrevTime = m_CurrTime;

	// Force nonnegative.  The DXSDK's CDXUTTimer mentions that if the 
	// processor goes into a power save mode or we get shuffled to another
	// processor, then mDeltaTime can be negative.
	if ( m_DeltaTime < 0.0 )
	{
		m_DeltaTime = 0.0;
	}
}

float Timer::TotalTime() const
{
	return ( float )( ( m_CurrTime - m_BaseTime ) * m_SecondsPerCount );
}

float Timer::DeltaTime() const
{
	if ( m_bUseFixedTimeStep )
	{
		return m_FixedTimeStep;
	}

	return ( float )m_DeltaTime;
}

void Timer::SetFixedTimeStep( float FixedTimeStep )
{
	if ( FixedTimeStep <= 0.0f )
	{
		m_bUseFixedTimeStep = false;
		m_FixedTimeStep = 0.0f;
	}
	else
	{
		m_bUseFixedTimeStep = true;
		m_FixedTimeStep = FixedTimeStep;
	}
}