#include "PCH.h"

#include "Win32RenderWindow.h"
#include "Vector2f.h"

using namespace Sand;

extern LRESULT CALLBACK WindowProc( HWND hwnd , UINT msg , WPARAM wParam , LPARAM lParam );

Win32RenderWindow::Win32RenderWindow()
{
	m_hWnd = 0;

	m_dStyle = ( WS_OVERLAPPEDWINDOW | WS_VISIBLE );
}

Win32RenderWindow::~Win32RenderWindow()
{
	Shutdown();
}

LRESULT CALLBACK InternalWindowProc( HWND hwnd , UINT msg , WPARAM wParam , LPARAM lParam )
{
	/*
		http://lonelywaiting.github.io/SetWindowLongPtr%E4%B8%8EGetWindowLongPtr/
	*/
	LONG_PTR ObjPtr = GetWindowLongPtr( hwnd , 0 );

	if ( ObjPtr == 0 )
	{
		return DefWindowProc( hwnd , msg , wParam , lParam );
	}
	else
	{
		return ( ( ( IWindowProc* )ObjPtr )->WindowProc( hwnd , msg , wParam , lParam ) );
	}
}

void Win32RenderWindow::Initialize( IWindowProc* WindowProObj )
{
	WNDCLASSEX wc;

	memset( &wc , 0 , sizeof( wc ) );
	wc.cbSize = sizeof( WNDCLASSEX );
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = InternalWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = sizeof( WindowProObj );
	wc.hInstance = 0;
	wc.hIcon = LoadIcon( NULL , IDI_APPLICATION );
	wc.hCursor = LoadCursor( NULL , IDC_ARROW );
	wc.hbrBackground = ( HBRUSH )GetStockObject( BLACK_BRUSH );
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"SoftRaster";
	wc.hIconSm = LoadIcon( NULL , IDI_APPLICATION );

	// 注册类
	RegisterClassEx( &wc );

	RECT rc;
	rc.top = rc.left = 0;
	rc.right = m_iWidth;
	rc.bottom = m_iHeight;

	// 根据设备尺寸调节窗口尺寸
	AdjustWindowRectEx( &rc , m_dStyle , false , 0 );

	long lWidth = rc.right - rc.left;
	long lHeight = rc.bottom - rc.top;

	long lLeft = ( long )m_iLeft;
	long lTop = ( long )m_iTop;

	// 创建窗口实例
	m_hWnd = CreateWindowEx(
		NULL ,
		wc.lpszClassName ,
		m_sCaption.c_str() ,
		m_dStyle ,
		lLeft , lTop ,
		lWidth , lHeight ,
		NULL ,
		NULL ,
		NULL ,
		NULL );

	RECT rect;
	GetClientRect( m_hWnd , &rect );
	m_iWidth = rect.right - rect.left;
	m_iHeight = rect.bottom - rect.top;

	if ( m_hWnd )
	{
		/*
			http://lonelywaiting.github.io/SetWindowLongPtr%E4%B8%8EGetWindowLongPtr/
		*/
		SetWindowLongPtr( m_hWnd , 0 , ( LONG_PTR )WindowProObj );

		ShowWindow( m_hWnd , SW_SHOWNORMAL );
		UpdateWindow( m_hWnd );
	}
}

void Win32RenderWindow::Shutdown()
{
	if ( m_hWnd )
	{
		DestroyWindow( m_hWnd );
	}

	m_hWnd = 0;
}

Vector2f Win32RenderWindow::GetCursorPosition()
{
	POINT p;
	// 获取鼠标位置，绝对坐标
	GetCursorPos( &p );
	// 从屏幕绝对坐标转为窗口相对坐标
	ScreenToClient( m_hWnd , &p );

	return Vector2f( static_cast< float >( p.x ) , static_cast< float >( p.y ) );
}