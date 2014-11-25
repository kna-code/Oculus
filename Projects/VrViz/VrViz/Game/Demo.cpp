#include "stdafx.h"

#include <Input/XBOXController.h>
#include <General\EventBus.hpp>

#include "Demo.hpp"
#include "DemoEventHandler.hpp"
#include "DemoRenderer.hpp"

using namespace Infrastructure;

Demo::Demo()
: m_Run(false)
{
	// Creat the controller.
	m_pController = new XBOXController(1);

	m_pEventHandler = new DemoEventHandler(this);	
}

Demo::~Demo()
{
	Stop();

	delete m_pController;
	m_pController = NULL;
}

void Demo::Run()
{
	m_Run = true;

	// Register for Events
	m_EventRegistrations.push_back(EventBus::AddHandler<XBOXControllerEvent>(m_pEventHandler));

	// Create the Renderer
	m_pRenderer = new DemoRenderer();
	m_pRenderer->Initialize();

	// Run the game loop....
	while(m_Run)
	{
		m_pController->Update();

		if(m_Run)
		{
			m_pRenderer->Update();

			//m_pViewer->frame(0);
			Sleep(100);
		}
	}
}

void Demo::Stop()
{
	if(!m_Run)
	{
		return;
	}

	m_Run = false;

	// Unregister Events
	for(HandlerRegistrationItr itr = m_EventRegistrations.begin();
		itr != m_EventRegistrations.end();
		++itr)
	{
		HandlerRegistration * reg = (*itr);
		reg->removeHandler();
		delete reg;
	}
	m_EventRegistrations.clear();

}