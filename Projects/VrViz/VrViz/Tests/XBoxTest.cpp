#include "stdafx.h"
#include "XBoxTest.h"
#include "windows.h"

// Infrastructure Libraries
#include "Input/XBOXController.h"

using namespace Infrastructure;

int XBoxTest::RunThumbStickTest()
{
	XBOXController * p1 = new XBOXController(1);

	while(1)
	{
		p1->Update();

		if(p1->IsConnected())
		{
			printf("Connected\n");
			
			Vec2 left, right;
			p1->GetLeftThumbStickPosition(left);
			p1->GetRightThumbStickPosition(right);
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
