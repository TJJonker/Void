#include <Void.h>
#include "MainLayer.h"
#include "Void/Core/EntryPoint.h"

class Sandbox : public Void::Application {
public:
	Sandbox() {
		//PushLayer(new MainLayer());
	}

	~Sandbox() {

	}
};


Void::Application* Void::CreateApplication() {
	return new Sandbox();
}