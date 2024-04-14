#include "deps.h"

/////////////////////////////
// Prevent the library to be
// initialized twice or more
// times
static bool initialized = false;

uint32_t AXIA_VERSION_MAJOR = 3;
uint32_t AXIA_VERSION_MINOR = 3;

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

	glfwDestroyWindow(t);

	initialized = true;
	return AXIA_OK;
}

void axiaDeinit() 
{
	glfwTerminate();
}
