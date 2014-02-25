#ifndef __TEXT_H
#define __TEXT_H

#include "GLCommon.h"

class CText
{
public:
	static SDL_Surface * Surface_text;
	static TTF_Font* ms_pPolice;
	static SDL_Renderer* renderer;
	static SDL_Rect textRect;
	static SDL_Texture* Texturetext;
	static SShaderGLSL m_Shader;

	static void InitText();
	static void Quit();

	static void WriteText(char* text);
};

#endif //__TEXT_H