//========================================//
//  This file contains the declaration    //
//  of AxiaAudioPlayer and related        //
//  funtions, which are used              //
//  for playing and managing different    //
//  form of audio, as well as giving      //
//  support for things such as            //
//  tridimensional positioning of         //
//  sounds.                               //
//                                        //
//  This part of axialotl depends on the  //
//  audio library miniaudio, which is     //
//  included only in sound.c to allow     //
//  developers exclude this part of       //
//  axialotl if they so wish.             //
//                                        //
//  Also, miniaudio is a cool library :)  //
//========================================//

#pragma once

#include "../dependencies/deps.h"

///////////////////////////////
// See sound.c for definition
typedef struct AxiaAudioPlayer_t *AxiaAudioPlayer;

typedef enum {
	AXIA_SOUND_STREAM            = 0x01,
	AXIA_SOUND_DECODE            = 0x02,
	AXIA_SOUND_NO_PITCH          = 0x04,
	AXIA_SOUND_NO_SPATIALIZATION = 0x08,
	AXIA_SOUND_LOOPING           = 0x10,
} AxiaSoundInitFlags;

typedef enum {
	AXIA_SOUND_START = 0x0,
	AXIA_SOUND_STOP  = 0x1,
} AxiaSoundState;

AxiaAudioPlayer axiaCreateAudioPlayer(uint32_t listener_count, 
                                      uint32_t sound_group_count, 
									  uint32_t sound_count);

void axiaDestroyAudioPlayer(AxiaAudioPlayer*);

AxiaError axiaLoadSoundFromFile(AxiaAudioPlayer,       uint32_t sound_index, 
                                const char *file_path, uint32_t sound_group_index,
								AxiaSoundInitFlags);

void axiaSetSoundState(AxiaAudioPlayer, uint32_t sound_index, AxiaSoundState);

void axiaSetSoundFadeIOFrames(AxiaAudioPlayer, 
                              uint32_t sound_index, uint64_t fade_frames, 
                              float volume_start, float volume_end);

void axiaSetSoundFadeIOMiliSec(AxiaAudioPlayer, 
                              uint32_t sound_index, uint64_t fade_frames, 
                              float volume_start, float volume_end);

void axiaSetSoundVolume(AxiaAudioPlayer, uint32_t sound_index, float volume);

float axiaGetSoundVolume(AxiaAudioPlayer, uint32_t sound_index);

void axiaSetSoundPitch(AxiaAudioPlayer, uint32_t sound_index, float pitch);

float axiaGetSoundPitch(AxiaAudioPlayer, uint32_t sound_index);

void axiaSetSoundPosition(AxiaAudioPlayer, uint32_t sound_index, AxiaVec3 position);

AxiaVec3 axiaGetSoundPosition(AxiaAudioPlayer, uint32_t sound_index);

void axiaSetSoundDirection(AxiaAudioPlayer, uint32_t sound_index, AxiaVec3 direction);

AxiaVec3 axiaGetSoundDirection(AxiaAudioPlayer, uint32_t sound_index);

void axiaSetSoundLooping(AxiaAudioPlayer, uint32_t sound_index, bool looping);

bool aixaIsSoundLooping(AxiaAudioPlayer, uint32_t sound_index);

float axiaGetSoundLengthSec(AxiaAudioPlayer, uint32_t sound_index);

uint64_t axiaGetSoundLengthPcmFrames(AxiaAudioPlayer, uint32_t sound_index);

void axiaSoundSeekPcmFrame(AxiaAudioPlayer, uint32_t sound_index, uint64_t frame);

void axiaSetSoundGroupVolume(AxiaAudioPlayer, uint32_t group_index, float volume);

float axiaGetSoundGroupVolume(AxiaAudioPlayer, uint32_t group_index);

void axiaSetSoundGroupPitch(AxiaAudioPlayer, uint32_t group_index, float pitch);

float axiaGetSoundGroupPitch(AxiaAudioPlayer, uint32_t group_index);
