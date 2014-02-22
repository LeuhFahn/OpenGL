
#include "shape.h"

CShape::CShape()
{
	m_pfVertices = nullptr;
}

CShape::~CShape()
{
	delete m_pfVertices;
}

void CShape::SetVertices(float* pfVertices)
{
	delete m_pfVertices;
	m_pfVertices = new float[m_nNbVertices];

	for (int i = 0 ; i < m_nNbVertices ; ++i)
		m_pfVertices[i] = pfVertices[i];
}

void CShape::Draw(float fDeltatime)
{
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, m_pfVertices);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}