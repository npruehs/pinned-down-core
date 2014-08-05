#include "ResourceManager.h"

using namespace PinnedDownCore;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	this->resourceMap.clear();
}

ResHandlePtr ResourceManager::GetResource(HashedString resourceName)
{
	// Lookup resource.
	std::map<unsigned long, ResHandlePtr>::iterator iterator = this->resourceMap.find(resourceName.GetHash());

	if (iterator != this->resourceMap.end())
	{
		// Return handle.
		return ResHandlePtr(iterator->second);
	}
	else
	{
		return nullptr;
	}
}

void ResourceManager::UnloadResource(HashedString resourceName)
{
	// Find resource to unload.
	for (std::map<unsigned long, ResHandlePtr>::iterator iterator = this->resourceMap.begin(); iterator != this->resourceMap.end(); iterator++)
	{
		if (iterator->first == resourceName.GetHash())
		{
			// Remove resource.
			resourceMap.erase(iterator);
			return;
		}
	}
}
