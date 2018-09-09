#pragma once

#include "stdafx.h"

class CShader
{
public:
	CShader(const char * vertex_program, const char * fragment_program);
	~CShader();

	auto Bind() -> void;
	auto UnBind() -> void;

	auto GetAttributeLocation(const char * name)->GLuint;

private:
	auto CompileErrorCheck(GLuint id) -> void;
	auto LinkingErrorCheck(GLuint id) -> void;

private:
	GLuint	m_id;
};

