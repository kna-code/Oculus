#include "stdafx.h"
#include "Player.h"
#include <math.h>

#include <General\EventBus.hpp>

using namespace Infrastructure;

Player::Player()
	: m_moveVelocity(1.0f)
	, m_rotateVelocity(1.0f)
	, m_position(0, 0, 1.0)
	, m_viewAngleVertical(0)
	, m_viewAngleHorizontal(0)
{
	Reset();

	// Register for Events	
	RegisterEventHandler(EventBus::AddHandler<XBOXControllerUpdateEvent>(this));
}

Player::~Player()
{
	// Unregister for Events
	UnregisterAllEventsHandlers();
}

void Player::Update()
{

}

void Player::Reset()
{
	m_position = osg::Vec3d(0, 0, 10.0);
	m_viewAngleVertical = 90;
	m_viewAngleHorizontal = 0;
}

// -------------------------------------------------------------------------------------
// Event Handlers
// -------------------------------------------------------------------------------------

void Player::onEvent(Infrastructure::XBOXControllerUpdateEvent* e)
{
	// Determine the player's new position data from the control.
	auto movementVector = e->GetLeftThumbStickPosition();
	auto rotationVector = e->GetRightThumbStickPosition();

	// Up/Down View orientation: -90 to 90 Degrees
	m_viewAngleVertical += (-rotationVector.y)*m_rotateVelocity;
	m_viewAngleVertical = max(min(m_viewAngleVertical, 180.0f), 0.0f);

	// Left/Right orientation: 0 to 360 Degress
	m_viewAngleHorizontal = m_viewAngleHorizontal += rotationVector.x*m_rotateVelocity;
	while(m_viewAngleHorizontal < 0 )
	{
		m_viewAngleHorizontal += 360;
	}
	while(m_viewAngleHorizontal > 360)
	{
		m_viewAngleHorizontal -= 360;
	}

	// Update the position taking the horizontal view angle int account

	float xPos = m_position.x() + movementVector.x*m_moveVelocity*tan(osg::DegreesToRadians(m_viewAngleHorizontal));
	float yPos = m_position.y() + movementVector.y*m_moveVelocity*tan(osg::DegreesToRadians(m_viewAngleHorizontal-90));
	m_position = osg::Vec3(xPos, yPos, 1);

}