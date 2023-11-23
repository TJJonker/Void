#pragma once

// TODO: Abstract to the point where GLFW can be deleted.

namespace Void {
	class Time
	{
	private:
		static double m_LastFrameTimestamp;
		static double m_DeltaTime;

	public:
		static float DeltaTime() { return (float)m_DeltaTime; };
		static void Update();
		static float TimeSinceStartup();
	};
}
