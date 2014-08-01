#pragma once

#include "HashedString.h"
#include <memory>

namespace PinnedDownCore
{
	class ResourceHandle
	{
	public:
		ResourceHandle();
		ResourceHandle(std::wstring resourceName);
		~ResourceHandle();

		std::shared_ptr<HashedString> GetResourceName();

	private:
		std::shared_ptr<HashedString> resourceName;
	};
}