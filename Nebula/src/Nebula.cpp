#include <Void.h>
#include "EditorLayer.h"
#include "Void/Core/EntryPoint.h"

namespace Nebula {
	class Nebula : public Void::Application {
	public:
		Nebula() {
			PushOverlay(new Editor::EditorLayer());
		}

		~Nebula() {
			
		}
	};
}

Void::Application* Void::CreateApplication() {
	return new Nebula::Nebula();
}