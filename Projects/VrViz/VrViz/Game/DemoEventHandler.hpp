#pragma once

#include "General\EventHandler.hpp"

namespace Infrastructure
{
	class XBOXControllerEvent;
}

class Demo;

class DemoEventHandler : public Infrastructure::EventHandler<Infrastructure::XBOXControllerEvent>
{
private:
	Demo * m_pDemo;
public:
	DemoEventHandler(Demo *demo);

	virtual ~DemoEventHandler();

	virtual void onEvent(Infrastructure::XBOXControllerEvent* e);
};
