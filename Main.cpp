#include <iostream>
#include <SFML/Window.hpp>
#include <GL/GL.h>
#include "Math/Math.hpp"
#include "LevelManager/LevelManager.hpp"
#include "Object/Object.hpp"
#include "Object/Entity/Player/Player.hpp"

const sf::Input *GlobalInput;

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
    L.LoadLevel("Resources/Level.txt");
	L.LoadTileset("Resources/Tileset.png");
	L.RegisterObject(new Player(vec2f(0,0)));
	L.Create();
	while(App.IsOpened()){
		sf::Event e;
		while (App.GetEvent(e)){
			if(e.Type == sf::Event::Closed) App.Close();
		}
		L.Tick();
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		glClearColor(0.3,0.67,0.7,1.0);
		glEnable(GL_TEXTURE_2D);
        glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER,0.5);
		L.Draw();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_ALPHA_TEST);
		App.Display();
	}
	return 0;
}
