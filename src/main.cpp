
#include <GLEW/glew.h>
#include <SDL/SDL.h>
#include <iostream>

#include "user/user.h"
#include "Scene/Scene.h"
#include "Tools/Timer.h"

int main(int argc, char **argv)
{	
	CScene Scene;
	Scene.Init();   
	// Boucle principale

	CTimer timer;
	timer.start();
	float fTimeStart = 0;
	float fTimeEnd = 0;
	float fEllapsedTime = 0.0f;
	float fps = 60.0f;
	int nNbFrames = 0;
	float fDeltatime = 0.0f;
	while(!Scene.GetQuit())
	{
		// Gestion des évènements
		// Récupération d'un évènement
		fDeltatime = 1.0f/fps;
		Scene.Process(fDeltatime);
		Scene.Draw(fDeltatime);

		// Gestion compteur
        fTimeEnd = timer.getTicks() / 1000.0f;
        fEllapsedTime = fTimeEnd - fTimeStart;
		
		if(fEllapsedTime > 1.0f)
		{
			fps = float(nNbFrames)/fEllapsedTime;
			nNbFrames = 0;
			fTimeStart = timer.getTicks() / 1000.0f;
		}
		else 
		{
			++nNbFrames;
		}
	}

	Scene.QuitApplication();
	
    return 0;
}