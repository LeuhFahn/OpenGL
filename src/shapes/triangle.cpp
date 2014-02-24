#include "triangle.h"
#include <cstdio>
#include <iostream>
#include "../Scene/Scene.h"

CTriangle::CTriangle()
{
	m_nNbVertices = 3;
	m_fTime = 0.0f;
	float pfVertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f};
	float pfColors[] = {1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0};

	SetVertices(pfVertices);
	SetColors(pfColors);
		
    const char * shaderFile = "../shaders/simple2D.glsl";
    int status = load_shader_from_file(m_Shader, shaderFile, SShaderGLSL::VERTEX_SHADER | SShaderGLSL::FRAGMENT_SHADER);
    if ( status == -1 )
    {
        fprintf(stderr, "Error on loading  %s\n", shaderFile);
        exit( EXIT_FAILURE );
    }
	
	// Apply shader
	glUseProgram(m_Shader.program);
	timeLocation = glGetUniformLocation(m_Shader.program, "Time");
}

CTriangle::~CTriangle()
{

}

void CTriangle::Draw(float fDeltatime)
{
	m_fTime += fDeltatime;

		// Select shader
    glUseProgram(m_Shader.program);

		// Upload uniforms
	glUniform1f(timeLocation, m_fTime);

	CShape2D::Draw(fDeltatime);
}