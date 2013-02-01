#pragma once
#include <GL/GL.h>
#include <string>
#include "../Math/Math.hpp"
#include "../ObjectManager/ObjectManager.hpp"

struct Tile{
    char BlockID;
    bool bSolid;
    Tile(char id=0,bool solid=false){
    	BlockID=id;
    	bSolid=solid;
    }
};

class LevelManager{
	private:
		Tile **Tileset;
		bool *TilesetTemplate;
		vec2i Size;
		vec2f CameraLocation;
		GLuint TilesetTexture;
		int TilesetWidth;
		int TilesetHeight;
		ObjectManager ObjectController;
		float R,G,B;
		Tile FallBack;

	public:
		LevelManager();
		~LevelManager();
		const Tile &GetBlockAt(const vec2i &Location);
		void SetBlockAt(const vec2i &Location, const Tile &T);
		void Create();
		void Tick();
		void Draw();
		void LoadTileset(const std::string &File);
		void LoadLevel(const std::string &File);
		void RegisterObject(Object *O);
		void DeleteObject(Object *O);
		int GetSizeX();
		vec2f &GetCameraLocation(){return CameraLocation;}

    protected:
};
