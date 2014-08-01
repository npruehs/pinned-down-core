#pragma once

#include "Event.h"

namespace PinnedDownCore
{
	class IEventListener
	{
	public:
		virtual void OnEvent(Event & event) = 0;
	};
}