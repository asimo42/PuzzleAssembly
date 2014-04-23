#pragma once

#include <dshow.h>
#include <string>

class SoundEffectPlayer
{
public:
	SoundEffectPlayer(void);
	~SoundEffectPlayer(void);
	int play_Sound(std::string filename);
	int playRandomPiecePlacedSound();
	std::string getSound(int sound_num);
private:
	IGraphBuilder *pGraph;
    IMediaControl *pControl;
    IMediaEvent   *pEvent;
	HRESULT hr;
	static const int NUM_SOUNDS = 7; //Number of piece placed sounds
	std::string sound_piece_placed1;
	std::string sound_piece_placed2;
	std::string sound_piece_placed3;
	std::string sound_piece_placed4;
	std::string sound_piece_placed5;
	std::string sound_piece_placed6;
	std::string sound_piece_placed7;
};

