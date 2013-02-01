#pragma once
#include<SFML/Audio.hpp>
#include <String>
#include <List>
#include <Map>
#include <SFML/Graphics.hpp>
#include <GL/GL.h>
#include "../Math.hpp"

template<typename T>
struct Resource
{
	std::string Name;
	T Value;
};

struct Animation
{
  int FramesCount;
  int * FrameKeys;
  float Ratescale;
  ~Animation()
  {
      delete [] FrameKeys;
  }
};

struct Sprite
{
    GLuint Texture;
    vec2i Size;
    vec2i FrameSize;
    vec2i Offset;
};

typedef std::map<std::string,Animation> AnimationSet;

GLuint ConvertToGLTexture(const sf::Image & Image);

inline char Lower(char C)
{
    return C >='A' && C<='Z' ? C+32 : C;
}

class ResourceManager
{
	private:
		std::list<Resource<sf::SoundBuffer> > SoundList;

		std::list<Resource<AnimationSet> > AnimationList;

		std::list<Resource<Sprite> > SpriteList;

	public:

		sf::SoundBuffer & LoadSound(const std::string & S);
		AnimationSet & LoadAnimationSet(const std::string & S);
		Sprite & LoadSprite(const std::string&PNGFile,const vec2i &FrameSize,const vec2i&Offset);

		void DrawSprite(const Sprite & S,int FrameIndex,const vec2f & Location,int Layer,const vec2f&Scale);

};

