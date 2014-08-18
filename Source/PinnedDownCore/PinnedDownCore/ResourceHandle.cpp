#include "ResourceHandle.h"

using namespace PinnedDownCore;

ResourceHandle::ResourceHandle()
{
}

ResourceHandle::ResourceHandle(std::string resourceName)
	: resourceName(std::make_shared<HashedString>(resourceName.c_str()))
{
}

std::shared_ptr<HashedString> ResourceHandle::GetResourceName()
{
	return std::shared_ptr<HashedString>(this->resourceName);
}

ResourceHandle::~ResourceHandle()
{
}