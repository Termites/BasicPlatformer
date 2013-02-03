#pragma once

#include<GL/GLEW.h>

class FrameBuffer
{
	private:
		GLuint Texture;
		GLuint FramebufferID;
		GLuint DepthbufferID;
		int Width,Height;

	public:
		FrameBuffer(int Width,int Height);
		~FrameBuffer();
		void Bind();
		void Draw();
		static void Unbind();
};
