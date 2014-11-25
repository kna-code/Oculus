#pragma once

#include <list>

namespace Infrastructure
{
	class XBOXController;
	class HandlerRegistration;

}

class DemoEventHandler;
class DemoRenderer;
class Player;
	
typedef std::list<Infrastructure::HandlerRegistration*> HandlerRegistrationList;
typedef std::list<Infrastructure::HandlerRegistration*>::iterator HandlerRegistrationItr;

class Demo
{
private:
	bool m_Run;
	Infrastructure::XBOXController * m_pController;
	DemoRenderer * m_pRenderer;
	Player * m_pPlayer;

	// Events
	DemoEventHandler * m_pEventHandler;
	HandlerRegistrationList m_EventRegistrations;

public:
	Demo();
	~Demo();

	void Run();
	void Stop();
	void Reset();
};