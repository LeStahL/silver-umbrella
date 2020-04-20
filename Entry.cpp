#include <QApplication>
#include <QDebug>

#include "Windows.h"
#include "MainWindow.hpp"
#include "MIDIMessage.hpp"
#include "InputController.hpp"
#include "OutputController.hpp"

int main(int argc, char **args)
{
    QApplication *application = new QApplication(argc, args);
    
    MainWindow *mainWindow = new MainWindow(application, nullptr);
    mainWindow->show();
    
    // Outputs
    QList<OutputController *> outputControllers;
    printf("Available MIDI output devices:\n");
    {
        int nDevices = midiOutGetNumDevs();
        MIDIOUTCAPS capabilities;
        for(int i=0; i<nDevices; ++i)
        {
            midiOutGetDevCaps(i, &capabilities, sizeof(MIDIOUTCAPS));
            printf("%s\n", capabilities.szPname);
            
            if(!strcmp(capabilities.szPname, "MIDISPORT 4x4 Anniv"))
                outputControllers.push_back(new OutputController(i));
            if(!strcmp(capabilities.szPname, "MIDIOUT2 (MIDISPORT 4x4 Anniv)"))
                outputControllers.push_back(new OutputController(i));
            if(!strcmp(capabilities.szPname, "MIDIOUT3 (MIDISPORT 4x4 Anniv)"))
                outputControllers.push_back(new OutputController(i));
            if(!strcmp(capabilities.szPname, "MIDIOUT4 (MIDISPORT 4x4 Anniv)"))
                outputControllers.push_back(new OutputController(i));
        }
    }
    
    // Inputs
    QList<InputController *> inputControllers;
    printf("Available MIDI input devices:\n");
    {
        int nDevices = midiInGetNumDevs();
        MIDIINCAPS capabilities;
        for(int i=0; i<nDevices; ++i)
        {
            midiInGetDevCaps(i, &capabilities, sizeof(MIDIINCAPS));
            printf("%s\n", capabilities.szPname);
            
            if(!strcmp(capabilities.szPname, "MIDISPORT 4x4 Anniv"))
                inputControllers.push_back(new InputController(i, &outputControllers));
        }
    }

    application->exec();

    for(int i=0; i<outputControllers.size(); ++i) delete outputControllers.at(i);
    for(int i=0; i<inputControllers.size(); ++i) delete inputControllers.at(i);
    
    return 0;
}
