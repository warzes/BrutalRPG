#pragma once

#include "ApplicationSettings.h"

class Application
{
public:
	Application(const ApplicationSettings &setting);
	~Application();



private:
	Application(const Application&) = delete;
	void operator=(const Application&) = delete;

	struct appImplData;
	appImplData *m_impl;
};