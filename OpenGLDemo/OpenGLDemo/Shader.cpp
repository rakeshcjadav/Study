#include "Shader.h"

CShader::CShader(const char * vertex_program, const char * fragment_program)
{
	m_id = glCreateProgram();
	GLuint vId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fId = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vId, 1, &vertex_program, nullptr);
	glShaderSource(fId, 1, &fragment_program, nullptr);

	glCompileShader(vId);
	glCompileShader(fId);

	CompileErrorCheck(vId);
	CompileErrorCheck(fId);

	glAttachShader(m_id, vId);
	glAttachShader(m_id, fId);

	glLinkProgram(m_id);

	LinkingErrorCheck(m_id);

	glUseProgram(m_id);
}

CShader::~CShader()
{
}

auto CShader::Bind() -> void
{
	glUseProgram(m_id);
}

auto CShader::UnBind() -> void
{
	glUseProgram(0);
}

auto CShader::GetAttributeLocation(const char * name) -> GLuint
{
	Bind();
	GLuint id = glGetAttribLocation(m_id, name);
	UnBind();
	return id;
}

auto CShader::CompileErrorCheck(GLuint id) -> void
{
	GLint comp;
	glGetShaderiv(id, GL_COMPILE_STATUS, &comp);

	if (comp == GL_FALSE) {
		cout << "Shader Compilation FAILED" << endl;
		GLchar messages[256];
		glGetShaderInfoLog(id, sizeof(messages), 0, &messages[0]);
		cout << messages;
	}
}

auto CShader::LinkingErrorCheck(GLuint id) -> void
{
	GLint linkStatus, validateStatus;
	glGetProgramiv(id, GL_LINK_STATUS, &linkStatus);

	if (linkStatus == GL_FALSE) {
		cout << "Shader Linking FAILED" << endl;
		GLchar messages[256];
		glGetProgramInfoLog(id, sizeof(messages), 0, &messages[0]);
		cout << messages;
	}

	glValidateProgram(id);
	glGetProgramiv(id, GL_VALIDATE_STATUS, &validateStatus);

	cout << "Link: " << linkStatus << "  Validate: " << validateStatus << endl;
	if (linkStatus == GL_FALSE) {
		cout << "Shader Validation FAILED" << endl;
		GLchar messages[256];
		glGetProgramInfoLog(id, sizeof(messages), 0, &messages[0]);
		cout << messages;
	}
}
