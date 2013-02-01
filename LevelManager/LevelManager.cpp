#include <iostream>
#define debug(a) std::cout << a << std::endl
#include<SFML/Graphics.hpp>
#include<GL/GL.h>
#include<fstream>
#include "LevelManager.hpp"
#include "../ResourceManager/GamePath.hpp"
#include "../ResourceManager/ResourceManager.hpp"

LevelManager::LevelManager(){
	Tileset=NULL;
}

LevelManager::~LevelManager(){
	if(Tileset){
		for(int i=0;i<Size.y;++i){
			delete []Tileset[i];
		}
		delete []Tileset;
	}
}

const Tile &LevelManager::GetBlockAt(const vec2i&Location){
	if(Location.x<0 || Location.y<0 || Location.x>=Size.x || Location.y>=Size.y) return FallBack;
	return Tileset[Location.y][Location.x];
}

void LevelManager::SetBlockAt(const vec2i &Location, const Tile &T){
	if(Location.x<0 || Location.y<0 || Location.x>=Size.x || Location.y>=Size.y) return;
	Tileset[Location.y][Location.x]=T;
	ObjectController.TileChanged(Location,T);
}

void LevelManager::LoadTileset(const std::string &File){
	sf::Image I;
	if(!I.LoadFromFile(GamePath::Tileset+File+".png")) return;
	TilesetTexture=ConvertToGLTexture(I);
	TilesetWidth=I.GetWidth()/16;
	TilesetHeight=I.GetHeight()/16;
	TilesetTemplate = new bool[TilesetHeight*TilesetHeight];
    std::string mFile=GamePath::Tileset+File+".info";
    std::ifstream Input(mFile);
    char Sep;
	for(int i(0); i<TilesetHeight*TilesetHeight; ++i){
        Input >> TilesetTemplate[i] >> Sep;
	}
    Input.close();
}

void LevelManager::LoadLevel(const std::string &File){
	std::ifstream Input(GamePath::Level+File.c_str()+".lev");
	if(!Input.is_open()) return;
	char Sep;
	Input >> R >> Sep >> G >> Sep >> B;
	Input >> Size.x >> Sep >> Size.y;
	Tileset=new Tile*[Size.y];
	for(int i=0; i<Size.y; ++i){
		Tileset[i]=new Tile[Size.x];
		for(int j=0; j<Size.x; ++j){
		    int id;
			Input >> id >> Sep;
			Tileset[i][j].BlockID=id;
            Tileset[i][j].bSolid=TilesetTemplate[id];
		}
	}
	Input.close();
}

void LevelManager::Create(){
    ObjectController.Create();
}

void LevelManager::Tick(){
    ObjectController.Tick();
    if(CameraLocation.x<0) CameraLocation.x=0;
    if(CameraLocation.y<0) CameraLocation.y=0;
    if(CameraLocation.x+320>=Size.x*16) CameraLocation.x=Size.x*16-320;
    if(CameraLocation.y+240>=Size.y*16) CameraLocation.y=Size.y*16-240;
}

void LevelManager::Draw(){
	glBegin(GL_QUADS);
        glColor3f(R+0.5f,G+0.5f,B+0.5f);
        glVertex3f(0,0,-99);
        glColor3f(R+0.5f,G+0.5f,B+0.5f);
        glVertex3f(320,0,-99);
        glColor3f(R,G,B);
        glVertex3f(320,240,-99);
        glColor3f(R,G,B);
        glVertex3f(0,240,-99);
    glEnd();
    glColor3f(1.f,1.f,1.f);
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,TilesetTexture);
	for(int i=0; i<Size.y; ++i){
		for(int j=0; j<Size.x; ++j){
			if(Tileset[i][j].BlockID!=0){
				vec2f Pos(j*16,i*16);
				Pos-=CameraLocation;
				vec2f TPos;
				TPos.x=Tileset[i][j].BlockID%TilesetWidth;
				TPos.y=Tileset[i][j].BlockID/TilesetWidth;
				TPos.x/=float(TilesetWidth);
				TPos.y/=float(TilesetHeight);
				float w=1.f/TilesetWidth;
				float h=1.f/TilesetHeight;
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

void LevelManager::RegisterObject(Object *O){
    O->SetLevel(this);
    ObjectController.RegisterObject(O);
}
void LevelManager::DeleteObject(Object *O){
    O->SetLevel(this);
    ObjectController.DeleteObject(O);
}

int LevelManager::GetSizeX(){
    return Size.x;
}
