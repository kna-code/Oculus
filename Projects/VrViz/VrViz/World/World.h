#pragma once

#include <osg/ref_ptr>

namespace osg
{
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
};