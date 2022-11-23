
#include <DynRPG/DynRPG.h>

#include <fstream>
#include <vector>
#include <algorithm>

#include "helper.cpp"
#include "Analysis.cpp"

std::map<std::string, std::string> configMap;

void LoadAnalysisSkills()
{
    CortiAnalysis::analysisSkillsPresent = false;
    bool stopRead = false;
    int increasingValue = 1;
    while(!stopRead)
    {
        std::stringstream keyName;
        keyName << "AnalysisSkill_" << (increasingValue);

        if(configMap.count(keyName.str()))
        {
            // Weiterer ID Eintrag vorhanden
            int value = (atoi(configMap[keyName.str()].c_str()));
            if(value>0)
            {
                CortiAnalysis::analysisSkills.push_back(value);
                CortiAnalysis::analysisSkillsPresent = true;
            }
        }
        else
        {   // Schleife abbrechen
            stopRead = true;
        }

        increasingValue++;
    }
}

// Handler called on startup, dont use for gamespecific things.
bool onStartup ( char *pluginName )
{
    configMap = RPG::loadConfiguration(pluginName);

    if(configMap.size()<1)
    {
        // Keine Konfigeinstellungen
        Helper::ShowInfoBoxString("Error. No settings found in DynRPG.ini. Use the readme or the example project to get working settings.","CortiAnalysis Plugin");
        return true;
    }

    // Analysis Required
    if(configMap.count("AnalysisArraySwitchId"))
    {
        CortiAnalysis::monsterSwitchesAutoset = false;
        int index = (atoi(configMap["AnalysisArraySwitchId"].c_str()));
        if(index>0)
        {
           //Helper::ShowInfoBox(index,"AutoSetSwitch id");
            CortiAnalysis::monsterSwitchesAutoset = true;
            CortiAnalysis::monsterSwitchesArray = index - 1;
        }
    }

    // SwitchSet Activated
    if(configMap.count("AutoActivateSwitch"))
    {
        CortiAnalysis::setSwitchBattlePage = false;
        int value = (atoi(configMap["AutoActivateSwitch"].c_str()));
        if(value>0)
        {
            CortiAnalysis::setSwitchBattlePage = true;
            CortiAnalysis::setSwitchBattlePageId = value;
        }
    }

    // Track Skill Used Id
    if(configMap.count("TrackingSkillUsed"))
    {
        CortiAnalysis::trackSkillId = false;
        int value = (atoi(configMap["TrackingSkillUsed"].c_str()));
        if(value>0)
        {
            CortiAnalysis::trackSkillId = true;
            CortiAnalysis::trackSkillIdVariable = value;
        }
    }

    // Track Item Used Id
    if(configMap.count("TrackingItemUsed"))
    {
        CortiAnalysis::trackItemId = false;
        int value = (atoi(configMap["TrackingItemUsed"].c_str()));
        if(value>0)
        {
            CortiAnalysis::trackItemId = true;
            CortiAnalysis::trackItemIdVariable = value;
        }
    }

    // Track Group Target Id
    if(configMap.count("TrackingGroupTargetId"))
    {
        CortiAnalysis::trackGroupTargetId = false;
        int value = (atoi(configMap["TrackingGroupTargetId"].c_str()));
        if(value>0)
        {
            CortiAnalysis::trackGroupTargetId = true;
            CortiAnalysis::trackGroupTargetIdVariable = value;
        }
    }

    // Track Group Target Id
    if(configMap.count("TrackingDatabaseId"))
    {
        CortiAnalysis::trackDatabaseId = false;
        int value = (atoi(configMap["TrackingDatabaseId"].c_str()));
        if(value>0)
        {
            CortiAnalysis::trackDatabaseId = true;
            CortiAnalysis::trackDatabaseIdVariable = value;
        }
    }

    // Track Group Target Id Array
    if(configMap.count("TrackingDatabaseIdArray"))
    {
        CortiAnalysis::trackDatabaseIdArray = false;
        int value = (atoi(configMap["TrackingDatabaseIdArray"].c_str()));
        if(value>0)
        {
            CortiAnalysis::trackDatabaseIdArray = true;
            CortiAnalysis::trackDatabaseIdArrayVariable = value;
        }
    }

    LoadAnalysisSkills();

    return true;
}

void onInitFinished()
{

}

// This handler is called when the game exits
void onExit()
{

}

// Passiert nach dem eine Kampfhandlung durchgeführt wurde.
bool onBattlerActionDone ( RPG::Battler *battler, bool success )
{
    // wird mehrfach aufgerufen, allerdings nur einmal mit "success = true"
    if ( success && ! ( battler->isMonster() ) )
    {
        CortiAnalysis::OnActionDone(battler);
    }
    return true;
}
