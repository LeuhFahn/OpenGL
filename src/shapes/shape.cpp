
#include "shape.h"

CShape::CShape()
{

}

CShape::~CShape()
{

}


void CShape::SetVertices(float* pfVertices)
{
	delete m_pfVertices;
	m_pfVertices = new float[2*m_nNbVertices];

	for (int i = 0 ; i < 2*m_nNbVertices ; ++i)
		m_pfVertices[i] = pfVertices[i];
}

void CShape::SetColors(float* pfColors)
{
	delete m_pfColors;
	m_pfColors = new float[3*m_nNbVertices];

	for (int i = 0 ; i < 3*m_nNbVertices ; ++i)
		m_pfColors[i] = pfColors[i];
}


void CShape::Draw(float fDeltatime)
{

}