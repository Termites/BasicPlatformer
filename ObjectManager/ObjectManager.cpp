#include "ObjectManager.hpp"

ObjectManager::ObjectManager(){}

ObjectManager::~ObjectManager(){
	for (auto it(CurrentObjectList.begin()); it!=CurrentObjectList.end(); ++it){
		Object *O=*it;
		delete O;
	}
}

void ObjectManager::RegisterObject(Object *NewObj){
	CurrentObjectList.push_back(NewObj);
}

void ObjectManager::DeleteObject(Object *Obj){
	ObjectsToDelete.push_back(Obj);
}

void ObjectManager::Create(){
	for(auto it(CurrentObjectList.begin()); it!=CurrentObjectList.end(); ++it){
		Object *O=*it;
		O->Create();
	}
}

void ObjectManager::Tick(){
	while(ObjectsToDelete.size()>0){
		Object *O=ObjectsToDelete.front();
		CurrentObjectList.remove(O);
		delete O;
		ObjectsToDelete.pop_front();
	}
	for(auto it(CurrentObjectList.begin()); it!=CurrentObjectList.end(); ++it){
		Object *O=*it;
		O->Tick();
	}
}

void ObjectManager::TileChanged(const vec2i &Location, const Tile &T){
   for(auto it(CurrentObjectList.begin()); it!=CurrentObjectList.end(); ++it){
        Object *O=*it;
        O->TileChanged(Location,T);
    }
}

void ObjectManager::Draw(){
	for(auto it(CurrentObjectList.begin()); it!=CurrentObjectList.end(); ++it){
		Object *O=*it;
		O->Draw();
	}
}
