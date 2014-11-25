#pragma once


// Forward Declarations
namespace osgViewer
{
	class Viewer;
}

class World;

// Class Definition
class DemoRenderer
{
private:	
	World * m_pWorld;
	osgViewer::Viewer * m_pViewer;

public:
	DemoRenderer();
	~DemoRenderer();

	void Initialize();
	void Update();


};