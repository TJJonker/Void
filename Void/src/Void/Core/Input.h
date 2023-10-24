#pragma once
#include <glm/glm.hpp>

namespace Void {
	class Input {
	private:
		static Input* m_Input;

	public:
		static bool KeyPressed(int keycode) { return m_Input->VKeyPressed(keycode); }
		static bool KeyDown(int keycode) { return m_Input->VKeyDown(keycode); }
		static bool MousePressed(int button) { return m_Input->VMousePressed(button); }
		static glm::vec2 MousePosition() { return m_Input->VMousePosition(); }

		static void Create(void* window);
	protected:
		// Keyboard
		virtual bool VKeyPressed(int keycode) = 0;
		virtual bool VKeyDown(int keycode) = 0;

		// Mouse
		virtual bool VMousePressed(int button) = 0;
		virtual glm::vec2 VMousePosition() = 0;
	};
}