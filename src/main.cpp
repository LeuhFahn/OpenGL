
#include <GLEW/glew.h>
#include <SDL/SDL.h>
#include <iostream>

#include "user/user.h"
#include "Scene/Scene.h"
#include "shapes/triangle.h"

int main(int argc, char **argv)
{	
	
    // Notre fenêtre
	
   CScene Scene;
   Scene.Init();   

    // Boucle principale
	while(!Scene.GetQuit())
    {
        // Gestion des évènements
		// Récupération d'un évènement
		Scene.Process(1);
		Scene.Draw();
    }

	Scene.QuitApplication();
    return 0;
}