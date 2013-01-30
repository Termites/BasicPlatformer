#pragma once
#include "Math.hpp"
#include <GL/GL.h>
#include <string>

#include "ObjectManager.hpp"

class LevelManager
{
	private:
		char ** Tileset;
		// Dimension de la carte :
		// Size.x = largeur
		// Size.y = hauteur
		vec2i Size;

		// Position de la caméra
		vec2f CameraLocation;

		// Tileset :
		GLuint TilesetTexture; // ID Texture OpenGL
		int TilesetWidth; // Largeur du tileset (en nombre de blocs)
		int TilesetHeight; // Hauteur du tileset (en nombre de blocs)

		ObjectManager ObjectController; // Contrôleur d'objets

	public:
		LevelManager();
		~LevelManager();

		// Renvoit le block à la case 'Location' :
		char GetBlockAt(const vec2i&Location);

		// Pour changer un bloc à une certaine case :
		void SetBlockAt(const vec2i&Location, char B);

		void Create(); // Lors de la création
		void Tick(); // Mise à jour du niveau
		void Draw(); // Dessiner le niveau

		// Charge un tileset
		void LoadTileset(const std::string&File);

		// Charge un niveau
		void LoadLevel(const std::string&File);

		// Ajouter un object sur la carte :
		void RegisterObject(Object*O)
		{
		    O->SetLevel(this);
		    ObjectController.RegisterObject(O);
		}

		// Supprimer un object de la carte :
		void DeleteObject(Object*O)
		{
		    ObjectController.DeleteObject(O);
		}
};
