#pragma once
#include "Window.h"
#include "Timer.h"
#include "Graphics/RenderManager.h"
#include "InputController.h"
#include <windows.h>
#include <WinUser.h>
#include <wrl.h>
#include <d3d.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <chrono>

class Game {
private:
	static Game* instance;

	const LPCWSTR name;	
	InputController inputController;
	Window window;
	RenderManager renderManager;
	Timer timer;
public:
	Game(LPCWSTR name, uint width, uint height, int ticksPerSecond = 20);

	static Game* getInstance();
	static bool isReady();
	void run();
	float getPartialTick();

	Window& getWindow();
	RenderManager& getRenderManager();

	/**
     * Singletons should not be cloned.
     */
	Game(Game& other) = delete;
	/**
	 * Singletons should not be assignable.
	 */
	void operator=(const Game&) = delete;

protected:
	virtual void init() = 0;
	virtual void tick() = 0;

private:
	static void setInstance(Game* game);
	void initInternals();
};