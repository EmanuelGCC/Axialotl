#include "axialotl/axia.h"
#include "render/render.h"

int main() 
{
	if(axiaInit())
		return 100;

	AxiaWindow win = axiaCreateWindow(900, 900, "Please work, Axia!", AXIA_WIN_DEFAULT);
	if(win == NULL)
		return 25;

	AxiaShape shape = axiaCreateRectangle(axiaVec2( 2, 2 ), axiaVec3( -1, -1, 0 ));

	AxiaTexture tex = axiaCreateTexture();
	AxiaFramebuffer framebuffer = axiaCreateFramebuffer((AxiaSize){ 900, 900 });
	if(axiaLoadTextureSource(tex, GL_RGBA, (AxiaSize){ 900, 900 }, NULL, false))
		return 1;

	axiaBindFramebufferTexture(framebuffer, tex);
	axiaUseFramebuffer(framebuffer);
	axiaClearColorFloat(0, 0, 0, 1);
	axiaClear();
	axiaUseWinFramebuffer(win);

	AxiaFont font = axiaCreateFont("/home/emanuel/Downloads/Happiness-Sans-Regular.ttf", 50, true);
	AxiaText text = axiaCreateText();

	axiaBindTextFont(text, font);
	//  Test with non-latin characters: 안녕하세요
	axiaSetTextString(text, L"안녕하세요", 10, AXIA_FORMAT_UTF16);
	axiaSetTextColor(text, 223, 175, 175);
	
	axiaDrawText(text, framebuffer);

	axiaBindShapeTexture(shape, tex);

	axiaClearColorFloat(0.3, 0.3, 0.3, 1);

	while(axiaIsWinOpen(win))
	{
		axiaPollEvents();

		axiaClear();

		axiaDrawShape(shape);

		axiaDisplay(win);
	}

	axiaDestroyFont(&font);
	axiaDestroyText(&text);
	axiaDestroyTexture(&tex);
	axiaDestroyFramebuffer(&framebuffer);
	axiaDestroyShape(&shape);
	axiaDestroyWindow(&win);

	printf("%x\n", glGetError());
	axiaDeinit();

	return 0;
}
