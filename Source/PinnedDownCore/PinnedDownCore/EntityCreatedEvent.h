#pragma once

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

		int entityId;

		explicit EntityCreatedEvent(int entityId)
		{
			this->entityId = entityId;
		}
	};
}