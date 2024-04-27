//==============================//
//  This file defines the       //
//  init and deinit functions,  //
//  and thereby assigns values  //
//  to the static variables     //
//==============================//

#include "axia.h"

static bool initialized = false;

uint32_t   AXIA_VERSION_MAJOR;
uint32_t   AXIA_VERSION_MINOR;

AxiaError axiaInitializeFunction(uint32_t version_major, uint32_t version_minor)
{
	if(initialized)
		return AXIA_ALREADY_INIT; 

	*(uint32_t*)(&AXIA_VERSION_MAJOR) = version_major;
	*(uint32_t*)(&AXIA_VERSION_MINOR) = version_minor;
	
	if(glfwInit() != GLFW_TRUE)
		return AXIA_GLFW_ERROR;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, AXIA_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, AXIA_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	GLFWwindow *t = glfwCreateWindow(1, 1, "", NULL, NULL);
	if(t == NULL)
		return AXIA_GLFW_ERROR;
	glfwMakeContextCurrent(t);

	if(glewInit() != GLEW_OK)
		return AXIA_GLEW_ERROR;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	initialized = true;

	glfwDestroyWindow(t);

	return AXIA_OK;
}

void axiaDeinit() 
{
	glfwTerminate();
}
