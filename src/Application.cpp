#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "test/TestClearColor.h"
#include "test/TestTexture2D.h"
#include "test/Test.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	

	/* Create a windowed mode window and its OpenGL context */
	int width = 1200;
	int height = 1200;
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		std::cout << "Error !" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	{
		//float positions[] = {
		//	-50.0f, -50.0f, 0.0f, 0.0f,//0
		//	50.0f,  -50.0f, 1.0f, 0.0f,//1
		//	50.0f,  50.0f, 1.0f, 1.0f,//2
		//	-50.0f, 50.0f, 0.0f, 1.0f //3
		//};

		//unsigned int indices[] = {
		//	0, 1, 2,
		//	2, 3, 0
		//};


		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		//VertexBuffer vb(positions, 4 * 4 * sizeof(float));
		//IndexBuffer ib(indices, 6);

		//VertexArray va;
		//VertexBufferLayout layout;
		//layout.Push<float>(2);
		//layout.Push<float>(2);
		//va.AddBuffer(vb, layout);

		//glm::mat4 proj = glm::ortho(0.0f, (float) width, 0.0f, (float) height, -1.0f,1.0f);
		//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));


		//Shader shader("res/shaders/Basic.shader");
		//shader.Bind();
		//shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

		//Texture texture("res/textures/cat.jpg");
		//texture.Bind();
		//shader.SetUniform1i("u_Texture", 0);
		//
		//float r = 0.0f;
		//float increment = 0.05f;

		//ib.Unbind();
		//va.Unbind();
		//shader.Unbind();

		Renderer renderer;

		/* ImGui init */
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;

		testMenu->RegisterTest<test::TestClearColor>("Clear Color");
		testMenu->RegisterTest<test::TestTexture2D>("Test Texture 2D");

		//test::TestClearColor test;

		//glm::vec3 translationA(200, 200, 0);
		//glm::vec3 translationB(100, 200, 0);
		//glm::vec4 colorA(1.0f, 1.0f, 1.0f, 1.0f);
		//glm::vec4 colorB(1.0f, 1.0f, 1.0f, 1.0f);
		//float scale = 1.0f;

		while (!glfwWindowShouldClose(window))
		{

			/* Render here */
			//glClear(GL_COLOR_BUFFER_BIT);
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			renderer.Clear();

			//test.OnUpdate(0.0f);
			//test.OnRender();

			/* ImGui new Frame */
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (currentTest)
			{
				currentTest->OnUpdate(0.0f);
				currentTest->OnRender();
				ImGui::Begin("Test");
				if (currentTest != testMenu && ImGui::Button("<-"))
				{
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();
				ImGui::End();
			}

			//test.OnImGuiRender();

			//{
			//	glm::mat4 model = glm::mat4(1.0f);
			//	model = glm::translate(model, translationA);
			//	model = glm::scale(model, glm::vec3(scale, scale, 0));
			//	glm::mat4 mvp = proj * view * model;

			//	shader.Bind();
			//	shader.SetUniform4f("u_Color", colorA.r, colorA.g, colorA.b, colorA.a);
			//	shader.SetUniformMat4f("u_MVP", mvp);

			//	renderer.Draw(va, ib, shader);
			//}

			//{
			//	glm::mat4 model = glm::mat4(1.0f);
			//	model = glm::translate(model, translationB);
			//	model = glm::scale(model, glm::vec3(scale, scale, 0));
			//	glm::mat4 mvp = proj * view * model;

			//	shader.Bind();
			//	shader.SetUniform4f("u_Color", colorB.r, colorB.g, colorB.b, colorB.a);
			//	shader.SetUniformMat4f("u_MVP", mvp);

			//	renderer.Draw(va, ib, shader);
			//}


			//if (r > 1.0f) {
			//	increment = -0.05f;
			//}
			//else if (r < 0.0f) {
			//	increment = 0.05f;
			//}
			//r += increment;

			//{
			//	ImGui::Begin("attributes");
			//	ImGui::SetWindowFontScale(1.8f);
			//	ImGui::SliderFloat3("Translation A ", &translationA.x, 0.0f, 960.0f);
			//	ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f);
			//	ImGui::SliderFloat("Scale", &scale, 0.0f, 10.0f);
			//	ImGui::ColorEdit4("colorA", &colorA.r);
			//	ImGui::ColorEdit4("colorB", &colorB.r);
			//	ImGui::Text("Application average %.3f FPS", ImGui::GetIO().Framerate);
			//	ImGui::End();
			//}

			/* ImGui render */
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);

			glfwPollEvents();
		}

		delete currentTest;
		if(currentTest != testMenu)
			delete testMenu;
	}

	//glDeleteProgram(shader); 
	/* ImGui shutdown */


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}