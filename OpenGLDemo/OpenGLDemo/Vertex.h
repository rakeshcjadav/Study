#pragma once

#include "stdafx.h"

class CVertex
{
public:
	CVertex(const glm::vec3 & pos, const glm::vec4 & color);
	~CVertex();

	glm::vec3	m_position;
	glm::vec4	m_color;
};

