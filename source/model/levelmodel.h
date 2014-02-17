#pragma once
//troen
#include "../forwarddeclarations.h"
#include "abstractmodel.h"
#include <btBulletDynamicsCommon.h>

namespace troen
{
	// helper class to abstract boxes from bullet and osg

	class BoxModel {
	public:
		BoxModel(btVector3 centerVec, btVector3 dimensionsVec) {
			center = centerVec;
			dimensions = dimensionsVec;
			rotation = btQuaternion(0, 0, 0, 1);
			name = "default";
			collisionType = LEVELOBSTACLETYPE;

		};

		BoxModel(btVector3 centerVec, btVector3 dimensionsVec, btQuaternion rotationQuat) {
			center = centerVec;
			dimensions = dimensionsVec;
			rotation = rotationQuat;
			name = "default";
			collisionType = LEVELOBSTACLETYPE;
		}

		BoxModel(btVector3 centerVec, btVector3 dimensionsVec, btQuaternion rotationQuat, std::string modelName, troen::COLLISIONTYPE collision_type) {
			center = centerVec;
			dimensions = dimensionsVec;
			rotation = rotationQuat;
			name = modelName;
			collisionType = collision_type;
		}

		btVector3 center;
		btVector3 dimensions;
		btQuaternion rotation;
		std::string name;
		troen::COLLISIONTYPE collisionType;
	};

	
	class LevelModel : public AbstractModel
	{
	public:
		LevelModel(const LevelController* levelController);
		int getLevelSize();

		std::vector<BoxModel>& getWalls() { return m_walls; };
		std::vector<BoxModel>& getFloors() { return m_floors; };
		std::vector<BoxModel>& getObstacles() { return m_obstacles; };

	private:
		void addBoxes(std::vector<BoxModel> &boxes,const COLLISIONTYPE type = ABSTRACTTYPE);
		void addWalls(const float levelSize, const float yPosition);
		void addFloor(const float size, const float yPosition);


		void auto_addObstacles();

		const LevelController* m_levelController;

		std::vector<BoxModel> m_walls;
		std::vector<BoxModel> m_floors;
		std::vector<BoxModel> m_obstacles;
	};

}