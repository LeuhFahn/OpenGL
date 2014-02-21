#ifndef __SCENE_H
#define __SCENE_H


#include "../Tools/GLCommon.h"
#include "../shapes/shape.h"
#include "../shapes/triangle.h"
#include "../Tools/ShaderGLSL.h"
#include "../Tools/Camera.h"
#include <vector>

class CScene
{
private:
	int m_nWidth;
	int m_nHeight;
	int m_nNbShapes;
	CShape** m_pShape;
	bool m_bQuit;

	SDL_Event m_Evenements;
	SDL_Window* m_pWindow;
    SDL_GLContext m_ContexteOpenGL;
	
	void InitSDL();

public:
	CScene();
	~CScene();

	void Init();
	void Process(float fDeltatime);
	void Draw();
	void QuitApplication();

	bool GetQuit() {return m_bQuit;}
};

#endif // __SCENE_H