#include "Game.h"
#include "EntityManager.h"
#include "EntityCreatedEvent.h"
#include "EntityRemovedEvent.h"

using namespace PinnedDownCore;

EntityManager::EntityManager(Game* game)
{
	this->game = game;
	this->nextEntity = 0;
}

Entity EntityManager::CreateEntity()
{
	Entity entity = ++this->nextEntity;

	// Raise event.
	auto entityCreatedEvent = std::make_shared<EntityCreatedEvent>(entity);
	this->game->eventManager->QueueEvent(entityCreatedEvent);

	return entity;
}

void EntityManager::RemoveEntity(Entity entity)
{
	this->removedEntities.insert(entity);

	// Raise event.
	auto entityRemovedEvent = std::make_shared<EntityRemovedEvent>(entity);
	this->game->eventManager->QueueEvent(entityRemovedEvent);
}

void EntityManager::AddComponent(Entity entity, const ComponentPtr & component)
{
	// Get the component type entry in the components map.
	std::map<Entity, ComponentMap>::iterator iterator = this->componentMaps.find(component->GetComponentType().GetHash());

	if (iterator != this->componentMaps.end())
	{
		ComponentMap & componentMap = iterator->second;

		// Add component.
		componentMap.insert(std::pair<int, ComponentPtr>(entity, component));
	}
	else
	{
		// Add new component map.
		ComponentMap componentMap = ComponentMap();
		componentMap.insert(std::pair<int, ComponentPtr>(entity, component));
		this->componentMaps.insert(std::pair<Entity, ComponentMap>(component->GetComponentType().GetHash(), componentMap));
	}
}

ComponentPtr EntityManager::GetComponent(Entity entity, const HashedString & componentType) const
{
	// Lookup component map.
	auto iterator = this->componentMaps.find(componentType.GetHash());

	if (iterator != this->componentMaps.end())
	{
		auto componentMap = iterator->second;

		// Lookup component.
		auto componentIterator = componentMap.find(entity);

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
	for (std::set<Entity>::iterator entityIterator = this->removedEntities.begin(); entityIterator != this->removedEntities.end(); ++entityIterator)
	{
		Entity entity = *entityIterator;

		// Find all attached components.
		for (std::map<Entity, ComponentMap>::iterator compMapIterator = this->componentMaps.begin(); compMapIterator != this->componentMaps.end(); ++compMapIterator)
		{
			ComponentMap & componentMap = compMapIterator->second;

			ComponentMap::iterator componentIterator = componentMap.find(entity);

			if (componentIterator != componentMap.end())
			{
				// Remove component.
				componentMap.erase(componentIterator);
			}
		}
	}

	this->removedEntities.clear();
}