#include "FrameBuffer.hpp"

#ifndef NULL
#define NULL (void*)0
#endif

FrameBuffer::FrameBuffer(int w,int h)
{
        Width=w;
        Height=h;
        glGenTextures(1,&Texture);
        glBindTexture(GL_TEXTURE_2D,Texture);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);
        glBindTexture(GL_TEXTURE_2D,0);

        glGenRenderbuffersEXT(1,&DepthbufferID);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT,DepthbufferID);
        glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT,GL_DEPTH_COMPONENT,w,h);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT,0);

        glGenFramebuffersEXT(1,&FramebufferID);
        glBindFramebufferEXT(GL_FRAMEBUFFER,FramebufferID);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,GL_COLOR_ATTACHMENT0_EXT,GL_TEXTURE_2D,Texture,0);
        glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER_EXT,DepthbufferID);

        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
        glDisable(GL_TEXTURE_2D);
}

void FrameBuffer::Bind()
{
    glBindFramebufferEXT(GL_FRAMEBUFFER,FramebufferID);
}

void FrameBuffer::Unbind()
{
    glBindFramebufferEXT(GL_FRAMEBUFFER,0);
}
FrameBuffer::~FrameBuffer()
{
        glDeleteTextures(1,&Texture);
		glDeleteRenderbuffersEXT(1,&DepthbufferID);
		glDeleteFramebuffersEXT(1,&FramebufferID);
}
