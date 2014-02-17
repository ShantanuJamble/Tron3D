#include "levelmodel.h"
//bullet
#include <btBulletDynamicsCommon.h>
#include "LinearMath/btHashMap.h"

#include "../controller/itemcontroller.h"
#include "objectinfo.h"
#include "../constants.h"

using namespace troen;

LevelModel::LevelModel(const LevelController* levelController)
{
	AbstractModel();
	m_levelController = levelController;
	m_rigidBodies = std::vector<std::shared_ptr<btRigidBody>>();

	btScalar levelSize = btScalar(getLevelSize());

	addWalls(levelSize, -10);

	addFloor(levelSize, -10);

	auto_addObstacles();
}

void LevelModel::addFloor(float size, float yPosition)
{
	m_floors.push_back({
		btVector3(0, 0, yPosition),
		btVector3(size, size, 20)
	});

	addBoxes(m_floors, LEVELGROUNDTYPE);
}

void LevelModel::addWalls(float levelSize, float yPosition)
{

	btScalar wallHeight = 40;

	std::vector<BoxModel> newWalls = {
		{
			btVector3(levelSize / 2, 1, yPosition + wallHeight/2),
			btVector3(2, levelSize, wallHeight)
		},
		{
			btVector3(-levelSize / 2, 0, yPosition + wallHeight / 2),
			btVector3(2, levelSize, wallHeight)
		},
		{
			btVector3(0, levelSize / 2, yPosition + wallHeight / 2),
			btVector3(levelSize, 2, wallHeight)
		},
		{
			btVector3(0, -levelSize / 2, yPosition + wallHeight / 2),
			btVector3(levelSize, 2, wallHeight)
		}
	};

	m_walls.insert(m_walls.end(), newWalls.begin(), newWalls.end());

	addBoxes(m_walls, LEVELWALLTYPE);
}

void LevelModel::addBoxes(std::vector<BoxModel> &boxes, COLLISIONTYPE type)
{
	for (int i = 0; i < boxes.size(); ++i)
	{
		std::shared_ptr<btBoxShape> wallShape = std::make_shared<btBoxShape>(boxes[i].dimensions / 2);
		std::shared_ptr<btDefaultMotionState> wallMotionState
			= std::make_shared<btDefaultMotionState>(btTransform(boxes[i].rotation, boxes[i].center));

		btRigidBody::btRigidBodyConstructionInfo
			wallRigidBodyCI(btScalar(0), wallMotionState.get(), wallShape.get(), btVector3(0, 0, 0));

		std::shared_ptr<btRigidBody> wallRigidBody = std::make_shared<btRigidBody>(wallRigidBodyCI);

		ObjectInfo* info;
		if (type == ABSTRACTTYPE)
			info = new ObjectInfo((void *)m_levelController, boxes[i].collisionType);
		else
			info = new ObjectInfo((void *) m_levelController, type);
		
		wallRigidBody->setUserPointer(info);

		m_collisionShapes.push_back(wallShape);
		m_motionStates.push_back(wallMotionState);
		m_rigidBodies.push_back(wallRigidBody);
	}
}



int LevelModel::getLevelSize() {
	return LEVEL_SIZE;
}

