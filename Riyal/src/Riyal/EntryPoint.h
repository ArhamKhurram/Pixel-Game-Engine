#pragma once

#ifdef RY_PLATFORM_WINDOWS

extern Riyal::Application* Riyal::CreateApplication();

int main(int argc, char** argv)
{
	Riyal::Log::Init();
	RY_CORE_WARN("Initialized Log!");
	int a = 5;
	RY_INFO("Hello! Var={0}", a);

	auto app = Riyal::CreateApplication();
	app->Run();
	delete app;
}

#endif