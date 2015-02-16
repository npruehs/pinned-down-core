#pragma once

#include "HashedString.h"
#include <memory>

namespace PinnedDownCore
{
	class ResourceHandle
	{
	public:
		ResourceHandle();
		ResourceHandle(const std::string & resourceName);
		~ResourceHandle();

		std::shared_ptr<HashedString> GetResourceName() const;

	private:
		std::shared_ptr<HashedString> resourceName;
	};
}