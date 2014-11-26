#pragma once

#include <osg/ref_ptr>
#include <General/Singleton.h>

namespace osg
{
	class DrawElementsUInt;
	class Geometry;
	class Group;	
	class Node;	
	class Geode;
}

class Player;

class World : public Infrastructure::Singleton<World>
{
	// TODO: Is this the correct way to protect the World constructor?
	friend class Infrastructure::Singleton<World>;

private:

	osg::ref_ptr<osg::Group> m_root;
    Player * m_player;

	World();

public:
	~World();

	osg::Node * GetRoot() const;
	Player * GetPlayer() const;

private:

	osg::DrawElementsUInt* World::CreateQuad(int v0, int v1, int v2, int v3);
	osg::Geode * CreateCheckerBoard(float checkSize, int numChecks);
};

// Inline Methods
inline osg::Node * World::GetRoot() const
{
	return (osg::Node*)m_root.get();
}

inline Player * World::GetPlayer() const
{
	return m_player;
}