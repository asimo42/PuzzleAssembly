#include "stdafx.h"
#include "SoundEffectPlayer.h"


SoundEffectPlayer::SoundEffectPlayer(void)
{
    // Initialize the COM library.
    hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        printf("ERROR - Could not initialize COM library");
    }
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
