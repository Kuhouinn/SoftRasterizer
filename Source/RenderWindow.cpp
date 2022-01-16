#include "RenderWindow.h"

#include <iostream>
#include <iomanip>

std::shared_ptr<RenderWindow> RenderWindow::instance = nullptr;

bool RenderWindow::Setup(int width, int height, std::string title)
{
	screenWidth = width;
	screenHeight = height;
	windowTitle = title;

	lastMouseX = 0;
	lastMouseY = 0;
	mouseDeltaX = 0;
	mouseDeltaY = 0;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	//Create window
	windowHandle = SDL_CreateWindow(
		windowTitle.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth,
		screenHeight,
		SDL_WINDOW_SHOWN);

	if (windowHandle == nullptr)
	{
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	//Get window surface
	screenSurface = SDL_GetWindowSurface(windowHandle);

	return true;
}

RenderWindow::~RenderWindow()
{
	//Destroy window
	SDL_DestroyWindow(windowHandle);
	windowHandle = nullptr;

	//Quit SDL subsystems
	SDL_Quit();
}

void RenderWindow::ReadyToStart()
{
	timer.Start();
	lastTimePoint = timer.GetTicks();

	fps = 0;
	fpsCounter = 0.0f;
	fpsTimeRecorder = 0.0f;
}

void RenderWindow::ProcessEvent()
{
	wheelDelta = 0;
	//Handle events queue
	while (SDL_PollEvent(&events) != 0)
	{
		//Quit the program
		if (events.type == SDL_QUIT || (
			events.type == SDL_KEYDOWN && events.key.keysym.sym == SDLK_ESCAPE))
		{
			quit = true;
		}

		if (events.type == SDL_MOUSEMOTION)
		{
			static bool firstEvent = true;
			if (firstEvent)
			{
				firstEvent = false;
				lastMouseX = events.motion.x;
				lastMouseY = events.motion.y;
				mouseDeltaX = 0;
				mouseDeltaY = 0;
			}
			else
			{
				mouseDeltaX = events.motion.x - lastMouseX;
				mouseDeltaY = events.motion.y - lastMouseY;
				lastMouseX = events.motion.x;
				lastMouseY = events.motion.y;
			}
		}

		if (events.type == SDL_MOUSEBUTTONDOWN && events.button.button == SDL_BUTTON_LEFT)
		{
			mouseLeftButtonPressed = true;
			lastMouseX = events.motion.x;
			lastMouseY = events.motion.y;
			mouseDeltaX = 0;
			mouseDeltaY = 0;
		}

		if (events.type == SDL_MOUSEBUTTONUP && events.button.button == SDL_BUTTON_LEFT)
		{
			mouseLeftButtonPressed = false;
		}

		if (events.type == SDL_MOUSEWHEEL)
		{
			wheelDelta = events.wheel.y;
		}

		if (events.type == SDL_KEYDOWN && events.key.keysym.sym == SDLK_p)
		{
			pressP = !pressP;
		}
	}
}

double RenderWindow::UpdateScreenSurface(
	const unsigned int* pixels,
	int width,
	int height,
	int channel)
{
	//Update pixels
	SDL_LockSurface(screenSurface);
	{
		Uint32* destPixels = (Uint32*)screenSurface->pixels;

		long length = width * height * 4;
		memcpy(destPixels, pixels, length);

// 		for (int i = 0; i < width * height; ++i)
// 		{
// //  			int index = i * channel;
// // 			Uint32 color = SDL_MapRGB(
// // 				screenSurface->format,
// // 				static_cast<uint8_t>(*(pixels+index)),
// // 				static_cast<uint8_t>(*(pixels+index + 1)),
// // 				static_cast<uint8_t>(*(pixels+index + 2)));
// //  			*(destPixels+i) = color;
// 
// // 			Uint32 color = SDL_MapRGB(
// // 				screenSurface->format,
// // 				static_cast<uint8_t>(pixels[index + 0]),
// // 				static_cast<uint8_t>(pixels[index + 1]),
// // 				static_cast<uint8_t>(pixels[index + 2]));
// // 			destPixels[i] = color;
// 		}
	}
	SDL_UnlockSurface(screenSurface);
	SDL_UpdateWindowSurface(windowHandle);

	deltaTime = timer.GetTicks() - lastTimePoint;
	lastTimePoint = timer.GetTicks();

	//FPS counting
	{
		fpsTimeRecorder += deltaTime;
		++fpsCounter;
		if (fpsTimeRecorder > 1000.0)
		{
			fps = static_cast<unsigned int>(fpsCounter);
			fpsCounter = 0.0f;
			fpsTimeRecorder = 0.0f;

			std::stringstream ss;
			ss << " FPS:" << std::setiosflags(std::ios::left) << std::setw(3) << fps;
			SDL_SetWindowTitle(windowHandle, (windowTitle + ss.str()).c_str());
		}
	}

	return deltaTime;
}

std::shared_ptr<RenderWindow> RenderWindow::GetInstance()
{
	if (instance == nullptr)
	{
		return GetInstance(800, 600, "WinApp");
	}
	return instance;
}

std::shared_ptr<RenderWindow> RenderWindow::GetInstance(int width, int height, const std::string title)
{
	if (instance == nullptr)
	{
		instance = std::shared_ptr<RenderWindow>(new RenderWindow());
		if (!instance->Setup(width, height, title))
		{
			return nullptr;
		}
	}
	return instance;
}

//-------------------------------------------Timer---------------------------------------------------

RenderWindow::LTimer::LTimer()
{
	//Initialize the variables
	startTicks = 0;
	pausedTicks = 0;

	paused = false;
	started = false;
}

void RenderWindow::LTimer::Start()
{
	//Start the timer
	started = true;

	//Unpause the timer
	paused = false;

	//Get the current clock time
	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void RenderWindow::LTimer::Stop()
{
	//Stop the timer
	started = false;

	//Unpause the timer
	paused = false;

	//Clear tick variables
	startTicks = 0;
	pausedTicks = 0;
}

void RenderWindow::LTimer::Pause()
{
	//If the timer is running and isn't already paused
	if (started && !paused)
	{
		//Pause the timer
		paused = true;

		//Calculate the paused ticks
		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void RenderWindow::LTimer::Unpause()
{
	//If the timer is running and paused
	if (started && paused)
	{
		//Unpause the timer
		paused = false;

		//Reset the starting ticks
		startTicks = SDL_GetTicks() - pausedTicks;

		//Reset the paused ticks
		pausedTicks = 0;
	}
}

Uint32 RenderWindow::LTimer::GetTicks()
{
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (started)
	{
		//If the timer is paused
		if (paused)
		{
			//Return the number of ticks when the timer was paused
			time = pausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - startTicks;
		}
	}

	return time;
}