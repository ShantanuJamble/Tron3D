#pragma once
// bullet
#include <btBulletDynamicsCommon.h>
//troen
#include "../forwarddeclarations.h"
#include "abstractcontroller.h"
#include "../player.h"

#include <osg/Vec3>

namespace troen
{
	class FenceController : public AbstractController
	{
	public:
		FenceController(Player * player, const btTransform initialTransform = btTransform::getIdentity());
		void update(btVector3 position, btQuaternion rotation);
		void attachWorld(std::shared_ptr<PhysicsWorld>& world);

		osg::ref_ptr<osg::Group> getViewNode() override;

		Player* player() { return m_player; };

		// fence manipulation
		void removeAllFences();
		void removeAllFencesFromModel();
		void setLimitFence(bool boolean);
		int getFenceLimit();

		// radar visibility
		void showFencesInRadarForPlayer(const int id);
		void hideFencesInRadarForPlayer(const int id);

		void setLastPosition(btQuaternion rotation, const btVector3 position);

		void updateFadeOutFactor(float fadeOutFactor);
		void setBendingActive(bool active);

	private:
		std::shared_ptr<FenceView> m_fenceView;
		std::shared_ptr<FenceModel> m_fenceModel;

		void adjustPositionUsingFenceOffset(const btQuaternion& rotation, btVector3& position);
		btVector3 m_lastPosition;
		bool m_fenceLimitActivated;

		Player * m_player;
		std::weak_ptr<PhysicsWorld> m_world;
	};
}