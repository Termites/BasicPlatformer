#pragma once
#include <list>
#include "../Object/Object.hpp"

typedef std::list<Object*> ObjectList;
struct Tile;

class ObjectManager{
	private:
		ObjectList CurrentObjectList;
		ObjectList ObjectsToDelete;

	public:
		ObjectManager();
		~ObjectManager();
		void RegisterObject(Object *NewObj);
		void DeleteObject(Object *Obj);
		void Create();
		void Tick();
		void Draw();
		void TileChanged(const vec2i &Location, const Tile &NewTile);

    protected:
};
