
#include "shape3D.h"
#include "../Scene/Scene.h"

CShape3D::CShape3D()
{

}

CShape3D::~CShape3D()
{

}

void CShape3D::Draw(float fDeltatime)
{
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
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, m_pfVertices);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);
}