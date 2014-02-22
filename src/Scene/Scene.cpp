#include <iostream>
#include "Scene.h"

int CScene::ms_nWidth = 1024;
int CScene::ms_nHeight = 768;
CCamera CScene::ms_Camera;

CScene::CScene() :

	m_nNbShapes(0),
	m_ContexteOpenGL(0),
	m_bQuit(false)
	
{
	m_pWindow = nullptr;
	m_pShape = new CShape*[12];
}

CScene::~CScene()
{
	delete m_pShape;
}

void CScene::Init()
{
	InitSDL();

	//Camera
    ms_Camera.camera_defaults(ms_Camera);
	


	m_pShape[0] = new CTriangle();
	m_nNbShapes++;
}

void CScene::Process(float fDeltatime)
{
	SDL_PollEvent(&m_Evenements);
	
	if(m_Evenements.window.event == SDL_WINDOWEVENT_CLOSE)
		m_bQuit = true;

	// Switch sur le type d'évènement
	switch(m_Evenements.type)
	{
		case SDL_KEYDOWN:
        
			// Gestion des touches
			switch(m_Evenements.key.keysym.scancode)
			{
				case SDL_SCANCODE_ESCAPE:
						m_bQuit = true;
				break;
			}

		break;
	}

       
}

void CScene::Draw(float fDeltatime)
{
	// Nettoyage de l'écran
	glClear(GL_COLOR_BUFFER_BIT);

	for(int i = 0 ; i < m_nNbShapes ; ++i)
		m_pShape[i]->Draw(fDeltatime);

	// On désactive le tableau Vertex Attrib puisque l'on n'en a plus besoin
	glDisableVertexAttribArray(0);

	// Actualisation de la fenêtre
	SDL_GL_SwapWindow(m_pWindow);
}

void CScene::QuitApplication()
{
	SDL_GL_DeleteContext(m_ContexteOpenGL);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
}

void CScene::InitSDL()
{
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
	
	
    // Création de la fenêtre
    m_pWindow = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ms_nWidth, ms_nHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(m_pWindow == 0)
    {
        std::cout << "Error window creation: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit( EXIT_FAILURE );
    }

    // Création du contexte OpenGL
    m_ContexteOpenGL = SDL_GL_CreateContext(m_pWindow);
    if(m_ContexteOpenGL == 0)
    {
		std::cout << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		exit( EXIT_FAILURE );
    }


    if (glewInit() != GLEW_OK)
    {
		std::cout << "Failed to initialize GLEW" << std::endl;
		SDL_GL_DeleteContext(m_ContexteOpenGL);
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		exit( EXIT_FAILURE );
    }
}