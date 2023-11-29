#pragma once
#include "IECSEventInfo.h"

namespace Void {
	struct IECSCommand {
		virtual void Execute(IECSEventInfo& info) = 0;
	};
}