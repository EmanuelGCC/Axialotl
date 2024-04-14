#include "../../../src/window/window.h"

int main() 
{
	if(axiaInit())
		return 100;

	AxiaWindow win = axiaCreateWindow(900, 900, "Please work, Axia!", NULL, AXIA_WIN_DEFAULT);
	if(win == NULL)
		return 25;

	AxiaShape simple_rect = axiaCreateRectangle((AxiaVec2){ 0.3, 0.3 }, (AxiaVec3){ 0, 0, 0 });
	float*    rect_mat = axiaGetShapeMatrix(simple_rect);

	AxiaTexture tex = axiaCreateTexture();
	if(axiaLoadFromImage(tex, "/home/emanuel/Pictures/Wallpapers/wp5728396-1080p-minimalist-wallpapers.jpg"))
		printf("Uy, se re compico la cosa\n");
	axiaBindShapeTexture(simple_rect, tex);

	axiaClearColorFloat(0.3, 0.3, 0.3, 1);

	AxiaMousePos m_pos = {};

	bool using_mouse = true;

	while(axiaIsWinOpen(win)) {
		axiaPollEvents();

		axiaClear();

		m_pos = axiaGetMousePos(win);
		
		if(using_mouse) {
			if(axiaIsKeyPressed(win, AXIA_KEY_SPACE)) { using_mouse = false; };

			rect_mat[AXIA_RECT_X] = m_pos.x / 450 - 1.f;
			rect_mat[AXIA_RECT_Y] = m_pos.y / -450 + 1.f;
		} else {
			if(axiaIsKeyPressed(win, AXIA_KEY_TAB)) { using_mouse = true; };

			if(axiaIsKeyPressed(win, AXIA_KEY_LEFT))  { rect_mat[AXIA_RECT_X] -= 0.02f; }
			if(axiaIsKeyPressed(win, AXIA_KEY_RIGHT)) { rect_mat[AXIA_RECT_X] += 0.02f; }
			if(axiaIsKeyPressed(win, AXIA_KEY_DOWN))  { rect_mat[AXIA_RECT_Y] -= 0.02f; }
			if(axiaIsKeyPressed(win, AXIA_KEY_UP))    { rect_mat[AXIA_RECT_Y] += 0.02f; }
		}

		axiaDrawShape(simple_rect);

		axiaDisplay(win);
	}

	glDeleteTextures(1, &tex);
	axiaDestroyShape(&simple_rect);
	axiaDestroyWindow(&win);

	axiaDeinit();

	return glGetError();
}
