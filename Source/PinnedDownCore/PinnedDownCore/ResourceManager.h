#pragma once

#include <map>
#include <memory>
#include "ResourceHandle.h"

typedef std::shared_ptr<PinnedDownCore::ResourceHandle> ResHandlePtr;

namespace PinnedDownCore
{
	class Game;

	class ResourceManager
	{
	public:
		ResourceManager(Game* game);
		~ResourceManager();

		ResHandlePtr GetResource(const HashedString & resourceName) const;
		void UnloadResource(const HashedString & resourceName);

		template <class T> std::shared_ptr<T> GetResource(const HashedString & resourceName) const
		{
			ResHandlePtr p = this->GetResource(resourceName);
			return std::static_pointer_cast<T>(p);
		}

	protected:
		Game* game;

		std::map<unsigned long, ResHandlePtr> resourceMap;
	};
}