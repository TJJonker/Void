#include "pch.h"
#include "Time.h"

namespace Void {

	float Time::m_LastFrameTimestamp = 0;
	float Time::m_DeltaTime = 0;

	void Void::Time::Update()
	{
		if (glfwGetTime() == m_LastFrameTimestamp) {
			VOID_CORE_WARN("Time is being updated twice in the same frame.");
			return;
		}

		m_DeltaTime = glfwGetTime() - m_LastFrameTimestamp;
		m_LastFrameTimestamp = glfwGetTime();
	}
}
