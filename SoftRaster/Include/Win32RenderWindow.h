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
			���WNDCLASSEX
			ע�ᴰ��
			��������
		*/
		virtual void Initialize( IWindowProc* WindowProObj );

		/*
			���ٴ���
		*/
		virtual void Shutdown();

		/*
			��ȡ����ڴ����ϵ����λ��
		*/
		Vector2f GetCursorPosition();
	};
}

#endif