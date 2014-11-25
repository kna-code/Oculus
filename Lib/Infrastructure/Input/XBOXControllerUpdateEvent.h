#pragma once

#include "../General/Event.hpp"
#include "../General/Types.h"
#include "XBOXController.h"

namespace Infrastructure
{

class XBOXControllerUpdateEvent : public Event
{
private:
	XBOXController * m_controller;
	Vec2 m_leftThumbStickPosition;
	Vec2 m_rightThumbStickPosition;

public:
	XBOXControllerUpdateEvent(Object* sender, XBOXController * controller, Vec2 leftThumbStick, Vec2 rightThumbStick)
	: Event(sender)
	, m_controller(controller)
	, m_leftThumbStickPosition(leftThumbStick)
	, m_rightThumbStickPosition(rightThumbStick)
	{
	}

	virtual ~XBOXControllerUpdateEvent() { }

	XBOXController * const GetController() {
		return m_controller;
	}

	const Vec2 GetLeftThumbStickPosition() const {
		return m_leftThumbStickPosition;
	}

	const Vec2 GetRightThumbStickPosition() const {
		return m_rightThumbStickPosition;
	}
};

}