#include "stdafx.h"
#include "DemoEventHandler.hpp"
#include <Input\XBOXController.h>
#include <Input\XBOXControllerEvent.hpp>
#include "Demo.hpp"

using namespace Infrastructure;

DemoEventHandler::DemoEventHandler(Demo *demo)
: m_pDemo(demo)
{
}

DemoEventHandler::~DemoEventHandler()
{
}

void DemoEventHandler::onEvent(Infrastructure::XBOXControllerEvent * e)
{
	// Ignore the event if it's already been canceled
	if (e->getCanceled()) {
		return;
	}

	printf("XBOXControllerEvent: %d\n", e->GetControlId());

	switch (e->GetControlId())
	{
	case XBOXControlId::BACK:
		m_pDemo->Stop();
		break;

	default:
		break;
	}
}

