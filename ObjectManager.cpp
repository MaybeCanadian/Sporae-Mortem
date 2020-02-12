#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}


ObjectManager & ObjectManager::getInstance()
{
	static ObjectManager instance;
	return instance;
}

ObjectManager::~ObjectManager()
{
}
