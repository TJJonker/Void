#pragma once

namespace Void {
	struct ICommand {
		virtual void Execute() = 0;
	};
}