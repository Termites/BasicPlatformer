#include "ObjectManager.hpp"

ObjectManager::ObjectManager()
{}

ObjectManager::~ObjectManager()
{
	for (auto it = CurrentObjectList.begin();it!=CurrentObjectList.end();++it)
	{
		Object * O = *it;
		delete O;
	}
}

void ObjectManager::RegisterObject(Object* NewObj)
{
	CurrentObjectList.push_back(NewObj);
}

void ObjectManager::Create()
{
	for (auto it = CurrentObjectList.begin();it!=CurrentObjectList.end();++it)
	{
		Object * O = *it;
		O->Create();
	}
}

void ObjectManager::Tick()
{
	for (auto it = CurrentObjectList.begin();it!=CurrentObjectList.end();++it)
	{
		Object * O = *it;
		if (!O->bShouldBeDestroyed())
		O->Tick();
		if (O->bShouldBeDestroyed())
            ObjectsToDelete.push_back(O);
	}

    while (ObjectsToDelete.size()>0)
	{
		Object * O = ObjectsToDelete.front();
		CurrentObjectList.remove(O);
		ObjectsToDelete.pop_front();
		delete O;
	}
}

void ObjectManager::TileChanged(const vec2i&Location,const Tile&T)
{
  	for (auto it = CurrentObjectList.begin();it!=CurrentObjectList.end();++it)
	{
		Object * O = *it;
		if (!O->bShouldBeDestroyed())
		O->TileChanged(Location,T);
	}
}

void ObjectManager::Draw()
{
	for (auto it = CurrentObjectList.begin();it!=CurrentObjectList.end();++it)
	{
		Object * O = *it;
		if (!O->bShouldBeDestroyed())
		O->Draw();
	}
}
