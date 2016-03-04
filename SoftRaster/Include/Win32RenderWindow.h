#ifndef Win32RenderWindow_h
#define Win32RenderWindow_h

#include "RenderWindow.h"

namespace Sand
{
	class Vector2f;

	class Win32RenderWindow : public RenderWindow
	{
	public:
		Win32RenderWindow();
		virtual ~Win32RenderWindow();

		/*
			填充WNDCLASSEX
			注册窗口
			创建窗口
		*/
		virtual void Initialize( IWindowProc* WindowProObj );

		/*
			销毁窗口
		*/
		virtual void Shutdown();

		/*
			获取鼠标在窗口上的相对位置
		*/
		Vector2f GetCursorPosition();
	};
}

#endif