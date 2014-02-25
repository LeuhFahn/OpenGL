#include <iostream>

#include "../Scene/Scene.h"
#include "Text.h"

SDL_Surface * CText::Surface_text = nullptr;;
TTF_Font* CText::ms_pPolice = nullptr;
SDL_Renderer* CText::renderer = nullptr;;
SDL_Rect CText::textRect;
SDL_Texture* CText::Texturetext = nullptr;
SShaderGLSL m_Shader;

void CText::InitText()
{
	int w = 100;
	int h = 100;
	if(TTF_Init() == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	} 

	ms_pPolice = TTF_OpenFont("../fonts/VeraMono.ttf", 65);
	SDL_Color white = {255, 0, 255};
	
	SDL_Surface* Surface_text = TTF_RenderText_Blended(ms_pPolice, "Salut les putes !", white);
	//SDL_FreeSurface(text);
	renderer = SDL_CreateRenderer(CScene::m_pWindow, -1, SDL_RENDERER_ACCELERATED );

	textRect.x=10;
	textRect.y=0;
	textRect.w=100;
	textRect.h=h;
}

void CText::Quit()
{
	TTF_CloseFont(ms_pPolice);
	TTF_Quit();
}

void CText::WriteText(char* pcText)
{
		//glClear(GL_COLOR_BUFFER_BIT);

		SDL_Color white = {255, 0, 0};
		Surface_text = TTF_RenderText_Solid(ms_pPolice, pcText, white);

		Texturetext = SDL_CreateTextureFromSurface(renderer, Surface_text);
		//SDL_QueryTexture(Ttext, NULL, NULL, &w, &h);

		SDL_RenderCopy(renderer, Texturetext, NULL, &textRect);

		SDL_RenderPresent(renderer);
		SDL_FreeSurface( Surface_text );
		//screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
		//SDL_FreeSurface(text);
		//apply_surface( 10, 0, text, screen );
		//SDL_GL_SwapWindow(CScene::m_pWindow);
}