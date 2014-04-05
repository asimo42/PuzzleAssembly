#pragma once

#include <dshow.h>
#include <string>

class SoundEffectPlayer
{
public:
	SoundEffectPlayer(void);
	~SoundEffectPlayer(void);
	int play_Sound(std::string filename);

private:
	IGraphBuilder *pGraph;
    IMediaControl *pControl;
    IMediaEvent   *pEvent;
	HRESULT hr;
};

