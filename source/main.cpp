#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "FrameBuffer.h"
#include "Camera.h"
#include "Renderer.h"
#include "Model.h"
#include "RenderWindow.h"
#include "DirectionalLight.h"

// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

int main(int argc, char* argv[])
{

	std::shared_ptr<RenderWindow> winApp = RenderWindow::GetInstance(SCR_WIDTH, SCR_HEIGHT, "Soft Rasterizer");

	if (winApp == nullptr)
	{
		return -1;
	}

	// glfw: initialize and configure
	// ------------------------------
// 	glfwInit();
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
// 	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	// glfw window creation
//	// --------------------
// 	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
// 	if (window == NULL)
// 	{
// 		std::cout << "Failed to create GLFW window" << std::endl;
// 		glfwTerminate();
// 		return 0;
// 	}
// 	glfwMakeContextCurrent(window);
// 	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
// 
// 	// glad: load all OpenGL function pointers
// 	// ---------------------------------------
// 	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
// 	{
// 		std::cout << "Failed to initialize GLAD" << std::endl;
// 		return 0;
// 	}

	Renderer renderer(SCR_WIDTH,SCR_HEIGHT);
	Camera camera;
	//Model myModel("./Model/AssimpResource/nanosuit.obj");
	Model myModel("./Model/diablo3_pose/diablo3_pose.obj");

	auto viewMatrix = camera.GetViewMatrix();
	auto projection = Renderer::CalculateProjectionMatrix(camera.GetCameraFov(), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.001f, 1000.0f);
	auto pv = projection * viewMatrix;
	renderer.SetViewMatrix(viewMatrix);
	renderer.SetProjectionMatrix(Renderer::CalculateProjectionMatrix(camera.GetCameraFov(), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.001f, 1000.0f));

	auto directionalLight = std::make_shared<DirectionalLight>();
	renderer.SetDirectionalLight(directionalLight);

	//这里将会使用第三方库加载模型，可能会定义一个数据结构去
	//存储顶点数据。

	winApp->ReadyToStart();

	// render loop
	// -----------
	//while (!glfwWindowShouldClose(window))
	while (!winApp->ShouldWindowClose())
	{
		// input
		// -----
// 		processInput(window);
// 		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
// 		glClear(GL_COLOR_BUFFER_BIT);

		winApp->ProcessEvent();

		renderer.ClearColor({ 0.2f, 0.3f, 0.3f,1.0f });

		//在这里将会实现软渲染器的渲染管线，替代OpenGL的渲染管线。预计是做一套可编程管线。
		//具体步骤包括顶点着色器处理，图元装配，裁剪，背面剔除，光栅化，片元着色器处理，深度测试。
		renderer.Render(myModel);


		//绘制到屏幕上
		double deltaTime = winApp->UpdateScreenSurface(
			renderer.GetRenderedColorBuffer(),
			SCR_WIDTH,
			SCR_HEIGHT,
			4);


// 		if (winApp->GetIsMouseLeftButtonPressed())
// 		{
// 			int deltaX = winApp->GetMouseMotionDeltaX();
// 			int deltaY = winApp->GetMouseMotionDeltaY();
// 			glm::mat4 cameraRotMat(1.0f);
// 			if (std::abs(deltaX) > std::abs(deltaY))
// 				cameraRotMat = glm::rotate(glm::mat4(1.0f), -deltaX * 0.001f, glm::vec3(0, 1, 0));
// 			else
// 				cameraRotMat = glm::rotate(glm::mat4(1.0f), -deltaY * 0.001f, glm::vec3(1, 0, 0));
// 
// 			cameraPos = glm::vec3(cameraRotMat * glm::vec4(cameraPos, 1.0f));
// 			renderer->setViewMatrix(TRUtils::calcViewMatrix(cameraPos, lookAtTarget, glm::vec3(0.0, 1.0, 0.0f)));
// 		}

		//Camera zoom in and zoom out
		if (winApp->GetMouseWheelDelta() != 0)
		{
			auto cameraDirection = camera.GetCameraDirection();
			auto newPosition = camera.GetCameraPosition() +  cameraDirection * (winApp->GetMouseWheelDelta() * 0.1f);
			camera.SetCameraPosition(newPosition);

			if ((newPosition - camera.GetCameraTarget()).Length() > 1.0f)
			{
				renderer.SetViewMatrix(camera.GetViewMatrix());
			}
		}
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
//	glfwTerminate();

	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, true);
//	}
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}