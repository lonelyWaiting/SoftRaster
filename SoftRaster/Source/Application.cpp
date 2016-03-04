#include "PCH.h"
#include "Application.h"
#include "Log.h"

using namespace Sand;

// 保持类只有一个实例
Application* Application::m_spApplication = nullptr;

Application::Application()
	: m_bLoop( true )
{
	m_spApplication = this;

	m_pTimer = new Timer;
	m_pTimer->Update();

	pWindow = new Win32RenderWindow;

	pSurface = new Surface;

	Log::Get().Open();
}

Application::~Application()
{
	Log::Get().Close();

	if ( m_pTimer != nullptr )
	{
		delete m_pTimer;
	}
}

Application* Application::Get()
{
	return m_spApplication;
}

void Application::MessageLoop()
{
	MSG msg;

	while ( true )
	{
		while ( PeekMessage( &msg , NULL , 0 , 0 , PM_REMOVE ) )
		{
			if ( msg.message == WM_QUIT )
			{
				return;
			}

			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		m_pTimer->Update();

		SetFrameRate( pWindow->GetHandle() );

		Update();
	}
}

LRESULT Application::WindowProc( HWND hwnd , UINT msg , WPARAM wParam , LPARAM lParam )
{
	switch ( msg )
	{
		case WM_DESTROY:
		{
			PostQuitMessage( 0 );
			return 0;
			break;
		}

		// ---------------------LButton------------------------
		case WM_LBUTTONUP:
		{
			OnMouseUp( wParam , GET_X_LPARAM( lParam ) , GET_Y_LPARAM( lParam ) );
			break;
		}

		case WM_LBUTTONDOWN:
		{
			OnMouseDown( wParam , GET_X_LPARAM( lParam ) , GET_Y_LPARAM( lParam ) );
			break;
		}

		// -----------------------MOUSE----------------------------------
		case WM_MOUSEMOVE:
		{
			OnMouseMove( wParam , GET_X_LPARAM( lParam ) , GET_Y_LPARAM( lParam ) );
			break;
		}
	}

	return DefWindowProc( hwnd , msg , wParam , lParam );
}

void Application::SetFrameRate( HWND hwnd )
{
	static int FrameCount = 0;
	static float TimeElapsed = 0.0f;

	FrameCount++;
	if ( m_pTimer->TotalTime() - TimeElapsed >= 1.0f )
	{
		float fps = ( float )FrameCount;
		float mspf = 1000.0f / fps;

		std::wostringstream outs;
		outs.precision( 6 );
		outs << GetName() << L" "
			<< L"FPS: " << fps << L" "
			<< L"Frame Time: " << mspf << L" (ms)";

		SetWindowText( hwnd , outs.str().c_str() );

		FrameCount = 0;
		TimeElapsed += 1.0f;
	}
}

void Application::OnMouseDown( WPARAM buttonState , int x , int y )
{

}

void Application::OnMouseUp( WPARAM buttonState , int x , int y )
{

}

void Application::OnMouseMove( WPARAM buttonState , int x , int y )
{

}