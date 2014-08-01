#include "ResourceHandle.h"

using namespace PinnedDownCore;

ResourceHandle::ResourceHandle()
{
}

ResourceHandle::ResourceHandle(std::wstring resourceName)
{
	this->resourceName = std::make_shared<HashedString>(resourceName.c_str());
}

std::shared_ptr<HashedString> ResourceHandle::GetResourceName()
{
	return std::shared_ptr<HashedString>(this->resourceName);
}

ResourceHandle::~ResourceHandle()
{
}