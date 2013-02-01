#include <iostream>
#include <SFML/Window.hpp>
#include <GL/GL.h>
#include "Math/Math.hpp"
#include "LevelManager/LevelManager.hpp"
#include "Object/Object.hpp"
#include "Object/Entity/Player/Fario/Fario.hpp"
#include "Object/Entity/Block/MystBlock.hpp"
#include "ResourceManager/GamePath.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "ResourceManager/SoundManager.hpp"

const sf::Input *GlobalInput;
ResourceManager R;
SoundManager SM;

void InitializeGL(int W,int H){
	glViewport(0,0,W,H);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0,320,240,0,-100,100);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
}

int main(int arg_c,char*argv[]){
	sf::Window App(sf::VideoMode(800,600,32),"FARIO");
	GlobalInput=&App.GetInput();
	App.SetFramerateLimit(60);
	InitializeGL(800,600);
	LevelManager L;
    GamePath::Root="C:\\Users\\JUX\\Desktop\\BasicPlatformer";
    GamePath::GeneratePath();
    L.LoadTileset("Tileset1");
    L.LoadLevel("1");
	L.RegisterObject(new Fario(vec2f(16*1,16*11)));
	L.RegisterObject(new MystBlock(vec2i(0,0)));
	L.Create();
	while(App.IsOpened()){
		sf::Event e;
		while (App.GetEvent(e)){
			if(e.Type == sf::Event::Closed) App.Close();
		}
		L.Tick();
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        glEnable(GL_ALPHA_TEST);
        glEnable(GL_DEPTH_TEST);
		glAlphaFunc(GL_GREATER,0.5);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		L.Draw();
		glDisable(GL_ALPHA_TEST);
		App.Display();
	}
	return 0;
}
