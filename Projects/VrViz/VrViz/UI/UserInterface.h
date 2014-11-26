#pragma once

#include <osg/ref_ptr>

namespace osg
{
	class Geometry;
	class Group;	
	class Node;	
	class Geode;
}

static const char * FontFilePath = ".\\data\\fonts\\arial.ttf";

class UserInterface
{
private:
	osg::ref_ptr<osg::Group> m_Root;

public:
	UserInterface();
	~UserInterface();

	void Update();

	osg::Node * GetRoot();

private:
	osg::Geode * CreateDisplay();
};


