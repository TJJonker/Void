#include <Void.h>


class Sandbox : public Void::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};


Void::Application* Void::CreateApplication() {
	return new Sandbox();
}