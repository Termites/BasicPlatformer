#include "LevelManager.hpp"
#include<SFML/Graphics.hpp>
#include<GL/GL.h>
#include<fstream>
#include<iostream>
#include "Resources/GamePath.hpp"
#include "Resources/ResourceManager.hpp"
#include "Debugger.hpp"

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

    if (TilesetTemplate)
	{
		for (int i=0;i<TilesetHeight;++i)
		{
			delete [] Tileset[i];
		}

		delete [] Tileset;
	}
}

const Tile& LevelManager::GetBlockAt(const vec2i& Location) const
{

	// Au cas où on cherche à accéder à un bloc inexistant :
	if (Location.x < 0 || Location.y <0 || Location.x>=Size.x || Location.y>=Size.y)
		return FallBack;

	return Tileset[Location.y][Location.x];
}

void LevelManager::SetBlockAt(const vec2i& Location, const Tile&T)
{
		// Au cas où on cherche à accéder à un bloc inexistant :
	if (Location.x < 0 || Location.y <0 || Location.x>=Size.x || Location.y>=Size.y)
		return;

	Tileset[Location.y][Location.x] = T;

	ObjectController.TileChanged(Location,T);
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
	TilesetTemplate = new bool[TilesetHeight*TilesetHeight];


    std::string mFile = GamePath::Tileset + File + ".info";
    std::ifstream Input(mFile);
    if (!Input.is_open())
    {

    }
    char Sep;
	for (int i=0;i<TilesetHeight*TilesetHeight;++i)
	{
            Input>>TilesetTemplate[i]>>Sep;
	}

    Input.close();
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
	SkyColor[0] = R/255.f;
	SkyColor[1] = G/255.f;
	SkyColor[2] = B/255.f;
	Input>>R>>Sep>>G>>Sep>>B;
	SkyColor[3] = R/255.f;
	SkyColor[4] = G/255.f;
	SkyColor[5] = B/255.f;

	Input>>Size.x>>Sep>>Size.y;

	Tileset = new Tile*[Size.y];
	for (int i=0;i<Size.y;++i)
	{
		Tileset[i] = new Tile[Size.x];
		for (int j=0;j<Size.x;++j)
		{
		    int id;
			Input>>id>>Sep;
			Tileset[i][j].BlockID = id;
			Tileset[i][j].bSolid = TilesetTemplate[id];
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
    if (CameraLocation.x <0 )
        CameraLocation.x = 0;

    if (CameraLocation.y <0 )
        CameraLocation.y = 0;

    if (CameraLocation.x+320 >= Size.x*16)
        CameraLocation.x = Size.x*16-320;

    if (CameraLocation.y+240 >= Size.y*16)
        CameraLocation.y = Size.y*16-240;
}

void LevelManager::Draw()
{

    glBegin(GL_QUADS);
        glColor3fv(SkyColor);
        glVertex3f(0,0,-99);
        glVertex3f(320,0,-99);
        glColor3fv(SkyColor+3);
        glVertex3f(320,240,-99);
        glVertex3f(0,240,-99);
    glEnd();

    glColor3f(1,1,1);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,TilesetTexture);

	for (int i=0;i<Size.y;++i)
	{
		for (int j=0;j<Size.x;++j)
		{
			if (Tileset[i][j].BlockID!=0)
			{

				vec2f Pos(j*16,i*16);
                Pos-=CameraLocation;
				vec2f TPos;
				// Recalcule les coordonnées dans le tileset :
				TPos.x = Tileset[i][j].BlockID%TilesetWidth;
				TPos.y = Tileset[i][j].BlockID/TilesetWidth;

				// Afin d'avoir x & y qui sont compris entre 0 et 1 :
				TPos.x /= float(TilesetWidth);
				TPos.y /= float(TilesetHeight);

				float w = 1.f/TilesetWidth;
				float h = 1.f/TilesetHeight;



				glBegin(GL_QUADS);
					glTexCoord2f(TPos.x,TPos.y);
					glVertex3f(Pos.x,Pos.y,-10);

					glTexCoord2f(TPos.x+w,TPos.y);
					glVertex3f(Pos.x+16,Pos.y,-10);

					glTexCoord2f(TPos.x+w,TPos.y+h);
					glVertex3f(Pos.x+16,Pos.y+16,-10);

					glTexCoord2f(TPos.x,TPos.y+h);
					glVertex3f(Pos.x,Pos.y+16,-10);
				glEnd();
			}
		}
	}
    glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D,0);
	glDisable(GL_TEXTURE_2D);

	ObjectController.Draw();
}
