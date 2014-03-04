#include <iostream>
#include "../user/user.h"
#include "Scene.h"
#include "../Tools/Timer.h"
#include "../imgui/imgui.h"
#include "../imgui/imguiRenderGL3.h"
#include "../shapes/triangle.h"
#include "../shapes/cube.h"

int CScene::ms_nWidth = 1024;
int CScene::ms_nHeight = 768;
CCamera CScene::ms_Camera;
SDL_Window* CScene::m_pWindow = nullptr;

const float SGUIStates::MOUSE_PAN_SPEED = 0.001f;
const float SGUIStates::MOUSE_ZOOM_SPEED = 0.05f;
const float SGUIStates::MOUSE_TURN_SPEED = 0.005f;

// Font buffers
extern const unsigned char DroidSans_ttf[];
extern const unsigned int DroidSans_ttf_len;   

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
	InitImgui();

	//Camera
    ms_Camera.camera_defaults(ms_Camera);

	m_guiStates.init_gui_states();
	
	m_pShape[0] = new CCube(10000);
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

	ProcessCamera(fDeltatime);
}

void CScene::Draw(float fDeltatime)
{
    // Default states
    glEnable(GL_DEPTH_TEST);

    // Clear the front buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(int i = 0 ; i < m_nNbShapes ; ++i)
		m_pShape[i]->Draw(fDeltatime);

	DrawGUI(fDeltatime);
	// Actualisation de la fenêtre
	SDL_GL_SwapWindow(m_pWindow);
}

void CScene::QuitApplication()
{
    imguiRenderGLDestroy();
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

void CScene::InitImgui()
{
	if (!imguiRenderGLInit(DroidSans_ttf, DroidSans_ttf_len))
    {
        fprintf(stderr, "Could not init GUI renderer.\n");
        exit(EXIT_FAILURE);
    }

	DrawGUI(1.0f);
}

void CScene::DrawGUI(float fDeltatime)
{
#ifdef DEBUG
	// Draw UI
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0, 0, ms_nWidth, ms_nHeight);
	
    unsigned char mbut = 0;
    int mscroll = 0;
    int mousex; int mousey;
    SDL_GetMouseState(&mousex, &mousey);
    mousey = ms_nHeight - mousey;

    imguiBeginFrame(mousex, mousey, mbut, mscroll);
    int logScroll = 0;
    char lineBuffer[512];
    imguiBeginScrollArea("Debug info", ms_nWidth - 210, ms_nHeight - 310, 200, 300, &logScroll);
    sprintf(lineBuffer, "FPS %f", 1.0f/fDeltatime);
    imguiLabel(lineBuffer);
    imguiEndScrollArea();
    imguiEndFrame();
    imguiRenderGLDraw(ms_nWidth, ms_nHeight); 

    glDisable(GL_BLEND);
#endif //DEBUG
}

void CScene::ProcessCamera(float fDeltatime)
{
	
	// Mouse states
	bool leftButton = SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1);
	bool rightButton = SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3);
	bool middleButton = SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(2);

	if(leftButton)
		m_guiStates.turnLock = true;
	else
		m_guiStates.turnLock = false;

	if( rightButton)
		m_guiStates.zoomLock = true;
	else
		m_guiStates.zoomLock = false;

	if( middleButton)
		m_guiStates.panLock = true;
	else
		m_guiStates.panLock = false;

	// Camera movements
	int altPressed = true;//glfwGetKey(GLFW_KEY_LSHIFT);
	if (!altPressed && (leftButton || rightButton || middleButton))
	{
		int x; int y;
		SDL_GetMouseState(&x, &y);
		m_guiStates.lockPositionX = x;
		m_guiStates.lockPositionY = y;
	}
	if (altPressed)
	{
		int mousex; int mousey;
		SDL_GetMouseState(&mousex, &mousey);
		int diffLockPositionX = mousex - m_guiStates.lockPositionX;
		int diffLockPositionY = mousey - m_guiStates.lockPositionY;
		if (m_guiStates.zoomLock)
		{
			float zoomDir = 0.0;
			if (diffLockPositionX > 0)
				zoomDir = -1.f;
			else if (diffLockPositionX < 0 )
				zoomDir = 1.f;
			ms_Camera.camera_zoom(ms_Camera, zoomDir * SGUIStates::MOUSE_ZOOM_SPEED);
		}
		else if (m_guiStates.turnLock)
		{
			ms_Camera.camera_turn(ms_Camera, diffLockPositionY * SGUIStates::MOUSE_TURN_SPEED,
						diffLockPositionX * SGUIStates::MOUSE_TURN_SPEED);

		}
		else if (m_guiStates.panLock)
		{
			ms_Camera.camera_pan(ms_Camera, diffLockPositionX * SGUIStates::MOUSE_PAN_SPEED,
						diffLockPositionY * SGUIStates::MOUSE_PAN_SPEED);
		}
		m_guiStates.lockPositionX = mousex;
		m_guiStates.lockPositionY = mousey;
	}
	
}