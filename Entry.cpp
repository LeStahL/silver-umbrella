#include <QApplication>
#include <QDebug>

#include "Windows.h"
#include "MainWindow.hpp"
#include "MIDIMessage.hpp"

HMIDIOUT outputDevices[4];
int playing[] = {0,0,0,0},
    notes[] = {0,0,0,0};
HMIDIIN inputDevice;

void CALLBACK inputCallback(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
    if(wMsg == MIM_DATA)
    {
        MidiMessage message(dwParam1, dwParam2);
        qDebug() << message.toString();
        
        if(message.isNoteOn()) // NOTE_ON
        {
            // Determine a synth that is not playing
            int nPlaying;
            for(nPlaying = 0; nPlaying < 4; ++nPlaying)
                if(playing[nPlaying] == 0) break;
            if(nPlaying == 4) return;
            printf("on nplaying: %d\n", nPlaying);
            midiOutShortMsg(outputDevices[nPlaying], dwParam1);
            playing[nPlaying] = 1;
            notes[nPlaying] = message.byte(1);
        }
        else if(message.isNoteOff()) // NOTE_OFF
        {
            // Determine which synth plays that note
            int nPlaying;
            for(nPlaying = 0; nPlaying < 4; ++nPlaying)
                if(notes[nPlaying] == message.byte(1)) break;
            if(nPlaying == 4) return;
            printf("off nplaying: %d\n", nPlaying);
            midiOutShortMsg(outputDevices[nPlaying], dwParam1);
            playing[nPlaying] = 0;
            notes[nPlaying] = message.byte(1);
        }
    }
    
	return;
}

int main(int argc, char **args)
{
    QApplication *application = new QApplication(argc, args);
    
    MainWindow *mainWindow = new MainWindow(application, nullptr);
    mainWindow->show();
    
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
    
    // Outputs
    printf("Available MIDI output devices:\n");
    {
        int nDevices = midiOutGetNumDevs();
        MIDIOUTCAPS capabilities;
        for(int i=0; i<nDevices; ++i)
        {
            midiOutGetDevCaps(i, &capabilities, sizeof(MIDIOUTCAPS));
            printf("%s\n", capabilities.szPname);
            
            if(!strcmp(capabilities.szPname, "MIDISPORT 4x4 Anniv"))
                midiOutOpen(&(outputDevices[0]), i, 0, 0, CALLBACK_NULL);
            if(!strcmp(capabilities.szPname, "MIDIOUT2 (MIDISPORT 4x4 Anniv)"))
                midiOutOpen(&(outputDevices[1]), i, 0, 0, CALLBACK_NULL);
            if(!strcmp(capabilities.szPname, "MIDIOUT3 (MIDISPORT 4x4 Anniv)"))
                midiOutOpen(&(outputDevices[2]), i, 0, 0, CALLBACK_NULL);
            if(!strcmp(capabilities.szPname, "MIDIOUT4 (MIDISPORT 4x4 Anniv)"))
                midiOutOpen(&(outputDevices[3]), i, 0, 0, CALLBACK_NULL);
        }
    }

    return application->exec();
}
