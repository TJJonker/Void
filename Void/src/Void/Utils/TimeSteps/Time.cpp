#include "pch.h"
#include "Time.h"
#include <GLFW/glfw3.h>

namespace Void {

	double Time::m_LastFrameTimestamp = 0;
	double Time::m_DeltaTime = 0;

	void Void::Time::Update()
	{
		if (glfwGetTime() == m_LastFrameTimestamp) {
			VOID_CORE_WARN("Time is being updated twice in the same frame.");
			return;
		}

		static bool firstTime = true;
		if (firstTime) {
			firstTime = false;

			m_DeltaTime = glfwGetTime() - m_LastFrameTimestamp;
			m_LastFrameTimestamp = glfwGetTime(); 
		}

		m_DeltaTime = glfwGetTime() - m_LastFrameTimestamp;
		m_LastFrameTimestamp = glfwGetTime();
	}

	float Time::TimeSinceStartup()
	{
		return (float)glfwGetTime();
	}
}
