#include "../struct_definitions.h"
#include "render.h"

//========================//
//  Function definitions  //
//========================//

	//============//
	//  AxiaView  //
	//============//

AxiaView axiaCreateView(
		const AxiaSize target_size, const AxiaVec3 cam_pos,
		const AxiaVec3 target,      const AxiaVec3 up)
{
	AxiaView ret = malloc(sizeof(AxiaView_t));
	if(ret == NULL)
		return NULL;

	axiaProjectionMat(ret->projection, 
	                   (float)target_size.height / (float)target_size.width,
	                   45.f, 0.1f, 100.f);

	axiaLookAt(ret->view, cam_pos, target, up);

	axiaMatXMat(ret->combined, ret->projection, ret->view);

	return ret;
}

void axiaDestroyView(AxiaView *view)
{
	if(view != NULL)
		free(*view);
}

void axiaChangeViewTargetSize(AxiaView view, const AxiaSize new_size)
{
	axiaProjectionMat(view->projection, 
	                   (float)new_size.height / (float)new_size.width,
	                   45.f, 0.1f, 100.f);
}

void axiaChangeViewLookAt(AxiaView view,         const AxiaVec3 cam_pos, 
                          const AxiaVec3 target, const AxiaVec3 up)
{
	axiaLookAt(view->view, cam_pos, target, up);
}

void axiaUpdateView(AxiaView view)
{
	axiaMatXMat(view->combined, view->projection, view->view);
}

void axiaUseView(const AxiaView view)
{
	glUniformMatrix4fv(0, 1, GL_FALSE, view->combined);
}

	//===================//
	//  AxiaFramebuffer  //
	//===================//

AxiaFramebuffer axiaCreateFramebuffer(const AxiaSize size)
{
	AxiaFramebuffer ret = malloc(sizeof(AxiaFramebuffer_t));
	if(ret == NULL)
		return NULL;

	glGenFramebuffers(1, &ret->framebuffer);
	glGenRenderbuffers(1, &ret->renderbuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, ret->framebuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, ret->renderbuffer);

	ret->size = size;
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.width, size.height);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, 
	                          GL_RENDERBUFFER, ret->renderbuffer);

	glClear(GL_DEPTH_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		axiaDestroyFramebuffer(&ret);
		return NULL;
	}

	return ret;
}

void axiaDestroyFramebuffer(AxiaFramebuffer *framebuffer)
{
	if(framebuffer == NULL)
		return;

	glDeleteFramebuffers(1, &(*framebuffer)->framebuffer);
	glDeleteRenderbuffers(1, &(*framebuffer)->renderbuffer);

	free(*framebuffer);
}

void axiaBindFramebufferTexture(AxiaFramebuffer framebuffer, AxiaTexture texture)
{
	GLint prm;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prm);
	
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->framebuffer);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
	                       GL_TEXTURE_2D, texture, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, prm);
}

void axiaUseFramebuffer(AxiaFramebuffer framebuffer)
{
	glViewport(0, 0, framebuffer->size.width, framebuffer->size.height);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->framebuffer);
}

	//==============================//
	//  Object rendering functions  //
	//==============================//

void axiaDrawShape(AxiaShape shape)
{
	glBindVertexArray(shape->vertex_array);

	glBindTexture(GL_TEXTURE_2D, shape->texture);
	glUniformMatrix4fv(1, 1, GL_FALSE, shape->model); 

	glDrawArrays(shape->draw_mode, 0, shape->vertex_count);
}

void axiaDrawIndexedShape(AxiaShape shape)
{
	glBindVertexArray(shape->vertex_array);

	glBindTexture(GL_TEXTURE_2D, shape->texture);
	glUniformMatrix4fv(1, 1, GL_FALSE, shape->model); 

	glDrawElements(shape->draw_mode, shape->index_count, shape->index_type, 0);
}

uint32_t axiaGetUTF16Index(AxiaText text, uint32_t *i)
{
	uint32_t r = FT_Get_Char_Index(text->font->face, 
	                               ((uint16_t*)text->string)[*i]);
	
	*i += 2;

	return r;
}

uint32_t axiaGetUTF32Index(AxiaText text, uint32_t *i)
{
	uint32_t r = FT_Get_Char_Index(text->font->face, 
	                               ((uint32_t*)text->string)[*i]);
	
	*i += 4;

	return r;
}

uint32_t axiaGetUTF8Index(AxiaText text, uint32_t *i)
{
	uint8_t *str      = (uint8_t*)text->string;
	uint32_t ft_index = ((uint8_t*)text->string)[*i];
	
	if(ft_index < 0x80) {
		*i += 1;
		return FT_Get_Char_Index(text->font->face, ft_index);
	}

	if(ft_index < 0xC0) {
		ft_index = 
			(((uint32_t)(str[*i] & 0x1F)) << 6) | ((str[*i+1] & 0x3F));
		*i += 2;
		
		return FT_Get_Char_Index(text->font->face, ft_index);
	}

	if(ft_index < 0xE0) {
		ft_index = (((uint32_t)(str[*i] & 0xF)) << 12) | 
		           (((uint32_t)(str[*i+1] & 0x3F)) << 6) |
		           (str[*i+3] & 0x3F);
		*i += 3;
		
		return FT_Get_Char_Index(text->font->face, ft_index);
	}

	ft_index = ((uint32_t)(str[*i] & 0x7) << 18)    |
	           ((uint32_t)(str[*i+1] & 0x3f) << 12) |
	           ((uint32_t)(str[*i+2] & 0x3f) << 6)  |
	           (str[*i+3] & 0x3f);
	*i += 4;
	
	return FT_Get_Char_Index(text->font->face, ft_index);
}

void axiaDrawText(AxiaText text, AxiaFramebuffer target)
{
	//  Get the current AxiaWindow to change shaders.
	struct AxiaWindow_t *current_win = 
		glfwGetWindowUserPointer(glfwGetCurrentContext());

	//  Get the general state of the shaders, framebuffers, etc
	//  before calling this function to recover at the end of it.
	GLint prev_viewport[4];
	GLint prev_program;
	GLint prev_framebuffer;
	glGetIntegerv(GL_VIEWPORT, prev_viewport);
	glGetIntegerv(GL_CURRENT_PROGRAM, &prev_program);
	glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &prev_framebuffer);

	axiaUseFramebuffer(target);
	glUseProgram(current_win->text_shader);

	uint32_t (*axiaGetTextIndex)(AxiaText, uint32_t*);
	switch(text->format) 
	{
		case AXIA_FORMAT_UTF16:
			axiaGetTextIndex = axiaGetUTF16Index;
			break;
		case AXIA_FORMAT_UTF8:
			axiaGetTextIndex = axiaGetUTF8Index;
			break;
		case AXIA_FORMAT_UTF32:
			axiaGetTextIndex = axiaGetUTF32Index;
			break;
		default:
			break;
	}

	AxiaFont font = text->font;
	const AxiaVec2 scale = axiaVec2(
		2.f / target->size.width,
		2.f / target->size.height
	);
	AxiaVec2 offset = axiaVec2( 0, 0 );

	for(uint32_t i=0, index=0;i<text->length;) 
	{
		glClear(GL_DEPTH_BUFFER_BIT);
		index = axiaGetTextIndex(text, &i);

		glBindVertexArray(text->vertex_array);


		glUniformMatrix4fv(0, 1, GL_FALSE, text->model);
		glUniform4f(1,
		            font->glyphs[index].sizes.x * scale.x,
                    font->glyphs[index].sizes.y * scale.y,
		            offset.x + font->glyphs[index].bearings.x * scale.x,
		            offset.y - font->glyphs[index].bearings.y * scale.y
		);
		glUniform3f(2, text->color[0], text->color[1], text->color[2]);

		glBindTexture(GL_TEXTURE_2D, font->textures[index]);
		
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		offset.x += font->glyphs[index].advance * scale.x;
	}

	glViewport(prev_viewport[0], 
	           prev_viewport[1],
	           prev_viewport[2],
	           prev_viewport[3]);
	glUseProgram(prev_program);
	glBindFramebuffer(GL_FRAMEBUFFER, prev_framebuffer);
}
