
#include "shape2D.h"

CShape2D::CShape2D()
{
	m_pfVertices = nullptr;
	m_pfColors = nullptr;
	m_nNbVertices = 0;
}

CShape2D::~CShape2D()
{
	delete m_pfVertices;
	delete m_pfColors;
}


void CShape2D::Draw(float fDeltatime)
{
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, m_pfVertices);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, m_pfColors);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	//glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(0);
}