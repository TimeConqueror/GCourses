#pragma once
#include "Utils.h"
#include "InputController.h"
#include <windows.h>

class Window {
private:
    InputController& inputController;
    // Handle to the programs executable module (the .exe file in memory)
    LPCWSTR name;
    // uid of window
    HWND hWnd;
    // window class information
    WNDCLASSEX wc;

    uint width;
    uint height;

public:
    Window(InputController& inputController, LPCWSTR name, uint width, uint height);
private:
    static Window& getInstance();
    static LRESULT CALLBACK handleMessage(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
public:
    void init();
    uint getWidth() const;
    uint getHeight() const;
    HWND getHWnd();
};
