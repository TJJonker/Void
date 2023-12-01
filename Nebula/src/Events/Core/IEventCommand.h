#pragma once

namespace Nebula::Events {
	template <typename T>
	struct IEventCommand {
		virtual void Execute(T& value) = 0;
	};
}