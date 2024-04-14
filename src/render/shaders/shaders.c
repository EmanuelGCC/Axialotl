//===============================//
//  Definition of the functions  //
//  and structs declared         //
//  in shaders.h                 //
//===============================//

#include "shaders.h"

AxiaShader axiaCreateShader(const char *code, GLenum shader_type)
{
	uint32_t shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);

	int32_t success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success) {
#ifdef AXIA_DEBUG
		char log[300];
		glGetShaderInfoLog(shader, 300, NULL, log);

		printf("axiaCreateShader: %s\n", log);
#endif

		return AXIA_INVALID_SHADER;
	}

	return shader;
}

void axiaDestroyShader(AxiaShader *shader)
{
	glDeleteShader(*shader);
	*(uint32_t*)shader = 0;
}

AxiaShaderProgram axiaCreateShaderProgram() 
{
	return glCreateProgram();
}

void axiaDestroyShaderProgram(AxiaShaderProgram* program) 
{
	glDeleteProgram(*program);
	*(uint32_t*)program = 0;
}

void axiaAttachShader(AxiaShaderProgram program, AxiaShader shader)
{
	glAttachShader(program, shader);
}

AxiaError axiaLinkProgram(AxiaShaderProgram program)
{
	glLinkProgram(program);

	int32_t success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if(!success)
	{
#ifdef AXIA_DEBUG
		char log[300];
		glGetProgramInfoLog(program, 300, NULL, log);

		printf("axiaLinkProgram: %s\n", log);
#endif
		return AXIA_GL_ERROR;
	}

	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
	if(!success)
	{
#ifdef AXIA_DEBUG
		char log[300];
		glGetProgramInfoLog(program, 300, NULL, log);

		printf("axiaLinkProgram: %s\n", log);
#endif
		return AXIA_GL_ERROR;
	}

	return AXIA_OK;
}
