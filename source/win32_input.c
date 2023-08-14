#include "win32_input.h"

void (*win32_controller_callback)(Win32InputProfile);

void win32ExecuteControllerCallback(Win32InputProfile profile) {
	win32_controller_callback(profile);
}

void win32SetControllerCallback(void (*callback)(Win32InputProfile)) {
	win32_controller_callback = callback;
}