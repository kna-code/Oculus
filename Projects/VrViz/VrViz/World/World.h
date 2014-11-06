#pragma once

#include <osg/ref_ptr>

namespace osg
{
	class DrawElementsUInt;
	class Geometry;
	class Group;	
	class Node;	
}

class World
{
private:

	osg::ref_ptr<osg::Group> m_Root;

public:
	World();
	~World();

	osg::Node * GetRoot();

private:

	osg::Geometry * CreateGeometry();
	osg::DrawElementsUInt* World::CreateQuad(int v0, int v1, int v2, int v3);
};