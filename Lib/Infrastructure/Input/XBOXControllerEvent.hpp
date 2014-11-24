#pragma once

#include "../General/Event.hpp"
#include "XBOXController.h"

#include <string>

namespace Infrastructure
{

class XBOXControllerEvent : public Event
{
private:
	XBOXController * m_controller;
	XBOXControlId m_controlId;

public:
	XBOXControllerEvent(Object* sender, XBOXController * controller, XBOXControlId controlId)
	: Event(sender)
	, m_controller(controller)
	, m_controlId(controlId) 
	{
	}

	virtual ~XBOXControllerEvent() { }

	XBOXController * const GetController() {
		return m_controller;
	}

	const XBOXControlId GetControlId() const {
		return m_controlId;
	}
};

}