#include "Mesh.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

CMesh::CMesh(CVertex * aVertices, unsigned int n, CShader * pShader)
{
	m_nVertices = n;
	m_pShader = pShader;

	GLuint idPosition = m_pShader->GetAttributeLocation("position");
	GLuint idColor = m_pShader->GetAttributeLocation("color");

	glGenVertexArrays(1, &m_idArrayObject);
	glBindVertexArray(m_idArrayObject);

	glGenBuffers(1, &m_idBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_idBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CVertex) * m_nVertices, aVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(idPosition);
	glVertexAttribPointer(idPosition, 3, GL_FLOAT, GL_FALSE, sizeof(CVertex), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(idColor);
	glVertexAttribPointer(idColor, 4, GL_FLOAT, GL_FALSE, sizeof(CVertex), BUFFER_OFFSET(sizeof(glm::vec3)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

CMesh::~CMesh()
{
}

auto CMesh::Draw()->void
{
	m_pShader->Bind();
	glBindVertexArray(m_idArrayObject);

	glDrawArrays(GL_TRIANGLE_FAN, 0, m_nVertices);

	glBindVertexArray(0);
	m_pShader->UnBind();
}
