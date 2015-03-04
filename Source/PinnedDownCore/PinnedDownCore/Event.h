#pragma once

#include <string>
#include <strstream>
#include "HashedString.h"
#include "NetRole.h"

#define INVALID_SENDER_ID -1

namespace PinnedDownCore
{
	class Event
	{
	public:
		// Id of the sending client if sent over the network, and INVALID_SENDER_ID otherwise.
		int sender = INVALID_SENDER_ID;

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