#pragma once
#include "pch.h"

#ifdef VOID_PLATFORM_WINDOWS

extern Void::Application* Void::CreateApplication();

int main(int argc, char** argv) {
	Void::Log::Init();

	Void::Application* app = Void::CreateApplication();
	app->Run();
	delete app;
}

#endif