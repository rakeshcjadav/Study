#include "Vertex.h"


CVertex::CVertex(const glm::vec3 & pos, const glm::vec4 & color)
{
	m_position = pos;
	m_color = color;
}

CVertex::~CVertex()
{
}
