#include<SFML/Window.hpp>
#include<GL/GL.h>
#include "Core/Math.hpp"

#include "Core/LevelManager.hpp"
#include "Core/Entity/Player.hpp"

/*
	Pour linker la SFML :

	Project > Build Options
		Debug (en dessous du nom du projet)
		Linker settings
		et dans Other settings :

		-lsfml-graphics-s
		-lsfml-window-s
		-lsfml-system-s
*/


/*
Niveau : Format ASCII :

R,G,B (Ciel)
W,H (Taille de la carte)
b0,b1,b2.. (tous les blocs)
bn,b,+1,...


128,128,128
4,4
0,0,0,0,
0,0,0,0,
0,0,0,0,
1,1,1,1,


*/

const sf::Input * GlobalInput;


void InitializeGL(int W,int H)
{
	// glViewport(BorderW,BorderH,Width,Height)
	glViewport(0,0,W,H);
	// On passe en matrice "model view" (en gros 3D)
	glMatrixMode(GL_MODELVIEW);
	// On charge en tant que matrice d'identitée
	glLoadIdentity();

	//  glOrtho(Left,Right,Bottom,Top,zNear,zFar)
	glOrtho(0,320,240,0,-100,100);
	// On passe en matrice de projection (en gros 2D)
	glMatrixMode(GL_PROJECTION);
	// On charge en tant que matrice d'identitée
	glLoadIdentity();

	// On efface l'écran
	// GL_COLOR_BUFFER_BIT : On efface les couleurs sur l'écran
	// GL_DEPTH_BUFFER_BIT : On efface la depth
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
}

int main(int arg_c,char*argv[])
{
	// Constructeur :
	//Window (sf::VideoMode Mode, const std::string &Title,...)
	sf::Window App(sf::VideoMode(800,600,32),"FARIO");
	// On tourne à 60FPS
	App.SetFramerateLimit(60);

	GlobalInput = &App.GetInput();

	InitializeGL(800,600);

	LevelManager L;

    L.LoadLevel("Level.txt");
	L.LoadTileset("Tileset.png");

	L.RegisterObject(new Player(vec2f(0,0)));

	L.Create();

	while (App.IsOpened())
	{

		// On traite les évenements :
		sf::Event e;
		// bool sf::Window::GetEvent(sf::Event & e)
		while (App.GetEvent(e))
		{
			// Types :
			// sf::Event::Resized
			// sf::Event::Closed
			if (e.Type == sf::Event::Closed)
			{
				// Ferme la fenêtre
				App.Close();
			}
		}

		L.Tick();

		// On redessine toute la scène :
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		// glClearColor(r,g,b,a)
		glClearColor(0.5,0.5,0.5,1.0);

		glEnable(GL_TEXTURE_2D);
        glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER,0.5);

		L.Draw();

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_ALPHA_TEST);

		App.Display();
	}



	// Fin
	return 0x0;

}

