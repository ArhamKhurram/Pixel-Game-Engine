#include <Riyal.h>

class Sandbox : public Riyal::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

};

Riyal::Application* Riyal::CreateApplication()
{
	return new Sandbox();
}