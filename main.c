#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Windows.h>

HMIDIOUT outputDevices[4];
int playing[] = {0,0,0,0},
    notes[] = {0,0,0,0};
HMIDIIN inputDevice;

void CALLBACK inputCallback(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
    if(wMsg == MIM_DATA)
    {
        BYTE b1 = (dwParam1 >> 24) & 0xFF,
            b2 = (dwParam1 >> 16) & 0xFF,
            b3 = (dwParam1 >> 8) & 0xFF,
            b4 = dwParam1 & 0xFF;
        BYTE b3lo = b3 & 0xF,
            b3hi = (b3 >> 4) & 0xF,
            b4lo = b4 & 0xF,
            b4hi = (b4 >> 4) & 0xF;
        
        BYTE channel = b4lo,
            button = b3;
        
        printf("input: wMsg=MIM_DATA, dwParam1=%08x, byte=%02x %02x h_%01x l_%01x %02x, dwParam2=%08x\n", dwParam1, b1, b2, b3hi, b3lo, b4, dwParam2);
        
        if(b4 == 0x90) // NOTE_ON
        {
            // Determine a synth that is not playing
            int nPlaying = 0;
            for(; nPlaying<4; ++nPlaying)
                if(!playing[nPlaying]) break;
            midiOutShortMsg(outputDevices[nPlaying], dwParam1);
            playing[nPlaying] = 1;
            notes[nPlaying] = b3;
        }
        else if(b4 == 0x80) // NOTE_OFF
        {
            // Determine which synth plays that note
            int nPlaying = 0;
            for(; nPlaying<4; ++nPlaying)
                if(notes[nPlaying] == b3)break;
            midiOutShortMsg(outputDevices[nPlaying], dwParam1);
            playing[nPlaying] = 0;
        }
    }
    
	return;
}

int WINAPI demo(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Enable terminal again
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

    // Inputs
    printf("Available MIDI input devices:\n");
    {
        int nDevices = midiInGetNumDevs();
        MIDIINCAPS capabilities;
        for(int i=0; i<nDevices; ++i)
        {
            midiInGetDevCaps(i, &capabilities, sizeof(MIDIINCAPS));
            printf("%s\n", capabilities.szPname);
            
            if(!strcmp(capabilities.szPname, "MIDISPORT 4x4 Anniv"))
                midiInOpen(&inputDevice, i, (DWORD)(void*)inputCallback, 0, CALLBACK_FUNCTION);
            
            midiInStart(inputDevice);
        }
    }
    
    // Inputs
    printf("Available MIDI output devices:\n");
    {
        int nDevices = midiOutGetNumDevs();
        MIDIOUTCAPS capabilities;
        for(int i=0; i<nDevices; ++i)
        {
            midiOutGetDevCaps(i, &capabilities, sizeof(MIDIOUTCAPS));
            printf("%s\n", capabilities.szPname);
            
            if(!strcmp(capabilities.szPname, "MIDISPORT 4x4 Anniv"))
                midiOutOpen(&outputDevices[0], i, 0, 0, CALLBACK_NULL);
            else if(!strcmp(capabilities.szPname, "MIDIOUT2 (MIDISPORT 4x4 Anniv)"))
                midiOutOpen(&outputDevices[1], i, 0, 0, CALLBACK_NULL);
            else if(!strcmp(capabilities.szPname, "MIDIOUT3 (MIDISPORT 4x4 Anniv)"))
                midiOutOpen(&outputDevices[2], i, 0, 0, CALLBACK_NULL);
            else if(!strcmp(capabilities.szPname, "MIDIOUT4 (MIDISPORT 4x4 Anniv)"))
                midiOutOpen(&outputDevices[3], i, 0, 0, CALLBACK_NULL);
        }
    }
    
    // Waste time until someone clicks X
    while(1);
}
