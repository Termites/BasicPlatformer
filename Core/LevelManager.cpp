#include "LevelManager.hpp"
#include<SFML/Graphics.hpp>
#include<GL/GL.h>
#include<fstream>
#include<iostream>
#include "Resources/GamePath.hpp"

GLuint ConvertToGLTexture(const sf::Image & Image)
{
	GLuint TextureID;

	// glGenTextures(int nb textures, GLuint* Tableau)
	glGenTextures(1,&TextureID);
	glBindTexture(GL_TEXTURE_2D,TextureID);

	//http://www.opengl.org/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(GL_TEXTURE_2D,0,4,Image.GetWidth(),Image.GetHeight(),0,GL_RGBA,
	GL_UNSIGNED_BYTE,Image.GetPixelsPtr());

	// Mode d'interpolation des pixels (pour les zooms/dézooms)
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);


	glBindTexture(GL_TEXTURE_2D,0);

	return TextureID;

}

LevelManager::LevelManager()
{
	Tileset=NULL;
}

LevelManager::~LevelManager()
{
	if (Tileset)
	{
		for (int i=0;i<Size.y;++i)
		{
			delete [] Tileset[i];
		}

		delete [] Tileset;
	}
}

char LevelManager::GetBlockAt(const vec2i& Location)
{
    std::cout<<"l\n";
    std::cout<<Size.x<<','<<Size.y<<std::endl;
	// Au cas où on cherche à accéder à un bloc inexistant :
	if (Location.x < 0 || Location.y <0 || Location.x>=Size.x || Location.y>=Size.y)
		return -1;

	return Tileset[Location.y][Location.x];
}

void LevelManager::SetBlockAt(const vec2i& Location, char B)
{
		// Au cas où on cherche à accéder à un bloc inexistant :
	if (Location.x < 0 || Location.y <0 || Location.x>=Size.x || Location.y>=Size.y)
		return;

	Tileset[Location.y][Location.x] = B;
}

void LevelManager::LoadTileset(const std::string& File)
{
	sf::Image I;
	// bool sf::Image::LoadFromFile(const std::string&,char*Format=NULL)
	if (!I.LoadFromFile(GamePath::Tileset + File + ".png"))
	{
		// Fail
		return;
	}


	TilesetTexture = ConvertToGLTexture(I);
	TilesetWidth = I.GetWidth()/16;
	TilesetHeight = I.GetHeight()/16;

}

void LevelManager::LoadLevel(const std::string&File)
{
    std::string full = GamePath::Level + File + ".lev";
	std::ifstream Input(full.c_str());
	if (!Input.is_open())
	{
		// fail..
		return;
	}

	int R,G,B;
	char Sep;
	// R,G,B :

	Input>>R>>Sep>>G>>Sep>>B;
	Input>>Size.x>>Sep>>Size.y;

	Tileset = new char*[Size.y];
	for (int i=0;i<Size.y;++i)
	{
		Tileset[i] = new char[Size.x];
		for (int j=0;j<Size.x;++j)
		{
		    int id;
			Input>>id>>Sep;
			Tileset[i][j] = id;
		}
	}

	Input.close();
}

void LevelManager::Create()
{
    ObjectController.Create();
}

void LevelManager::Tick()
{
    ObjectController.Tick();
}

void LevelManager::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,TilesetTexture);

	for (int i=0;i<Size.y;++i)
	{
		for (int j=0;j<Size.x;++j)
		{
			if (Tileset[i][j]!=0)
			{
				vec2i Pos(j*16,i*16);

				vec2f TPos;
				// Recalcule les coordonnées dans le tileset :
				TPos.x = Tileset[i][j]%TilesetWidth;
				TPos.y = Tileset[i][j]/TilesetWidth;

				// Afin d'avoir x & y qui sont compris entre 0 et 1 :
				TPos.x /= float(TilesetWidth);
				TPos.y /= float(TilesetHeight);

				float w = 1.f/TilesetWidth;
				float h = 1.f/TilesetHeight;

				glBegin(GL_QUADS);
					glTexCoord2f(TPos.x,TPos.y);
					glVertex3f(Pos.x,Pos.y,0);

					glTexCoord2f(TPos.x+w,TPos.y);
					glVertex3f(Pos.x+16,Pos.y,0);

					glTexCoord2f(TPos.x+w,TPos.y+h);
					glVertex3f(Pos.x+16,Pos.y+16,0);

					glTexCoord2f(TPos.x,TPos.y+h);
					glVertex3f(Pos.x,Pos.y+16,0);
				glEnd();
			}
		}
	}

	glBindTexture(GL_TEXTURE_2D,0);
	glDisable(GL_TEXTURE_2D);

	ObjectController.Draw();
}
