// VrViz.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "Input/XBOXController.h"



#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osg/CoordinateSystemNode>

#include <osg/Switch>
#include <osgText/Text>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>


int TestXBox()
{
	XBOXController * p1 = new XBOXController(1);

	while(1)
	{
		if(p1->IsConnected())
		{
			printf("Connected\n");
		}
		else
		{
			printf("Not Connected\n");
		}
		
		Sleep(100);
	}

	delete p1;

	return 0;
}


int TestScene()
{
	const std::string fileName = "C:\\Dev\\GitHub\\Oculus\\Lib\\OpenSceneGraph\\3.2.1\\data\\cow.osgt";

	osgViewer::Viewer viewer;
	osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile( fileName );
	if(!loadedModel)
	{
		printf("Failed to load: %s\n", fileName.c_str());
		return 1;
	}

	osgUtil::Optimizer optimizer;
    optimizer.optimize(loadedModel.get());
    viewer.setSceneData( loadedModel.get() );
    viewer.realize();

	return viewer.run();
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	TestScene();
	

	return 0;
}




