//=====================================//
//  This file contains the definition  //
//  of both struct and functions       //
//  declared in sound.h, as well as    //
//  being the only file that includes  //
//  miniaudio.h                        //
//=====================================//

#include "sound.h"
#include "../dependencies/miniaudio/miniaudio.h"

//========================//
//  Debug error messeges  //
//========================//

#ifdef AXIA_DEBUG
static const char *player_is_null = "[axia%s] AxiaAudioPlayer is NULL\n";
static const char *sound_out_of_bounds = "[axia%s] sound_index is out of bounds\n";
static const char *group_out_of_bounds = "[axia%s] group_index is out of bounds\n";
#else
#define player_is_null      ""
#define sound_out_of_bounds ""
#define group_out_of_bounds ""
#endif

//=====================//
//  struct definition  //
//=====================//

typedef struct {
	bool     initialized;
	ma_sound sound;
} AxiaSound;

struct AxiaAudioPlayer_t 
{
	ma_engine       engine;
	uint32_t        listener_count;
	uint32_t        sound_group_count;
	ma_sound_group *sound_groups;
	uint32_t        sound_count;
	AxiaSound      *sounds;
};

//=============//
//  Functions  //
//=============//

AxiaAudioPlayer axiaCreateAudioPlayer(uint32_t listener_count, 
                                      uint32_t sound_group_count, 
									  uint32_t sound_count)
{
	AxiaAudioPlayer player = malloc(sizeof(struct AxiaAudioPlayer_t));
	if(player == NULL) {
		axiaprintdbg("Failed to allocate AxiaAudioPlayer\n");
		return NULL;
	}

	player->listener_count    = listener_count;
	player->sound_group_count = sound_group_count;
	player->sound_count       = sound_count;	

	ma_engine_config conf = ma_engine_config_init();
	conf.listenerCount = listener_count;

	if(ma_engine_init(&conf, &player->engine) != MA_SUCCESS) {
		axiaprintdbg("Failed to create a miniaudio engine\n");
		free(player);
		return NULL;
	}

	if(sound_group_count != 0) {
		player->sound_groups = malloc(sizeof(ma_sound_group) * sound_group_count);

		if(player->sound_groups == NULL) {
			axiaprintdbg("Failed to allocate space for the sound groups\n");
			axiaDestroyAudioPlayer(&player);
			return NULL;
		}
		
		for(uint32_t i=0;i<sound_group_count;++i) {
			if(ma_sound_group_init(&player->engine, 0, NULL, &player->sound_groups[i]) != MA_SUCCESS) {
				axiaprintdbg("Failed create the sound group indexed %d\n", i);
				player->sound_group_count = i;
				axiaDestroyAudioPlayer(&player);
				return NULL;
			}
		}
	}
	else
		player->sound_groups = NULL;

	if(sound_count == 0)
		sound_count += 1;

	player->sounds = malloc(sizeof(AxiaSound) * sound_count);
	if(player->sounds == NULL) {
		axiaprintdbg("Failed to allocate space for the sounds\n");
		axiaDestroyAudioPlayer(&player);
		return NULL;
	}	

	for(uint32_t i=0;i<sound_count;++i) {
		player->sounds[i].initialized = false;
	}

	return player;
}

void axiaDestroyAudioPlayer(AxiaAudioPlayer *audio_player)
{
	if(audio_player == NULL)
		return;

	AxiaAudioPlayer player = *audio_player;

	if(player->sounds != NULL) {
		for(uint32_t i=0;i<player->sound_count;++i) {
			if(player->sounds[i].initialized) 
				ma_sound_uninit(&player->sounds[i].sound);
		}
		free(player->sounds);
	}

	if(player->sound_groups != NULL) {
		for(uint32_t i=0;i<player->sound_group_count;++i) {
			ma_sound_group_uninit(&player->sound_groups[i]);
		}
		free(player->sound_groups);
	}

	ma_engine_uninit(&player->engine);

	free(player);
	*audio_player = NULL;
}

AxiaError axiaLoadSoundFromFile(AxiaAudioPlayer audio_player, uint32_t sound_index, 
                                const char *file_path, uint32_t sound_group_index,
								AxiaSoundInitFlags flags)
{
	axiacheckarg(audio_player == NULL, AXIA_INVALID_ARG, 
	             player_is_null, "LoadSoundFromFile");

	axiacheckarg(sound_index >= audio_player->sound_count,
	          AXIA_OUT_OF_BOUNDS,
	          sound_out_of_bounds, "LoadSoundFromFile");

	if(audio_player->sounds[sound_index].initialized)
		ma_sound_uninit(&audio_player->sounds[sound_index].sound);

	uint32_t mini_flags = 0;
	if((flags & AXIA_SOUND_STREAM) != 0)
		mini_flags |= MA_SOUND_FLAG_STREAM;
	else
		mini_flags |= MA_SOUND_FLAG_DECODE;

	if((flags & AXIA_SOUND_NO_PITCH) != 0)
		mini_flags |= MA_SOUND_FLAG_NO_PITCH;
	if((flags & AXIA_SOUND_NO_SPATIALIZATION) != 0)
		mini_flags |= MA_SOUND_FLAG_NO_SPATIALIZATION;	

	ma_result r = ma_sound_init_from_file(&audio_player->engine, 
	                        file_path, 
	                        flags, 
	                        (sound_group_index < audio_player->sound_group_count)? 
	                        	&audio_player->sound_groups[sound_group_index] : NULL,
	                        NULL, 
	                        &audio_player->sounds[sound_index].sound);

	if(r != MA_SUCCESS) 
		return AXIA_LODING_FAILED;

	if((mini_flags & AXIA_SOUND_LOOPING) != 0)
		ma_sound_set_looping(&audio_player->sounds[sound_index].sound, true);

	return AXIA_OK;
}

void axiaSetSoundState(AxiaAudioPlayer audio_player, 
                       uint32_t sound_index, AxiaSoundState state)
{
	axiacheckarg(audio_player == NULL,,
	             player_is_null, "SetSoundState");

	axiacheckarg(sound_index >= audio_player->sound_count,,
	             sound_out_of_bounds, "SetSoundState");

	if(state == AXIA_SOUND_START)
		ma_sound_start(&audio_player->sounds[sound_index].sound);
	else
		ma_sound_stop(&audio_player->sounds[sound_index].sound);
}

void axiaSetSoundFadeIOFrames(AxiaAudioPlayer audio_player, 
                              uint32_t sound_index, uint64_t fade_frames, 
                              float volume_start, float volume_end)
{
	axiacheckarg(audio_player == NULL,,
	             player_is_null, "SetSoundFadeIOFrames");

	axiacheckarg(sound_index >= audio_player->sound_count,,
	             sound_out_of_bounds, "SetSoundFadeIOFrames");

	ma_sound_set_fade_in_pcm_frames(&audio_player->sounds[sound_index].sound,
	                                volume_start, volume_end, fade_frames);
}

void axiaSetSoundFadeIOMiliSec(AxiaAudioPlayer audio_player, 
                              uint32_t sound_index, uint64_t fade_secs, 
                              float volume_start, float volume_end)
{
	axiacheckarg(audio_player == NULL,,
	             player_is_null, "SetSoundFadeIOMiliSec");

	axiacheckarg(sound_index >= audio_player->sound_count,,
	             sound_out_of_bounds, "SetSoundFadeIOMiliSec");

	ma_sound_set_fade_in_milliseconds(&audio_player->sounds[sound_index].sound,
	                                  volume_start, volume_end, fade_secs);
}

void axiaSetSoundVolume(AxiaAudioPlayer audio_player, uint32_t sound_index, float volume)
{
	axiacheckarg(audio_player == NULL,,
	             player_is_null, "SetSoundVolume");

	axiacheckarg(sound_index >= audio_player->sound_count,,
	             sound_out_of_bounds, "SetSoundVolume");

	ma_sound_set_volume(&audio_player->sounds[sound_index].sound, volume);
}

float axiaGetSoundVolume(AxiaAudioPlayer audio_player, uint32_t sound_index)
{
	axiacheckarg(audio_player == NULL, -100.f,
	             player_is_null, "GetSoundVolume");

	axiacheckarg(sound_index >= audio_player->sound_count, -200.f,
	             sound_out_of_bounds, "GetSoundVolume");

	if(audio_player == NULL)
		return -100.f;

	if(sound_index >= audio_player->sound_count)
		return -200.f;

	return ma_sound_get_volume(&audio_player->sounds[sound_index].sound);
}

void axiaSetSoundPitch(AxiaAudioPlayer audio_player, uint32_t sound_index, float pitch)
{
	axiacheckarg(audio_player == NULL,,
	             player_is_null, "SetSoundPitch");

	axiacheckarg(sound_index >= audio_player->sound_count,,
	             sound_out_of_bounds, "SetSoundPitch");

	ma_sound_set_pitch(&audio_player->sounds[sound_index].sound, pitch);
}

float axiaGetSoundPitch(AxiaAudioPlayer audio_player, uint32_t sound_index)
{
	axiacheckarg(audio_player == NULL,-100.f,
	             player_is_null, "GetSoundPitch");

	axiacheckarg(sound_index >= audio_player->sound_count,-200.f,
	             sound_out_of_bounds, "GetSoundPitch");

	return ma_sound_get_pitch(&audio_player->sounds[sound_index].sound);
}

void axiaSetSoundPosition(AxiaAudioPlayer audio_player, uint32_t sound_index, 
                          AxiaVec3 position)
{
	axiacheckarg(audio_player == NULL,,
	             player_is_null, "SetSoundPosition");

	axiacheckarg(sound_index >= audio_player->sound_count,,
	             sound_out_of_bounds, "SetSoundPosition");

	ma_sound_set_position(&audio_player->sounds[sound_index].sound,
	                      position.x, position.y, position.z);
}

AxiaVec3 axiaGetSoundPosition(AxiaAudioPlayer audio_player, uint32_t sound_index)
{
	axiacheckarg(audio_player == NULL, axiaVec3(0,0,0),
	             player_is_null, "GetSoundPosition");

	axiacheckarg(sound_index >= audio_player->sound_count, axiaVec3(0,0,0),
	             sound_out_of_bounds, "GetSoundPosition");

	ma_vec3f temp;
	temp = ma_sound_get_position(&audio_player->sounds[sound_index].sound);
	return axiaVec3(temp.x, temp.y, temp.z);
}

void axiaSetSoundDirection(AxiaAudioPlayer audio_player, uint32_t sound_index, 
                           AxiaVec3 direction)
{
	axiacheckarg(audio_player == NULL,,
	             player_is_null, "SetSoundDirection");

	axiacheckarg(sound_index >= audio_player->sound_count,,
	             sound_out_of_bounds, "SetSoundDirection");

	ma_sound_set_direction(&audio_player->sounds[sound_index].sound,
	                      direction.x, direction.y, direction.z);
}

AxiaVec3 axiaGetSoundDirection(AxiaAudioPlayer audio_player, uint32_t sound_index)
{
	axiacheckarg(audio_player == NULL, axiaVec3(0,0,0),
	             player_is_null, "GetSoundDirection");

	axiacheckarg(sound_index >= audio_player->sound_count, axiaVec3(0,0,0),
	             sound_out_of_bounds, "GetSoundDirection");

	ma_vec3f temp;
	temp = ma_sound_get_direction(&audio_player->sounds[sound_index].sound);
	return axiaVec3(temp.x, temp.y, temp.z);
}

void axiaSetSoundLooping(AxiaAudioPlayer audio_player, 
                         uint32_t sound_index, bool looping)
{
	axiacheckarg(audio_player == NULL,,
	             player_is_null, "SetSoundLooping");

	axiacheckarg(sound_index >= audio_player->sound_count,,
	             sound_out_of_bounds, "SetSoundLooping");

	ma_sound_set_looping(&audio_player->sounds[sound_index].sound, looping);
}

bool aixaIsSoundLooping(AxiaAudioPlayer audio_player, uint32_t sound_index)
{
	axiacheckarg(audio_player == NULL, false,
	             player_is_null, "IsSoundLooping");

	axiacheckarg(sound_index >= audio_player->sound_count, false,
	             sound_out_of_bounds, "IsSoundLooping");

	return ma_sound_is_looping(&audio_player->sounds[sound_index].sound);
}

float axiaGetSoundLengthSec(AxiaAudioPlayer audio_player, uint32_t sound_index)
{
	axiacheckarg(audio_player == NULL, 0,
	             player_is_null, "GetSoundLengthSec");

	axiacheckarg(sound_index >= audio_player->sound_count, 0,
	             sound_out_of_bounds, "GetSoundLengthSec");

	float len;
	if(ma_sound_get_length_in_seconds(
	       &audio_player->sounds[sound_index].sound, &len) != MA_SUCCESS)
		return 0;

	return len; 
}

uint64_t axiaGetSoundLengthPcmFrames(AxiaAudioPlayer audio_player, uint32_t sound_index)
{
	axiacheckarg(audio_player == NULL, 0,
	             player_is_null, "GetSoundLengthPcmFrames");

	axiacheckarg(sound_index >= audio_player->sound_count, 0,
	             sound_out_of_bounds, "GetSoundLengthPcmFrames");

	uint64_t len;
	if(ma_sound_get_length_in_pcm_frames(
	       &audio_player->sounds[sound_index].sound, (ma_uint64*)&len) != MA_SUCCESS)
		return 0;

	return len; 
}

void axiaSoundSeekPcmFrame(AxiaAudioPlayer audio_player, 
                           uint32_t sound_index, uint64_t frame)
{
	axiacheckarg(audio_player == NULL,,
	             player_is_null, "SoundSeekPcmFrame");

	axiacheckarg(sound_index >= audio_player->sound_count,,
	             sound_out_of_bounds, "SoundSeekPcmFrame");
	
	ma_sound_seek_to_pcm_frame(&audio_player->sounds[sound_index].sound, frame);
}

void axiaSetSoundGroupVolume(AxiaAudioPlayer audio_player, 
                             uint32_t group_index, float volume)
{
	axiacheckarg(audio_player == NULL,,
	             player_is_null, "SetSoundGroupVolume");

	axiacheckarg(group_index >= audio_player->sound_count,,
	             sound_out_of_bounds, "SetSoundGroupVolume");

	ma_sound_group_set_volume(&audio_player->sound_groups[group_index], volume);
}

float axiaGetSoundGroupVolume(AxiaAudioPlayer audio_player, uint32_t group_index)
{
	axiacheckarg(audio_player == NULL, 0,
	             player_is_null, "GetSoundGroupVolume");

	axiacheckarg(group_index >= audio_player->sound_count, 0,
	             sound_out_of_bounds, "GetSoundGroupVolume");

	return ma_sound_group_get_volume(&audio_player->sound_groups[group_index]);
}

void axiaSetSoundGroupPitch(AxiaAudioPlayer audio_player, 
                             uint32_t group_index, float pitch)
{
	axiacheckarg(audio_player == NULL,,
	             player_is_null, "SetSoundGroupPitch");

	axiacheckarg(group_index >= audio_player->sound_count,,
	             sound_out_of_bounds, "SetSoundGroupPitch");

	ma_sound_group_set_pitch(&audio_player->sound_groups[group_index], pitch);
}

float axiaGetSoundGroupPitch(AxiaAudioPlayer audio_player, uint32_t group_index)
{
	axiacheckarg(audio_player == NULL, 0,
	             player_is_null, "GetSoundGroupPitch");

	axiacheckarg(group_index >= audio_player->sound_count, 0,
	             sound_out_of_bounds, "GetSoundGroupPitch");

	return ma_sound_group_get_pitch(&audio_player->sound_groups[group_index]);
}
