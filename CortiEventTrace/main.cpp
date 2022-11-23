#define AUTO_DLLMAIN

// Allgemeine Includes
#include <DynRPG/DynRPG.h>

#include <algorithm>    // Helper
#include <fstream>      // Helper

#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <time.h>

// Aus meinem Project1
#include "helper.cpp"
#include "EventLookup.cpp"
#include "CortiFileOperations.cpp"

// We store the configuration here
std::map<std::string, std::string> configuration;

// Gibt an, dass dauerhaft geloggt werden soll.
bool configRunAlways = false;
// Die ID des Switches mit dem das Feature aktiviert wird.
int configRunSwitchId = 0;
// Gibt an, ob die Dateiausgabe bereits initalisiert wurde.
bool initDone = false;

// Initialize pose types on-startup
bool onStartup (char *pluginName)
{
    // We load the configuration from the DynRPG.ini file here
    configuration = RPG::loadConfiguration(pluginName);

    if(configuration.count("RunAlways"))
    {
        int value = atoi(configuration["RunAlways"].c_str());
        if(value>0)
        {
            configRunAlways = true;
        }
    }

    if(configuration.count("RunSwitchId"))
    {
        int value = atoi(configuration["RunSwitchId"].c_str());
        if(value>0)
        {
            configRunSwitchId = value;
        }
    }

    return true;
}

// Ausgelöst bei Spielstart nachdem Makerdaten vorhanden sind.
void onInitFinished()
{
    FillLookup();
}

// Aufgerufen wenn das Spiel beendet wird.
void onExit()
{
    CortiFile::Exit();
}

// Bei Kommentar
bool onEventCommand (
    RPG::EventScriptLine* scriptLine,
    RPG::EventScriptData* scriptData,
    int eventId,
    int pageId,
    int lineId,
    int* nextLineId )
{
    // Abbrechen der Funktion
    if(!configRunAlways)
    {
        // Switch ist konfiguriert
        if(configRunSwitchId<=0)
        {
            return true;
        }
        else
        {
            if(!RPG::switches[configRunSwitchId])
            {
                return true;
            }
        }
    }

    if(!initDone)
    {
        CortiFile::Init();
        initDone = true;
    }

    std::ostringstream outLine;
    if(evcmdNames.count(scriptLine->command)>0)
    {
        outLine << "Evcmd[" << evcmdNames[scriptLine->command] << "]";
    }
    else
    {
        outLine << "Evcmd[" << scriptLine->command << "]";
    }

    outLine << " EventId[" << eventId << "] PageId[" << pageId << "] lineId[" << lineId << "] ";

    if(scriptLine->parameters.size>0)
    {
        outLine << " IntPar[" << scriptLine->parameters.size << "] ";
        for(int i = 0; i < scriptLine->parameters.size; i++)
        {
            outLine << scriptLine->parameters[i] << ", ";
        }
    }

    if(scriptLine->stringParameter.length() > 0)
    {
        outLine << "Str.Par " << scriptLine->stringParameter.s_str();
    }

    CortiFile::LogLine("EVENT",outLine.str());

    return true;
}

// This function is called after every frame
/*
void onFrame(RPG::Scene scene)
{
    // D:\Daten\Privat\CortiPluginsTest\DynPlugins\CortiTrace\main.cpp|72|error: invalid conversion from 'void (*)(std::string, std::string)' to 'int'|
    RPG::variables[124] = (int)&CortiFile::LogLine;

    void (*foo)(std::string, std::string);
    foo = &CortiFile::LogLine;
} */
