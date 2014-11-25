#include "stdafx.h"
#include "XBoxTest.h"
#include "windows.h"

// Infrastructure Libraries
#include <General\EventBus.hpp>
#include <General\EventHandler.hpp>
#include <Input\XBOXController.h>
#include <Input\XBOXControllerButtonEvent.h>
#include <Input\XBOXControllerUpdateEvent.h>


using namespace Infrastructure;

class XBOXTestEventHandler 
	: public EventHandler<XBOXControllerButtonEvent>
	, public EventHandler<XBOXControllerUpdateEvent>
{
public:
	XBOXTestEventHandler() {}

	virtual ~XBOXTestEventHandler() {}

	virtual void onEvent(Infrastructure::XBOXControllerButtonEvent* e)
	{
		printf("XBOXControllerButtonEvent: %d\t%s\n", e->GetButtonId(), e->GetEventType() ? "UP" : "DOWN" );
	}

	virtual void onEvent(Infrastructure::XBOXControllerUpdateEvent* e)
	{
		auto left = e->GetLeftThumbStickPosition();
		auto right = e->GetRightThumbStickPosition();

		printf("XBOXControllerUpdateEvent: Left Stick: [%f %f]\t\tRightStick: [%f %f]\n", left.x, left.y, right.x, right.y);
	}
};


int XBoxTest::RunThumbStickTest()
{
	XBOXController controller = XBOXController(1);
	XBOXTestEventHandler eventHandler;
    Infrastructure::HandlerRegistration * updateEventReg = EventBus::AddHandler<XBOXControllerUpdateEvent>(&eventHandler);
	Infrastructure::HandlerRegistration * buttonEventReg = EventBus::AddHandler<XBOXControllerButtonEvent>(&eventHandler);

	bool connected = false;

	while(1)
	{
		controller.Update();
		if(controller.IsConnected() != connected)
		{
			connected = controller.IsConnected();
			if(connected)
			{
				printf("Connected\n");			
			}
			else
			{
				printf("Not Connected\n");
			}
		}
		
		Sleep(50);
	}

	updateEventReg->removeHandler();
	delete updateEventReg;

	buttonEventReg->removeHandler();
	delete buttonEventReg;

	return 0;
}
