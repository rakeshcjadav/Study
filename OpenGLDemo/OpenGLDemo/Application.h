#pragma once

#include "stdafx.h"
#include "Mesh.h"

class CApplication
{
public:
	CApplication();
	CApplication(int iWidth, int iHeight);
	~CApplication();

	static auto OnKeyDown(GLFWwindow* window, int key, int scancode, int action, int mods) -> void;
	static auto OnMouseMove(GLFWwindow* window, double x, double y) -> void;
	static auto OnMouseDown(GLFWwindow* window, int button, int action, int mods) -> void;

	auto Start() -> void;

	auto Draw() -> void;

private:
	GLFWwindow * m_pWindow;

	int m_iWidth;
	int m_iHeight;

	std::list<CMesh *>		m_aMesh;
	CShader *				m_pShader;
};

