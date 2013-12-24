#include "sampleosgviewer.h"
#include <iostream>

using namespace troen;

SampleOSGViewer::SampleOSGViewer(osg::GraphicsContext* context /*= nullptr*/)
{
	setThreadingModel(osgViewer::ViewerBase::SingleThreaded);    
}

SampleOSGViewer::~SampleOSGViewer()
{
}
