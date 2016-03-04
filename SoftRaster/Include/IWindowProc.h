#ifndef IWindowProc_h
#define IWindowProc_h

#include "PCH.h"

// 该类为接口类，用于指定应用程序必须实现的功能
namespace Sand
{
	class IWindowProc
	{
	public:
		virtual LRESULT WindowProc( HWND hwnd , UINT msg , WPARAM wParam , LPARAM lParam ) = 0;
	};
}

#endif