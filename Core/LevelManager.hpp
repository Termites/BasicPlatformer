#pragma once
#include "Math.hpp"
#include <GL/GL.h>
#include <string>

#include "ObjectManager.hpp"

struct Tile
{
    char BlockID;
    bool bSolid;
    Tile(char id=0,bool solid=false)
    {
    	BlockID=id;
    	bSolid=solid;
    }
};

class LevelManager
{
	private:
		Tile ** Tileset;
		bool * TilesetTemplate;
		// Dimension de la carte :
		// Size.x = largeur
		// Size.y = hauteur
		vec2i Size;

		// Position de la cam�ra
		vec2f CameraLocation;

		// Tileset :
		GLuint TilesetTexture; // ID Texture OpenGL
		int TilesetWidth; // Largeur du tileset (en nombre de blocs)
		int TilesetHeight; // Hauteur du tileset (en nombre de blocs)

		ObjectManager ObjectController; // Contr�leur d'objets

		float SkyColor[6];

		Tile FallBack;

	public:
		LevelManager();
		~LevelManager();

		// Renvoit le block � la case 'Location' :
		const Tile& GetBlockAt (const vec2i&Location) const;

		// Pour changer un bloc � une certaine case :
		void SetBlockAt(const vec2i&Location,const Tile&T);

		void Create(); // Lors de la cr�ation
		void Tick(); // Mise � jour du niveau
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

		vec2f& GetCameraLocation()  {return CameraLocation;}
};
