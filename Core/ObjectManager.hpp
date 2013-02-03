#pragma once

#include "Object.hpp"
#include <list>

struct Tile;

// Pour �viter d'�crire � chaque fois std::list<Object*>
typedef std::list<Object*> ObjectList;

/*
	Class qui contr�le la liste d'objets pr�sent sur un
	niveau

*/
class ObjectManager
{
	private:

		// Liste d'objets pr�sent sur le niveau :
		ObjectList CurrentObjectList;
		// Liste d'objets � d�truire
		ObjectList ObjectsToDelete;

	public:
		ObjectManager();
		~ObjectManager();

		//@param NewObj : Objet � enregister
		void RegisterObject(Object* NewObj);

		//@param Obj : Objet � supprimer
		//void DeleteObject(Object* Obj);

		// Cr�er tous les objets
		void Create();

		// Met � jour tous les objets
		void Tick();

		// Dessine tous les objets
		void Draw();

		// Lorsqu'un tile a �t� chang� pendant le jeu, on le pr�cise :
		void TileChanged(const vec2i&Location,const Tile&NewTile);

};
