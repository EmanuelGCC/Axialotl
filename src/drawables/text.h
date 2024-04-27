//=======================================//
//  This file contains the declarations  //
//  of AxiaFont and AxiaText, which      //
//  are used for loading and rendering   //
//  text                                 //
//=======================================//
//  See drawables.c for definitions //
//==================================//

#pragma once

#include "../dependencies/deps.h"

typedef struct AxiaFont_t AxiaFont_t;
typedef AxiaFont_t* AxiaFont;

typedef struct AxiaText_t AxiaText_t;
typedef AxiaText_t* AxiaText;

typedef enum {
	AXIA_FORMAT_UTF8  = 1,
	AXIA_FORMAT_UTF16 = 2,
	AXIA_FORMAT_UTF32 = 4,
} AxiaTextFormat;

typedef enum {
	AXIA_TEXT_X      = 0xC,
	AXIA_TEXT_Y      = 0xD,
	AXIA_TEXT_Z      = 0xE,
	AXIA_TEXT_WIDTH  = 0x0,
	AXIA_TEXT_HEIGHT = 0x5,
} AxiaTextDataNames;

	//=============//
	//  functions  //
	//=============//

AxiaFont axiaCreateFont(const char *font_path, 
                        uint8_t aprox_cuality,
						bool mipmapped);

void axiaDestroyFont(AxiaFont*);

size_t axiaGetGlyphCount(AxiaFont);

AxiaText axiaCreateText();

void axiaDestroyText(AxiaText*);

void axiaBindTextFont(AxiaText, AxiaFont);

void axiaSetTextString(AxiaText, void *string, uint32_t byte_length, AxiaTextFormat);

void *axiaGetTextString(AxiaText);

uint32_t axiaGetTextLength(AxiaText);

AxiaTextFormat axiaGetTextFormat(AxiaText);

void axiaSetTextColor(AxiaText, uint8_t r, uint8_t g, uint8_t b);

float *axiaGetTextColor(AxiaText);
