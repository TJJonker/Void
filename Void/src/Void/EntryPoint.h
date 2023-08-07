#pragma once

#ifdef VOID_PLATFORM_WINDOWS

extern Void::Application* Void::CreateApplication();

int main(int argc, char** argv) {
	Void::Log::Init();
	VOID_CORE_WARN("Logger initialised!");
	int a = 9;
	VOID_INFO("Logger initialised! Something is {0}", a);

	auto app = Void::CreateApplication();
	app->Run();
	delete app;
}

#endif