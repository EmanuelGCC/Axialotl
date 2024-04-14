//================================//
//  Definition of the functions   //
//  declared in window.h and the  //
//  AxiaWindow opaque struct      //
//================================//
// See input/input.(h/c) for //
// functions relating to     //
// inputs form the user      //
//===========================//

#include "../struct_definitions.h"
#include "window.h"

void framebuffer_callback(GLFWwindow *glfw_win, int w, int h)
{
	glViewport(0, 0, w, h);
	AxiaWindow win = glfwGetWindowUserPointer(glfw_win);

	win->size.width  = w;
	win->size.height = h;

	axiaProjectionMat(win->view.projection, (float)w/(float)h, 
	                   axiaToRad(90.f), 0.1f, 100.f);

	axiaMatXMat(win->view.combined, win->view.view, win->view.projection);

	glUniformMatrix4fv(0, 1, GL_FALSE, win->view.combined);
}

	//=========================//
	//  Functions that take a  //
	//  AxiaWindow pointer     //
	//=========================//

//  Defined later...
static void axiaMouseTracking_fun(GLFWwindow*, double, double);

AxiaWindow axiaCreateWindow(
		int32_t width, int32_t height, 
		const char *title, AxiaShaderProgram *program, 
		AxiaWinOps options)
{	
	AxiaWindow win = malloc(sizeof(AxiaWindow_t));
	if(win == NULL)
		return NULL;

	win->size.width  = width;
	win->size.height = height;
	win->title       = title;
	win->shader      = AXIA_INVALID_SHADER_PROGRAM;	
	win->cursor      = NULL;
	win->mouse.x     = 0;
	win->mouse.y     = 0;
	win->last_button = 0;
	win->utf_buffer  = NULL;
	win->utf_index   = 0;
	win->utf_size    = 0;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, AXIA_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, AXIA_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, 
	               (options & AXIA_WIN_RESIZEABLE) != 0);

	glfwWindowHint(GLFW_DECORATED,
	               (options & AXIA_WIN_DECORATED) != 0);

	glfwWindowHint(GLFW_VISIBLE,
	               (options & AXIA_WIN_VISIBLE) != 0);

	if((win->win = glfwCreateWindow(width, height, title, NULL, NULL)) == NULL) {
		free(win);
		return NULL;
	}

	glfwMakeContextCurrent(win->win);

	glViewport(0, 0, width, height);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(win->win, framebuffer_callback);
	glfwSetCursorPosCallback(win->win, axiaMouseTracking_fun);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	axiaMakeMatZero(win->view.projection);
	axiaMakeMatDefault(win->view.view);

	axiaProjectionMat(win->view.projection, (float)width/(float)height, 
				axiaToRad(90.f), 0.1f, 100.f);

	//////////////////////////////////
	// This calculation is expensive
	// and constant, so the returned
	// value is used directly;
	// this operation is equivalent
	// to axiaDefaultMat[14] = -1
	//////////////////////////////////
	//
	//axiaLookAt(temp_view, 
	//		(AxiaVec3){ 0, 0, 1 },
	//		(AxiaVec3){ 0, 0, 0 },
	//		(AxiaVec3){ 0, 1, 0 }
	//);
	
	win->view.view[14] = -1;

	axiaMatXMat(win->view.combined, win->view.view, win->view.projection);

	glfwSetWindowUserPointer(win->win, win);

	if((options & AXIA_WIN_NO_SHADER) != 0)
		return win;

	if(program != NULL) {
		win->shader = *program;

		return win;
	}

const char vertex_code[] = "#version 330\n"
"layout (location = 0) in vec3 vertex;\n"
"layout (location = 1) in vec2 text;\n"

"uniform mat4 combined;\n"
"uniform mat4 model;\n"
"out vec2 textCoords;\n" 
	
"void main()\n"
"{\n"
"    gl_Position = combined * (model * vec4(vertex, 1));\n"

"    textCoords = text;\n"
"}\0";

const char fragment_code[] = "#version 330\n"
"in vec2 textCoords;\n"
"uniform sampler2D texture2D;\n"
"out vec4 fragColor;\n"

"void main()\n"
"{\n"
"    fragColor = texture(texture2D, textCoords, -1);\n"
"}\0";

	win->shader = axiaCreateShaderProgram();

	AxiaShader vertex = 
		axiaCreateShader(vertex_code, GL_VERTEX_SHADER);
	
	if(vertex == AXIA_INVALID_SHADER) {
		axiaDestroyWindow(&win);
		return NULL;
	}

	AxiaShader fragment = 
		axiaCreateShader(fragment_code, GL_FRAGMENT_SHADER);

	if(fragment == AXIA_INVALID_SHADER) {
		axiaDestroyShader(&vertex);
		axiaDestroyWindow(&win);
		return NULL;
	}

	axiaAttachShader(win->shader, vertex);
	axiaAttachShader(win->shader, fragment);

	uint32_t success = axiaLinkProgram(win->shader);

	axiaDestroyShader(&vertex);
	axiaDestroyShader(&fragment);

	if(success != AXIA_OK) {
		axiaDestroyWindow(&win);
		return NULL;
	}

	glUseProgram(win->shader);
	glUniformMatrix4fv(0, 1, GL_FALSE, win->view.combined);

	return win;
}

void axiaDestroyWindow(AxiaWindow *win) 
{
	if(win == NULL)
		return;
	
	if((*win)->shader !=AXIA_INVALID_SHADER_PROGRAM)
		axiaDestroyShaderProgram(&(*win)->shader);

	if((*win)->win == glfwGetCurrentContext())
		glfwMakeContextCurrent(NULL);

	if((*win)->cursor != NULL)
		glfwDestroyCursor((*win)->cursor);

	if((*win)->win != NULL)
		glfwDestroyWindow((*win)->win);
	
	free(*win);
	*win = NULL;
}

void axiaMakeWinCurrent(AxiaWindow win) {
	glfwMakeContextCurrent(win->win);
}

bool axiaIsWinOpen(AxiaWindow win) {
	return !glfwWindowShouldClose(win->win);
}

void axiaDisplay(AxiaWindow win) {
	glfwSwapBuffers(win->win);
}

void axiaUseWinFramebuffer(AxiaWindow win) {
	glViewport(0, 0, win->size.width, win->size.height);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void axiaUseWinView(AxiaWindow win) {
	glUniformMatrix4fv(0, 1, GL_FALSE, win->view.combined);
}

void axiaUseWinShaderProgram(AxiaWindow win) {
	glUseProgram(win->shader);
}

AxiaView axiaGetWinView(AxiaWindow win) {
	return &win->view;
}

		//========================//
		//  Non-Crucial functions //
		//========================//

AxiaSize axiaGetWinSize(AxiaWindow win) {
	glfwGetWindowSize(win->win, &win->size.width, &win->size.height);
	return win->size;
}

void axiaSetWinSize(AxiaWindow win, AxiaSize new_size) {
	glfwSetWindowSize(win->win, new_size.width, new_size.height);
	win->size = new_size;
}

void axiaMaximizeWin(AxiaWindow win) {
	glfwMaximizeWindow(win->win);
}

void axiaMinimizeWin(AxiaWindow win) {
	glfwIconifyWindow(win->win);
}

void axiaRestoreWin(AxiaWindow win) {
	glfwRestoreWindow(win->win);
}

AxiaScreenPos axiaGetWinPos(AxiaWindow win) {
	AxiaScreenPos pos;
	glfwGetWindowPos(win->win, &pos.x, &pos.y);
	return pos;
}

void axiaSetWinPos(AxiaWindow win, AxiaScreenPos new_pos) {
	glfwSetWindowPos(win->win, new_pos.x, new_pos.y);
}

void axiaSetWinCursor(AxiaWindow win, bool created) {
	glfwSetCursor(win->win, created? win->cursor : NULL);
}

void axiaSetWinTitle(AxiaWindow win, const char *new_title) {
	glfwSetWindowTitle(win->win, new_title);
	win->title = new_title;
}

const char *axiaGetWinTite(AxiaWindow win) {
	return win->title;
}

	//=============================//
	//  Functions that don't       //
	//  take a AxiaWindow pointer  //
	//=============================//

void axiaClear(void) {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void axiaClearColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	glClearColor(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

void axiaClearColorFloat(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}

	//=====================//
	//  Private functions  //
	//=====================//
	
static void axiaMouseTracking_fun(GLFWwindow *glfw_win, double x, double y)
{
	AxiaWindow win = glfwGetWindowUserPointer(glfw_win);

	win->mouse.x = x;
	win->mouse.y = y;
}
