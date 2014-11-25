// VrViz.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"

#include "Tests/XBoxTest.h"
#include "Tests/OpenSceneGraphTest.h"
#include "Game/Demo.hpp"



int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		//OpenSceneGraphTest::RunWorldTest();
		//OpenSceneGraphTest::RunCompositeViewerTest();
		//XBoxTest::RunThumbStickTest();
		Demo demo;
		demo.Run();

		return 0;
	}
	catch (std::runtime_error & e)
	{
		printf("Runtime exception: %s\n", e.what());
	}
}




