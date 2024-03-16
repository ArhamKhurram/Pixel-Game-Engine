#pragma once

#include "Core.h"

namespace Riyal {

	class RIYAL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}