#include "SetCurrentEntityCommand.h"

namespace Nebula::Events {
	void SetCurrentEntityCommand::Execute(EntitySelected& value)
	{
		*m_Value = value.entity;
	}
}