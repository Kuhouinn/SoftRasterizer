#include "FrameBuffer.h"
#include "Camera.h"
#include "Renderer.h"
#include "Model.h"
#include "RenderWindow.h"
#include "DirectionalLight.h"

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

int main(int argc, char* argv[])
{

	std::shared_ptr<RenderWindow> winApp = RenderWindow::GetInstance(SCR_WIDTH, SCR_HEIGHT, "Soft Rasterizer");

	if (winApp == nullptr)
	{
		return -1;
	}

	Renderer renderer(SCR_WIDTH,SCR_HEIGHT);
	Camera camera;


	auto viewMatrix = camera.GetViewMatrix();
	auto projection = Renderer::CalculateProjectionMatrix(camera.GetCameraFov(), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.001f, 1000.0f);

	renderer.SetViewMatrix(viewMatrix);
	renderer.SetProjectionMatrix(projection);

	auto directionalLight = std::make_shared<DirectionalLight>();
	renderer.SetDirectionalLight(directionalLight);

	//这里将会使用第三方库加载模型，可能会定义一个数据结构去
	//存储顶点数据。
	Model myModel("./Model/diablo3_pose/diablo3_pose.obj");

	winApp->ReadyToStart();

	// render loop
	while (!winApp->ShouldWindowClose())
	{
		winApp->ProcessEvent();

		renderer.ClearColor({ 0.2f, 0.3f, 0.3f,1.0f });

		renderer.SetRasterizerLine(winApp->GetPressP());

		//在这里将会实现软渲染器的渲染管线，替代OpenGL的渲染管线。预计是做一套可编程管线。
		//具体步骤包括顶点着色器处理，图元装配，裁剪，背面剔除，光栅化，片元着色器处理，深度测试。
		renderer.Render(myModel);

		//绘制到屏幕上
		double deltaTime = winApp->UpdateScreenSurface(
			renderer.GetRenderedColorBuffer(),
			SCR_WIDTH,
			SCR_HEIGHT,
			4);

		//给光源一个旋转，好观察
		Matrix4 lightRotateMatrix;
		auto cosTheta = std::cos(deltaTime * 0.0008f);
		auto sinTheta = std::sin(deltaTime * 0.0008f);
		lightRotateMatrix.m[0][0] = cosTheta;
		lightRotateMatrix.m[0][2] = sinTheta;
		lightRotateMatrix.m[2][0] = -sinTheta;
		lightRotateMatrix.m[2][2] = cosTheta;

		auto newDirection = lightRotateMatrix * Vector4(directionalLight->direction);
		directionalLight->direction = { newDirection.x,newDirection.y,newDirection.z };

		//按住鼠标左键旋转模型
		if (winApp->GetIsMouseLeftButtonPressed())
		{
			int deltaX = winApp->GetMouseMotionDeltaX();
			int deltaY = winApp->GetMouseMotionDeltaY();
			Matrix4 rotateMatrix;

			if (std::abs(deltaX) > std::abs(deltaY))
			{
				auto cosTheta = std::cos(-deltaX * 0.005f);
				auto sinTheta = std::sin(-deltaX * 0.005f);
				rotateMatrix.m[0][0] = cosTheta;
				rotateMatrix.m[0][2] = sinTheta;
				rotateMatrix.m[2][0] = -sinTheta;
				rotateMatrix.m[2][2] = cosTheta;
			}
			else
			{
				auto cosTheta = std::cos(-deltaY * 0.005f);
				auto sinTheta = std::sin(-deltaY * 0.005f);
				rotateMatrix.m[1][1] = cosTheta;
				rotateMatrix.m[1][2] = -sinTheta;
				rotateMatrix.m[2][1] = sinTheta;
				rotateMatrix.m[2][2] = cosTheta;
			}
			auto result = rotateMatrix * Vector4{ camera.GetCameraPosition() };
			camera.SetCameraPosition({ result.x,result.y,result.z });
			renderer.SetViewMatrix(camera.GetViewMatrix());
		}

		//Camera zoom in and zoom out
		if (winApp->GetMouseWheelDelta() != 0)
		{
			auto cameraDirection = camera.GetCameraDirection();
			auto newPosition = camera.GetCameraPosition() +  cameraDirection * (winApp->GetMouseWheelDelta() * 0.1f);
			camera.SetCameraPosition(newPosition);

			if ((newPosition - camera.GetCameraTarget()).Length() > 0.0001f)
			{
				renderer.SetViewMatrix(camera.GetViewMatrix());
			}
		}
	}

	return 0;
}