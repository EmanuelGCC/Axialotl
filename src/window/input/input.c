#include "../../struct_definitions.h"
#include "input.h"

void axiaPollEvents()
{
	glfwPollEvents();
}

const GLFWgamepadstate disconnected_state;

void axiaPollGamepad(AxiaGamepad *gp, uint32_t gamepad_id)
{
	glfwGetGamepadState(gamepad_id, gp);
}

void axiaPollJoystick(AxiaJoystick *jstck, uint32_t joystick_id)
{
	jstck->buttons = glfwGetJoystickButtons(joystick_id, &jstck->button_count);
	jstck->hats    = glfwGetJoystickHats(joystick_id, &jstck->hat_count);
	jstck->axes    = glfwGetJoystickAxes(joystick_id, &jstck->axes_count);

	if(jstck->buttons == NULL)
		jstck->buttons = disconnected_state.buttons;

	if(jstck->axes == NULL)
		jstck->axes = disconnected_state.axes;
}

bool axiaKeyEvent(AxiaWindow win, AxiaKeyInput input, AxiaInputEvent ev)
{
	return glfwGetKey(win->win, input) == ev;
}

AxiaMousePos axiaGetMousePos(AxiaWindow win)
{
	return win->mouse;
}

void axiaDisableMouse(AxiaWindow win) 
{
	glfwSetInputMode(win->win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void axiaHideMouse(AxiaWindow win)
{
	glfwSetInputMode(win->win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void axiaRawMouse(AxiaWindow win)
{
	glfwSetInputMode(win->win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(win->win, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

void axiaNormalMouse(AxiaWindow win)
{
	glfwSetInputMode(win->win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

AxiaError axiaSetWinUTF8Buffer(AxiaWindow win, char *buffer, uint32_t size)
{
	if(buffer == NULL || size < 4)
		return AXIA_INVALID_ARG;

	win->utf_size   = size;
	win->utf_buffer = buffer;
	win->utf_index  = 0;

	return AXIA_OK;
}

AxiaError axiaSetWinUTF32Buffer(AxiaWindow win, uint32_t *buffer, uint32_t size)
{
	if(buffer == NULL || size < 4)
		return AXIA_INVALID_ARG;

	win->utf_size   = size;
	win->utf_buffer = (uint8_t*)buffer;
	win->utf_index  = 0;

	return AXIA_OK;
}

uint32_t axiaGetWinBufferIndex(AxiaWindow win)
{
	return win->utf_index;
}

//  Defined later...
static void aixaUTF8BufferCallback_fun(GLFWwindow*, uint32_t);
AxiaError axiaStartUTF8Input(AxiaWindow win)
{
	if(win->utf_buffer == NULL)
		return AXIA_INVALID_CONDITIONS;

	glfwSetCharCallback(win->win, aixaUTF8BufferCallback_fun);

	return AXIA_OK;
}

//  Defined later...
static void aixaUTF32BufferCallback_fun(GLFWwindow*, uint32_t);
AxiaError axiaStartUTF32Input(AxiaWindow win)
{
	if(win->utf_buffer == NULL)
		return AXIA_INVALID_CONDITIONS;

	glfwSetCharCallback(win->win, aixaUTF32BufferCallback_fun);

	return AXIA_OK;
}

void axiaStopTextInput(AxiaWindow win) 
{
	glfwSetCharCallback(win->win, NULL);
}

//  Defined later...
static void axiaRegisterKey_fun(GLFWwindow*, int, int, int, int);
void axiaStoreNextKey(AxiaWindow win)
{
	glfwSetKeyCallback(win->win, axiaRegisterKey_fun);
}

//  Defined later...
static void axiaRegisterMouseBtn_fun(GLFWwindow*, int, int, int);
void axiaStoreNextButton(AxiaWindow win)
{
	glfwSetMouseButtonCallback(win->win, axiaRegisterMouseBtn_fun);
}

uint32_t axiaGetStoredButton(AxiaWindow win)
{
	return win->last_button;
}

void axiaClearStoredButton(AxiaWindow win) {
	win->last_button = 0;
}

bool axiaIsGamepadConnected(uint32_t gamepad_id)
{
	return glfwJoystickPresent(gamepad_id);	
}

bool axiaIsJoystickGamepad(uint32_t joystick_id)
{
	return glfwJoystickIsGamepad(joystick_id);
}

void (*connected_func)(int) = NULL;
void (*disconnected_func)(int) = NULL;

//  Defined later...
static void axiaJoystickLookout_fun(int jid, int event);
void axiaJoystickGamepadLookout(
		AxiaWindow win, 
		void (*connected)(int id),
		void (*disconnected)(int id)) 
{
	if(connected == NULL && disconnected == NULL) {
		glfwSetJoystickCallback(NULL);
		return;
	}
	if(connected != NULL)
		connected_func = connected;
	if(disconnected != NULL)
		disconnected_func = disconnected;

	glfwSetJoystickCallback(axiaJoystickLookout_fun);
}

	//=====================//
	//  Private functions  //
	//=====================//

static void axiaJoystickLookout_fun(int jid, int event)
{
	if(event == GLFW_CONNECTED) {
		if(connected_func != NULL)
			connected_func(jid);
	}
	else if(event == GLFW_DISCONNECTED) {
		if(disconnected_func != NULL)
			disconnected_func(jid);
	}
}

static void aixaUTF8BufferCallback_fun(GLFWwindow *glfw_win, uint32_t c) 
{
#ifdef AXIA_DEBUG
	printf("%d\n", c);
#endif

	AxiaWindow win = glfwGetWindowUserPointer(glfw_win);

	char     *buffer = win->utf_buffer;
	uint32_t  index;
   
	printf("%d %d %d\n", win->utf_index, win->utf_size, ((win->utf_index + 4) < win->utf_size));
		//  Ensure that we are not writing out of bounds  //
	if((win->utf_index + 4) < win->utf_size) 
		index = win->utf_index;
	else 
		index = 0;

	//  ASCII characters
	if(c < 0x7F) {
		buffer[index] = c;
		win->utf_index = index + 1;
		return;
	}

	//  Latin Based characters
	if(c < 0x7FF) {
		buffer[index]   = 0xC0 | ((c & 0x7C) >> 3);
		buffer[index+1] = 0x80 | (c & 0x3F); 
		win->utf_index  = index + 2;
		return;
	}

	//  Remaining languages
	if(c < 0xFFFF) {
		buffer[index]   = 0xE0 | (c >> 12);
		buffer[index+1] = 0x80 | ((c & 0xFC0) >> 6);
		buffer[index+2] = 0x80 | (c & 0x3F);
		win->utf_index  = index + 3;
		return;
	}
	// Mic characters

	buffer[index]   = 0xF0 | (c >> 20);
	buffer[index+1] = 0x80 | ((c & 0x3F000) >> 12);
	buffer[index+2] = 0x80 | ((c & 0xFC0) >> 6);
	buffer[index+3] = 0x80 | (c & 0x3F);
	win->utf_index  = index + 4;
}

static void aixaUTF32BufferCallback_fun(GLFWwindow *glfw_win, uint32_t c) 
{
#ifdef AXIA_DEBUG
	 printf("%x\n", c);
#endif

	AxiaWindow win = glfwGetWindowUserPointer(glfw_win);

	uint32_t *buffer = win->utf_buffer;
   
		//  Ensure that we are not writing out of bounds  //
	if(win->utf_index >= win->utf_size) 
		win->utf_index = 0;

	buffer[win->utf_index] = c;
	win->utf_index += 1;
}

static void axiaRegisterKey_fun(GLFWwindow *glfw_win, int key, int _scancode, int action, int _mods)
{
	AxiaWindow win = glfwGetWindowUserPointer(glfw_win);

	if(action == GLFW_PRESS) {
		win->last_button = key;
		glfwSetKeyCallback(glfw_win, NULL);
	}
}

static void axiaRegisterMouseBtn_fun(GLFWwindow *glfw_win, int btn, int action, int _)
{
	AxiaWindow win = glfwGetWindowUserPointer(glfw_win);

	if(action == GLFW_PRESS) {
		win->last_button = btn;
		glfwSetMouseButtonCallback(glfw_win, NULL);
	}
}
