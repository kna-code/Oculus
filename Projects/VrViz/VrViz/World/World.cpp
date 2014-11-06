#include "stdafx.h"
#include "World.h"

#include <osg\Geometry>
#include <osg\Geode>
#include <osg\Node>
#include <osg\Array>


// ------------------------------------------------------------------------------------------------------------------------
// Constructor
// ------------------------------------------------------------------------------------------------------------------------

World::World()
{
	m_Root = new osg::Group();
	osg::Geode* geode = new osg::Geode();
	osg::Geometry * geometry = CreateGeometry();

	geode->addDrawable(geometry); 
    m_Root->addChild(geode);
}

// ------------------------------------------------------------------------------------------------------------------------
// Public Methods
// ------------------------------------------------------------------------------------------------------------------------

World::~World()
{
	if(m_Root != NULL)
	{		
		m_Root = NULL;
	}
}

osg::Node * World::GetRoot()
{
	return m_Root;
}

// ------------------------------------------------------------------------------------------------------------------------
// Private Methods
// ------------------------------------------------------------------------------------------------------------------------

osg::Geometry * World::CreateGeometry()
{
	osg::Geometry * geometry = new osg::Geometry();

	// Create the vertices
	osg::Vec3Array* verts = new osg::Vec3Array;
	verts->push_back( osg::Vec3( 0, 0, 0) ); // front left
	verts->push_back( osg::Vec3(10, 0, 0) ); // front right
	verts->push_back( osg::Vec3(10,10, 0) ); // back right 
	verts->push_back( osg::Vec3( 0,10, 0) ); // back left 
	verts->push_back( osg::Vec3( 5, 5,10) ); // peak

	// Add the verts to the geometry
	geometry->setVertexArray( verts ); 

	// Create a primitive set and add it to the pyramid geometry. 

	osg::DrawElementsUInt* pyramidBase = 
		new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	pyramidBase->push_back(3);
	pyramidBase->push_back(2);
	pyramidBase->push_back(1);
	pyramidBase->push_back(0);
	geometry->addPrimitiveSet(pyramidBase); 

	osg::DrawElementsUInt* faceOne = 
		new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	faceOne->push_back(0);
	faceOne->push_back(1);
	faceOne->push_back(4);
	geometry->addPrimitiveSet(faceOne);

	osg::DrawElementsUInt* faceTwo = 
		new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	faceTwo->push_back(1);
	faceTwo->push_back(2);
	faceTwo->push_back(4);
	geometry->addPrimitiveSet(faceTwo);

	osg::DrawElementsUInt* faceThree = 
		new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	faceThree->push_back(2);
	faceThree->push_back(3);
	faceThree->push_back(4);
	geometry->addPrimitiveSet(faceThree);

	osg::DrawElementsUInt* faceFour = 
		new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	faceFour->push_back(3);
	faceFour->push_back(0);
	faceFour->push_back(4);
	geometry->addPrimitiveSet(faceFour);

	// Declare and load an array of Vec4 elements to store colors.

	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) ); //index 0 red
	colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f) ); //index 1 green
	colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f) ); //index 2 blue
	colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f) ); //index 3 white 
	colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) ); //index 4 red
  
   
	// Declare the variable that will match vertex array elements to color array elements. 
	geometry->setColorArray(colors);
	geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	return geometry;
}