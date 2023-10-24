#pragma once
#include <GLFW/glfw3.h>

// TODO: Abstract to the point where GLFW can be deleted.

namespace Void {
	class Time
	{
	private:
		static float m_LastFrameTimestamp;
		static float m_DeltaTime;

	public:
		static float DeltaTime() { return m_DeltaTime; };
		static void Update();
		static float TimeSinceStartup() { return glfwGetTime(); };
	};
}
