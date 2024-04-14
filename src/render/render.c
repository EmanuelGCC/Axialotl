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
	glRenderbufferStorage(GL_FRAMEBUFFER, GL_DEPTH24_STENCIL8, size.width, size.height);

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
	int32_t prm;
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
