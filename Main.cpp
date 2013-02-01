#include<SFML/Window.hpp>
#include<GL/GL.h>
#include "Core/Math.hpp"

#include "Core/LevelManager.hpp"
#include "Core/Entity/Player.hpp"

#include "Core/Resources/GamePath.hpp"
#include "Core/Resources/ResourceManager.hpp"
#include "Core/SoundManager.hpp"
#include "Core/Entity/Tile/MystBlock.hpp"

/*
	Pour linker la SFML :

	Project > Build Options
		Debug (en dessous du nom du projet)
		Linker settings
		et dans Other settings :

		-lsfml-graphics-s
		-lsfml-window-s
		-lsfml-audio-s
		-lsfml-system-s
*/

 ResourceManager R;
 SoundManager SM;
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

	GamePath::Root = "D:\\Development\\GithubShared\\BasicPlatformer\\Public\\";
	GamePath::GeneratePath();

	GlobalInput = &App.GetInput();

	InitializeGL(800,600);

	LevelManager L;

    L.LoadTileset("mTileset");
    L.LoadLevel("Level");

	L.RegisterObject(new Player(vec2f(0,0)));
    L.RegisterObject(new MysteriousBlock(vec2i(8,2)));

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
			else if (e.Type == sf::Event::Resized)
            {
                InitializeGL(App.GetWidth(),App.GetHeight());
            }
		}

		L.Tick();
		SM.Tick();

		// On redessine toute la scène :
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		// glClearColor(r,g,b,a)


		glEnable(GL_TEXTURE_2D);
        glEnable(GL_ALPHA_TEST);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glAlphaFunc(GL_GREATER,0.1);
		glDepthFunc(GL_LESS);

		L.Draw();


		glDisable(GL_TEXTURE_2D);
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

		App.Display();

	}



	// Fin
	return 0x0;

}

