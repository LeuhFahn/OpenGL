#include <iostream>
#include "Tools/GLCommon.h"
#include "Tools/ShaderGLSL.h"

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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Creating a window and context
	GLFWwindow* window = glfwCreateWindow(nWidth, nHeight, "openGL", NULL, NULL);
	//GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", glfwGetPrimaryMonitor(), NULL); //for fullscreen
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Making the OpenGL context current
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
         fprintf( stderr, "Failed to initialize GLEW\n" );
         exit( EXIT_FAILURE );
    }

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	 // Try to load and compile shader
    int status;
    ShaderGLSL base_shader;
    status = load_shader_from_file(base_shader, "../shaders/base.glsl", ShaderGLSL::VERTEX_SHADER | ShaderGLSL::FRAGMENT_SHADER);
    if ( status == -1 )
    {
        fprintf(stderr, "Error on loading  shader/base.glsl\n");
        exit( EXIT_FAILURE );
    }

	//Geometrie
/*	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	GLfloat vertices[] = { -0.5, -0.5, 1, 0, 0, 0.5, -0.5, 0, 1, 0, 0, 0.5, 0, 0, 1 };

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), 
		vertices, GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	// glVertexAttribPointer(index, size, type, normalized, stride, pointer)
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,  5 * sizeof(GLfloat), 0 * sizeof(GLfloat));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  5 * sizeof(GLfloat), (const GLvoid*) (2 * sizeof(GLfloat)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
*/
	float vertices[] = {-0.5, -0.5,   0.0, 0.5,   0.5, -0.5};

	while (!glfwWindowShouldClose(window))
	{
		/*glViewport( 0, 0, nWidth, nHeight  );
		glClear(GL_COLOR_BUFFER_BIT);

		// Bind gbuffer shader
        glUseProgram(base_shader.program);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);*/

		glClear(GL_COLOR_BUFFER_BIT);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);


		// On affiche le triangle

		glDrawArrays(GL_TRIANGLES, 0, 3);


		// On désactive le tableau Vertex Attrib puisque l'on en a plus besoin

		glDisableVertexAttribArray(0);


        glfwSwapBuffers(window);
        glfwPollEvents();
	}
/*
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
*/
	//terminating GLFW
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}