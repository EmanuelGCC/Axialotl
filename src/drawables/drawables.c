//======================================//
//  This file defines everything that   //
//  was declared in geometry.h and      //
//  texture.h.                          //
//                                      //
//  This file also includes stb_image,  //
//  the reason this is not done in      //
//  dependencies.h is because only      //
//  this file uses the library, and     //
//  because stb_image does not have     //
//  pragma once                         //
//======================================//

//============//
//  Includes  //
//============//

/////////////////////////////////
// For the sake of convinience,
// the stb_image (which is just
// a single .h file) is provided
// directly by Axialotl, however,
// this does mean that stb image
// may not be up to date. To solve
// that, change STB_IMAGE_PATH value
// when compiling this file.
//
// stb (image)'s github:
// https://github.com/nothings/stb
#define STB_IMAGE_IMPLEMENTATION

#ifndef STB_IMAGE_PATH
#define STB_IMAGE_PATH "../dependencies/stb_image.h"
#endif

#include STB_IMAGE_PATH

#include "../struct_definitions.h"
#include "geometry.h"
#include "text.h"

//=============//
//  Functions  //
//=============//

	//===============//
	//  AxiaTexture  //
	//===============//

AxiaTexture axiaCreateTexture() 
{
	uint32_t ret;
	glGenTextures(1, &ret);
	return ret;
}

void axiaDestroyTexture(AxiaTexture *texture)
{
	glDeleteTextures(1, texture);
	*(uint32_t*)texture = 0;
}

AxiaError axiaLoadTextureSource(AxiaTexture texture, AxiaTextureFormat format,
		const AxiaSize size, const uint8_t *data, bool bitmapped)
{
	if(format != AXIA_RGBA && format != AXIA_RGB &&
	   format != AXIA_RG   && format != AXIA_GRAY)
		return AXIA_INVALID_ARG;

	//  Acutally load the image

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
			bitmapped? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.width, size.height, 
			     0, format, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);

	return AXIA_OK;
}


AxiaError axiaLoadFromImage(AxiaTexture texture, const char *img_path)
{
	AxiaSize size;
	int32_t channels;

	stbi_set_flip_vertically_on_load(true);
	uint8_t *data = stbi_load(img_path, &size.width, &size.height, &channels, 0);

	if(data == NULL)
		return AXIA_LODING_FAILED;

	/////////////////////////////////////////////////
	//  Unfortunately, because of how OpenGL handles
	//  it's formats, there needs to be a if chain
	//  for the image's format to be set.
	//
	uint32_t format;
	if(channels == 3) { format = AXIA_RGB; }
	else if(channels == 4) { format = AXIA_RGBA; }
	else if(channels == 2) { format = AXIA_RG; }
	else { format = AXIA_GRAY; }

	axiaLoadTextureSource(texture, format, size, data, true);

	stbi_image_free(data);

	return AXIA_OK;
}

void axiaTextureFromColor(AxiaTexture texture, 
		uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	AxiaSize size = { 1, 1 };
	uint8_t data[4] = { r, g, b, a };

	axiaLoadTextureSource(texture, AXIA_RGBA, size, data, false);
}

	//=============//
	//  AxiaShape  //
	//=============//
	
AxiaShape axiaCreateShape(AxiaShapeDrawMode draw_mode)
{
	AxiaShape ret = malloc(sizeof(AxiaShape_t));
	if(ret == NULL)
		return NULL;

	axiaMakeMatDefault(ret->model);

	glGenVertexArrays(1, &ret->vertex_array);
	glGenBuffers(1, &ret->vertex_buffer);

	ret->draw_mode = draw_mode;
	ret->texture = 0;
	ret->vertex_count = 0;
	ret->element_buffer = 0;
	ret->index_count = 0;

	return ret;
}

void axiaDestroyShape(AxiaShape *shape)
{
	if(shape == NULL)
		return;

	glDeleteVertexArrays(1, &(*shape)->vertex_array);
	glDeleteBuffers(1, &(*shape)->vertex_buffer);

	if((*shape)->element_buffer != 0)
		glDeleteBuffers(1, &(*shape)->element_buffer);

	free(*shape);
}

void axiaPopulateShape(AxiaShape shape, const float *data, 
                       uint32_t float_count, 
                       uint32_t vertex_count, 
                       uint32_t texcoor_start, 
                       size_t   texture_stride)
{
	glBindVertexArray(shape->vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, shape->vertex_buffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*float_count, data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(AxiaVec3), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 
	                      texture_stride, (void*)((size_t)texcoor_start));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	shape->vertex_count = vertex_count;
}

AxiaError axiaShapeIndices(AxiaShape shape, const void *indices,
                           uint32_t index_count,
                           AxiaIndexType index_type)
{
	if(shape == NULL)
		return AXIA_INVALID_ARG;

	uint32_t size;
	switch(index_type) {
		case AXIA_INDEX_BYTE:
			size = index_count; break;
		case AXIA_INDEX_SHORT:
			size = 2 * index_count; break;
		case AXIA_INDEX_INT:
			size = 4 * index_count; break;
		default:
			return AXIA_INVALID_ARG; break;
	}

	if(shape->element_buffer == 0)
		glGenBuffers(1, &shape->element_buffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape->element_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	shape->index_type = index_type;
	shape->index_count = index_count;

	return AXIA_OK;
}

AxiaMatPtr axiaGetShapeMatrix(AxiaShape shape)
{
	return shape->model;
}

void axiaBindShapeTexture(AxiaShape shp, AxiaTexture tex)
{
	shp->texture = tex;
}

	//============================//
	//  Specific shape functions  //
	//============================//

AxiaShape axiaCreateRectangle(AxiaVec2 size, AxiaVec3 pos)
{
	AxiaShape rec = axiaCreateShape(AXIA_DRAW_TRIANGLE_STRIP);

	float data[] = {
		0, 0, 0,  1, 0, 0,
		0, 1, 0,  1, 1, 0
	};

	axiaPopulateShape(rec, data, 12, 4, 0, sizeof(AxiaVec3));

	rec->model[AXIA_RECT_WIDTH]  = size.x;
	rec->model[AXIA_RECT_HEIGHT] = size.y;
	rec->model[AXIA_RECT_X]      = pos.x;
	rec->model[AXIA_RECT_Y]      = pos.y;
	rec->model[AXIA_RECT_Z]      = pos.z;

	return rec;
}

AxiaShape axiaCreateCube(AxiaVec3 size, AxiaVec3 pos)
{
	AxiaShape cub = axiaCreateShape(AXIA_DRAW_TRIANGLE_STRIP);

	float data[] = {
		0, 0, 0,  1, 0, 0,
		0, 1, 0,  1, 1, 0,
		1, 1, 1,  1, 0, 1,
		0, 0, 1,  0, 1, 1
	};
	uint8_t indices[] = {
		0, 1, 2, 3, 4, 1, 5, 
		0, 6, 2, 7, 4, 6, 5
	};

	axiaPopulateShape(cub, data, 24, 8, 0, sizeof(AxiaVec3));
	axiaShapeIndices(cub, indices, 14, AXIA_INDEX_BYTE);

	cub->model[AXIA_CUBE_X]      = pos.x;
	cub->model[AXIA_CUBE_Y]      = pos.y;
	cub->model[AXIA_CUBE_Z]      = pos.z;
	cub->model[AXIA_CUBE_WIDTH]  = size.x;
	cub->model[AXIA_CUBE_HEIGHT] = size.y;
	cub->model[AXIA_CUBE_DEPTH]  = size.z;

	return cub;
}

AxiaShape axiaCreateTriangle(AxiaVec3 pos, AxiaVec3 vert1, AxiaVec3 vert2)
{
	AxiaShape tri = axiaCreateShape(AXIA_DRAW_TRIANGLES);

	float data[] = {
		0, 0, 0,  1, 0, 0,  0, 1, 0
	};

	axiaPopulateShape(tri, data, 9, 3, 0, sizeof(AxiaVec3));

	tri->model[AXIA_TRIA_X] = pos.x;
	tri->model[AXIA_TRIA_Y] = pos.y;
	tri->model[AXIA_TRIA_Z] = pos.z;

	tri->model[AXIA_TRIA_VERT1_X] = vert1.x;
	tri->model[AXIA_TRIA_VERT1_Y] = vert1.y;
	tri->model[AXIA_TRIA_VERT1_Z] = vert1.z;

	tri->model[AXIA_TRIA_VERT2_X] = vert2.x;
	tri->model[AXIA_TRIA_VERT2_Y] = vert2.y;
	tri->model[AXIA_TRIA_VERT2_Z] = vert2.z;

	return tri;
}

AxiaShape axiaCreateTetrahedron(AxiaVec3 pos, AxiaVec3 vert1, 
                                AxiaVec3 vert2, AxiaVec3 vert3)
{
	AxiaShape tet = axiaCreateShape(AXIA_DRAW_TRIANGLE_STRIP);

	float data[] = {
		0, 0, 0,  0, 0, 1,
		1, 0, 0,  0, 1, 0
	};
	uint8_t indices[] = {
		0, 1, 3, 2, 0, 1
	};

	axiaPopulateShape(tet, data, 12, 4, 0, sizeof(AxiaVec3));
	axiaShapeIndices(tet, indices, 6, AXIA_INDEX_BYTE);

	tet->model[AXIA_TETRA_X] = pos.x;
	tet->model[AXIA_TETRA_Y] = pos.y;
	tet->model[AXIA_TETRA_Z] = pos.z;

	tet->model[AXIA_TETRA_VERT1_X] = vert1.x;
	tet->model[AXIA_TETRA_VERT1_Y] = vert1.y;
	tet->model[AXIA_TETRA_VERT1_Z] = vert1.z;

	tet->model[AXIA_TETRA_VERT2_X] = vert2.x;
	tet->model[AXIA_TETRA_VERT2_Y] = vert2.y;
	tet->model[AXIA_TETRA_VERT2_Z] = vert2.z;

	tet->model[AXIA_TETRA_VERT3_X] = vert3.x;
	tet->model[AXIA_TETRA_VERT3_Y] = vert3.y;
	tet->model[AXIA_TETRA_VERT3_Z] = vert3.z;

	return tet;
}

AxiaShape axiaCreateCircle(AxiaVec3 pos, float radious, uint8_t comp)
{
	const uint16_t complexity = comp << 2;

	AxiaShape cir = axiaCreateShape(AXIA_DRAW_TRIANGLE_FAN);

	float *data = malloc(sizeof(float) * complexity*
	                     (sizeof(AxiaVec3)+sizeof(AxiaVec2)));
	AxiaVec3 *vertices = (AxiaVec3*)data;
	AxiaVec2 *texture  = (AxiaVec2*)(data+complexity*3);

	const float angle = 2.f * M_PI / complexity;
	float sin, cos;
	
	for(uint8_t i=0;i<complexity;++i) {
		sin = sinf(i * angle);
		cos = cosf(i * angle);

		vertices[i].x = sin;
		vertices[i].y = cos;
		vertices[i].z = 0;

		texture[i].x = 0.5*(sin + 1);
		texture[i].y = 0.5*(cos + 1);
	}
 
	axiaPopulateShape(cir, data, 
	                  complexity*5, 
	                  complexity, 
					  complexity*sizeof(AxiaVec3), 
					  sizeof(AxiaVec2));

	cir->model[AXIA_CIRCLE_X]       = pos.x;
	cir->model[AXIA_CIRCLE_Y]       = pos.y;
	cir->model[AXIA_CIRCLE_Z]       = pos.z;
	cir->model[AXIA_CIRCLE_SCALE_X] = radious;
	cir->model[AXIA_CIRCLE_SCALE_Y] = radious;

	free(data);

	return cir;
}

AxiaShape axiaCreateSphere(AxiaVec3 pos, float radious, 
                           uint8_t horizontal, uint8_t vertical)
{

/*
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!! TODO: 
	!!    As it currently stands, the following code is inefficiant because
	!!    it makes use of base*2 more vertices than what are needed;
	!!    all vertices[i] for i < base are equal, and the same is true for
	!!    the last base of vertices. As of right now, I haven't been able
	!!    to figure out a way to optimize the code, however, ideally it 
	!!    will be changed.
*/

	AxiaShape sph = axiaCreateShape(AXIA_DRAW_TRIANGLES);

	const uint16_t complexity  = (uint16_t)(horizontal + 1) * (vertical + 1);
	const uint16_t index_count = 6 * (horizontal * (vertical - 1));
	const float    latitude    = 2.f * M_PI / horizontal;
	const float    longitude   = M_PI / vertical;

	uint8_t  *data       = malloc((sizeof(AxiaVec3) + sizeof(AxiaVec2)) * complexity);
	uint16_t *indices    = malloc(sizeof(uint16_t) * index_count);
	AxiaVec3 *vertices   = (AxiaVec3*)data;
	AxiaVec2 *tex_coords = (AxiaVec2*)(data+(sizeof(AxiaVec3) * complexity));

	// Okay, now the problem is that for base != 4
	// the obtained vertices are different.
	//
	// Check obtained_results and expected_results
	// and try to debug that

	uint16_t i, o, j=0;
	float sin_i, cos_i, tex_coord_y;
	for(i=0;i<=vertical;++i) 
	{
		cos_i = cosf(M_PI / 2 - i * longitude);
		sin_i = sinf(M_PI / 2 - i * longitude);
		tex_coord_y = (float)i / vertical;
		for(o=0;o<=horizontal;++o,++j) 
		{
			vertices[j] = axiaVec3( 
				cos_i * cosf(o * latitude), 
				cos_i * sinf(o * latitude), 
				sin_i 
			);

			tex_coords[j] = axiaVec2(
				(float)o / horizontal,
				tex_coord_y
			);
		}
	}

	uint16_t k, v; j=0;
	for(i=0;i<vertical;++i) 
	{
		k = i * (horizontal + 1);
		v = k + horizontal + 1;
		for(o=0;o<horizontal;++o,++k,++v)
		{
			if(i != 0) {
				indices[j]   = k;
				indices[j+1] = v;
				indices[j+2] = k + 1;
				j += 3;
			}

			if(i != (vertical - 1)) {
				indices[j] = k + 1;
				indices[j+1] = v;
				indices[j+2] = v + 1;
				j += 3;
			}
		}
	}

	axiaPopulateShape(
			sph, (float*)data, 
			complexity * 5,                 // Float count
	        complexity,                     // Vertex count
			complexity * sizeof(AxiaVec3),  // Text-Coord start
			sizeof(AxiaVec2));              // Texture Stride
	axiaShapeIndices(sph, indices, index_count, AXIA_INDEX_SHORT);

	sph->model[AXIA_SPHERE_X]       = pos.x;
	sph->model[AXIA_SPHERE_Y]       = pos.y;
	sph->model[AXIA_SPHERE_Z]       = pos.z;
	sph->model[AXIA_SPHERE_SCALE_X] = radious;
	sph->model[AXIA_SPHERE_SCALE_Y] = radious;
	sph->model[AXIA_SPHERE_SCALE_Z] = radious;

	free(data);
	free(indices);

	return sph;
}

	//========//
	//  Text  //
	//========//

AxiaFont axiaCreateFont(const char *font_path, 
                        uint8_t aprox_cuality,
						bool mipmapped)
{
	FT_Library lib;
	FT_Face    face;

	FT_Init_FreeType(&lib);
	if(FT_New_Face(lib, font_path, 0, &face))
		return NULL;

	AxiaFont font = malloc(sizeof(AxiaFont_t));

	font->lib  = lib;
	font->face = face;

	font->textures = malloc(sizeof(uint32_t) * face->num_glyphs);
	font->glyphs   = malloc(sizeof(AxiaGlyphDetails) * face->num_glyphs);

	glGenTextures(face->num_glyphs, font->textures);

	FT_Set_Pixel_Sizes(face, 0, aprox_cuality);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
	                (mipmapped)? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	FT_UInt  index;
	FT_ULong code = FT_Get_First_Char(face, &index);
	
	while(index != 0)
	{
		if(FT_Load_Char(face, code, FT_LOAD_RENDER)) {
			axiaDestroyFont(&font);
			return NULL;
		}

		glBindTexture(GL_TEXTURE_2D, font->textures[index]);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
					 face->glyph->bitmap.width,
					 face->glyph->bitmap.rows,
					 0, GL_RED, GL_UNSIGNED_BYTE,
					 face->glyph->bitmap.buffer);

		glGenerateMipmap(GL_TEXTURE_2D);

		font->glyphs[index] = (AxiaGlyphDetails){
			axiaVec2((float)face->glyph->bitmap.width,
					 (float)face->glyph->bitmap.rows),
			axiaVec2((float)face->glyph->bitmap_left,
					 (float)(face->glyph->bitmap.rows-face->glyph->bitmap_top)),
			(float)(face->glyph->advance.x >> 6)
		};

		code = FT_Get_Next_Char(face, code, &index);
	}

	return font;
}

void axiaDestroyFont(AxiaFont *font)
{
	if(font == NULL)
		return;

	FT_Done_Face((*font)->face);
	FT_Done_FreeType((*font)->lib);

	glDeleteTextures((*font)->face->num_glyphs, (*font)->textures);

	free((*font)->glyphs);
	free((*font)->textures);
	free(*font);
}

size_t axiaGetGlyphCount(AxiaFont font)
{
	return font->face->num_glyphs;
}

AxiaText axiaCreateText()
{
	AxiaText text = malloc(sizeof(AxiaText_t));
	if(text == NULL)
		return NULL;

	float data[] = {
		0.f, 0.f, 0.f,  1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,  1.f, 1.f, 0.f
	};

	axiaMakeMatDefault(text->model);
	text->string   = NULL;
	text->length   = 0;
	text->format   = AXIA_FORMAT_UTF16;
	text->color[0] = 1;
	text->color[1] = 1;
	text->color[2] = 1;
	text->font     = NULL;

	glGenVertexArrays(1, &text->vertex_array);
	glGenBuffers(1, &text->vertex_buffer);

	glBindVertexArray(text->vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, text->vertex_buffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(AxiaVec3), (void*)0);

	glEnableVertexAttribArray(0);

	return text;
}

void axiaDestroyText(AxiaText *text)
{
	if(text == NULL)
		return;

	glDeleteVertexArrays(1, &(*text)->vertex_array);
	glDeleteBuffers(1, &(*text)->vertex_buffer);

	free(*text);
}

void axiaBindTextFont(AxiaText text, AxiaFont font)
{
	text->font = font;
}

void axiaSetTextString(AxiaText text, void *string, 
                       uint32_t length, AxiaTextFormat format)
{
	text->string = string;
	text->length = length;
	if((format & (AXIA_FORMAT_UTF16 | AXIA_FORMAT_UTF8 | AXIA_FORMAT_UTF32)) == 0) {
#ifdef AXIA_DEBUG
		printf("[axiaSetTextString] : Invalid format\n");
#endif
		return;
	}

	text->format = format;
}

void *axiaGetTextString(AxiaText text) 
{
	return text->string;
}

uint32_t axiaGetTextLength(AxiaText text)
{
	return text->length;
}

AxiaTextFormat axiaGetTextFormat(AxiaText text)
{
	return text->format;
}

void axiaSetTextColor(AxiaText text, uint8_t r, uint8_t g, uint8_t b)
{
	text->color[0] = (float)r / 255;
	text->color[1] = (float)g / 255;
	text->color[2] = (float)b / 255;
}

float *axiaGetTextColor(AxiaText text)
{
	return text->color;
}

	//===============================//
	//  The two window functions     //
	//  that coudn't go in window.c  //
	//===============================//
	
AxiaError axiaSetWinIcon(struct AxiaWindow_t *win, const char* img)
{
	int32_t width, height, channels;
	uint8_t *data = stbi_load(img, &width, &height, &channels, 0);
	if(data == NULL)
		return AXIA_FAILED_MALLOC;

	GLFWimage icon = {
		.width  = width,
		.height = height,
		.pixels = data,	
	};

	glfwSetWindowIcon(win->win, 1, &icon);

	return AXIA_OK;
}

AxiaError axiaMakeWinCursor(struct AxiaWindow_t *win, const char* img, 
		                    int32_t xhot_spot, int32_t yhot_spot)
{
	int32_t width, height, channels;
	uint8_t *data = stbi_load(img, &width, &height, &channels, 0);
	if(data == NULL)
		return AXIA_FAILED_MALLOC;

	GLFWimage image = {
		.width  = width,
		.height = height,
		.pixels = data,	
	};

	win->cursor = glfwCreateCursor(&image, xhot_spot, yhot_spot);

	return AXIA_OK;
}

