#include "Game.h"
#include "EntityManager.h"
#include "EntityCreatedEvent.h"
#include "EntityRemovedEvent.h"

using namespace PinnedDownCore;

EntityManager::EntityManager(Game* game)
{
	this->game = game;
	this->nextEntityId = 0;
}

int EntityManager::CreateEntity()
{
	int entityId = ++this->nextEntityId;

	// Raise event.
	auto entityCreatedEvent = std::make_shared<EntityCreatedEvent>(entityId);
	this->game->eventManager->QueueEvent(entityCreatedEvent);

	return entityId;
}

void EntityManager::RemoveEntity(int entityId)
{
	this->removedEntities.insert(entityId);

	// Raise event.
	auto entityRemovedEvent = std::make_shared<EntityRemovedEvent>(entityId);
	this->game->eventManager->QueueEvent(entityRemovedEvent);
}

void EntityManager::AddComponent(int entityId, ComponentPtr const & component)
{
	// Get the component type entry in the components map.
	std::map<unsigned long, ComponentMap>::iterator iterator = this->componentMaps.find(component->GetComponentType().getHash());

	if (iterator != this->componentMaps.end())
	{
		ComponentMap & componentMap = iterator->second;

		// Add component.
		componentMap.insert(std::pair<int, ComponentPtr>(entityId, component));
	}
	else
	{
		// Add new component map.
		ComponentMap componentMap = ComponentMap();
		componentMap.insert(std::pair<int, ComponentPtr>(entityId, component));
		this->componentMaps.insert(std::pair<unsigned long, ComponentMap>(component->GetComponentType().getHash(), componentMap));
	}
}

ComponentPtr EntityManager::GetComponent(int entityId, HashedString componentType)
{
	// Lookup component map.
	std::map<unsigned long, ComponentMap>::iterator iterator = this->componentMaps.find(componentType.getHash());

	if (iterator != this->componentMaps.end())
	{
		ComponentMap & componentMap = iterator->second;

		// Lookup component.
		ComponentMap::iterator componentIterator = componentMap.find(entityId);

		if (componentIterator != componentMap.end())
		{
			return ComponentPtr(componentIterator->second);
		}
	}

	// No component found.
	return nullptr;
}

void EntityManager::CleanUpEntities()
{
	for (std::set<int>::iterator entityIterator = this->removedEntities.begin(); entityIterator != this->removedEntities.end(); ++entityIterator)
	{
		int entityId = *entityIterator;

		// Find all attached components.
		for (std::map<unsigned long, ComponentMap>::iterator compMapIterator = this->componentMaps.begin(); compMapIterator != this->componentMaps.end(); ++compMapIterator)
		{
			ComponentMap & componentMap = compMapIterator->second;

			ComponentMap::iterator componentIterator = componentMap.find(entityId);

			if (componentIterator != componentMap.end())
			{
				// Remove component.
				componentMap.erase(componentIterator);
			}
		}
	}

	this->removedEntities.clear();
}