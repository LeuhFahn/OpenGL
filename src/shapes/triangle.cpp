#include "triangle.h"
#include <cstdio>
#include <iostream>
#include "../Scene/Scene.h"

CTriangle::CTriangle()
{
	m_nNbVertices = 6;
	m_fTime = 0.0f;
	float pfVertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f};

	SetVertices(pfVertices);

		
    const char * shaderFile = "../shaders/simple.glsl";
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
}

CTriangle::~CTriangle()
{

}

void CTriangle::Draw(float fDeltatime)
{
	m_fTime += fDeltatime;

	// Get camera matrices
	glm::mat4 projection = glm::perspective(45.0f, (float)CScene::ms_nWidth / CScene::ms_nHeight, 0.1f, 100.f); 
	glm::mat4 worldToView = glm::lookAt(CScene::ms_Camera.eye, CScene::ms_Camera.o, CScene::ms_Camera.up);
    glm::mat4 objectToWorld;

		// Select shader
    glUseProgram(m_Shader.program);

		// Upload uniforms
    glUniformMatrix4fv(projectionLocation, 1, 0, glm::value_ptr(projection));
    glUniformMatrix4fv(viewLocation, 1, 0, glm::value_ptr(worldToView));
    glUniformMatrix4fv(objectLocation, 1, 0, glm::value_ptr(objectToWorld));
	glUniform1f(timeLocation, m_fTime);


	CShape::Draw(fDeltatime);
}