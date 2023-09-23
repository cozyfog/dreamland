#ifndef WIN32_CONTROLLER_H
#define WIN32_CONTROLLER_H

#include <windows.h>
#include <xinput.h>
#include "typedef.h"
/*
internal void win32VibrationEnable(DWORD controller_index) {
	XINPUT_VIBRATION vibration;
	vibration.wLeftMotorSpeed = vibration.wRightMotorSpeed = 30000;
	XInputSetState(controller_index, &vibration);
}

internal void win32VibrationDisable(DWORD controller_index) {
	XINPUT_VIBRATION vibration;
	vibration.wLeftMotorSpeed = vibration.wRightMotorSpeed = 0;
	XInputSetState(controller_index, &vibration);
}*/

class(Win32InputProfile) {
	DWORD index;
	
	bool dpad_up;
	bool dpad_down;
	bool dpad_left;
	bool dpad_right;
	
	bool start;
	bool back;
	
	bool shoulder_left;
	bool shoulder_right;
	
	bool button_a;
	bool button_b;
	bool button_x;
	bool button_y;
	
	i16 stick_x;
	i16 stick_y;
};

void win32ExecuteControllerCallback(Win32InputProfile profile);
void win32SetControllerCallback(void (*callback)(Win32InputProfile));

#if defined(_WIN32_MAIN_C)
#define XINPUT_GET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_STATE *pState)
#define XINPUT_SET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_VIBRATION *pVibration)

typedef XINPUT_GET_STATE(xinput_get_state);
typedef XINPUT_SET_STATE(xinput_set_state);

XINPUT_GET_STATE(XInputGetStateStub) {
	return 0;
}

XINPUT_SET_STATE(XInputSetStateStub) {
	return 0;
}

#undef XInputGetState
#undef XInputSetState
#define XInputGetState DY_XInputGetState
#define XInputSetState DY_XInputSetState

global xinput_get_state *DY_XInputGetState = XInputGetStateStub;
global xinput_set_state *DY_XInputSetState = XInputSetStateStub;
/* XInput Costum Include and Ovveride using DLL */

internal bool win32LoadXInput() {
	CoInitialize(NULL);
	HMODULE library = LoadLibrary("Xinput1_4.dll");
	
	if (!library) {
		HMODULE library = LoadLibrary("Xinput1_3.dll");
	}
	
	if (!library) {
		HMODULE library = LoadLibrary("Xinput9_1_0.dll");
	}
	
	if (library) {
		XInputGetState = (xinput_get_state*)GetProcAddress(library, "XInputGetState");
		XInputSetState = (xinput_set_state*)GetProcAddress(library, "XInputSetState");
		
		return true;
	}
	
	return false;
}

internal Win32InputProfile win32GetControllerProfile(DWORD controller_index) {
	XINPUT_STATE controller_state;
	Win32InputProfile profile = {0};
	profile.index = controller_index;
	
	if (XInputGetState(controller_index, &controller_state) == ERROR_SUCCESS) {
		XINPUT_GAMEPAD *gamepad = &controller_state.Gamepad;
		
		profile.dpad_up    = (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_UP);
		profile.dpad_down  = (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
		profile.dpad_left  = (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
		profile.dpad_right = (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
		
		profile.start = (gamepad->wButtons & XINPUT_GAMEPAD_START);
		profile.back  = (gamepad->wButtons & XINPUT_GAMEPAD_BACK);
		
		profile.shoulder_left  = (gamepad->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
		profile.shoulder_right = (gamepad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
		
		profile.button_a = (gamepad->wButtons & XINPUT_GAMEPAD_A);
		profile.button_b = (gamepad->wButtons & XINPUT_GAMEPAD_B);
		profile.button_x = (gamepad->wButtons & XINPUT_GAMEPAD_X);
		profile.button_y = (gamepad->wButtons & XINPUT_GAMEPAD_Y);
		
		profile.stick_x = gamepad->sThumbLX;
		profile.stick_y = gamepad->sThumbLY;
	}
	
	return profile;
}
#endif

#endif //WIN32_CONTROLLER_H