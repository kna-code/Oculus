#pragma once

#include "General\EventHandler.hpp"

namespace Infrastructure
{
	class XBOXControllerButtonEvent;
}

class Demo;

class DemoEventHandler : public Infrastructure::EventHandler<Infrastructure::XBOXControllerButtonEvent>
{
private:
	Demo * m_pDemo;
public:
	DemoEventHandler(Demo *demo);

	virtual ~DemoEventHandler();

	virtual void onEvent(Infrastructure::XBOXControllerButtonEvent* e);
};
