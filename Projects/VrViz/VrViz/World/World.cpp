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
	verts->push_back( osg::Vec3( 0, 0, 0) ); // bottom front left
	verts->push_back( osg::Vec3(10, 0, 0) ); // bottom front right
	verts->push_back( osg::Vec3(10,10, 0) ); // bottom back right 
	verts->push_back( osg::Vec3( 0,10, 0) ); // bottom back left 
	verts->push_back( osg::Vec3( 0, 0, 10) ); // top front left
	verts->push_back( osg::Vec3(10, 0, 10) ); // top front right
	verts->push_back( osg::Vec3(10,10, 10) ); // top back right 
	verts->push_back( osg::Vec3( 0,10, 10) ); // top back left 

	// Add the verts to the geometry
	geometry->setVertexArray( verts ); 

	// Add the primitive sets
	geometry->addPrimitiveSet(CreateQuad(3, 2, 1, 0)); // Bottom
	geometry->addPrimitiveSet(CreateQuad(7, 6, 5, 4)); // Top
	geometry->addPrimitiveSet(CreateQuad(5, 4, 0, 1)); // Front
	geometry->addPrimitiveSet(CreateQuad(7, 6, 2, 3)); // Back
	geometry->addPrimitiveSet(CreateQuad(7, 4, 0, 3)); // Left
	geometry->addPrimitiveSet(CreateQuad(6, 5, 1, 2)); // Right
	// Declare and load an array of Vec4 elements to store colors.

	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) ); //index 0 red
	colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f) ); //index 1 green
	colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f) ); //index 2 blue
	colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f) ); //index 3 white 
	colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) ); //index 4 red
	colors->push_back(osg::Vec4(0.0f, 1.0f, 1.0f, 1.0f) ); //index 5 yellow
	colors->push_back(osg::Vec4(1.0f, 0.0f, 1.0f, 1.0f) ); //index 6 purple
	colors->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f) ); //index 7 black
  
   
	// Declare the variable that will match vertex array elements to color array elements. 
	geometry->setColorArray(colors);
	geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	return geometry;
}

osg::DrawElementsUInt* World::CreateQuad(int v0, int v1, int v2, int v3)
{
	osg::DrawElementsUInt* quad = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	quad->push_back(v0);
	quad->push_back(v1);
	quad->push_back(v2);
	quad->push_back(v3);

	return quad;
}