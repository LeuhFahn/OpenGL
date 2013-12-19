#include <iostream>

//#define GLFW_DLL
#include <GLFW\glfw3.h>

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
	int nWidth = 1024, nHeight = 768;

	// Initializing GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

	//Creating a window and context
	GLFWwindow* window = glfwCreateWindow(nWidth, nHeight, "My Title", NULL, NULL);
	//GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", glfwGetPrimaryMonitor(), NULL); //for fullscreen

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Making the OpenGL context current
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	while (!glfwWindowShouldClose(window))
	{
		float ratio;

        glfwGetFramebufferSize(window, &nWidth, &nHeight);
        ratio = nWidth / (float) nHeight;

        glViewport(0, 0, nWidth, nHeight);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

        glBegin(GL_TRIANGLES);
			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(-0.6f, -0.4f, 0.f);
			glColor3f(0.f, 1.f, 0.f);
			glVertex3f(0.6f, -0.4f, 0.f);
			glColor3f(0.f, 0.f, 1.f);
			glVertex3f(0.f, 0.6f, 0.f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
	}

	//terminating GLFW
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}