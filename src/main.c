#include "axialotl/axia.h"
#include "render/render.h"
#include "sound/sound.h"

int main() 
{
	if(axiaInit())
		return 100;

	AxiaWindow win = axiaCreateWindow(900, 900, "Please work, Axia!", AXIA_WIN_DEFAULT);
	if(win == NULL)
		return 25;

	AxiaAudioPlayer player = axiaCreateAudioPlayer(1, 0, 1);
	if(player == NULL)
		return 34567;
	AxiaShape shape = axiaCreateRectangle(axiaVec2( 2, 2 ), axiaVec3( -1, -1, 0 ));
	AxiaTexture tex = axiaCreateTexture();
	axiaLoadFromImage(tex, "/home/emanuel/Pictures/New_Sun.png");
	
	axiaBindShapeTexture(shape, tex);

	axiaClearColorFloat(0.3, 0.3, 0.3, 1);

	if(axiaLoadSoundFromFile(player, 0, "/home/emanuel/Documents/Dev/C/AudioTest/sound.wav", 0, AXIA_SOUND_DECODE) != AXIA_OK)
		return 998;

	printf("length in sec: %f\nlength in pcm: %ld\n", axiaGetSoundLengthSec(player,0), axiaGetSoundLengthPcmFrames(player,0));
	axiaSetSoundState(player, 0, AXIA_SOUND_START);

	while(axiaIsWinOpen(win))
	{
		axiaPollEvents();

		axiaClear();

		axiaDrawShape(shape);

		axiaDisplay(win);
	}

	axiaDestroyAudioPlayer(&player);
	axiaDestroyTexture(&tex);
	axiaDestroyShape(&shape);
	axiaDestroyWindow(&win);

	printf("%x\n", glGetError());
	axiaDeinit();

	return 0;
}
