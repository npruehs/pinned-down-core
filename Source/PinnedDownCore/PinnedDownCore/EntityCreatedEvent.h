#pragma once

#include "EntityManager.h"
#include "Event.h"

namespace PinnedDownCore
{
	struct EntityCreatedEvent : public Event
	{
		static const HashedString EntityCreatedEventType;

		const HashedString & GetEventType() const
		{
			return EntityCreatedEventType;
		}

		Entity entity;

		explicit EntityCreatedEvent(Entity entity)
		{
			this->entity = entity;
		}
	};
}