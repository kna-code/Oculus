#pragma once

#include <list>
#include <General\EventHandlerTracker.h>

namespace Infrastructure
{
	class XBOXController;
	class HandlerRegistration;
}

class DemoEventHandler;
class DemoRenderer;
class Player;

class Demo 
	: public Infrastructure::EventHandlerTracker 
{
private:
	bool m_Run;
	Infrastructure::XBOXController * m_pController;
	DemoRenderer * m_pRenderer;
	
	// Events
	DemoEventHandler * m_pEventHandler;

public:
	Demo();
	~Demo();

	void Run();
	void Stop();
	void Reset();
};