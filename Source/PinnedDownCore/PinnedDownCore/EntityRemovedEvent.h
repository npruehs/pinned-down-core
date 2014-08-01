#pragma once

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

		int entityId;

		explicit EntityRemovedEvent(int entityId)
		{
			this->entityId = entityId;
		}
	};
}