#include "Application.h"

const char vertet_program[] =
"#version 330\n"

"in vec4 position;\n"
"in vec4 color;\n"

"out vec4 oColor;\n"

"void main()\n"
"{\n"
	"gl_Position = position;\n"
	"oColor = color;\n"
"}\n"
;

const char fragment_program[] =
"#version 330\n"

"in vec4 oColor;\n"

"out vec4 finalColor;\n"

"void main()\n"
"{\n"
	"finalColor = oColor;\n"
"}\n"
;

CApplication::CApplication() :
	CApplication(1280, 720)
{

}

CApplication::CApplication(int iWidth, int iHeight) :
	m_iWidth(iWidth),
	m_iHeight(iHeight)
{
	glfwInit();

	m_pWindow = glfwCreateWindow(m_iWidth, m_iHeight, "Hello World", nullptr, nullptr);
	if (m_pWindow == nullptr)
	{
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_pWindow);

	glewInit();

	cout << "OpenGL Version : " << glGetString(GL_VERSION) << endl;
	cout << "GLSL Version : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEFT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLineWidth(3.0f);

	//register callbacks for keyboard and mouse
	glfwSetKeyCallback(m_pWindow, CApplication::OnKeyDown);
	glfwSetCursorPosCallback(m_pWindow, CApplication::OnMouseMove);
	glfwSetMouseButtonCallback(m_pWindow, CApplication::OnMouseDown);

	m_pShader = new CShader(vertet_program, fragment_program);

	CVertex aVertices[3] = {
		CVertex(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),
		CVertex(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),
		CVertex(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))
	};
	m_aMesh.push_back(new CMesh(aVertices, 3, m_pShader));

	CVertex aVertices2[3] = {
		CVertex(glm::vec3(0.0f, 1.0f, -0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f)),
		CVertex(glm::vec3(1.0f, 0.0f, -0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f)),
		CVertex(glm::vec3(0.0f, -1.0f, -0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f))
	};

	m_aMesh.push_back(new CMesh(aVertices2, 3, m_pShader));
}

CApplication::~CApplication()
{
	glfwTerminate();
}

auto CApplication::OnKeyDown(GLFWwindow* window, int key, int scancode, int action, int mods) -> void
{
	cout << key << " " << scancode << " " << action << " " << mods << endl;
}

auto CApplication::OnMouseMove(GLFWwindow* window, double x, double y) -> void
{
	cout << "X " << x << " Y " << y << endl;
}

auto CApplication::OnMouseDown(GLFWwindow* window, int button, int action, int mods) -> void
{
	cout << button << " " << action << " " << mods << endl;
}

auto CApplication::Start() -> void
{
	while (!glfwWindowShouldClose(m_pWindow))
	{
		glfwGetFramebufferSize(m_pWindow, &m_iWidth, &m_iHeight);
		glViewport(0, 0, m_iWidth, m_iHeight);

		glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Draw();

		glfwSwapBuffers(m_pWindow);

		glfwPollEvents();
	}
}

auto CApplication::Draw() -> void
{
	for (CMesh * pMesh : m_aMesh)
	{
		pMesh->Draw();
	}
}
