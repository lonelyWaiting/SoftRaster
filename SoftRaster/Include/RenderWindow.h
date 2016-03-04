#ifndef RenderWindow_h
#define RenderWindow_h

#include "PCH.h"
#include "IWindowProc.h"

namespace Sand
{
	/*
		提供了一组关于窗口宽高，位置，风格，标题，以及交换链的存取方法
	*/
	class RenderWindow
	{
	public:
		RenderWindow();
		virtual ~RenderWindow();

		virtual void Initialize( IWindowProc* WindowProcObj ) = 0;
		virtual void Shutdown() = 0;

		HWND GetHandle();

		// 窗口宽高
		void SetWidth( int width );
		void SetHeight( int height );
		int GetWidth();
		int GetHeight();

		// 窗口位置
		int GetLeft();
		int GetTop();

		// 设置窗口宽高
		void SetSize( int width , int height );

		// 设置窗口位置
		void SetPosition( int left , int top );

		// 重置窗口大小
		void ResizeWindow( int width , int height );

		// 窗口标题
		void SetCaption( std::wstring& caption );
		std::wstring GetCaption();

		// 窗口风格
		DWORD GetStyle();
		void SetStyle( DWORD dStyle );


	protected:

		void UpdateWindowState();

		HWND m_hWnd;

		// 标题
		std::wstring m_sCaption;

		// 风格
		DWORD m_dStyle;

		// 宽高
		int m_iWidth;
		int m_iHeight;

		// 位置
		int m_iLeft;
		int m_iTop;
	};
}

#endif