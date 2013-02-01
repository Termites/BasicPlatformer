#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <GL/GL.h>
#include <algorithm>
#include <string>
#include <list>
#include <map>
#include "../Math/Math.hpp"

GLuint ConvertToGLTexture(const sf::Image & Image);

template<typename T>
struct Resource{
	std::string Name;
	T Value;
};

struct Anim{
    int FramesCount;
    int *Frames;
    float FrameRate;
};

typedef std::map<std::string,Anim> AnimPack;

struct Sprite{
    GLuint Tex;
    int Width,Height;
    vec2i FrameSize;
};

inline char Lower(char C){
    return (C>='A' && C<='Z')?C+32:C;
}

class ResourceManager{
	private:
		std::list<Resource<sf::SoundBuffer>> SoundList;
		std::list<Resource<AnimPack>> AnimList;
		std::list<Resource<Sprite>> SpriteList;

	public:
		sf::SoundBuffer &LoadSound(const std::string &S);
		AnimPack &LoadAnim(const std::string &S);
		Sprite &LoadSprite(const std::string &S, const vec2i &FS);
		void DrawSprite(Sprite &S, const vec2f &Location, int FrameIndex, const vec2f &Scale);

    protected:
};

