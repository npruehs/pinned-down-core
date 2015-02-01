#pragma once

#include <set>
#include <list>
#include <map>
#include <memory>
#include "Event.h"
#include "IEventListener.h"
#include "HashedString.h"

typedef std::shared_ptr<PinnedDownCore::Event> EventPtr;

#define EVENT_HANDLER_DECLARATION(EventType) void On##EventType(EventType& data)

#define EVENT_HANDLER_DEFINITION(ClassName, EventType) void ClassName::On##EventType(EventType& data)

#define CALL_EVENT_HANDLER(EventType)\
	if (newEvent.GetEventType() == EventType::EventType##Type)\
			{\
		auto e = static_cast<EventType&>(newEvent);\
		this->On##EventType(e);\
		return;\
			}\

namespace PinnedDownCore
{
	class EventManager
	{
	public:
		EventManager();

		// Adds the passed listener for events of all types.
		void AddListener(IEventListener* listener);

		// Adds the passed listener for events of the specified type.
		void AddListener(IEventListener* listener, HashedString const & eventType);

		// Removes the passed listener for events of all types.
		void RemoveListener(IEventListener* listener);

		// Removes the passed listener for events of the specified type.
		void RemoveListener(IEventListener* listener, HashedString const & eventType);

		// Queues the specified event for processing in the next tick.
		void QueueEvent(EventPtr const & newEvent);

		// Raises the specified event to be handled immediately.
		void RaiseEvent(EventPtr const & newEvent);

		// Raises all queued events.
		void Tick();

	private:
		// Set of registered event types.
		std::set<HashedString> eventTypes;

		// Maps event types to listeners.
		std::map<unsigned long, std::list<IEventListener*>> listeners;
			
		// Listeners for all events.
		std::list<IEventListener*> listenersForAllEvents;

		// Events that are currently being processed.
		std::list<EventPtr> currentEvents;

		// New events to be processed soon.
		std::list<EventPtr> newEvents;
	};
}
