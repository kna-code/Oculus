#include "stdafx.h"

#include <Input/XBOXController.h>
#include <General\EventBus.hpp>

#include "Demo.hpp"
#include "DemoEventHandler.hpp"
#include "DemoRenderer.hpp"
#include "Player.hpp"

using namespace Infrastructure;

Demo::Demo()
: m_Run(false)
{
	// Create the objects
	m_pPlayer = new Player();
	m_pController = new XBOXController(1);	
	m_pRenderer = new DemoRenderer();
	m_pEventHandler = new DemoEventHandler(this);	
	
}

Demo::~Demo()
{
	Stop();

	delete m_pController;
	m_pController = NULL;

	delete m_pPlayer;
	m_pPlayer = NULL;

	delete m_pRenderer;
	m_pRenderer = NULL;

	delete m_pEventHandler;
	m_pEventHandler = NULL;
}

void Demo::Run()
{
	m_Run = true;

	// Register for Events
	m_EventRegistrations.push_back(EventBus::AddHandler<XBOXControllerButtonEvent>(m_pEventHandler));
	m_EventRegistrations.push_back(EventBus::AddHandler<XBOXControllerUpdateEvent>(m_pPlayer));

	// Create the Renderer
	m_pRenderer->Initialize();

	// Run the game loop....
	while(m_Run)
	{
		m_pController->Update();

		if(m_Run)
		{
			const osg::Vec3 &pos = m_pPlayer->GetPosition();
			const osg::Vec3 &rot = m_pPlayer->GetRotation();
			printf("Player: X=%.3f, Y=%.3f, Z=%0.3f, Pitch=%0.4f, Yaw=%0.3f\n",
				pos.x(), pos.y(), pos.x(), rot.x(), rot.y());

			// Update the Camera for the player & render the scene.
			m_pRenderer->SetCameraPosition(pos);
			m_pRenderer->SetCameraPitch(rot.x());
			m_pRenderer->SetCameraYaw(rot.y());
			m_pRenderer->Update();
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