#ifndef IWindowProc_h
#define IWindowProc_h

#include "PCH.h"

// ����Ϊ�ӿ��࣬����ָ��Ӧ�ó������ʵ�ֵĹ���
namespace Sand
{
	class IWindowProc
	{
	public:
		virtual LRESULT WindowProc( HWND hwnd , UINT msg , WPARAM wParam , LPARAM lParam ) = 0;
	};
}

#endif