#include "PCH.h"

#include "Application.h"
#include "Log.h"

using namespace Sand;

int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPreInstance , LPSTR lpCmdLine , int nShowCmd )
{
	// 获取应用程序实例对象
	Application* m_pApp = Application::Get();
	if ( !m_pApp )
	{
		return -1;
	}

	// 配置引擎
	if ( !m_pApp->ConfigureEngineComponents() )
	{
		// 若配置失败，则销毁引擎组件
		m_pApp->ShutdownEngineComponents();

		return -1;
	}


	// 应用程序初始化
	m_pApp->Initialize();

	// 主循环
	m_pApp->MessageLoop();

	// 善后工作
	m_pApp->Shutdown();
	m_pApp->ShutdownEngineComponents();

	return 1;
}