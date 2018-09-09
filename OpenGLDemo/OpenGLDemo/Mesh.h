#pragma once
#include "stdafx.h"
#include "Vertex.h"
#include "Shader.h"

class CMesh
{
public:
	CMesh(CVertex * aVertices, unsigned int n, CShader * pShader);
	~CMesh();

	auto Draw()->void;

private:
	GLuint			m_idArrayObject;
	GLuint			m_idBuffer;
	unsigned int	m_nVertices;
	CShader *		m_pShader;
};

