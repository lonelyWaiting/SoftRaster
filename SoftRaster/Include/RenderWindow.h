#ifndef RenderWindow_h
#define RenderWindow_h

#include "PCH.h"
#include "IWindowProc.h"

namespace Sand
{
	/*
		�ṩ��һ����ڴ��ڿ�ߣ�λ�ã���񣬱��⣬�Լ��������Ĵ�ȡ����
	*/
	class RenderWindow
	{
	public:
		RenderWindow();
		virtual ~RenderWindow();

		virtual void Initialize( IWindowProc* WindowProcObj ) = 0;
		virtual void Shutdown() = 0;

		HWND GetHandle();

		// ���ڿ��
		void SetWidth( int width );
		void SetHeight( int height );
		int GetWidth();
		int GetHeight();

		// ����λ��
		int GetLeft();
		int GetTop();

		// ���ô��ڿ��
		void SetSize( int width , int height );

		// ���ô���λ��
		void SetPosition( int left , int top );

		// ���ô��ڴ�С
		void ResizeWindow( int width , int height );

		// ���ڱ���
		void SetCaption( std::wstring& caption );
		std::wstring GetCaption();

		// ���ڷ��
		DWORD GetStyle();
		void SetStyle( DWORD dStyle );


	protected:

		void UpdateWindowState();

		HWND m_hWnd;

		// ����
		std::wstring m_sCaption;

		// ���
		DWORD m_dStyle;

		// ���
		int m_iWidth;
		int m_iHeight;

		// λ��
		int m_iLeft;
		int m_iTop;
	};
}

#endif