
#include <GLEW/glew.h>
#include <SDL/SDL.h>
#include <iostream>

#include "user/user.h"
#include "Scene/Scene.h"
#include "Tools/Timer.h"
#include "Tools/Text.h"

/*
SDL_Surface * Surface_text;
TTF_Font* ms_pPolice = nullptr;
SDL_Renderer* renderer;
SDL_Rect textRect;

void Init()
{
	
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

		
}

void Process()
{
			int w = 100;
		int h = 100;

	glClear(GL_COLOR_BUFFER_BIT);

		//SDL_GetRendererOutputSize(renderer, &w, &h);
		SDL_Color white = {255, 0, 255};
		Surface_text = TTF_RenderText_Blended(ms_pPolice, "Salut les pds", white);

		SDL_Texture* Ttext = SDL_CreateTextureFromSurface(renderer, Surface_text);
		//SDL_QueryTexture(Ttext, NULL, NULL, &w, &h);
		textRect.x=10;textRect.y=0;
		textRect.w=500;textRect.h=h;

		SDL_RenderCopy(renderer, Ttext, NULL, &textRect);
		//}

		SDL_RenderPresent(renderer);

		//screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
		//SDL_FreeSurface(text);
		//apply_surface( 10, 0, text, screen );
		SDL_GL_SwapWindow(CScene::m_pWindow);
}
*/
int main(int argc, char **argv)
{	
	CScene Scene;
	Scene.Init();   
	// Boucle principale

	CTimer timer;
	timer.start();

	while(!Scene.GetQuit())
	{
		// Gestion des évènements
		// Récupération d'un évènement
		Scene.Process(1.0f/60.0f);
		Scene.Draw(1.0f/60.0f);
		//CText::WriteText("bla");
	}

	Scene.QuitApplication();
	/*
	CScene Scene;
	Scene.Init();  
	// Initialisation de la SDL	
    /*if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Error init SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
		
        exit( EXIT_FAILURE );
    }
	
    // Version d'OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	
	
    // Double Buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	
	
    // Création de la fenêtre

   SDL_Window* m_pWindow = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(m_pWindow == 0)
    {
        std::cout << "Error window creation: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit( EXIT_FAILURE );
    }

    // Création du contexte OpenGL
    SDL_GLContext m_ContexteOpenGL = SDL_GL_CreateContext(CScene::m_pWindow);
    if(m_ContexteOpenGL == 0)
    {
		std::cout << SDL_GetError() << std::endl;
		SDL_DestroyWindow(CScene::m_pWindow);
		SDL_Quit();
		exit( EXIT_FAILURE );
    }


    if (glewInit() != GLEW_OK)
    {
		std::cout << "Failed to initialize GLEW" << std::endl;
		SDL_GL_DeleteContext(m_ContexteOpenGL);
		SDL_DestroyWindow(CScene::m_pWindow);
		SDL_Quit();
		exit( EXIT_FAILURE );
    }

	SDL_Event m_Evenements;
	
	Init();
		
	bool bQuit = false; 
	while(!bQuit){

		SDL_PollEvent(&m_Evenements);
	
		if(m_Evenements.window.event == SDL_WINDOWEVENT_CLOSE)
			bQuit = true;

		// Switch sur le type d'évènement
		switch(m_Evenements.type)
		{
			case SDL_KEYDOWN:
        
				// Gestion des touches
				switch(m_Evenements.key.keysym.scancode)
				{
					case SDL_SCANCODE_ESCAPE:
						bQuit = true;
					break;
				}

			break;
		}

		Process();
	}
	
	TTF_CloseFont(ms_pPolice);
	//SDL_GL_DeleteContext(m_ContexteOpenGL);
    SDL_DestroyWindow(CScene::m_pWindow);
    SDL_Quit();
	*/
    return 0;
}