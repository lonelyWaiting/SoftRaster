#include "PCH.h"
#include "Surface.h"

using namespace Sand;

Surface::Surface()
	:m_pData( nullptr ) ,
	m_DeviceContext( NULL ) ,
	m_iSurfaceWidth( 0 ) , m_iSurfaceHeight( 0 )
{
	
}

Surface::~Surface()
{
	Release();
}

void Surface::Init( HWND hwnd , int width , int height )
{
	if ( m_DeviceContext == NULL || m_iSurfaceWidth != width || m_iSurfaceHeight != height )
	{
		Release();

		HDC hdc = GetDC( hwnd );
		m_DeviceContext = ::CreateCompatibleDC( hdc );
		ReleaseDC( hwnd , hdc );

		m_iSurfaceWidth = width;
		m_iSurfaceHeight = height;
		BITMAPINFO BitmapInfo = 
		{
			{
				sizeof( BITMAPINFOHEADER ) ,
				m_iSurfaceWidth ,
				-m_iSurfaceHeight ,
				1 ,
				32 ,
				BI_RGB ,
				m_iSurfaceWidth * m_iSurfaceHeight * 4 ,
				0 , 
				0 , 
				0 ,
				0
			}
		};

		m_hBitmap = CreateDIBSection( m_DeviceContext , &BitmapInfo , DIB_RGB_COLORS , ( void** )&m_pData , NULL , 0 );

		assert( m_hBitmap != NULL );

		m_hOldBitmap = ( HBITMAP )::SelectObject( m_DeviceContext , m_hBitmap );
		::SetBkMode( m_DeviceContext , TRANSPARENT );
	}
}

void Surface::Release()
{
	if ( m_DeviceContext != NULL )
	{
		::SelectObject( m_DeviceContext , m_hOldBitmap );
		::DeleteObject( m_hBitmap );
		::DeleteObject( m_DeviceContext );
		m_DeviceContext = NULL;
	}
}