#include "stdafx.h"
#include "Application.h"
#include "CoreLogSystem.h"

struct Application::appImplData
{
	appImplData(const ApplicationSettings &refSetting)
		: setting(refSetting)
		, logSystem(refSetting.coreLog)
	{
	}

	ApplicationSettings setting;
	CoreLogSystem logSystem;
};

Application::Application(const ApplicationSettings& setting)
	: m_impl(new Application::appImplData(setting))
{
}

Application::~Application()
{
	delete m_impl;
}