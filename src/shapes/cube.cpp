#include "cube.h"
#include <cstdio>
#include <iostream>
#include "../Scene/Scene.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../stb/stb_image.h"

CCube::CCube()
{
	m_nNbVertices = 12;
	m_fTime = 0.0f;

	glGenVertexArrays(1, &m_Vao);
	glGenBuffers(4, m_Vbo);

    int cube_triangleList[] = {0, 1, 2, 2, 1, 3, 4, 5, 6, 6, 5, 7, 8, 9, 10, 10, 9, 11, 12, 13, 14, 14, 13, 15, 16, 17, 18, 19, 17, 20, 21, 22, 23, 24, 25, 26, };
    float cube_uvs[] = {0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, 0.f,  1.f, 0.f,  1.f, 1.f,  0.f, 1.f,  1.f, 1.f,  0.f, 0.f, 0.f, 0.f, 1.f, 1.f,  1.f, 0.f,  };
    float cube_vertices[] = {-0.5, -0.5, 0.5, 0.5, -0.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, 0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, 0.5, -0.5, 0.5, 0.5 };
    float cube_normals[] = {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, };


	float pfVertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f};

	glBindVertexArray(m_Vao);
    // Bind indices and upload data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Vbo[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_triangleList), cube_triangleList, GL_STATIC_DRAW);
    // Bind vertices and upload data
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[1]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*3, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
    // Bind normals and upload data
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[2]);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*3, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_normals), cube_normals, GL_STATIC_DRAW);
    // Bind uv coords and upload data
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[3]);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*2, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_uvs), cube_uvs, GL_STATIC_DRAW);
		
	glGenTextures(1, m_pTextures);
    int x;
    int y;
    int comp; 
    unsigned char * diffuse = stbi_load("../textures/spnza_bricks_a_diff.tga", &x, &y, &comp, 3);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_pTextures[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, diffuse);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    fprintf(stderr, "Diffuse %dx%d:%d\n", x, y, comp);

    const char * shaderFile = "../shaders/Diffuse.glsl";
    int status = load_shader_from_file(m_Shader, shaderFile, SShaderGLSL::VERTEX_SHADER | SShaderGLSL::FRAGMENT_SHADER);
    if ( status == -1 )
    {
        fprintf(stderr, "Error on loading  %s\n", shaderFile);
        exit( EXIT_FAILURE );
    }
	// Apply shader
	// GLuint program = shader.program;
	glUseProgram(m_Shader.program);
	projectionLocation = glGetUniformLocation(m_Shader.program, "Projection");
	viewLocation = glGetUniformLocation(m_Shader.program, "View");
	objectLocation = glGetUniformLocation(m_Shader.program, "Object");
	timeLocation = glGetUniformLocation(m_Shader.program, "Time");
	diffuseLocation = glGetUniformLocation(m_Shader.program, "Diffuse");
}

CCube::~CCube()
{

}

void CCube::Draw(float fDeltatime)
{
	m_fTime += fDeltatime;

		// Get camera matrices
	glm::mat4 projection = glm::perspective(45.0f, (float)CScene::ms_nWidth / CScene::ms_nHeight, 0.1f, 100.f); 
    glm::mat4 worldToView = glm::lookAt(CScene::ms_Camera.eye, CScene::ms_Camera.o,  CScene::ms_Camera.up);
    glm::mat4 objectToWorld;
    glm::mat4 worldToScreen = projection * worldToView;
    glm::mat4 screenToWorld = glm::transpose(glm::inverse(worldToScreen));

	glUseProgram(m_Shader.program);
	glUniform1f(timeLocation, m_fTime);
	glUniformMatrix4fv(projectionLocation, 1, 0, glm::value_ptr(projection));
	glUniformMatrix4fv(viewLocation, 1, 0, glm::value_ptr(worldToView));
	glUniformMatrix4fv(objectLocation, 1, 0, glm::value_ptr(objectToWorld));
	glUniform1i(diffuseLocation, 0);

	// Bind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_pTextures[0]);

	// Render vaos
    glBindVertexArray(m_Vao);
    glDrawElementsInstanced(GL_TRIANGLES, m_nNbVertices * 3, GL_UNSIGNED_INT, (void*)0, 4);
}