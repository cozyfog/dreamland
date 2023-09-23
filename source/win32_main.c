#define _UTILS_WIN32
#define _WIN32_MAIN_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <objbase.h>
#include <windows.h>
#include <xinput.h>
#include <math.h>
#include "gl/glew.h"
#include "typedef.h"
#include "utils.h"
#include "win32_main.h"

// Game code.
#include "dreamland.h"
#include "physics.h"
#include "render.h"
#include "vector.h"
#include "core.h"
#include "input.h"

// Win32 external modules.
#include "win32_controller.h"

global bool running;

internal LRESULT win32WindowCallback(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
	LRESULT result = 0;
	
	switch (message) {
		case WM_SIZE: {
			glViewport(0, 0, LOWORD(lparam), HIWORD(lparam));
			break;
		}
		
		// ERROR(daniel): Only executes on exception.
		case WM_DESTROY: {
			assert(!running, "Fatal Error: Window destroyed forcefully, exception thrown.");
			running = false;
			break;
		}
		
		case WM_CLOSE: {
			running = false;
			break;
		}
		
		case WM_ACTIVATEAPP: {
			break;
		}
		
		case WM_PAINT: {
			PAINTSTRUCT paint;
			BeginPaint(window, &paint);
			EndPaint(window, &paint);
			break;
		}
		
		// NOTE(daniel): useless
		/*case WM_SYSKEYDOWN: {
			sprintf(msg, "%lp", wparam);
			OutputDebugString(msg);
			OutputDebugString("\n");
			break;
		}
		
		case WM_SYSKEYUP: {
			sprintf(msg, "%lp", wparam);
			OutputDebugString(msg);
			OutputDebugString("\n");
			break;
		}*/
		
		case WM_KEYDOWN: {
			inputKeyPressCallback(wparam);
			break;
		}
		
		case WM_KEYUP: {
			inputKeyReleaseCallback(wparam);
			break;
		}
		
		default: {
			result = DefWindowProc(window, message, wparam, lparam);
			break;
		}
	}
	
	return result;
}

i32 APIENTRY WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR cmd_line, i32 show_code) {
	// Loading Win32 external modules.
	if (win32LoadXInput()) {
		OutputDebugString("Loaded Xinput dll.\n");
	} else {
		OutputDebugString("Failed to load XInput dll.\nController input not supported.\n");
	}
	
	// Win32 window.
	WNDCLASS window_class = {0};
	HWND window_handle;
	
	HDC device_context;
	HGLRC opengl_context;
	
	PIXELFORMATDESCRIPTOR pfd;
	i32 pixel_format;
	
	// ERROR(daniel): Window class registration.
	window_class.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	window_class.lpfnWndProc = win32WindowCallback;
	window_class.hInstance = instance;
	window_class.lpszClassName = "OpenGLWindow";
	
	assert(RegisterClass(&window_class), "Error: Window class registration.");
	
	// ERROR(daniel): Creating window handle.
	window_handle = CreateWindowEx(0, window_class.lpszClassName, "dreamland", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, WIN32_WINDOW_WIDTH, WIN32_WINDOW_HEIGHT, 0, 0, instance, 0);
	assert(window_handle, "Error: Creating window handle.");
	
	// Remove window maximize button.
	//SetWindowLong(window_handle, GWL_STYLE, GetWindowLong(window_handle, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	
	// ERROR(daniel): Getting device context.
	device_context = GetDC(window_handle);
	assert(device_context, "Error: Getting device context.");
	
	// Creating pixel format.
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize      = sizeof(pfd);
	pfd.nVersion   = 1;
	pfd.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	
	// ERROR(daniel): Choosing pixel format.
	pixel_format = ChoosePixelFormat(device_context, &pfd);
	assert(pixel_format, "Error: Choosing pixel format.");
	
	// ERROR(daniel): Setting pixel format.
	assert(SetPixelFormat(device_context, pixel_format, &pfd), "Error: Setting pixel format.");
	DescribePixelFormat(device_context, pixel_format, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
	
	// ERROR(daniel): Creating OpenGL context.
	opengl_context = wglCreateContext(device_context);
	assert(opengl_context, "Error: Creating OpenGL context.");
	wglMakeCurrent(device_context, opengl_context);
	
	// ERROR(daniel): Modern OpenGL initialisation.
	assert(glewInit() == GLEW_OK, "Error: GLEW initialisation.");
	renderEntry();
	
	// Dreamland initialisation.
	running = true;
	dreamlandEntry();
	physicsEntry();
	
	// Window main loop.
	ShowWindow(window_handle, show_code);
	while (running) {
		MSG message;
		
		while (PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		
		if (message.message == WM_QUIT) {
			running = false;
		}
		
		for (DWORD controller_index = 0; controller_index < XUSER_MAX_COUNT; ++controller_index) {
			Win32InputProfile profile = win32GetControllerProfile(controller_index);
			
			profile.stick_x *= 0.0001;
			profile.stick_y *= 0.0001;
			
			//win32ExecuteControllerCallback(profile);
		}
		
		coreUpdateTime();
		dreamlandUpdate();
		physicsUpdate();
		renderUpdate();
		
		UpdateWindow(window_handle);
	}
	
	return 0;
}