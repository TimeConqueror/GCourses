#include "Window.h"
#include "Game.h"
#include <iostream>

Window::Window(InputController& inputController, LPCWSTR name, uint width, uint height)
	:inputController(inputController), name(name), width(width), height(height) {
	HINSTANCE hInstance = GetModuleHandle(nullptr);

	WNDCLASSEX wc;

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = handleMessage;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = name;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	this->wc = wc;

	RECT windowRect = {0, 0, static_cast<LONG>(width), static_cast<LONG>(height)};
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	auto dwStyle = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME;

	auto posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	auto posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

	this->hWnd = CreateWindowEx(WS_EX_APPWINDOW, name, name,
							   dwStyle,
							   posX, posY,
							   windowRect.right - windowRect.left,
							   windowRect.bottom - windowRect.top,
							   nullptr, nullptr, hInstance, this);
}

Window& Window::getInstance() {
	return Game::getInstance()->getWindow();
}

LRESULT Window::handleMessage(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
	if (message == WM_DESTROY) {
		PostQuitMessage(0);
		return 0;
	}

	Window* window;

	if (message == WM_CREATE) {
		const auto create_struct = reinterpret_cast<CREATESTRUCT*>(lparam);
		window = static_cast<Window*>(create_struct->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
	} else {
		window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	switch (message) {
		case WM_KEYDOWN:
		{
			uint keyCode = static_cast<uint>(wparam);
			window->inputController.setKeyPressed(keyCode);
			return 0;
		}
		case WM_KEYUP:
		{
			uint keyCode = static_cast<uint>(wparam);
			window->inputController.setKeyReleased(keyCode);
			return 0;
		}
		case WM_SIZE:
		{
			window->width = LOWORD(lparam);
			window->height = HIWORD(lparam);
			return 0;
		}
		case WM_MOUSEMOVE:
		{
			window->inputController.setMousePos(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
			return 0;
		}
		default:
		{
			return DefWindowProc(hwnd, message, wparam, lparam);
		}
	}


}

void Window::init() {
	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	ShowCursor(true);
}

uint Window::getWidth() const {
	return width;
}

uint Window::getHeight() const {
	return height;
}

HWND Window::getHWnd() {
	return hWnd;
}
