#include<GL/GLEW.h>
#include<SFML/Window.hpp>

//#include<GL/GL.h>
#include "Core/Math.hpp"

#include "Core/LevelManager.hpp"
#include "Core/Entity/Player.hpp"

#include "Core/Resources/GamePath.hpp"
#include "Core/Resources/ResourceManager.hpp"
#include "Core/SoundManager.hpp"
#include "Core/Entity/Tile/MystBlock.hpp"
#include "Core/Entity/Tile/BrickBlock.hpp"
#include "Core/FrameBuffer.hpp"

#include<fstream>
#include<iostream>

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
    glewInit();
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

struct Shader
{
	GLuint FragShad;
	GLuint VertShad;
	GLuint Prog;
	~Shader()
	{
		glDetachShader(Prog,VertShad);
		glDetachShader(Prog,FragShad);

		glDeleteShader(VertShad);
		glDeleteShader(FragShad);

		glDeleteProgram(Prog);
	}
};

bool CheckShader(const Shader&S)
{
    int infoL=0;
    int charWritten=0;
    char*infoLog;

    GLint Vert_CS,Frag_CS;
    glGetShaderiv(S.VertShad,GL_COMPILE_STATUS,&Vert_CS);
    glGetShaderiv(S.FragShad,GL_COMPILE_STATUS,&Frag_CS);

    if (Vert_CS==GL_TRUE && Frag_CS == GL_TRUE)
        return true;

    glGetShaderiv(S.VertShad,GL_INFO_LOG_LENGTH,&infoL);

    if (infoL>0)
    {
        infoLog = new char [infoL];
        glGetShaderInfoLog(S.VertShad,infoL,&charWritten,infoLog);
        std::cout<<"Vertex Shader : "<<infoLog<<std::endl;
        delete [] infoLog;
    }

    glGetShaderiv(S.FragShad,GL_INFO_LOG_LENGTH,&infoL);

    if (infoL>0)
    {
        infoLog = new char [infoL];
        glGetShaderInfoLog(S.FragShad,infoL,&charWritten,infoLog);
        std::cout<<"Fragment Shader : "<<infoLog<<std::endl;
        delete [] infoLog;

    }

    return false;
}

std::string LoadSource(const std::string&SrcFile)
{
	std::ifstream File;
	File.open(SrcFile.c_str(),std::ios::binary);
	if (!File.is_open())
        return NULL;

	File.seekg(0,std::ios::end);
	int Size = File.tellg(); // size_t tellg()
	File.seekg(0,std::ios::beg);

	char * Buff =new char[Size+1];
	File.read(Buff,Size);
	File.close();
	Buff[Size]='\0';
    std::string S = Buff;

    delete [] Buff;
	return S;
}

Shader LoadShader(const std::string&VertFile,const std::string&FragFile)
{
	Shader NewShader;
	std::string VertFileC = LoadSource(VertFile); // Contenu du fichier vert
	std::string FragFileC = LoadSource(FragFile); // Contenu du fichier frag


	NewShader.FragShad = glCreateShader(GL_FRAGMENT_SHADER);
	NewShader.VertShad = glCreateShader(GL_VERTEX_SHADER);

    const char* VertFileCPtr = VertFileC.c_str();
    const char* FragFileCPtr = FragFileC.c_str();
	// GLuint Shader
	// int Nombre de 'fichiers texte'
	// char** Tableau de strings
	// int nb lettres NULL (0) pour préciser que la fin a un '\0'
	glShaderSource(NewShader.VertShad,1,const_cast<const GLchar**>(&VertFileCPtr),NULL);
	glShaderSource(NewShader.FragShad,1,const_cast<const GLchar**>(&FragFileCPtr),NULL);

	glCompileShader(NewShader.VertShad);
	glCompileShader(NewShader.FragShad);

	NewShader.Prog = glCreateProgram();

	glAttachShader(NewShader.Prog,NewShader.VertShad);
	glAttachShader(NewShader.Prog,NewShader.FragShad);

	glLinkProgram(NewShader.Prog); // ...

    if (CheckShader(NewShader))
        std::cout<<"OK ! \n";
    else
        std::cout<<"Error..\n";


	return NewShader;
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

    for (int i=0;i<6;i++)
        L.RegisterObject(new BrickBlock(vec2i(9+i,2)));

	L.Create();

	//Shader S = LoadShader("VertexShader.shad","FragmentShader.shad");

    FrameBuffer F(512,512);

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

        //glUseProgram(S.Prog);

        //F.Bind();
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
       // glUseProgram(0);

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

        //FrameBuffer::Unbind();
		App.Display();

	}



	// Fin
	return 0x0;

}

