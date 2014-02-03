#pragma once
// OSG
#include <osgViewer/View>
#include <osgText/Text>
// troen
#include "../forwarddeclarations.h"
#include "abstractview.h"

namespace troen
{

	class HUDView : public AbstractView
	{
	public:
		HUDView(const osg::Vec4 playerColor);

		// initialization
		void attachSceneToRadarCamera(osg::Group* scene);
		void setTrackNode(osg::Node* trackNode);
		
		// updating
		void updateRadarCamera();
		void resize(const int width, const int height);

		// text setter
		void setSpeedText(const float speed);
		void setHealthText(const float health);
		void setPointsText(const float points);
		void setCountdownText(const int countdown);
		void setCountdownText(const std::string text);
		void setTimeText(const double gameTime, const int timeLimit);
		void setDeathCountText(const int deathCount);

	private:
		osg::Camera* createHUD();
		osg::Camera* createRadar();

		void resizeHudComponents(const int width, const int height);

		osg::ref_ptr<osg::Camera> m_camera;
		osg::ref_ptr<osg::Camera> m_radarCamera;
		osg::ref_ptr<osgGA::NodeTrackerManipulator> m_radarManipulator;
		osg::Geode* m_savedGeode;
		osg::Node* m_trackNode;

		osg::ref_ptr<osgText::Text> m_healthText;
		osg::ref_ptr<osgText::Text> m_speedText;
		osg::ref_ptr<osgText::Text> m_pointsText;
		osg::ref_ptr<osgText::Text> m_countdownText;
		osg::ref_ptr<osgText::Text> m_timeText;
		osg::ref_ptr<osgText::Text> m_deathCountText;

		osg::Vec4 m_playerColor;
	};
}