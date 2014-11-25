#include "stdafx.h"
#include "DemoEventHandler.hpp"
#include <Input\XBOXController.h>
#include <Input\XBOXControllerButtonEvent.h>
#include "Demo.hpp"

using namespace Infrastructure;

DemoEventHandler::DemoEventHandler(Demo *demo)
: m_pDemo(demo)
{
}

DemoEventHandler::~DemoEventHandler()
{
}

void DemoEventHandler::onEvent(Infrastructure::XBOXControllerButtonEvent * e)
{
	// Ignore the event if it's already been canceled
	if (e->getCanceled()) {
		return;
	}

	//printf("XBOXControllerButtonEvent: %d\t%d\n", e->GetButtonId(), e->GetEventType());

	if(e->GetEventType() == ButtonEventType::BUTTON_PRESSED)
	{
		switch (e->GetButtonId())
		{
		case XBOXButtonId::BACK:
			m_pDemo->Stop();
			break;
		case XBOXButtonId::START:
			m_pDemo->Reset();
			break;
		default:
			break;
		}
	}
}

