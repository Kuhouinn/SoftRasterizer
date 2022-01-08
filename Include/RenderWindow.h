#ifndef TRWINDOWSAPP_H
#define TRWINDOWSAPP_H

#include "SDL2/SDL.h"

#include <string>
#include <sstream>
#include <memory>

class RenderWindow
{
private:
	RenderWindow() = default;

	RenderWindow(RenderWindow&) = delete;
	RenderWindow& operator=(const RenderWindow&) = delete;

	bool Setup(int width, int height, std::string title);

public:

	//Timer
	class LTimer
	{
	public:
		//Initializes variables
		LTimer();

		//The various clock actions
		void Start();
		void Stop();
		void Pause();
		void Unpause();

		//Gets the timer's time
		Uint32 GetTicks();

		//Checks the status of the timer
		bool IsStarted() { return started; }
		bool IsPaused() { return paused && started; }

	private:
		//The clock time when the timer started
		Uint32 startTicks;

		//The ticks stored when the timer was paused
		Uint32 pausedTicks;

		//The timer status
		bool paused;
		bool started;
	};

	~RenderWindow();

	void ReadyToStart();

	//Event
	void ProcessEvent();
	bool ShouldWindowClose() const { return quit; }
	double GetTimeFromStart() { return timer.GetTicks(); }
	int GetMouseMotionDeltaX() const { return mouseDeltaX; }
	int GetMouseMotionDeltaY() const { return mouseDeltaY; }
	int GetMouseWheelDelta() const { return wheelDelta; }
	bool GetIsMouseLeftButtonPressed() const { return mouseLeftButtonPressed; }

	bool GetPressP() const { return pressP; }

	//Copy the rendered image to screen for displaying
	double UpdateScreenSurface(
		const unsigned char* pixels,
		int width,
		int height,
		int channel);

	static std::shared_ptr<RenderWindow> GetInstance();
	static std::shared_ptr<RenderWindow> GetInstance(int width, int height, const std::string title = "winApp");

private:

	//Mouse tracking
	int lastMouseX, lastMouseY;
	int mouseDeltaX, mouseDeltaY;
	bool mouseLeftButtonPressed = false;
	int lastWheelPos;
	int wheelDelta;

	bool pressP = false;

	//Timer
	LTimer timer;
	double lastTimePoint;
	double deltaTime;
	double fpsCounter;
	double fpsTimeRecorder;
	unsigned int fps;

	//Screen size
	int screenWidth;
	int screenHeight;

	bool quit = false;

	//Window title
	std::string windowTitle;

	//Event handler
	SDL_Event events;

	//Window handler
	SDL_Window* windowHandle = nullptr;
	SDL_Surface* screenSurface = nullptr;

	//Singleton pattern
	static std::shared_ptr<RenderWindow> instance;
};

#endif
