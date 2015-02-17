#pragma once

#include <string>
#include <strstream>
#include "HashedString.h"
#include "NetRole.h"

namespace PinnedDownCore
{
	class Event
	{
	public:
		virtual const HashedString & GetEventType() const = 0;

		virtual std::string ToString() const
		{
			return this->GetEventType().GetString();
		}

		virtual const NetRole GetNetRole() const
		{
			return NetRole::None;
		}

		virtual void Serialize(std::ostrstream& out) const { }
		virtual void Deserialize(std::istrstream& in) { }
	};
}