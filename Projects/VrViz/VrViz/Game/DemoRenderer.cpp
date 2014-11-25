#include "stdafx.h"
#include <math.h>
#include <Windows.h>
#include "DemoRenderer.hpp"
#include "../World/World.h"
#include <osgViewer/CompositeViewer>

// HUD Camera: http://stackoverflow.com/questions/12643045/what-is-the-correct-view-matrix-for-the-hud-camera

DemoRenderer::DemoRenderer()
	: m_viewer(NULL)
	, m_pWorld(NULL)
{
}

DemoRenderer::~DemoRenderer()
{
	// Smart Pointers
	m_viewer = NULL;
	m_view = NULL;

	delete m_pWorld;
	m_pWorld = NULL;
}

void DemoRenderer::Initialize()
{
	// Create the Window
	m_pWorld = new World();
	m_viewer = CreateViewer();
	m_view = CreateView();

	
	// Initialize the Viewer for the data.
	m_viewer->addView(m_view);
    m_viewer->setReleaseContextAtEndOfFrameHint(false);
	m_viewer->realize();

}

void DemoRenderer::Update()
{
	m_viewer->frame();
}

void DemoRenderer::SetCameraPosition(const osg::Vec3d pos)
{
	m_CameraPos = pos;
	UpdateCamera();
}

void DemoRenderer::SetCameraPitch(const float pitch)
{
	m_CameraPitch = min(max(pitch, -90.0f), 90.0f);
	UpdateCamera();
}

void DemoRenderer::SetCameraYaw(const float yaw)
{
	m_CameraYaw = min(max(yaw,  -90.0f), 90.0f);
	UpdateCamera();
}

void DemoRenderer::GetCameraPosition(osg::Vec3d &pos)
{
	pos = m_CameraPos;
}

float DemoRenderer::GetCameraPitch()
{
	return m_CameraPitch;
}

float DemoRenderer::GetCameraYaw()
{
	return m_CameraYaw;
}

//------------------------------------------------------------------------------------
// Private Methods
//---------------------------------------------------------------------------

osgViewer::CompositeViewer * DemoRenderer::CreateViewer()
{
	// Setup the Screen Size
	osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
	if (!wsi)
	{
		osg::notify(osg::NOTICE)<<"Error, no WindowSystemInterface available, cannot create windows."<<std::endl;
		return NULL;
	}

	unsigned int width, height;
	wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(0), width, height);
	
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->x = 100;
	traits->y = 100;
	traits->width = 1000;
	traits->height = 800;
	traits->windowDecoration = true;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;
	
	osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
	if (gc.valid())
	{
		osg::notify(osg::INFO)<<"  GraphicsWindow has been created successfully."<<std::endl;
	
		// need to ensure that the window is cleared make sure that the complete window is set the correct colour
		// rather than just the parts of the window that are under the camera's viewports
		gc->setClearColor(osg::Vec4f(0.2f,0.2f,0.6f,1.0f));
		gc->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	else
	{
		osg::notify(osg::NOTICE)<<"  GraphicsWindow has not been created successfully."<<std::endl;
	}
		
	osgViewer::CompositeViewer * viewer = new osgViewer::CompositeViewer();	
	viewer->setThreadingModel(osgViewer::CompositeViewer::SingleThreaded);
	viewer->setThreadingModel(osgViewer::CompositeViewer::CullDrawThreadPerContext);
	viewer->setThreadingModel(osgViewer::CompositeViewer::CullThreadPerCameraDrawThreadPerContext);

	return viewer;
}

osgViewer::View * DemoRenderer::CreateView()
{
	osgViewer::View* view = new osgViewer::View;
	view->setName("View one");		
	view->setUpViewOnSingleScreen(0);
	view->setSceneData(m_pWorld->GetRoot());

	return view;
}



void DemoRenderer::UpdateCamera()
{
	osg::Matrixd translation, rotationX, rotationY;
	translation.makeTranslate(m_CameraPos);
	rotationX.makeRotate(m_CameraPitch, osg::Vec3(1.0, 0.0, 0.0));
	rotationY.makeRotate(m_CameraYaw, osg::Vec3(0.0, 1.0, 0.0));

	osg::Matrixd transform = translation * rotationX * rotationY;

	m_view->getCamera()->setViewMatrix(transform);
}
