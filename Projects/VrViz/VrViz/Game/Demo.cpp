#include "stdafx.h"

#include <General\EventBus.hpp>
#include <Input\XBOXController.h>
#include <Input\XBOXControllerButtonEvent.h>

#include "Demo.hpp"
#include "DemoEventHandler.hpp"
#include "DemoRenderer.h"

#include "..\World\World.h"
#include "..\World\Player.h"

using namespace Infrastructure;

Demo::Demo()
: m_Run(false)
{
	// Create the objects
	m_pController = new XBOXController(1);	
	m_pRenderer = new DemoRenderer();
	m_pEventHandler = new DemoEventHandler(this);	
}

Demo::~Demo()
{
	Stop();

	delete m_pController;
	m_pController = NULL;

	delete m_pRenderer;
	m_pRenderer = NULL;

	delete m_pEventHandler;
	m_pEventHandler = NULL;
}

void Demo::Run()
{
	m_Run = true;

	// Register for Events
	RegisterEventHandler(EventBus::AddHandler<XBOXControllerButtonEvent>(m_pEventHandler));

	// Create the Renderer
	World::CreateInstance();

	m_pRenderer->Initialize();

	// Run the game loop....
	while(m_Run)
	{
		m_pController->Update();

		if(m_Run)
		{
			const Player *player = World::Instance()->GetPlayer();
			const osg::Vec3 &pos = player->GetPosition();
			const float angleVert = player->GetViewAngleVertical();
			const float angleHoriz = player->GetViewAngleHorizontal();
			printf("Player: X=%.1f\tY=%.1f\tZ=%0.1f\tPitch=%0.1f\tYaw=%0.1f\n",
				pos.x(), pos.y(), pos.z(), angleVert, angleHoriz);

			// Update the Camera for the player & render the scene.
			m_pRenderer->SetCameraPosition(pos);
			m_pRenderer->SetCameraPitch(angleVert);
			m_pRenderer->SetCameraYaw(angleHoriz);
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

	UnregisterAllEventsHandlers();
		
	World::DestroyInstance();

}

void Demo::Reset()
{
	World::Instance()->GetPlayer()->Reset();
}