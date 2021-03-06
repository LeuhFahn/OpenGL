#ifndef __SCENE_H
#define __SCENE_H

#include "../Tools/GLCommon.h"
#include "../shapes/shape.h"
#include "../Tools/Camera.h"

class CScene
{
public:
	static int ms_nWidth;
	static int ms_nHeight;
	static CCamera ms_Camera;
	static SDL_Window* m_pWindow;
	SGUIStates m_guiStates;

private:
	int m_nNbShapes;
	CShape** m_pShape;
	bool m_bQuit;
	
	SDL_Event m_Evenements;
    SDL_GLContext m_ContexteOpenGL;
	
	void InitSDL();
	void InitImgui();
	void DrawGUI(float fDeltatime);
	void ProcessCamera(float fDeltatime);
public:
	CScene();
	~CScene();

	void Init();
	void Process(float fDeltatime);
	void Draw(float fDeltatime);
	void QuitApplication();

	bool GetQuit() {return m_bQuit;}
};

#endif // __SCENE_H