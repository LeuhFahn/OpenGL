
#include <GLEW/glew.h>
#include <SDL/SDL.h>
#include <iostream>

#include "user/user.h"
#include "shapes/triangle.h"

int main(int argc, char **argv)
{	
	int nWidth = 1024, nHeight = 768;
    // Notre fen�tre
	
    SDL_Window* window(0);
    SDL_GLContext contexteOpenGL(0);
	
    SDL_Event evenements;
    bool bQuit(false);
	
	
    // Initialisation de la SDL
	
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
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
	
	
    // Cr�ation de la fen�tre
    window = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, nWidth, nHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(window == 0)
    {
        std::cout << "Error window creation: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit( EXIT_FAILURE );
    }

    // Cr�ation du contexte OpenGL
    contexteOpenGL = SDL_GL_CreateContext(window);
    if(contexteOpenGL == 0)
    {
		std::cout << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit( EXIT_FAILURE );
    }


    if (glewInit() != GLEW_OK)
    {
		std::cout << "Failed to initialize GLEW" << std::endl;
		SDL_GL_DeleteContext(contexteOpenGL);
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit( EXIT_FAILURE );
    }

    // Vertices et coordonn�es
    CTriangle triangle;

    // Boucle principale
    while(!bQuit)
    {
        // Gestion des �v�nements
		// R�cup�ration d'un �v�nement
		SDL_PollEvent(&evenements);
	
        if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
            bQuit = true;

		// Switch sur le type d'�v�nement
		switch(evenements.type)
		{
			case SDL_KEYDOWN:
        
				// Gestion des touches
				switch(evenements.key.keysym.scancode)
				{
					case SDL_SCANCODE_ESCAPE:
						 bQuit = true;
					break;
				}

			break;
		}

        // Nettoyage de l'�cran
        glClear(GL_COLOR_BUFFER_BIT);

		triangle.Draw();

        // On d�sactive le tableau Vertex Attrib puisque l'on n'en a plus besoin
        glDisableVertexAttribArray(0);

        // Actualisation de la fen�tre
        SDL_GL_SwapWindow(window);
    }


    // On quitte la SDL
    SDL_GL_DeleteContext(contexteOpenGL);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}