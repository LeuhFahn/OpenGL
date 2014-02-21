#include "triangle.h"

CTriangle::CTriangle()
{
	m_nNbVertices = 6;
	float pfVertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f};

	SetVertices(pfVertices);
}

CTriangle::~CTriangle()
{

}

