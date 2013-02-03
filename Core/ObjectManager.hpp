#pragma once

#include "Object.hpp"
#include <list>

struct Tile;

// Pour éviter d'écrire à chaque fois std::list<Object*>
typedef std::list<Object*> ObjectList;

/*
	Class qui contrôle la liste d'objets présent sur un
	niveau

*/
class ObjectManager
{
	private:

		// Liste d'objets présent sur le niveau :
		ObjectList CurrentObjectList;
		// Liste d'objets à détruire
		ObjectList ObjectsToDelete;

	public:
		ObjectManager();
		~ObjectManager();

		//@param NewObj : Objet à enregister
		void RegisterObject(Object* NewObj);

		//@param Obj : Objet à supprimer
		//void DeleteObject(Object* Obj);

		// Créer tous les objets
		void Create();

		// Met à jour tous les objets
		void Tick();

		// Dessine tous les objets
		void Draw();

		// Lorsqu'un tile a été changé pendant le jeu, on le précise :
		void TileChanged(const vec2i&Location,const Tile&NewTile);

};
