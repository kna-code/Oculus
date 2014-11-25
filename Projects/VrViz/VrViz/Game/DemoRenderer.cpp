#include "stdafx.h"
#include "DemoRenderer.hpp"
#include "../World/World.h"

#include <osgViewer/Viewer>

DemoRenderer::DemoRenderer()
	: m_pViewer(NULL)
	, m_pWorld(NULL)
{
}

DemoRenderer::~DemoRenderer()
{
	// Smart Pointers
	m_pViewer = NULL;
	m_pWorld = NULL;
}

void DemoRenderer::Initialize()
{/*
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits; 
	traits->x = 0; // In screen space, so it's the top-left corner 
	traits->y = 0; 
	traits->width = 500; 
	traits->height = 500; 
	traits->windowName = "Demo";
	traits->supportsResize = true;
	traits->windowDecoration = true; // keep the window's border 
	osg::GraphicsContext::createGraphicsContext(traits); 

	auto windowInterface = osg::GraphicsContext::getWindowingSystemInterface(); 
	auto numScreens = windowInterface->getNumScreens();
	windowInterface->se
	// Create the world
	m_pWorld = new World();
	m_pViewer = new osgViewer::Viewer();
	m_pViewer->setSceneData(m_pWorld->GetRoot());
    //m_pViewer->setUpViewerAsEmbeddedInWindow(0, 0, 500, 500);
	m_pViewer->realize();
	m_pViewer->setReleaseContextAtEndOfFrameHint(false);
	*/
}

void DemoRenderer::Update()
{

}
