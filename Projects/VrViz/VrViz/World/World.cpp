#include "stdafx.h"
#include "World.h"

#include <osg\Geometry>
#include <osg\Geode>
#include <osg\Node>
#include <osg\Array>
#include <osg\Transform>
#include <osg\PositionAttitudeTransform>


// ------------------------------------------------------------------------------------------------------------------------
// Constructor
// ------------------------------------------------------------------------------------------------------------------------

World::World()
{
	m_Root = new osg::Group();
	osg::Geode * geode = CreateCheckerBoard(10, 10);

	// Center the world at 0,0
	osg::BoundingBox bounds = geode->getBoundingBox();
	osg::PositionAttitudeTransform *centerNode = new osg::PositionAttitudeTransform();
	centerNode->setPosition(osg::Vec3(-bounds.center().x(), -bounds.center().y(), -bounds.center().z()));
	centerNode->addChild(geode);
    
	m_Root->addChild(centerNode);
}

// ------------------------------------------------------------------------------------------------------------------------
// Public Methods
// ------------------------------------------------------------------------------------------------------------------------

World::~World()
{
	m_Root = NULL;
}

osg::Node * World::GetRoot()
{
	return m_Root;
}

// ------------------------------------------------------------------------------------------------------------------------
// Private Methods
// ------------------------------------------------------------------------------------------------------------------------

osg::DrawElementsUInt* World::CreateQuad(int v0, int v1, int v2, int v3)
{
	osg::DrawElementsUInt* quad = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	quad->push_back(v0);
	quad->push_back(v1);
	quad->push_back(v2);
	quad->push_back(v3);

	return quad;
}

osg::Geode * World::CreateCheckerBoard(float checkSize, int numChecks)
{	
	osg::Geode* geode = new osg::Geode();
	
	osg::Vec4 color1(0.0, 0.0, 0.0, 1.0);
	osg::Vec4 color2(1.0, 1.0, 1.0, 1.0);

	// Create the Geometry for each square
	// TODO: This could probablly be done as one piece of geometry with all the vertices.
	for(int x = 0; x < numChecks; ++x)
	{
		bool useColor1 = x%2 == 0;

		for(int y = 0; y < numChecks; ++y)
		{
			float xPos = x*checkSize;
			float yPos = y*checkSize;
						
			osg::Geometry * geometry = new osg::Geometry();

			// Creat the vertices
			osg::Vec3Array* verts = new osg::Vec3Array();
			verts->push_back( osg::Vec3( xPos, yPos, 0) ); 
			verts->push_back( osg::Vec3( xPos, yPos + checkSize, 0) ); 
			verts->push_back( osg::Vec3( xPos + checkSize, yPos + checkSize, 0) ); 
			verts->push_back( osg::Vec3( xPos + checkSize, yPos, 0) ); 
			geometry->setVertexArray( verts ); 
			geometry->addPrimitiveSet(CreateQuad(0, 1, 2, 3)); 
			
			// Create the colors
			osg::Vec4Array* colors = new osg::Vec4Array();
			osg::Vec4 color = useColor1 ? color1 : color2;
			colors->push_back(color);
			colors->push_back(color);
			colors->push_back(color);
			colors->push_back(color);

			// Add to the geometry			
			geometry->setColorArray(colors);
			geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
			geode->addDrawable(geometry);	


			// Flip the color
			useColor1 = !useColor1;
		}
	}	

	return geode;
}