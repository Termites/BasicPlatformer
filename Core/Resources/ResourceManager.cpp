#include "ResourceManager.hpp"
#include "GamePath.hpp"

#include<algorithm>
#include<fstream>
#include<iostream>
#define debug(a) std::cout<<a<<std::endl

GLuint ConvertToGLTexture(const sf::Image & Image)
{
	GLuint TextureID;

	// glGenTextures(int nb textures, GLuint* Tableau)
	glGenTextures(1,&TextureID);
	glBindTexture(GL_TEXTURE_2D,TextureID);

	//http://www.opengl.org/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(GL_TEXTURE_2D,0,4,Image.GetWidth(),Image.GetHeight(),0,GL_RGBA,
	GL_UNSIGNED_BYTE,Image.GetPixelsPtr());

	// Mode d'interpolation des pixels (pour les zooms/dézooms)
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D,0);

	return TextureID;

}

sf::SoundBuffer & ResourceManager::LoadSound(const std::string&Snd)
{
			std::string LowerName;
			LowerName.resize(Snd.size());
			std::transform(Snd.begin(),Snd.end(),LowerName.begin(),Lower);

			// On vérifie que le son n'est pas déjà chargé :

			for (std::list<Resource<sf::SoundBuffer> >::iterator it = SoundList.begin();it!=SoundList.end();++it)
			{
				Resource<sf::SoundBuffer> & R = *it;

				if (R.Name == LowerName)
					return R.Value;
			}


			SoundList.resize(SoundList.size()+1);

			Resource<sf::SoundBuffer> &R = SoundList.back();
			R.Name = LowerName;
			std::cout<<" ?? "<<Snd<<R.Value.LoadFromFile(GamePath::Sound+Snd+".wav")<<std::endl;

			return R.Value;
}

Sprite & ResourceManager::LoadSprite(const std::string & PNGFile,const vec2i& FrameSize,const vec2i&Offset)
{
            std::string LowerName;
			LowerName.resize(PNGFile.size());
			std::transform(PNGFile.begin(),PNGFile.end(),LowerName.begin(),Lower);

            // On vérifie que le sprite n'a pas déjà été chargé :
			for (std::list<Resource<Sprite> >::iterator it = SpriteList.begin();it!=SpriteList.end();++it)
			{
				Resource<Sprite> & R = *it;

				if (R.Name == LowerName)
					return R.Value;
			}

			SpriteList.resize(SpriteList.size()+1);
			Resource<Sprite> & Spr = SpriteList.back();
			Spr.Name = LowerName;
			Spr.Value.FrameSize = FrameSize;
			Spr.Value.Offset = Offset;

			sf::Image I;
			I.LoadFromFile(GamePath::Animation+PNGFile + ".png");

			Spr.Value.Size.x = I.GetWidth();
			Spr.Value.Size.y = I.GetHeight();
			Spr.Value.Texture = ConvertToGLTexture(I);

			return Spr.Value;

}

void ResourceManager::DrawSprite(const Sprite & Spr,int FrameIndex, const vec2f&Location,int Layer,const vec2f&Scale)
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,Spr.Texture);
    vec2f UV;
    vec2f UVs;
    UVs = vec2f(Spr.FrameSize)/vec2f(Spr.Size);

    int nbW = Spr.Size.x / Spr.FrameSize.x;

    UV.x = (FrameIndex%nbW);
    UV.y = (FrameIndex/nbW) ;

    UV *= UVs;

    float x0,x1,y0,y1;

    x0 = UV.x;
    y0 = UV.y;
    x1 = UV.x + UVs.x;
    y1 = UV.y + UVs.y;

    if (sign(Scale.x) <0 )
    {
        float r = x0;
        x0 = x1;
        x1 = r;
    }


    glBegin(GL_QUADS);
    glTexCoord2f(x0,y0);
    glVertex3f(Location.x,Location.y,Layer);

    glTexCoord2f(x1,y0);
    glVertex3f(Location.x + Spr.FrameSize.x * fabs(Scale.x),Location.y,Layer);

    glTexCoord2f(x1,y1);
    glVertex3f(Location.x+ Spr.FrameSize.x * fabs(Scale.x),Location.y+ Spr.FrameSize.y * fabs(Scale.y),Layer);

    glTexCoord2f(x0,y1);
    glVertex3f(Location.x,Location.y+ Spr.FrameSize.y * fabs(Scale.y),Layer);
    glEnd();

    glBindTexture(GL_TEXTURE_2D,0);
    glDisable(GL_TEXTURE_2D);
}

AnimationSet & ResourceManager::LoadAnimationSet(const std::string&PackageName)
{

 			std::string LowerName;
			LowerName.resize(PackageName.size());
			std::transform(PackageName.begin(),PackageName.end(),LowerName.begin(),Lower);

            // On vérifie que le package n'a pas déjà été chargé :
			for (std::list<Resource<AnimationSet> >::iterator it = AnimationList.begin();it!=AnimationList.end();++it)
			{
				Resource<AnimationSet> & R = *it;

				if (R.Name == LowerName)
					return R.Value;
			}
            AnimationList.resize(AnimationList.size()+1);

            Resource<AnimationSet> & R = AnimationList.back();
            R.Name = LowerName;

            std::string Full = GamePath::Animation + PackageName + ".anim";
            std::ifstream Input(Full.c_str());
            if (Input.is_open())
            {
                while (Input.good())
                {
                    std::string L = "";
                    while (L.size()==0 && Input.good())
                        Input>>L;
                    if (L.size()>0)
                    {
                        // L = nom de l'animation :
                        L.erase(L.begin());
                        L.erase(L.end()-1);
                        debug("["<<L<<"]");
                        std::string AnimationName = L;
                        Animation &NewAnim =R.Value[AnimationName] ;

                        Input>>NewAnim.FramesCount;
                        NewAnim.FrameKeys = new int [NewAnim.FramesCount];
                        char Sep;
                        for (int i=0;i<NewAnim.FramesCount;++i)
                        {
                            int k;
                            Input>>k>>Sep;
                            NewAnim.FrameKeys[i]=k;
                        }

                        Input>>NewAnim.Ratescale;

                    }
                }
            }
            Input.close();

            return R.Value;
}
