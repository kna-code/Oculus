#pragma once

#include <list>

#include "EventHandler.hpp"

namespace Infrastructure
{	
// Forward Declarations
class HandlerRegistration;

// TypeDefs
typedef std::list<Infrastructure::HandlerRegistration*> HandlerRegistrationList;
typedef std::list<Infrastructure::HandlerRegistration*>::iterator HandlerRegistrationItr;

// Keeps track of event handlers.
class EventHandlerTracker
{
public:
	EventHandlerTracker();
	virtual ~EventHandlerTracker();

	void RegisterEventHandler(HandlerRegistration * handler);

	void UnregisterAllEventsHandlers();

private:	
	HandlerRegistrationList m_EventRegistrations;
};

}