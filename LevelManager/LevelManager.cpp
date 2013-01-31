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
		for (int i=0;i<Size.y;++i){
			delete []Tileset[i];
		}
		delete []Tileset;
	}
}

char LevelManager::GetBlockAt(const vec2i &Location){
	if(Location.x<0 || Location.y<0 || Location.x>=Size.x || Location.y>=Size.y) return -1;
	return Tileset[Location.y][Location.x];
}

void LevelManager::SetBlockAt(const vec2i &Location, char B){
	if(Location.x<0 || Location.y<0 || Location.x>=Size.x || Location.y>=Size.y) return;
	Tileset[Location.y][Location.x]=B;
}

void LevelManager::LoadTileset(const std::string &File){
	sf::Image I;
	if(!I.LoadFromFile(GamePath::Tileset+"Tileset"+File+".png")) return;
	TilesetTexture=ConvertToGLTexture(I);
	TilesetWidth=I.GetWidth()/16;
	TilesetHeight=I.GetHeight()/16;
}

void LevelManager::LoadLevel(const std::string &File){
	std::ifstream Input(GamePath::Level+File.c_str()+".lev");
	if(!Input.is_open()) return;
	char Sep;
	Input >> R >> Sep >> G >> Sep >> B;
	Input >> Size.x >> Sep >> Size.y;
	Tileset=new char*[Size.y];
	for(int i=0; i<Size.y; ++i){
		Tileset[i]=new char[Size.x];
		for(int j=0; j<Size.x; ++j){
		    int id;
			Input >> id >> Sep;
			Tileset[i][j]=id;
		}
	}
	Input.close();
}

void LevelManager::Create(){
    ObjectController.Create();
}

void LevelManager::Tick(){
    ObjectController.Tick();
}

void LevelManager::Draw(){
    glClearColor(R,G,B,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,TilesetTexture);
	for(int i=0; i<Size.y; ++i){
		for(int j=0; j<Size.x; ++j){
			if(Tileset[i][j]!=0){
				vec2i Pos(j*16,i*16);
				vec2f TPos;
				TPos.x=Tileset[i][j]%TilesetWidth;
				TPos.y=Tileset[i][j]/TilesetWidth;
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
