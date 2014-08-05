#pragma once

#include "HashedString.h"

namespace PinnedDownCore
{
	class IEntityComponent
	{
	public:
		virtual const HashedString & GetComponentType() const = 0;
	};
}