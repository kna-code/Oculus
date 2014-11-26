#pragma once

#include <osg\ref_ptr>
#include <osg\Array>

// Forward Declarations
namespace osg
{
	class Camera;
}
namespace osgViewer
{
	class CompositeViewer;
	class View;	
}

class World;
class UserInterface;

// Class Definition
class DemoRenderer
{
private:	
	UserInterface *m_pUserInterface;

	osg::ref_ptr<osgViewer::CompositeViewer> m_viewer;
	osg::ref_ptr<osgViewer::View> m_worldView;
	osg::ref_ptr<osgViewer::View> m_hudView;

	// Camera
	osg::Vec3d m_CameraPos;
	float m_CameraPitch;
	float m_CameraYaw;

public:
	DemoRenderer();
	~DemoRenderer();

	void Initialize();
	void Update();

	void SetCameraPosition(const osg::Vec3d pos);
	void SetCameraPitch(const float pitch);
	void SetCameraYaw(const float yaw);

	void GetCameraPosition(osg::Vec3d &pos);
	float GetCameraPitch();
	float GetCameraYaw();

private:
	osgViewer::CompositeViewer * CreateViewer(int width, int height);
	osgViewer::View * CreateWorldView();
	osgViewer::View * CreateHUDView(int width, int height);

	void UpdateWorldCamera();
	osg::Camera * CreateHUDCamera(int width, int height);
};