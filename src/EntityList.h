#pragma once

#include <iterator>
#include <list>
#include <vector>

class Entity;

class EntityList
{
public:
	EntityList();
	~EntityList();

	void AddEntity(Entity* entity);

	void AddToDeleteList(Entity* entity);
	void CleanUpDeleteList();

	//void FindEntity();
	// return iterator?

private:
	std::list<Entity*> m_entityList;

};

extern EntityList gEntityList;
