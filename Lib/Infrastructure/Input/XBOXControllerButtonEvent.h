#pragma once

#include "../General/Event.hpp"
#include "XBOXController.h"

namespace Infrastructure
{

enum ButtonEventType
{
	BUTTON_PRESSED,
	BUTTON_RELEASED
};

class XBOXControllerButtonEvent : public Event
{
private:
	XBOXController * m_controller;
	XBOXButtonId m_buttonId;
	ButtonEventType m_eventType;

public:
	XBOXControllerButtonEvent(Object* sender, XBOXController * controller, XBOXButtonId buttonId, ButtonEventType eventType)
	: Event(sender)
	, m_controller(controller)
	, m_buttonId(buttonId)
	, m_eventType(eventType)
	{
	}

	virtual ~XBOXControllerButtonEvent() { }

	XBOXController * const GetController() {
		return m_controller;
	}

	const XBOXButtonId GetButtonId() const {
		return m_buttonId;
	}

	const ButtonEventType GetEventType() const {
		return m_eventType;
	}

};

}