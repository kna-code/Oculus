#include "stdafx.h"
#include "UserInterface.h"

// OSG
#include <osgUtil/Optimizer>
#include <osg/Material>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/BlendFunc>
#include <osg/Depth>
#include <osg/PolygonOffset>
#include <osg/MatrixTransform>
#include <osg/Camera>
#include <osg/RenderInfo>
#include <osg/Node>
#include <osgText/Text>

UserInterface::UserInterface()
{	
	m_Root = new osg::Group();	
	m_Root->addChild(CreateDisplay());
}

UserInterface::~UserInterface()
{
	m_Root = NULL;
}

osg::Node * UserInterface::GetRoot()
{
	return m_Root;
}

void UserInterface::Update()
{
	// TODO: This should update the display scene with the latest values.
}

osg::Geode * UserInterface::CreateDisplay()
{

    osg::Geode* geode = new osg::Geode();

    //std::string font(FontFilePath);
	std::string font(""); // Default Font

    // turn lighting off for the text and disable depth test to ensure it's always ontop.
    osg::StateSet* stateset = geode->getOrCreateStateSet();
    stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);

    osg::Vec3 position(150.0f,800.0f,0.0f);
    osg::Vec3 delta(0.0f,-120.0f,0.0f);

    {
        osgText::Text* text = new  osgText::Text;
        geode->addDrawable( text );

        //text->setFont(font);
        text->setPosition(position);
        text->setText("Head Up Displays are simple :-)");

		auto f = text->getFont();

        position += delta;
    }
	
	{
        osgText::Text* text = new  osgText::Text;
        geode->addDrawable( text );

        //text->setFont(font);
        text->setPosition(position);
        text->setText("Head Up Displays are simple :-)");

		auto f = text->getFont();

        position += delta;
    }

    {
        osgText::Text* text = new  osgText::Text;
        geode->addDrawable( text );

        text->setFont(font);
        text->setPosition(position);
        text->setText("All you need to do is create your text in a subgraph.");

        position += delta;
    }


    {
        osgText::Text* text = new  osgText::Text;
        geode->addDrawable( text );

        text->setFont(font);
        text->setPosition(position);
        text->setText("Then place an osg::Camera above the subgraph\n"
                        "to create an orthographic projection.\n");

        position += delta;
    }

    {
        osgText::Text* text = new  osgText::Text;
        geode->addDrawable( text );

        text->setFont(font);
        text->setPosition(position);
        text->setText("Set the Camera's ReferenceFrame to ABSOLUTE_RF to ensure\n"
                        "it remains independent from any external model view matrices.");

        position += delta;
    }

    {
        osgText::Text* text = new  osgText::Text;
        geode->addDrawable( text );

        text->setFont(font);
        text->setPosition(position);
        text->setText("And set the Camera's clear mask to just clear the depth buffer.");

        position += delta;
    }

    {
        osgText::Text* text = new  osgText::Text;
        geode->addDrawable( text );

        text->setFont(font);
        text->setPosition(position);
        text->setText("And finally set the Camera's RenderOrder to POST_RENDER\n"
                        "to make sure it's drawn last.");

        position += delta;
    }


    {
        osg::BoundingBox bb;
        for(unsigned int i=0;i<geode->getNumDrawables();++i)
        {
			auto b = geode->getDrawable(i)->getBound();
            bb.expandBy(b);
        }

        osg::Geometry* geom = new osg::Geometry;

        osg::Vec3Array* vertices = new osg::Vec3Array;
        float depth = bb.zMin()-0.1;
        vertices->push_back(osg::Vec3(bb.xMin(),bb.yMax(),depth));
        vertices->push_back(osg::Vec3(bb.xMin(),bb.yMin(),depth));
        vertices->push_back(osg::Vec3(bb.xMax(),bb.yMin(),depth));
        vertices->push_back(osg::Vec3(bb.xMax(),bb.yMax(),depth));
        geom->setVertexArray(vertices);

        osg::Vec3Array* normals = new osg::Vec3Array;
        normals->push_back(osg::Vec3(0.0f,0.0f,1.0f));
        geom->setNormalArray(normals, osg::Array::BIND_OVERALL);

        osg::Vec4Array* colors = new osg::Vec4Array;
        colors->push_back(osg::Vec4(1.0f,1.0,0.8f,0.2f));
        geom->setColorArray(colors, osg::Array::BIND_OVERALL);

        geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS,0,4));

        osg::StateSet* stateset = geom->getOrCreateStateSet();
        stateset->setMode(GL_BLEND,osg::StateAttribute::ON);
        //stateset->setAttribute(new osg::PolygonOffset(1.0f,1.0f),osg::StateAttribute::ON);
        stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

        geode->addDrawable(geom);
    }

	return geode;
}