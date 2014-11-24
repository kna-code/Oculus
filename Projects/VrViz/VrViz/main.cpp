// VrViz.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"

// Infrastructure Libraries
#include "Input/XBOXController.h"

#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osg/CoordinateSystemNode>
#include <osg/Switch>
#include <osgText/Text>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/FirstPersonManipulator>

#include "World/World.h"
#include "Game/Demo.hpp"

using namespace Infrastructure;

int TestXBox()
{
	XBOXController * p1 = new XBOXController(1);

	while(1)
	{
		p1->Update();

		if(p1->IsConnected())
		{
			printf("Connected\n");
			
			const Vec2 left = p1->GetLeftThumbStickPosition();
			const Vec2 right = p1->GetRightThumbStickPosition();
			printf("Left Stick: [%f %f]\t\tRightStick: [%f %f]\n", left.x, left.y, right.x, right.y);
		}
		else
		{
			printf("Not Connected\n");
		}
		
		Sleep(500);
	}

	delete p1;

	return 0;
}


int TestScene()
{
	osgViewer::Viewer viewer;
	
    // set up the camera manipulators.
    {
        osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;
        keyswitchManipulator->addMatrixManipulator( '1', "FirstPerson", new osgGA::FirstPersonManipulator() );
        viewer.setCameraManipulator( keyswitchManipulator.get() );
    }

	/*	
	const std::string fileName = "C:\\Dev\\GitHub\\Oculus\\Lib\\OpenSceneGraph\\3.2.1\\data\\cow.osgt";
	osg::ref_ptr<osg::Node> scene = osgDB::readNodeFile( fileName );	
	if(!loadedModel)
	{
		printf("Failed to load: %s\n", fileName.c_str());
		return 1;
	}
	*/
	World world;
	osg::ref_ptr<osg::Node> scene = world.GetRoot();

	osgUtil::Optimizer optimizer;
    optimizer.optimize(scene.get());
    viewer.setSceneData( scene.get() );
    viewer.realize();

	return viewer.run();
}

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		//TestScene();
		//TestXBox();
		Demo demo;
		demo.Run();

		return 0;
	}
	catch (std::runtime_error & e)
	{
		printf("Runtime exception: %s\n", e.what());
	}
}




