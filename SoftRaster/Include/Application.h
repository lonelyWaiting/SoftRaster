#ifndef Application_h
#define Application_h

#include "IWindowProc.h"
#include "Timer.h"

#include "Win32RenderWindow.h"

#include "Surface.h"

namespace Sand
{
	class Application : public IWindowProc
	{
	public:
		Application();
		virtual ~Application();

		static Application* Get();

		virtual bool ConfigureEngineComponents() = 0;
		virtual bool ShutdownEngineComponents() = 0;

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Shutdown() = 0;
		virtual void MessageLoop();

		virtual LRESULT WindowProc( HWND hwnd , UINT msg , WPARAM wParam , LPARAM lParam );

		// 应用程序名
		virtual std::wstring GetName() = 0;

		// 设置帧率到窗口
		void SetFrameRate( HWND hwnd );

		/*
			鼠标响应
		*/
		virtual void OnMouseDown( WPARAM buttonState , int x , int y );
		virtual void OnMouseUp( WPARAM buttonState , int x , int y );
		virtual void OnMouseMove( WPARAM buttonState , int x , int y );

		bool m_bLoop;

		Timer* m_pTimer;

		Surface* pSurface;

		Win32RenderWindow* pWindow;

	protected:
		static Application* m_spApplication;

		POINT m_LastMousePos;
	};
};
#endif