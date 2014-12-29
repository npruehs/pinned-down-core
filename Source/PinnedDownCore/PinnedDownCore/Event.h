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

		virtual std::wstring ToString()
		{
			std::string eventType(this->GetEventType().GetString());
			return std::wstring(eventType.begin(), eventType.end());
		}

		virtual const NetRole GetNetRole() const
		{
			return NetRole::None;
		}

		virtual void Serialize(std::ostrstream& out) { }
		virtual void Deserialize(std::istrstream& in) { }
	};
}