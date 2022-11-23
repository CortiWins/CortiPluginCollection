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
#include "CortiFileOperations.cpp"

// We store the configuration here
std::map<std::string, std::string> configuration;

// Initialize pose types on-startup
bool onStartup (char *pluginName)
{
    // We load the configuration from the DynRPG.ini file here
    configuration = RPG::loadConfiguration(pluginName);
    return true;
}

// Ausgelöst bei Spielstart nachdem Makerdaten vorhanden sind.
void onInitFinished()
{
    CortiFile::Init();
}

// Aufgerufen wenn das Spiel beendet wird.
void onExit()
{
    CortiFile::Exit();
}

void WorkComment(const RPG::ParsedCommentData *parsedData, std::string category)
{
    // Datenstrom erstellen. Kann nun beliebig gefüllt werden.
    std::ostringstream dataStream;

    int numParams = parsedData->parametersCount;
    if(numParams>0)
    {
        // Helper::ShowInfoBox((int)numParams,"[CortiLogs] Debug: numParams");
        for(int i = 0; i < numParams ; i++)
        {
            RPG::ParsedCommentParameterType type = parsedData->parameters[i].type;
            if(type == RPG::PARAM_NUMBER)
            {
                double doubleValue = parsedData->parameters[i].number;
                dataStream << doubleValue << " ";
                // Helper::ShowInfoBox((int)doubleValue,"[CortiLogs] Debug: Num");
            }
            else
            {
                std::string strriii = parsedData->parameters[i].text;
                dataStream << strriii << " ";
                // Helper::ShowInfoBoxString(strriii,"[CortiLogs] Debug: Text");
            }
        }
    }

    CortiFile::LogLine(category, dataStream.str());
}

bool onComment(
    const char *text,
    const RPG::ParsedCommentData *parsedData,
    RPG::EventScriptLine *nextScriptLine,
    RPG::EventScriptData *scriptData,
    int	eventId,
    int pageId,
    int lineId,
    int *nextLineId)
{
    if(!strcmp(parsedData->command, "corti_log"))
    {
        WorkComment(parsedData,"LOG");
        return false;
    }
    else if(!strcmp(parsedData->command, "corti_error"))
    {
        WorkComment(parsedData,"ERROR");
        return false;
    }

    return true;
}

// Called before the player loads a game from a savestate.
void onLoadGame (int id, char *data, int length)
{
    SYSTEMLINE("Load Game on ID: " << id);
}

// Called before the player saves a game.
void onSaveGame (int id, void __cdecl(*savePluginData)(char *data, int length))
{
    SYSTEMLINE("Save Game on ID: " << id);
}

