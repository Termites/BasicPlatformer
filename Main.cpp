#include <GL/GLEW.h>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include "Math/Math.hpp"
#include "LevelManager/LevelManager.hpp"
#include "Object/Object.hpp"
#include "Object/Entity/Player/Fario/Fario.hpp"
#include "Object/Entity/Block/MystBlock.hpp"
#include "Object/Entity/Block/Brick.hpp"
#include "ResourceManager/GamePath.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "ResourceManager/SoundManager.hpp"

const sf::Input *GlobalInput;
ResourceManager R;
SoundManager SM;

void InitializeGL(int W,int H){
    glewInit();
	glViewport(0,0,W,H);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0,320,240,0,-100,100);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
}

struct Shader{
	GLuint FragShad;
	GLuint VertShad;
	GLuint Prog;
	~Shader(){
		glDetachShader(Prog,VertShad);
		glDetachShader(Prog,FragShad);
		glDeleteShader(VertShad);
		glDeleteShader(FragShad);
		glDeleteProgram(Prog);
	}
};

bool CheckShader(const Shader &S){
    int infoL=0;
    int charWritten=0;
    char *infoLog;
    GLint Vert_CS,Frag_CS;
    glGetShaderiv(S.VertShad,GL_COMPILE_STATUS,&Vert_CS);
    glGetShaderiv(S.FragShad,GL_COMPILE_STATUS,&Frag_CS);
    if(Vert_CS==GL_TRUE && Frag_CS==GL_TRUE) return true;
    glGetShaderiv(S.VertShad,GL_INFO_LOG_LENGTH,&infoL);
    if(infoL>0){
        infoLog=new char [infoL];
        glGetShaderInfoLog(S.VertShad,infoL,&charWritten,infoLog);
        std::cout << "Vertex Shader : " << infoLog << std::endl;
        delete []infoLog;
    }
    glGetShaderiv(S.FragShad,GL_INFO_LOG_LENGTH,&infoL);
    if(infoL>0){
        infoLog = new char [infoL];
        glGetShaderInfoLog(S.FragShad,infoL,&charWritten,infoLog);
        std::cout << "Fragment Shader : " << infoLog << std::endl;
        delete []infoLog;
    }
    return false;
}

std::string LoadSource(const std::string&SrcFile){
	std::ifstream File;
	File.open(SrcFile.c_str(),std::ios::binary);
	if (!File.is_open()) return NULL;
	File.seekg(0,std::ios::end);
	int Size = File.tellg();
	File.seekg(0,std::ios::beg);
	char * Buff =new char[Size+1];
	File.read(Buff,Size);
	File.close();
	Buff[Size]='\0';
    std::string S = Buff;
    delete [] Buff;
	return S;
}

Shader LoadShader(const std::string&VertFile,const std::string&FragFile){
	Shader NewShader;
	std::string VertFileC = LoadSource(VertFile);
	std::string FragFileC = LoadSource(FragFile);
	NewShader.FragShad = glCreateShader(GL_FRAGMENT_SHADER);
	NewShader.VertShad = glCreateShader(GL_VERTEX_SHADER);
    const char* VertFileCPtr = VertFileC.c_str();
    const char* FragFileCPtr = FragFileC.c_str();
	glShaderSource(NewShader.VertShad,1,const_cast<const GLchar**>(&VertFileCPtr),NULL);
	glShaderSource(NewShader.FragShad,1,const_cast<const GLchar**>(&FragFileCPtr),NULL);
	glCompileShader(NewShader.VertShad);
	glCompileShader(NewShader.FragShad);
	NewShader.Prog = glCreateProgram();
	glAttachShader(NewShader.Prog,NewShader.VertShad);
	glAttachShader(NewShader.Prog,NewShader.FragShad);
	glLinkProgram(NewShader.Prog);
    if (CheckShader(NewShader)) std::cout<<"OK ! \n";
    else std::cout<<"Error..\n";
	return NewShader;
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
	L.RegisterObject(new MystBlock(vec2i(3,9)));
	L.RegisterObject(new Brick(vec2i(4,9)));
	L.Create();
	Shader S=LoadShader("VertexShader.shad","FragmentShader.shad");
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
		glUseProgram(S.Prog);
		L.Draw();
        glUseProgram(0);
		glDisable(GL_ALPHA_TEST);
		App.Display();
	}
	return 0;
}
