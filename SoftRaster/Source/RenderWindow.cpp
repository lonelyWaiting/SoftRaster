#include "PCH.h"

#include "RenderWindow.h"

using namespace Sand;

RenderWindow::RenderWindow()
{
	m_hWnd = 0;
	m_dStyle = ( WS_OVERLAPPEDWINDOW | WS_VISIBLE );
	m_sCaption = L"";
	m_iWidth = 640;
	m_iHeight = 480;
	m_iLeft = 100;
	m_iTop = 100;
}

RenderWindow::~RenderWindow()
{

}

HWND RenderWindow::GetHandle()
{
	return m_hWnd;
}

void RenderWindow::SetSize( int width , int height )
{
	m_iWidth = width;
	m_iHeight = height;

	UpdateWindowState();
}

//-------------��----------------
void RenderWindow::SetWidth( int width )
{
	m_iWidth = width;

	UpdateWindowState();
}

int RenderWindow::GetWidth()
{
	// ��ȡ�ͻ���
	RECT rect;
	GetClientRect( m_hWnd , &rect );

	return ( rect.right - rect.left );
}

//-------------��------------------
void RenderWindow::SetHeight( int height )
{
	m_iHeight = height;

	UpdateWindowState();
}

int RenderWindow::GetHeight()
{
	RECT rect;
	GetClientRect( m_hWnd , &rect );

	return ( rect.bottom - rect.top );
}

//--------------λ��------------------
void RenderWindow::SetPosition( int left , int top )
{
	m_iLeft = left;
	m_iTop = top;

	UpdateWindowState();
}

int RenderWindow::GetLeft()
{
	POINT point;
	point.x = 0;
	point.y = 0;

	// client��(0 , 0)��Ӧ����Ļ����
	ClientToScreen( m_hWnd , &point );

	return point.x;
}

int RenderWindow::GetTop()
{
	POINT point;
	point.x = 0;
	point.y = 0;

	ClientToScreen( m_hWnd , &point );

	return point.y;
}


void RenderWindow::ResizeWindow( int width , int height )
{
	// ���������WM_SIZE����
	m_iWidth = width;
	m_iHeight = height;
}

//-------------------����----------------------
void RenderWindow::SetCaption( std::wstring& caption )
{
	m_sCaption = caption;

	if ( m_hWnd != 0 )
	{
		SetWindowText( m_hWnd , m_sCaption.c_str() );
	}
}

std::wstring RenderWindow::GetCaption()
{
	return m_sCaption;
}

//--------------���ڷ��------------------
DWORD RenderWindow::GetStyle()
{
	return m_dStyle;
}

void RenderWindow::SetStyle( DWORD dStyle )
{
	m_dStyle = dStyle;

	// GWL_EXSTYLE:���ڻ�ȡ���ڶ�������չ�����ڴ��ַ
	// �ú�������д���µĴ�����չ���
	SetWindowLongPtr( m_hWnd , GWL_EXSTYLE , m_dStyle );
}

void RenderWindow::UpdateWindowState()
{
	if ( m_hWnd != 0 )
	{
		RECT ClientRect;
		ClientRect.left = 0;
		ClientRect.top = 0;
		ClientRect.right = m_iWidth;
		ClientRect.bottom = m_iHeight;

		RECT WindowRect = ClientRect;
		AdjustWindowRect( &WindowRect , m_dStyle , FALSE );

		int deltaX = ( WindowRect.right - ClientRect.right ) / 2;
		int deltaY = ( WindowRect.bottom - ClientRect.bottom ) / 2;

		MoveWindow( m_hWnd , m_iLeft - deltaX , m_iTop - deltaY , m_iWidth + deltaX * 2 , m_iHeight + deltaY * 2 , true );
	}
}