#pragma once

#include <osg/ref_ptr>
#include <osg/Array>

// Forward Declarations
namespace osg
{
	class Geometry;
	class Group;	
	class Node;	
	class Geode;
}

namespace osgText
{
	class Text;
}

static const char * FontFilePath = ".\\data\\fonts\\arial.ttf";

class UserInterface
{
private:
	osg::ref_ptr<osg::Group> m_Root;
	osg::Vec2 m_screenSize;

	osg::ref_ptr<osgText::Text> m_pPlayerLocText;

public:
	UserInterface(const osg::Vec2 & screenSize);
	~UserInterface();

	void Update();

	osg::Node * GetRoot();

	const osg::Vec2 & GetScreenSize() const;
	const float GetScreenWidth() const;
	const float GetScreenHeight() const;

private:
	osg::Geode * CreateDisplay();
};

// Inline Methods

inline const osg::Vec2 & UserInterface::GetScreenSize() const
{
	return m_screenSize;
}

inline const float UserInterface::GetScreenWidth() const
{
	return m_screenSize.x();
}

inline const float UserInterface::GetScreenHeight() const
{
	return m_screenSize.y();
}

