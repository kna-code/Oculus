#include "stdafx.h"
#include "UserInterface.h"

#include <stdio.h>

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

// Game
#include "..\World\World.h"
#include "..\World\Player.h"

UserInterface::UserInterface(const osg::Vec2 & screenSize)
	: m_screenSize(screenSize)
	, m_pPlayerLocText(NULL)
{	
	m_Root = new osg::Group();	
	m_Root->addChild(CreateDisplay());
}

UserInterface::~UserInterface()
{
	m_Root = NULL;
	m_pPlayerLocText = NULL;
}

osg::Node * UserInterface::GetRoot()
{
	return m_Root;
}

void UserInterface::Update()
{
	// Update Player Location
	{
		const Player *player = World::Instance()->GetPlayer();
		
		const osg::Vec3& pos = player->GetPosition();
		const float  vertAngle = player->GetViewAngleVertical();
		const float  horizAngle = player->GetViewAngleHorizontal();
		
		const int textLen = 256;
		char text[textLen];
		_snprintf(text, textLen, "X: %06.1f\nY: %06.1f\nZ: %06.1f\nVert:   %03.1f\nHoriz:  %03.1f\0",
				pos.x(), pos.y(), pos.z(), vertAngle, horizAngle);

		m_pPlayerLocText->setText(text);

	}
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

	// Player Loc Text
	{
		m_pPlayerLocText = new osgText::Text();
		m_pPlayerLocText->setFont(font);
		m_pPlayerLocText->setPosition(osg::Vec3(GetScreenWidth()-300, 200, 0.0f));
		m_pPlayerLocText->setText("[Player Location Goes Here");
		geode->addDrawable( m_pPlayerLocText );
	}

	// Controls Text
	{
		auto text = new osgText::Text();
		text->setFont(font);
		text->setPosition(osg::Vec3(GetScreenWidth()-300, GetScreenHeight()-50, 0.0f));
		text->setText("CONTROLS\nBack: Exit\nStart: Reset");
		geode->addDrawable( text );


	}
	
	// Draws a background box arround the text.
	/*
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
    }*/

	return geode;
}