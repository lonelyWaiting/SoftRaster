#ifndef App_h
#define App_h

#include "Application.h"

#include "Renderer.h"

#include "Entity.h"

namespace Sand
{
	class App : public Application
	{
	public:
		App();
		virtual ~App();

		virtual bool ConfigureEngineComponents();
		virtual bool ShutdownEngineComponents();

		virtual void Initialize();
		virtual void Update();
		virtual void Shutdown();

		virtual std::wstring GetName();

		/*
			 Û±ÍœÏ”¶
		*/
		virtual void OnMouseDown( WPARAM buttonState , int x , int y );
		virtual void OnMouseUp( WPARAM buttonState , int x , int y );
		virtual void OnMouseMove( WPARAM buttonState , int x , int y );

	protected:
		int m_iWidth;
		int m_iHeight;
		Renderer* m_pRenderer;

		Entity* m_Entity;

		Camera* m_pCamera;
	};
}
#endif