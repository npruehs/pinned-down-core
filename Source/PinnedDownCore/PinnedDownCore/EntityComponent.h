#pragma once

#include "HashedString.h"

namespace PinnedDownCore
{
	class EntityComponent
	{
	public:
		virtual const HashedString & GetComponentType() const = 0;
	};
}