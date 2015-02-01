#include "EventManager.h"

using namespace PinnedDownCore;

EventManager::EventManager()
{
}

void EventManager::AddListener(IEventListener* listener)
{
	this->listenersForAllEvents.push_back(listener);
}

void EventManager::AddListener(IEventListener* listener, HashedString const & eventType)
{
	// Get the event type entry in the listeners map.
	std::map<unsigned long, std::list<IEventListener*>>::iterator iterator = this->listeners.find(eventType.GetHash());

	if (iterator != this->listeners.end())
	{
		std::list<IEventListener*> & eventListeners = iterator->second;

		// Add listener.
		eventListeners.push_back(listener);
	}
	else
	{
		// Add new entry to listeners map.
		std::list<IEventListener*> eventListeners = std::list<IEventListener*>();
		eventListeners.push_back(listener);
		this->listeners.insert(std::pair<unsigned long, std::list<IEventListener*>>(eventType.GetHash(), eventListeners));
	}
}

void EventManager::RemoveListener(IEventListener* listener)
{
	this->listenersForAllEvents.remove(listener);
}

void EventManager::RemoveListener(IEventListener* listener, HashedString const & eventType)
{
	// Find listener to remove.
	std::map<unsigned long, std::list<IEventListener*>>::iterator it = this->listeners.find(eventType.GetHash());

	if (it != this->listeners.end())
	{
		std::list<IEventListener*>& eventListeners = it->second;

		for (std::list<IEventListener*>::iterator it2 = eventListeners.begin(); it2 != eventListeners.end(); ++it2)
		{
			if (*it2 == listener)
			{
				// Remove listener.
				eventListeners.erase(it2);
				return;
			}
		}
	}
}

void EventManager::QueueEvent(EventPtr const & newEvent)
{
	// Queue event.
	this->newEvents.push_back(newEvent);
}

void EventManager::RaiseEvent(EventPtr const & newEvent)
{
	HashedString const & eventType = newEvent->GetEventType();
	unsigned long eventHash = eventType.GetHash();

	// Get listeners for the event.
	std::map<unsigned long, std::list<IEventListener*>>::iterator itListeners = this->listeners.find(eventHash);

	if (itListeners != this->listeners.end())
	{
		std::list<IEventListener*> & eventListeners = itListeners->second;

		// Notify all listeners.
		for (std::list<IEventListener*>::iterator it = eventListeners.begin(); it != eventListeners.end(); )
		{
			(*it++)->OnEvent(*newEvent);
		}
	}

	// Get listeners for all events.
	for (std::list<IEventListener*>::iterator it = this->listenersForAllEvents.begin(); it != this->listenersForAllEvents.end(); ++it)
	{
		(*it)->OnEvent(*newEvent);
	}
}

void EventManager::Tick()
{
	while (!this->newEvents.empty())
	{
		// Move events from new event queue to current event queue.
		EventPtr newEvent = this->newEvents.front();
		this->newEvents.pop_front();
		this->currentEvents.push_back(newEvent);

		// Process all events.
		while (!this->currentEvents.empty())
		{
			// Get next event to process.
			EventPtr currentEvent = this->currentEvents.front();
			this->currentEvents.pop_front();

			this->RaiseEvent(currentEvent);
		}
	}
}