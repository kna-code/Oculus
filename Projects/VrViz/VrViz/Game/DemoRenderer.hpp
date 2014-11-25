#pragma once

#include <osg\ref_ptr>
#include <osg\Array>

// Forward Declarations
namespace osgViewer
{
	class CompositeViewer;
	class View;
}

class World;

// Class Definition
class DemoRenderer
{
private:	
	World * m_pWorld;	
	osg::ref_ptr<osgViewer::CompositeViewer> m_viewer;
	osg::ref_ptr<osgViewer::View> m_view;

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
	osgViewer::CompositeViewer * CreateViewer();
	osgViewer::View * CreateView();

	void UpdateCamera();
};