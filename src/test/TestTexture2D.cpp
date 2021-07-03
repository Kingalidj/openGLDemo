#include "TestTexture2D.h"

#include "Renderer.h"
#include <GL/glew.h>

#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace test
{

	TestTexture2D::TestTexture2D()
		: m_TranslationA(200, 200, 0), m_TranslationB(200, 400, 0),
		m_Proj(glm::ortho(0.0f, 1200.0f, 0.0f, 1200.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_ScaleA(1.0f), m_ScaleB(1.0f)
	{
		float positions[] = {
			-50.0f, -50.0f, 0.0f, 0.0f,//0
			50.0f,  -50.0f, 1.0f, 0.0f,//1
			50.0f,  50.0f, 1.0f, 1.0f,//2
			-50.0f, 50.0f, 0.0f, 1.0f //3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_VAO = std::make_unique<VertexArray>();

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

		m_Texture = std::make_unique<Texture>("res/textures/cat.jpg");
		m_Shader->SetUniform1i("u_Texture", 0);
	}

	TestTexture2D::~TestTexture2D()
	{

	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{

	}

	void TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		m_Texture->Bind();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			model = glm::scale(model, glm::vec3(m_ScaleA, m_ScaleA, 0));
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			model = glm::scale(model, glm::vec3(m_ScaleB, m_ScaleB, 0));
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat2("Translation A", &m_TranslationA.x, 0.0f, 1200.0f);
		ImGui::SliderFloat("Scale A", &m_ScaleA, 0.0f, 10.0f);
		ImGui::SliderFloat2("Translation B", &m_TranslationB.x, 0.0f, 1200.0f);
		ImGui::SliderFloat("Scale B", &m_ScaleB, 0.0f, 10.0f);
	}

}
