#include "stdafx.h"
#include "OpenSceneGraphTest.h"
#include "windows.h"

#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osg/CoordinateSystemNode>
#include <osg/Switch>
#include <osgText/Text>
#include <osgViewer/Viewer>
#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/FirstPersonManipulator>

#include "../World/World.h"

int OpenSceneGraphTest::RunSceneTest()
{
	osgViewer::Viewer viewer;
		
	const std::string fileName = "C:\\Dev\\GitHub\\Oculus\\Lib\\OpenSceneGraph\\3.2.1\\data\\cow.osgt";
	osg::ref_ptr<osg::Node> scene = osgDB::readNodeFile( fileName );	
	if(!scene)
	{
		printf("Failed to load: %s\n", fileName.c_str());
		return 1;
	}

	osgUtil::Optimizer optimizer;
    optimizer.optimize(scene.get());
    viewer.setSceneData( scene.get() );
    viewer.realize();

	return viewer.run();
}

// RunCompositeViewerTest:
// Reference: http://trac.openscenegraph.org/projects/osg//browser/OpenSceneGraph/trunk/examples/osgcompositeviewer/osgcompositeviewer.cpp
int OpenSceneGraphTest::RunCompositeViewerTest()
{
	osgViewer::CompositeViewer viewer;

	const std::string fileName = "C:\\Dev\\GitHub\\Oculus\\Lib\\OpenSceneGraph\\3.2.1\\data\\cow.osgt";
	osg::ref_ptr<osg::Node> scene = osgDB::readNodeFile( fileName );	
	if(!scene)
	{
		printf("Failed to load: %s\n", fileName.c_str());
		return 1;
	}

	// Setup the Screen Size
	osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
	if (!wsi)
	{
		osg::notify(osg::NOTICE)<<"Error, no WindowSystemInterface available, cannot create windows."<<std::endl;
		return 1;
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

	
	// Create a View
	osgViewer::View* view = new osgViewer::View;
	view->setName("View one");		
	view->setUpViewOnSingleScreen(0);
	view->setSceneData(scene);
	//view->setCameraManipulator(new osgGA::TrackballManipulator);	
	viewer.addView(view);
	

	// Seetings 
	viewer.setThreadingModel(osgViewer::CompositeViewer::SingleThreaded);
	viewer.setThreadingModel(osgViewer::CompositeViewer::CullDrawThreadPerContext);
	viewer.setThreadingModel(osgViewer::CompositeViewer::CullThreadPerCameraDrawThreadPerContext);

	return viewer.run();
}