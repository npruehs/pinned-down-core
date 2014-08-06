#pragma once

#include "EntityManager.h"
#include "Event.h"

namespace PinnedDownCore
{
	struct EntityRemovedEvent : public Event
	{
		static const HashedString EntityRemovedEventType;

		const HashedString & GetEventType() const
		{
			return EntityRemovedEventType;
		}

		Entity entity;

		explicit EntityRemovedEvent(Entity entity)
		{
			this->entity = entity;
		}
	};
}