#include<iostream>
#include<algorithm>
#include <fstream>
#include "ResourceManager.hpp"
#include "GamePath.hpp"

GLuint ConvertToGLTexture(const sf::Image & Image){
	GLuint TextureID;
	glGenTextures(1,&TextureID);
	glBindTexture(GL_TEXTURE_2D,TextureID);
	glTexImage2D(GL_TEXTURE_2D,0,4,Image.GetWidth(),Image.GetHeight(),0,GL_RGBA,
	GL_UNSIGNED_BYTE,Image.GetPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D,0);
	return TextureID;
}

sf::SoundBuffer &ResourceManager::LoadSound(const std::string &Snd){
    std::string LowerName;
    LowerName.resize(Snd.size());
    std::transform(Snd.begin(),Snd.end(),LowerName.begin(),Lower);
    for (auto it=SoundList.begin(); it!=SoundList.end(); ++it){
        Resource<sf::SoundBuffer> &R=*it;
        if(R.Name==LowerName) return R.Value;
    }
    SoundList.resize(SoundList.size()+1);
    Resource<sf::SoundBuffer> &R=SoundList.back();
    R.Name=LowerName;
    R.Value.LoadFromFile(GamePath::Sound+Snd+".wav");
    return R.Value;
}

AnimPack &ResourceManager::LoadAnim(const std::string &AnimFile){
    std::string LowerName;
    LowerName.resize(AnimFile.size());
    std::transform(AnimFile.begin(),AnimFile.end(),LowerName.begin(),Lower);
    for (auto it=AnimList.begin(); it!=AnimList.end(); ++it){
        Resource<AnimPack> &R=*it;
        if(R.Name==LowerName) return R.Value;
    }
    AnimList.resize(AnimList.size()+1);
    Resource<AnimPack> &R=AnimList.back();
    R.Name=LowerName;
    std::string Path=GamePath::Animation+AnimFile+".anim";
    std::ifstream File(Path.c_str());
    while(File.good()){
        std::string AnimName;
        Anim Tmp;
        std::string TmpName="";
        char Sep;
        File >> TmpName;
        TmpName.erase(TmpName.begin());
        TmpName.erase(TmpName.end()-1);
        AnimName=TmpName;
        File >> Tmp.FramesCount;
        Tmp.Frames=new int[Tmp.FramesCount];
        for(int i(0); i<Tmp.FramesCount; ++i){
            File >> Tmp.Frames[i] >> Sep;
        }
        File >> Tmp.FrameRate;
        R.Value[AnimName]=Tmp;
    }
    return R.Value;
}

Sprite &ResourceManager::LoadSprite(const std::string &SpriteFile, const vec2i &FrameSize){
	std::string LowerName;
    LowerName.resize(SpriteFile.size());
    std::transform(SpriteFile.begin(),SpriteFile.end(),LowerName.begin(),Lower);
    for (auto it=SpriteList.begin(); it!=SpriteList.end(); ++it){
        Resource<Sprite> &R=*it;
        if(R.Name==LowerName) return R.Value;
    }
    SpriteList.resize(SpriteList.size()+1);
    Resource<Sprite> &R=SpriteList.back();
    R.Name=LowerName;
    sf::Image I;
	I.LoadFromFile(GamePath::Animation+SpriteFile+".png");
	R.Name=SpriteFile;
	R.Value.Tex=ConvertToGLTexture(I);
	R.Value.Width=I.GetWidth();
	R.Value.Height=I.GetHeight();
	R.Value.FrameSize=FrameSize;
    return R.Value;
}

void ResourceManager::DrawSprite(Sprite &S, const vec2f &Location, int FrameIndex, const vec2f &Scale){
    vec2f UV;
    float w=S.FrameSize.x/float(S.Width);
    float h=S.FrameSize.y/float(S.Height);
    UV.x=FrameIndex%S.Width;
    UV.y=FrameIndex/S.Width;
    UV.x*=w;
    UV.y*=h;
    float x1,x2,y1,y2;
    x1=UV.x;
    x2=UV.x+w;
    y1=UV.y;
    y2=UV.y+h;
    if(Scale.x<0){
        float tmp=x1;
        x1=x2;
        x2=tmp;
    }
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,S.Tex);
    glBegin(GL_QUADS);
        glTexCoord2f(x1,y1);
        glVertex3f(Location.x,Location.y,1);
        glTexCoord2f(x2,y1);
        glVertex3f(Location.x+(S.FrameSize.x*fabs(Scale.x)),Location.y,1);
        glTexCoord2f(x2,y2);
        glVertex3f(Location.x+(S.FrameSize.x*fabs(Scale.x)),Location.y+(S.FrameSize.y*fabs(Scale.y)),1);
        glTexCoord2f(x1,y2);
        glVertex3f(Location.x,Location.y+(S.FrameSize.y*fabs(Scale.y)),1);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,0);
    glDisable(GL_TEXTURE_2D);
}
