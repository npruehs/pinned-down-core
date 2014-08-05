#pragma once

#include <strstream>
#include "HashedString.h"
#include "NetRole.h"

namespace PinnedDownCore
{
	class Event
	{
	public:
		virtual const HashedString & GetEventType() const = 0;

		virtual const NetRole GetNetRole() const
		{
			return NetRole::None;
		}

		virtual void Serialize(std::ostrstream& out) { }
		virtual void Deserialize(std::istrstream& in) { }
	};
}