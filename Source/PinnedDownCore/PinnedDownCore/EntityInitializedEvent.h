#pragma once

#include "EntityManager.h"
#include "Event.h"

namespace PinnedDownCore
{
	struct EntityInitializedEvent : public Event
	{
		static const HashedString EntityInitializedEventType;

		const HashedString & GetEventType() const
		{
			return EntityInitializedEventType;
		}

		Entity entity;

		explicit EntityInitializedEvent(Entity entity)
		{
			this->entity = entity;
		}
	};
}