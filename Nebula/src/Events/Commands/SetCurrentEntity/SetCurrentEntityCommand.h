#pragma once
#include "Events/Core/IEventCommand.h"
#include "Events/EventStructs/EntitySelected.h"

namespace Nebula::Events {
	class SetCurrentEntityCommand : public IEventCommand<EntitySelected>
	{
	public:
		SetCurrentEntityCommand(Void::Entity** valueToUpdate)
			: m_Value(valueToUpdate) { }

		virtual void Execute(EntitySelected& value) override;

	private:
		Void::Entity** m_Value;
	};
}
