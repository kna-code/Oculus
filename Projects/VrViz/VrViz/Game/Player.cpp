#include "stdafx.h"
#include "Player.hpp"
#include <Input\XBOXControllerUpdateEvent.h>

using namespace Infrastructure;

Player::Player()
	: m_velocity(0.1f)
	, m_position(0, 0, 0)
	, m_rotation(0, 0, 0)
{

}

void Player::Update()
{

}

// -------------------------------------------------------------------------------------
// Event Handlers
// -------------------------------------------------------------------------------------

void Player::onEvent(Infrastructure::XBOXControllerUpdateEvent* e)
{
	// Determine the player's new position data from the control.
	auto movementVector = e->GetLeftThumbStickPosition();
	auto rotationVector = e->GetRightThumbStickPosition();

	// Todo: Correctly handle velocity on the diagonal instead
	// of applying it directly to both legs.

	float xPos = m_position.x()+ movementVector.x*m_velocity;
	float yPos = m_position.y() + movementVector.y*m_velocity;
	m_position = osg::Vec3(xPos, yPos, 1);

	float xRot = rotationVector.x*90;;
	float yRot = rotationVector.y*90;
	m_rotation = osg::Vec3(xRot, yRot, 0);
}