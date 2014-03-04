
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

	while(!Scene.GetQuit())
	{

		int pute = timer.getTicks();
		// Gestion des évènements
		// Récupération d'un évènement
		Scene.Process(1.0f/60.0f);
		Scene.Draw(1.0f/60.0f);
	}

	Scene.QuitApplication();
	
    return 0;
}