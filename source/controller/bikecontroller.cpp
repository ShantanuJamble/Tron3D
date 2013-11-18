#include "bikecontroller.h"
// OSG
#include "osg/PositionAttitudeTransform"
//troen
#include "../input/bikeinputstate.h"
#include "../view/bikeview.h"
#include "../model/bikemodel.h"

using namespace troen;

BikeController::BikeController()
{
	// use static casts to convert from Abstract class type
	m_view = std::static_pointer_cast<BikeView>(std::make_shared<BikeView>());
	m_model = std::static_pointer_cast<BikeModel>(std::make_shared<BikeModel>(getViewNode()));
}

void BikeController::setInputState(osg::ref_ptr<input::BikeInputState> bikeInputState)
{
	std::static_pointer_cast<BikeModel>(m_model)->setInputState(bikeInputState);
}

void BikeController::attachTrackingCamera(osg::ref_ptr<osgGA::NodeTrackerManipulator> manipulator)
{
	osg::Matrixd cameraOffset;
	cameraOffset.makeTranslate(0, -100, -20);

	osg::PositionAttitudeTransform* pat = dynamic_cast<osg::PositionAttitudeTransform*> (getViewNode()->getChild(0));
	// set the actual node as the track node, not the pat
	manipulator->setTrackNode(pat->getChild(0));
	manipulator->setHomePosition(pat->getPosition(), pat->getPosition() * cameraOffset, osg::Vec3d(0, -1, 0));
}

void BikeController::updateModel()
{
	std::static_pointer_cast<BikeModel>(m_model)->updateState();
}