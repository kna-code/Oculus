#pragma once

#include "General\EventHandler.hpp"
#include "General\EventHandlerTracker.h"
#include "Input\XBOXControllerUpdateEvent.h"
#include <osg\array>

namespace Infrastructure
{
	class XBOXController;
}	

class Player 
	: public Infrastructure::EventHandlerTracker
	, public Infrastructure::EventHandler<Infrastructure::XBOXControllerUpdateEvent>
{
private:
	float m_moveVelocity;
	float m_rotateVelocity;
	osg::Vec3 m_position;
	float m_viewAngleVertical;
	float m_viewAngleHorizontal;

public:
	Player();
	virtual ~Player();

	void Update();
	void Reset();

	const osg::Vec3& GetPosition() const;
	const float GetViewAngleVertical() const;
	const float GetViewAngleHorizontal() const;

	// Event Handlers	
	virtual void onEvent(Infrastructure::XBOXControllerUpdateEvent* e);

};

inline const osg::Vec3& Player::GetPosition() const
{
	return m_position;
}

inline const float Player::GetViewAngleVertical() const
{
	return m_viewAngleVertical;
}

inline const float Player::GetViewAngleHorizontal() const
{
	return m_viewAngleHorizontal;
}