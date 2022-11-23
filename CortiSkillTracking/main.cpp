#define AUTO_DLLMAIN
#define MAX_MONSTERS 8

#include <DynRPG/DynRPG.h>
#include <sstream>
#include <fstream>
#include <algorithm>

// Diesen Define auskommentieren wenn du nicht ich bist ;-)
#include "helper.cpp"

// We store the configuration here
std::map<std::string, std::string> configuration;
// < SkillId , VariablenId > Wertepaar welcher Skill welche Variable erhöht
std::map<int,int> skillUsesMap;
// < Hero-DatabaseId , VariablenId > Wertepaar welcher Held in welche Variablen synchronisiert wird.
std::map<int,int> trackingMap;
// Variablen-ID von Helden, die keine spezifische ID zugewiesen bekamen
int otherHeroesVariable = 0;

void LoadTrackingMap()
{
    // Auslesen der Konfigurationseinstellungen
    bool endChecking = false;
    int increasingValue = 1;
    int valueHeroId;
    int valueVariableId;

    do
    {
        // Konstruieren des Schlüssels. z.B.
        std::stringstream keyName;
        keyName << "HeroId" << (increasingValue);
        // Prüfen ob für den Schlüssel ein Wertepaar vorhanden ist
        if(configuration.count(keyName.str()))
        {
            // Wenn Paar vorhanden, Wert auslesen. Dieser entspricht der Nummer des Skills
            valueHeroId = (atoi(configuration[keyName.str()].c_str()));
            if((valueHeroId>0)) // Ckecken ob die Skill-Nummer im erlaubten Bereich ist
            {
                // Konstruieren des Schlüssels. z.B.
                std::stringstream keyNameVariable;
                keyNameVariable << "HeroIdVariableBegin" << (increasingValue);
                // Prüfen ob für den Schlüssel ein Wertepaar vorhanden ist
                if(configuration.count(keyNameVariable.str()))
                {
                    // Wenn Paar vorhanden, Wert auslesen. Dieser entspricht der Id der Variable, in die gezählt wird.
                    valueVariableId = (atoi(configuration[keyNameVariable.str()].c_str()));
                    if((valueVariableId>0)) // Ckecken ob die Skill-Nummer im erlaubten Bereich ist
                    {
                        // Assoziation SkillId <-> VaribleId hinterlegen
                        trackingMap[valueHeroId] = valueVariableId;
                    }
                }
                else
                {   // Wertepaar nicht vorhanden. Auslesen dieser Daten stoppen.
                    endChecking = true;
                }
            }
            increasingValue++;
        }
        else
        {   // Wertepaar nicht vorhanden. Auslesen dieser Daten stoppen.
            endChecking = true;
        }
    }
    while(!endChecking);
}

void LoadSkillUsesMap()
{
     // Auslesen der Konfigurationseinstellungen
    bool endChecking = false;
    int increasingValue = 1;
    int valueSkillId;
    int valueVariableId;

    do
    {
        // Konstruieren des Schlüssels. z.B.
        std::stringstream keyName;
        keyName << "SkillUsesId" << (increasingValue);
        // Prüfen ob für den Schlüssel ein Wertepaar vorhanden ist
        if(configuration.count(keyName.str()))
        {
            // Wenn Paar vorhanden, Wert auslesen. Dieser entspricht der Nummer des Skills
            valueSkillId = (atoi(configuration[keyName.str()].c_str()));
            if((valueSkillId>0)) // Ckecken ob die Skill-Nummer im erlaubten Bereich ist
            {
                // Konstruieren des Schlüssels. z.B.
                std::stringstream keyNameVariable;
                keyNameVariable << "SkillUsesVar" << (increasingValue);
                // Prüfen ob für den Schlüssel ein Wertepaar vorhanden ist
                if(configuration.count(keyNameVariable.str()))
                {
                    // Wenn Paar vorhanden, Wert auslesen. Dieser entspricht der Id der Variable, in die gezählt wird.
                    valueVariableId = (atoi(configuration[keyNameVariable.str()].c_str()));
                    if((valueVariableId>0)) // Ckecken ob die Skill-Nummer im erlaubten Bereich ist
                    {
                        // Assoziation SkillId <-> VaribleId hinterlegen
                        skillUsesMap[valueSkillId] = valueVariableId;
                    }
                }
                else
                {   // Wertepaar nicht vorhanden. Auslesen dieser Daten stoppen.
                    endChecking = true;
                }
            }
            increasingValue++;
        }
        else
        {   // Wertepaar nicht vorhanden. Auslesen dieser Daten stoppen.
            endChecking = true;
        }
    }
    while(!endChecking);
}

// Initialize pose types on-startup
bool onStartup (char *pluginName)
{
    // We load the configuration from the DynRPG.ini file here
    configuration = RPG::loadConfiguration(pluginName);

    LoadSkillUsesMap();
    LoadTrackingMap();

    if(configuration.count("OtherHeroesVariableBegin"))
    {
        int useVariable = atoi(configuration["OtherHeroesVariableBegin"].c_str());

        if(useVariable>0)
        {
            otherHeroesVariable = useVariable;
        }
    }
    return true;
}

int variableIdCurrentHero = 0;

bool CheckHeroVariableDump(int heroDatabaseId)
{
    if(trackingMap.count(heroDatabaseId))
    {
        variableIdCurrentHero = trackingMap[heroDatabaseId];
        return true;
    }
    else if(otherHeroesVariable>0)
    {
        variableIdCurrentHero = otherHeroesVariable;
        return true;
    }
    variableIdCurrentHero = 0;
    return false;
}

// Passiert nach dem eine Kampfhandlung durchgeführt wurde.
bool onBattlerActionDone ( RPG::Battler *battler, bool success )
{
    if ( success && !battler->isMonster() )
    {   // Held benutzt Skill
        if(battler->action->kind == RPG::AK_SKILL)
        {   // Prüfen, ob der Skill hinterlegt ist
            if(skillUsesMap.count(battler->action->skillId))
            {
                // SkillId in Map hinterlegt.
                int variableId = skillUsesMap[battler->action->skillId];
                RPG::variables[variableId]++;
            }
        }
        // Prüfen, ob für diesen Helden eine Variablen-ID hinterlegt ist
        if(CheckHeroVariableDump(battler->id))
        {
            RPG::variables[variableIdCurrentHero] = battler->id;
            RPG::variables[variableIdCurrentHero+1] = (battler->action->kind == RPG::AK_SKILL) ? battler->action->skillId : -1;
            RPG::variables[variableIdCurrentHero+2] = ((battler->action->target == RPG::TARGET_ACTOR) || (battler->action->target == RPG::TARGET_MONSTER))
                                                        ? battler->action->target : -1;
            RPG::variables[variableIdCurrentHero+3] = battler->action->targetId +1;
        }
    }

    return true;
}
