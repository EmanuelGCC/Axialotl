//===================================//
//  This file defines and declares   //
//  a couple of enums and functions  //
//  used for input processing, this  //
//  includes mouse, keyboard,        //
//  and controller inputs.           //
//===================================//

#pragma once

#include "../../dependencies/deps.h"

	//=========//
	//  Enums  //
	//=========//

typedef enum {
	AXIA_KEY_ESCAPE      = GLFW_KEY_ESCAPE,
	AXIA_KEY_F1          = GLFW_KEY_F1,
	AXIA_KEY_F2          = GLFW_KEY_F2,
	AXIA_KEY_F3          = GLFW_KEY_F3,
	AXIA_KEY_F4          = GLFW_KEY_F4,
	AXIA_KEY_F5          = GLFW_KEY_F5,
	AXIA_KEY_F6          = GLFW_KEY_F6,
	AXIA_KEY_F7          = GLFW_KEY_F7,
	AXIA_KEY_F8          = GLFW_KEY_F8,
	AXIA_KEY_F9          = GLFW_KEY_F9,
	AXIA_KEY_F10         = GLFW_KEY_F10,
	AXIA_KEY_F11         = GLFW_KEY_F11,
	AXIA_KEY_F12         = GLFW_KEY_F12,
	AXIA_KEY_PRINTSCREEN = GLFW_KEY_PRINT_SCREEN,
	AXIA_KEY_PAUSE       = GLFW_KEY_PAUSE,
	AXIA_KEY_HOME        = GLFW_KEY_HOME,
	AXIA_KEY_PAGE_UP     = GLFW_KEY_PAGE_UP,
	AXIA_KEY_PAGE_DOWN   = GLFW_KEY_PAGE_DOWN,
	AXIA_KEY_END         = GLFW_KEY_END,

	AXIA_KEY_GRAVE_ACCENT  = GLFW_KEY_GRAVE_ACCENT,
	AXIA_KEY_1             = GLFW_KEY_1,
	AXIA_KEY_2             = GLFW_KEY_2,
	AXIA_KEY_3             = GLFW_KEY_3,
	AXIA_KEY_4             = GLFW_KEY_4,
	AXIA_KEY_5             = GLFW_KEY_5,
	AXIA_KEY_6             = GLFW_KEY_6,
	AXIA_KEY_7             = GLFW_KEY_7,
	AXIA_KEY_8             = GLFW_KEY_8,
	AXIA_KEY_9             = GLFW_KEY_9,
	AXIA_KEY_0             = GLFW_KEY_0,
	AXIA_KEY_MINUS         = GLFW_KEY_MINUS,
	AXIA_KEY_PLUS          = GLFW_KEY_EQUAL,
	AXIA_KEY_BACKSPACE     = GLFW_KEY_BACKSPACE,
	AXIA_KEY_NUMLOCK       = GLFW_KEY_NUM_LOCK,
	AXIA_KEYPAD_DIVIDE     = GLFW_KEY_KP_DIVIDE,
	AXIA_KEYPAD_MULTIPLY   = GLFW_KEY_KP_MULTIPLY,
	AXIA_KEYPAD_SUBSTRACT  = GLFW_KEY_KP_SUBTRACT,

	AXIA_KEY_TAB       = GLFW_KEY_TAB,
	AXIA_KEY_Q         = GLFW_KEY_Q,
	AXIA_KEY_W         = GLFW_KEY_W,
	AXIA_KEY_E         = GLFW_KEY_E,
	AXIA_KEY_R         = GLFW_KEY_R,
	AXIA_KEY_T         = GLFW_KEY_T,
	AXIA_KEY_Y         = GLFW_KEY_Y,
	AXIA_KEY_U         = GLFW_KEY_U,
	AXIA_KEY_I         = GLFW_KEY_I,
	AXIA_KEY_O         = GLFW_KEY_O,
	AXIA_KEY_P         = GLFW_KEY_P,
	AXIA_KEY_LBRACKET  = GLFW_KEY_LEFT_BRACKET,
	AXIA_KEY_RBRACKET  = GLFW_KEY_RIGHT_BRACKET,
	AXIA_KEY_BACKSLASH = GLFW_KEY_BACKSLASH,
	AXIA_KEYPAD_7      = GLFW_KEY_KP_7,
	AXIA_KEYPAD_8      = GLFW_KEY_KP_8,
	AXIA_KEYPAD_9      = GLFW_KEY_KP_9,
	AXIA_KEYPAD_PLUS   = GLFW_KEY_KP_ADD,

	AXIA_KEY_CAPSLOCK   = GLFW_KEY_CAPS_LOCK,
	AXIA_KEY_A          = GLFW_KEY_A,
	AXIA_KEY_S          = GLFW_KEY_S,
	AXIA_KEY_D          = GLFW_KEY_D,
	AXIA_KEY_F          = GLFW_KEY_F,
	AXIA_KEY_G          = GLFW_KEY_G,
	AXIA_KEY_H          = GLFW_KEY_H,
	AXIA_KEY_J          = GLFW_KEY_J,
	AXIA_KEY_K          = GLFW_KEY_K,
	AXIA_KEY_L          = GLFW_KEY_L,
	AXIA_KEY_SEMICOLON  = GLFW_KEY_SEMICOLON,
	AXIA_KEY_APOSTROPHE = GLFW_KEY_APOSTROPHE,
	AXIA_KEY_ENTER      = GLFW_KEY_BACKSPACE,
	AXIA_KEYPAD_4       = GLFW_KEY_KP_4,
	AXIA_KEYPAD_5       = GLFW_KEY_KP_5,
	AXIA_KEYPAD_6       = GLFW_KEY_KP_6,

	AXIA_KEY_LSHIFT    = GLFW_KEY_LEFT_SHIFT,
	AXIA_KEY_Z         = GLFW_KEY_Z,
	AXIA_KEY_X         = GLFW_KEY_X,
	AXIA_KEY_C         = GLFW_KEY_C,
	AXIA_KEY_V         = GLFW_KEY_V,
	AXIA_KEY_B         = GLFW_KEY_B,
	AXIA_KEY_N         = GLFW_KEY_N,
	AXIA_KEY_M         = GLFW_KEY_M,
	AXIA_KEY_COMMA     = GLFW_KEY_COMMA,
	AXIA_KEY_PERIOD    = GLFW_KEY_PERIOD,
	AXIA_KEY_SLASH     = GLFW_KEY_SLASH,
	AXIA_KEY_RSHIFT    = GLFW_KEY_RIGHT_SHIFT,
	AXIA_KEYPAD_1      = GLFW_KEY_KP_1,
	AXIA_KEYPAD_2      = GLFW_KEY_KP_2,
	AXIA_KEYPAD_3      = GLFW_KEY_KP_3,
	AXIA_KEYPAD_ENTER  = GLFW_KEY_KP_ENTER,

	AXIA_KEY_LCONTROL   = GLFW_KEY_LEFT_CONTROL,
	AXIA_KEY_LSUPER     = GLFW_KEY_LEFT_SUPER,
	AXIA_KEY_LALT       = GLFW_KEY_LEFT_ALT,
	AXIA_KEY_KEY_SPACE  = GLFW_KEY_SPACE,
	AXIA_KEY_RALT       = GLFW_KEY_RIGHT_ALT,
	AXIA_KEY_RSUPER     = GLFW_KEY_RIGHT_SUPER,
	AXIA_KEY_RCONTROL   = GLFW_KEY_RIGHT_CONTROL,
	AXIA_KEY_LEFT       = GLFW_KEY_LEFT,
	AXIA_KEY_RIGHT      = GLFW_KEY_RIGHT,
	AXIA_KEY_UP         = GLFW_KEY_UP,
	AXIA_KEY_DOWN       = GLFW_KEY_DOWN,
	AXIA_KEYPAD_0       = GLFW_KEY_KP_0,
	AXIA_KEYPAD_DECIMAL = GLFW_KEY_KP_DECIMAL,

	AXIA_KEY_SPACE         = GLFW_KEY_SPACE,
	AXIA_KEY_EQUAL         = GLFW_KEY_EQUAL,
	AXIA_KEY_WORLD1        = GLFW_KEY_WORLD_1,
	AXIA_KEY_WORLD2        = GLFW_KEY_WORLD_2,
	AXIA_KEY_INSERT        = GLFW_KEY_INSERT,
	AXIA_KEY_DELETE        = GLFW_KEY_DELETE,
	AXIA_KEY_CAPS_LOCK     = GLFW_KEY_CAPS_LOCK,
	AXIA_KEY_SCROLL_LOCK   = GLFW_KEY_SCROLL_LOCK,
	AXIA_KEY_NUM_LOCK      = GLFW_KEY_NUM_LOCK,
	AXIA_KEY_PRINT_SCREEN  = GLFW_KEY_PRINT_SCREEN,

	AXIA_KEY_F13 = GLFW_KEY_F13,
	AXIA_KEY_F14 = GLFW_KEY_F14,
	AXIA_KEY_F15 = GLFW_KEY_F15,
	AXIA_KEY_F16 = GLFW_KEY_F16,
	AXIA_KEY_F17 = GLFW_KEY_F17,
	AXIA_KEY_F18 = GLFW_KEY_F18,
	AXIA_KEY_F19 = GLFW_KEY_F19,
	AXIA_KEY_F20 = GLFW_KEY_F20,
	AXIA_KEY_F21 = GLFW_KEY_F21,
	AXIA_KEY_F22 = GLFW_KEY_F22,
	AXIA_KEY_F23 = GLFW_KEY_F23,
	AXIA_KEY_F24 = GLFW_KEY_F24,
	AXIA_KEY_F25 = GLFW_KEY_F25,
	
	AXIA_KEYPAD_SUBTRACT  = GLFW_KEY_KP_SUBTRACT,
	AXIA_KEYPAD_ADD       = GLFW_KEY_KP_ADD,
	AXIA_KEYPAD_EQUAL     = GLFW_KEY_KP_EQUAL,
	AXIA_KEY_LEFT_SHIFT   = GLFW_KEY_LEFT_SHIFT,
	AXIA_KEY_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
	AXIA_KEY_LEFT_ALT     = GLFW_KEY_LEFT_ALT,
	AXIA_KEY_LEFT_SUPER   = GLFW_KEY_LEFT_SUPER,
	AXIA_KEY_RIGHT_SHIFT  = GLFW_KEY_RIGHT_SHIFT,
	AXIA_KEY_RIGHT_CONTRO = GLFW_KEY_RIGHT_CONTROL,
	AXIA_KEY_RIGHT_ALT    = GLFW_KEY_RIGHT_ALT,
	AXIA_KEY_RIGHT_SUPER  = GLFW_KEY_RIGHT_SUPER,
	AXIA_KEY_MENU         = GLFW_KEY_MENU,
} AxiaKeyInput;

typedef enum {
	AXIA_PRESSED  = GLFW_PRESS,
	AXIA_RELEASED = GLFW_RELEASE,
	AXIA_REPEAT   = GLFW_REPEAT,
} AxiaInputEvent;

typedef enum {
	AXIA_HAT_CENTERED = GLFW_HAT_CENTERED,
	AXIA_HAT_UP       = GLFW_HAT_UP,
	AXIA_HAT_RIGHT    = GLFW_HAT_RIGHT,
	AXIA_HAT_DOWN     = GLFW_HAT_DOWN,
	AXIA_HAT_LEFT     = GLFW_HAT_LEFT,
	
	AXIA_GP_BUTTON_A          = GLFW_GAMEPAD_BUTTON_A,
	AXIA_GP_BUTTON_B          = GLFW_GAMEPAD_BUTTON_B,
	AXIA_GP_BUTTON_X          = GLFW_GAMEPAD_BUTTON_X,
	AXIA_GP_BUTTON_Y          = GLFW_GAMEPAD_BUTTON_Y,
	AXIA_GP_BUTTON_LBUMPER    = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
	AXIA_GP_BUTTON_RBUMPER    = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
	AXIA_GP_BUTTON_BACK       = GLFW_GAMEPAD_BUTTON_BACK,
	AXIA_GP_BUTTON_START      = GLFW_GAMEPAD_BUTTON_START,
	AXIA_GP_BUTTON_GUIDE      = GLFW_GAMEPAD_BUTTON_GUIDE,
	AXIA_GP_BUTTON_LTHUMB     = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
	AXIA_GP_BUTTON_RTHUMB     = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
	AXIA_GP_BUTTON_DPAD_UP    = GLFW_GAMEPAD_BUTTON_DPAD_UP,
	AXIA_GP_BUTTON_DPAD_RIGHT = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
	AXIA_GP_BUTTON_DPAD_DOWN  = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
	AXIA_GP_BUTTON_DPAD_LEFT  = GLFW_GAMEPAD_BUTTON_DPAD_LEFT, 
} AxiaJoystickInput;

typedef struct {
	const uint8_t *buttons;
	const float   *axes;
	const uint8_t *hats;
	
	int button_count;
	int hat_count;
	int axes_count;
} AxiaJoystick;

typedef GLFWgamepadstate AxiaGamepad;

	//=============//
	//  Functions  //
	//=============//

typedef struct AxiaWindow_t AxiaWindow_t;
typedef AxiaWindow_t* AxiaWindow;

void axiaPollEvents();
void axiaPollGamepad(AxiaGamepad *gp, uint32_t gamepad_id);
void axiaPollJoystick(AxiaJoystick *jstck, uint32_t joystick_id);

AxiaMousePos axiaGetMousePos(AxiaWindow win);

void axiaDisableMouse(AxiaWindow win);

void axiaHideMouse(AxiaWindow win);

void axiaRawMouse(AxiaWindow win);

void axiaNormalMouse(AxiaWindow win);

AxiaError axiaSetWinUTF8Buffer(AxiaWindow win, char *buffer, uint32_t size);

AxiaError axiaSetWinUTF32Buffer(AxiaWindow win, uint32_t *buffer, uint32_t size);

uint32_t axiaGetWinBufferIndex(AxiaWindow win);

AxiaError axiaStartUTF8Input(AxiaWindow win);

AxiaError axiaStartUTF32Input(AxiaWindow win);

void axiaStopTextInput(AxiaWindow win);

void axiaStoreNextKey(AxiaWindow win);

void axiaStoreNextButton(AxiaWindow win);

uint32_t axiaGetStoredButton(AxiaWindow win);

void axiaClearStoredButton(AxiaWindow win);

bool axiaKeyEvent(AxiaWindow, AxiaKeyInput, AxiaInputEvent);

bool axiaIsJoystickConnected(uint32_t joystick_id);

///////////////////////////////////////
/// If both connected_func and
/// disconnected_func are set to NULL,
/// then it will use default behaviour
void axiaJoystickGamepadLookout(
	AxiaWindow, 
	void (*connected_func)(int id),
	void (*disconnected_func)(int id)
);


bool axiaIsJoystickGamepad(uint32_t joystick_id);
