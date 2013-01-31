#pragma once
#include <GL/GL.h>
#include <string>
#include "../Math/Math.hpp"
#include "../ObjectManager/ObjectManager.hpp"

class LevelManager{
	private:
		char** Tileset;
		vec2i Size;
		vec2f CameraLocation;
		GLuint TilesetTexture;
		int TilesetWidth;
		int TilesetHeight;
		ObjectManager ObjectController;
		float R,G,B;

	public:
		LevelManager();
		~LevelManager();
		char GetBlockAt(const vec2i &Location);
		void SetBlockAt(const vec2i &Location, char B);
		void Create();
		void Tick();
		void Draw();
		void LoadTileset(const std::string &File);
		void LoadLevel(const std::string &File);
		void RegisterObject(Object *O);
		void DeleteObject(Object *O);

    protected:
};
