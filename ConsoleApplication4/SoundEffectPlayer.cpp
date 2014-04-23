#include "stdafx.h"
#include "SoundEffectPlayer.h"
#include <cstdlib>
#include <time.h>

SoundEffectPlayer::SoundEffectPlayer(void)
{
    // Initialize the COM library.
    hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        printf("ERROR - Could not initialize COM library");
    }
	// seed random number generator used to play random sounds
	srand(time(NULL));

	sound_piece_placed1 = "guitar1.mp3";
	sound_piece_placed2 = "guitar2.mp3";
	sound_piece_placed3 = "guitar3.mp3";
	sound_piece_placed4 = "guitar4.mp3";
	sound_piece_placed5 = "guitar5.mp3";
	sound_piece_placed6 = "guitar6.mp3";
	sound_piece_placed7 = "guitar7.mp3";
}


SoundEffectPlayer::~SoundEffectPlayer(void)
{
	pControl->Release();
    pEvent->Release();
    pGraph->Release();
    CoUninitialize();
}

int SoundEffectPlayer::play_Sound(std::string filename)
{
	// Conver string to wide-character string
	std::wstring stemp = std::wstring(filename.begin(), filename.end());
	LPCWSTR sw = stemp.c_str();

    pGraph = NULL;
    pControl = NULL;
    pEvent = NULL;

    // Create the filter graph manager and query for interfaces.
    hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
                        IID_IGraphBuilder, (void **)&pGraph);
    if (FAILED(hr))
    {
        printf("ERROR - Could not create the Filter Graph Manager.");
    }

	hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
    hr = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);

    // Build the graph.
    hr = pGraph->RenderFile(sw, NULL);
    if (SUCCEEDED(hr))
    {
        // Run the graph.
        hr = pControl->Run();
/*	
        if (SUCCEEDED(hr))
        {
            // Wait for completion.
            long evCode;
            pEvent->WaitForCompletion(INFINITE, &evCode);

            // Note: Do not use INFINITE in a real application, because it
            // can block indefinitely.
        }
*/
		
    }
	return 0;
}

int SoundEffectPlayer::playRandomPiecePlacedSound()
{
	int rand_num = rand() % NUM_SOUNDS + 1; //random number from 1 - NUM_SOUNDS
	switch(rand_num) {
		case 1: play_Sound(sound_piece_placed1);
			break;
		case 2: play_Sound(sound_piece_placed2);
			break;
		case 3: play_Sound(sound_piece_placed3);
			break;
		case 4: play_Sound(sound_piece_placed4);
			break;
		case 5: play_Sound(sound_piece_placed5);
			break;
		case 6: play_Sound(sound_piece_placed6);
			break;
		case 7: play_Sound(sound_piece_placed7);
			break;
		default:
			printf("playRandomPiecePlacedSound(): Sound not available");
			return -1;
	}
	return 0;	
}

string SoundEffectPlayer::getSound(int sound_num)
{
		switch(sound_num) {
		case 1: return sound_piece_placed1;
			break;
		case 2: return sound_piece_placed1;
			break;
		case 3: return sound_piece_placed1;
			break;
		case 4: return sound_piece_placed1;
			break;
		case 5: return sound_piece_placed1;
			break;
		case 6: return sound_piece_placed1;
			break;
		case 7: return sound_piece_placed1;
			break;
		default:
			printf("getSound(): Sound not available.");
		}
}