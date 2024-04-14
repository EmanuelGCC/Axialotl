#include "drawables/geometry.h"
#include "math/matrix.h"
#include "window/window.h"

int main() 
{
	if(axiaInit())
		return 100;

	AxiaWindow win = axiaCreateWindow(1000, 900, "Please work, Axia!", NULL, AXIA_WIN_DEFAULT);
	if(win == NULL)
		return 25;
	
	AxiaShape shape = axiaCreateRectangle(axiaVec2( 0.3, 0.3 ), axiaVec3( 0, 0, 0 ));
	AxiaMatPtr mat = axiaGetShapeMatrix(shape);

	AxiaTexture tex = axiaCreateTexture();
	axiaLoadFromImage(tex, "/home/emanuel/Downloads/sphere/bin/earth2048.bmp");

	axiaBindShapeTexture(shape, tex);

	axiaClearColorFloat(0.3, 0.3, 0.3, 1);

	AxiaGamepad gp;

	while(axiaIsWinOpen(win))
	{
		axiaPollEvents();
		axiaPollGamepad(&gp, 0);

		axiaClear();

		if(gp.buttons[AXIA_GP_BUTTON_DPAD_UP] || axiaKeyEvent(win, AXIA_KEY_UP, AXIA_PRESSED))       { mat[AXIA_RECT_Y] += 0.02; }
		if(gp.buttons[AXIA_GP_BUTTON_DPAD_DOWN] || axiaKeyEvent(win, AXIA_KEY_DOWN, AXIA_PRESSED))   { mat[AXIA_RECT_Y] -= 0.02; }
		if(gp.buttons[AXIA_GP_BUTTON_DPAD_RIGHT] || axiaKeyEvent(win, AXIA_KEY_RIGHT, AXIA_PRESSED)) { mat[AXIA_RECT_X] += 0.02; }
		if(gp.buttons[AXIA_GP_BUTTON_DPAD_LEFT] || axiaKeyEvent(win, AXIA_KEY_LEFT, AXIA_PRESSED))   { mat[AXIA_RECT_X] -= 0.02; }

		axiaDrawShape(shape);

		axiaDisplay(win);
	}

	glDeleteTextures(1, &tex);
	axiaDestroyShape(&shape);
	axiaDestroyWindow(&win);

	axiaDeinit();

	return glGetError();
}
