#include "stdafx.h"
#include <math.h>
#include <Windows.h>
#include "DemoRenderer.hpp"
#include "../World/World.h"
#include "../UI/UserInterface.h"
#include <osgViewer/CompositeViewer>
#include <osgViewer/Viewer>

// HUD Camera: http://stackoverflow.com/questions/12643045/what-is-the-correct-view-matrix-for-the-hud-camera

DemoRenderer::DemoRenderer()
	: m_viewer(NULL)
	, m_pWorld(NULL)
	, m_pUserInterface(NULL)
	, m_worldView(NULL)
	, m_hudView(NULL)

{
}

DemoRenderer::~DemoRenderer()
{
	// Smart Pointers
	m_viewer = NULL;
	m_worldView = NULL;
	m_hudView = NULL;

	if( m_pUserInterface != NULL)
	{
		delete m_pUserInterface;
		m_pUserInterface = NULL;
	}

	if(m_pWorld != NULL)
	{
		delete m_pWorld;
		m_pWorld = NULL;
	}
}

void DemoRenderer::Initialize()
{
	// Create the Window
	m_viewer = CreateViewer();

	// Create World	
	m_pWorld = new World();
	m_worldView = CreateWorldView();
	m_viewer->addView(m_worldView);

	// Create UI	
	m_pUserInterface = new UserInterface();
	m_hudView = CreateHUDView();
	m_viewer->addView(m_hudView);

	// Initialize the Viewer for the data.	
    m_viewer->setReleaseContextAtEndOfFrameHint(false);
	m_viewer->realize();
}

void DemoRenderer::Update()
{	
	UpdateWorldCamera();
	m_viewer->frame();
}

void DemoRenderer::SetCameraPosition(const osg::Vec3d pos)
{
	m_CameraPos = pos;
}

void DemoRenderer::SetCameraPitch(const float pitch)
{
	m_CameraPitch = pitch;
}

void DemoRenderer::SetCameraYaw(const float yaw)
{
	m_CameraYaw = yaw;
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

osgViewer::View * DemoRenderer::CreateWorldView()
{
	osgViewer::View* view = new osgViewer::View;
	view->setName("World View");		
	view->setUpViewOnSingleScreen(0);
	view->setSceneData(m_pWorld->GetRoot());
	return view;
}

osgViewer::View * DemoRenderer::CreateHUDView()
{
	osgViewer::Viewer::Windows windows;
    m_viewer->getWindows(windows);

	//TODO: Get Screen resolution.
	osg::Camera * hudCamera = CreateHUDCamera(1920,1600);
	hudCamera->addChild(m_pUserInterface->GetRoot());

	hudCamera->setGraphicsContext(windows[0]);
    hudCamera->setViewport(0,0,windows[0]->getTraits()->width, windows[0]->getTraits()->height);

    osgViewer::View* view = new osgViewer::View;		
	view->setName("HUD View");		
	//view->setUpViewOnSingleScreen(0);
	view->setCamera(hudCamera);

	return view;
}

void DemoRenderer::UpdateWorldCamera()
{
	osg::Matrixd translation, rotation;
	translation.makeTranslate(m_CameraPos);
	rotation.makeRotate(
          0, osg::Vec3(0,1,0), // roll
          osg::DegreesToRadians(m_CameraPitch), osg::Vec3(1,0,0) , // pitch
          osg::DegreesToRadians(m_CameraYaw), osg::Vec3(0,0,1) ); // heading 

	osg::Matrixd cameraMatrix;
	cameraMatrix.invert( rotation * translation);
	m_worldView->getCamera()->setViewMatrix(cameraMatrix);
}

osg::Camera * DemoRenderer::CreateHUDCamera(int width, int height)
{
	// Source: http://trac.openscenegraph.org/projects/osg//browser/OpenSceneGraph/trunk/examples/osghud/osghud.cpp
	osg::Camera* camera = new osg::Camera;
	
	// set the projection matrix
	camera->setProjectionMatrix(osg::Matrix::ortho2D(0,width,0,height));

	// set the view matrix
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	camera->setViewMatrix(osg::Matrix::identity());
	
	// only clear the depth buffer
	camera->setClearMask(GL_DEPTH_BUFFER_BIT);
	
	// draw subgraph after main camera view.
	camera->setRenderOrder(osg::Camera::POST_RENDER);
	
	// we don't want the camera to grab event focus from the viewers main camera(s).
	camera->setAllowEventFocus(false);

	return camera;
}
