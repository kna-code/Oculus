#pragma once

#include "General\EventHandler.hpp"
#include "Input\XBOXControllerUpdateEvent.h"
#include <osg\array>

namespace Infrastructure
{
	class XBOXController;
}	

class Player : public Infrastructure::EventHandler<Infrastructure::XBOXControllerUpdateEvent>
{
private:
	float m_velocity;
	osg::Vec3 m_position;
	osg::Vec3 m_rotation;

public:
	Player();

	void Update();

	const osg::Vec3& GetPosition() const;
	const osg::Vec3& GetRotation() const;

	// Event Handlers	
	virtual void onEvent(Infrastructure::XBOXControllerUpdateEvent* e);

};

inline const osg::Vec3& Player::GetPosition() const
{
	return m_position;
}

inline const osg::Vec3& Player::GetRotation() const
{
	return m_rotation;
}