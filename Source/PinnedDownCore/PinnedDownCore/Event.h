#pragma once

#include "HashedString.h"

namespace PinnedDownCore
{
	class Event
	{
	public:
		virtual const HashedString & GetEventType() const = 0;
	};
}