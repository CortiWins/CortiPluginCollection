
#define _WIN32_WINNT 0x0500
#define AUTO_DLLMAIN
#include <DynRPG/DynRPG.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <ctime>    // For time()
#include "helper.cpp"

// Regelung der Geschwindigkeit des Atb-Systems auf Basis der Anzahl aktiver Kampfteilnehmer
#include "KeyPressSimulation.cpp"
#include "SpeedLog.cpp"
#include "CortiAtbSpeed.cpp"

//! Enthält Configuration
std::map<std::string, std::string> configMap;

int fileSwitch = 0;

void LoadSlowSwitches()
{
    int countUp = 1;

    /* Durchsuchen der  ConfigMap nach validen Ersatzeinträgen */
    // Nach Keys des Namens "SlowSwitchX" suchen, wobei X solange erhöht wird bis ein Eintrag nicht gefunden wurde.
    while(countUp<=16)
    {
        std::stringstream keyName;
        keyName << "SlowSwitch" << countUp;

        // Check ob Key "SlowSwitchX" vorhanden ist
        if(configMap.count(keyName.str()))
        {
            int switchId = atoi(configMap[keyName.str()].c_str());
            if( switchId > 0 )
            {
                // ConditionId gefunden -> in Vektor hinterlegen
                CortiAtbSpeedConfig::slowSwitchesVector.push_back(switchId);
            }
        }
        else
        {
            break;
        }

        countUp++;
    }
    // Wenn Switches vorhanden, Filterung aktivieren
    if(CortiAtbSpeedConfig::slowSwitchesVector.empty())
    {
        CortiAtbSpeedConfig::slowSwitchesPresend = false;
    }
    else
    {
        CortiAtbSpeedConfig::slowSwitchesPresend = true;
    }

}

void LoadCrowdControlsConditions()
{
    int countUp = 1;

    /* Durchsuchen der  ConfigMap nach validen Ersatzeinträgen */
    // Nach Keys des Namens "ConditionX" suchen, wobei X solange erhöht wird bis ein Eintrag nicht gefunden wurde.
    while(true)
    {
        std::stringstream keyName;
        keyName << "Condition" << countUp;

        // Check ob Key "ConditionX" vorhanden ist
        if(configMap.count(keyName.str()))
        {
            int condtionId = atoi(configMap[keyName.str()].c_str());
            if( (condtionId > 0 ) && ( condtionId < 500) )
            {
                // ConditionId gefunden -> in Vektor hinterlegen
                CortiAtbSpeedConfig::conditionVector.push_back(condtionId);
            }
        }
        else
        {
            // ConditionX nicht gefunden, Schleife beenden.
            //Helper::ShowInfoBox(countUp,"Skill NOT Found");
            break;
        }

        countUp++;
    }
    // Wenn Conditions vorhanden, Filterung aktivieren

    if(CortiAtbSpeedConfig::conditionVector.empty())
    {
        CortiAtbSpeedConfig::conditionFilter = false;
    }
    else
    {
        CortiAtbSpeedConfig::conditionFilter = true;
    }
}

// Handler called on startup
bool onStartup(char *pluginName)
{
    // We load the configuration from the DynRPG.ini file here
    configMap = RPG::loadConfiguration(pluginName);

    if(configMap.count("DebugFileSwitchId"))
    {
        int switchId = atoi(configMap["DebugFileSwitchId"].c_str());
        if(switchId>0)
        {
            fileSwitch = switchId;
            if(configMap.count("DebugFileName"))
            {
                std::string filenamex = configMap["DebugFileName"];
                if(filenamex.length()>0)
                {
                    Log::filename = filenamex;
                }
            }
        }
    }

    if(configMap.count("SpeedPerBattler"))
    {
        int speedValue = atoi(configMap["SpeedPerBattler"].c_str());

        if(speedValue < 20 || speedValue >  2000)
        {
            //Helper::ShowInfoBox("CortiAtbSpeed SpeedPerBattler value sucks.","Plugin Parameter Error");
            //return false;
        }
        else
        {
            CortiAtbSpeedConfig::SpeedPerBattler = speedValue;
        }
    } // Wenn nicht vorhanden -> Defaultwert behalten

    if(configMap.count("AccelerationAfterTurnFrames"))
    {
        int accFrames = atoi(configMap["AccelerationAfterTurnFrames"].c_str());

        if(accFrames > 0)
        {
            // Wenn > "0" dann valide Zahl
            CortiAtbSpeedConfig::AccelerationAfterTurnFrames = accFrames;
        }
        else
        {
            CortiAtbSpeedConfig::AccelerationAfterTurnEnable = false;
        }
    }

    if(configMap.count("BrakeBeforeTurn"))
    {
        int brakeValue = atoi(configMap["BrakeBeforeTurn"].c_str());

        if(brakeValue > 0 && brakeValue < CortiAtbSpeed::kAtbMax)
        {
            // Wenn > "0" dann valide Zahl
            CortiAtbSpeedConfig::BrakePart = brakeValue;
            CortiAtbSpeedConfig::BrakePartInverse = CortiAtbSpeed::kAtbMax - CortiAtbSpeedConfig::BrakePart;

            // Helper::ShowInfoBox(CortiAtbSpeedConfig::BrakePart,"BrakePart");
        }
        else
        {
            CortiAtbSpeedConfig::BrakeBeforeTurnEnable = false;
        }
    }

    if(configMap.count("SlowWithinTurnsEnable"))
    {
        int slowWithinValue = atoi(configMap["SlowWithinTurnsEnable"].c_str());

        if(slowWithinValue <= 0)
        {
            // Wenn > "0" oder kleiner -> deaktivieren
            CortiAtbSpeedConfig::SlowWithinTurnsEnable = false;
        }
    }

    if(configMap.count("DisableSlowWhenFilled"))
    {
        int slowWhenFilled = atoi(configMap["DisableSlowWhenFilled"].c_str());

        if(slowWhenFilled > 0)
        {
            // Wenn > "0" -> deaktivieren
            CortiAtbSpeedConfig::DisableSlowWhenFilled = true;
        }
    }

    if(configMap.count("WithinActionSlowdownMax"))
    {
        int paramValue = atoi(configMap["WithinActionSlowdownMax"].c_str());

        if(paramValue > 40)
        {
            CortiAtbSpeedConfig::WithinActionSlowdownMax = paramValue;
        }
    }

    if(configMap.count("WithinActionSlowdownMaxDone"))
    {
        int paramValue = atoi(configMap["WithinActionSlowdownMaxDone"].c_str());

        if(paramValue > 30)
        {
            CortiAtbSpeedConfig::WithinActionSlowdownMaxDone = paramValue;
        }
    }

    if(configMap.count("HitsFullSlowdownMax"))
    {
        int paramValue = atoi(configMap["HitsFullSlowdownMax"].c_str());

        if(paramValue > 15)
        {
            CortiAtbSpeedConfig::HitsFullSlowdownMax = paramValue;
        }
    }

    if(configMap.count("WithinActionSlowdownDefenseMax"))
    {
        int paramValue = atoi(configMap["WithinActionSlowdownDefenseMax"].c_str());

        if(paramValue > 15)
        {
            CortiAtbSpeedConfig::WithinActionSlowdownDefenseMax = paramValue;
        }
    }

    if(configMap.count("EnableSimulatedReturnKey"))
    {
        int valueParam = atoi(configMap["EnableSimulatedReturnKey"].c_str());
        KeyPressSimu::useSystem = (valueParam > 0) ? true :false;
    }

    if(configMap.count("EnableSimulatedReturnKeyDisableSwitch"))
    {
        KeyPressSimu::deadSwitch = atoi(configMap["EnableSimulatedReturnKeyDisableSwitch"].c_str());
    }
    // Feature nur aktivieren wenn SwitchID > 0
    KeyPressSimu::checkDeadSwitch = KeyPressSimu::deadSwitch > 0 ? true : false;

    if(configMap.count("DisableDifferentAtbInit"))
    {
        int valueParam = atoi(configMap["DisableDifferentAtbInit"].c_str());
        CortiAtbSpeedConfig::useDifferentAtbInit = (valueParam > 0) ? false :true;
    }

    LoadCrowdControlsConditions();
    LoadSlowSwitches();

    return true;
}

void onInitFinished()
{
    CortiAtbSpeed::SetAtbModeWait();

    if(KeyPressSimu::useSystem)
    {
        KeyPressSimu::GetWindowOnInit();
    }
}

// Zum Überspringen des ersten Zeichenaufrufes des BattleActionWindow
bool skipFlag = false;
RPG::Scene lastScene;
void onFrame ( RPG::Scene scene )
{
    // AtbUpdate nur in der Battle-Scene.
    if ( scene == RPG::SCENE_BATTLE )
    {
        CortiAtbSpeed::SetAtbModeWait();
        skipFlag = false;
        if(lastScene != RPG::SCENE_BATTLE )
        {
            if(lastScene != RPG::SCENE_DEBUG )
            {
                // Reset wenn Szenenwechsel und vorherige Szene ungleich Debug
                // Sprung in den Kampf

                if(CortiAtbSpeedConfig::useDifferentAtbInit)
                {
                    CortiAtbSpeed::ReduceAtbValuesMonster();
                    CortiAtbSpeed::ReduceAtbValuesHeros();
                }

            }
        }

        CortiAtbSpeed::UpdateAtbSpeed();
        CortiAtbSpeed::OnFrameBattleKeys();

        if(fileSwitch>0)
        {
            if(RPG::switches[fileSwitch])
            {
                Log::NewLog();
                Log::LogLine("CortiAtbSpeed Log:");

                Log::LogValue("SpeedPerBattler", CortiAtbSpeedConfig::SpeedPerBattler);
                Log::LogValue("battleSpeedValueByNumbers", CortiAtbSpeed::battleSpeedValueByNumbers);
                Log::LogValue("battleSpeedValueBySlow", CortiAtbSpeed::battleSpeedValueBySlow);
                Log::LogValue("maximumAtbValue", CortiAtbSpeed::maximumAtbValue);

                Log::LogLine("Counted Battlers:");
                Log::LogValue("numBattlers", CortiAtbSpeed::numBattlers);
                Log::LogValue("numMonstersInGroup", CortiAtbSpeed::numMonstersInGroup);
                Log::LogValue("numMonstersHidden", CortiAtbSpeed::numMonstersHidden);
                Log::LogValue("numMonstersNotHidden", CortiAtbSpeed::numMonstersNotHidden);
                Log::LogValue("numHeros", CortiAtbSpeed::numHeros);
                Log::LogValue("numTellingToWaitHero", CortiAtbSpeed::numTellingToWaitHero);
                Log::LogValue("numTellingToWaitMonster", CortiAtbSpeed::numTellingToWaitMonster);
                Log::LogValue("numAfflictedByFilter", CortiAtbSpeed::numAfflictedByFilter);
                Log::LogLine(" ");

                Log::LogValue("unChosenMenuIsShown", CortiAtbSpeed::unChosenMenuIsShown);
                Log::LogValue("frames", CortiAtbSpeed::frames);
                Log::LogValue("selectedHeroIndexZb", CortiAtbSpeed::selectedHeroIndexZb);
                Log::LogValue("withinActionSlowdown", CortiAtbSpeed::withinActionSlowdown);
                Log::LogValue("chosenMenuIsShown", CortiAtbSpeed::chosenMenuIsShown);
                Log::LogValue("actionSlowDownFrames", CortiAtbSpeed::actionSlowDownFrames);
                Log::LogLine(" ");

                Log::LogLine("OneIsfull Conditions:");
                Log::LogValue("oneIsFull", CortiAtbSpeed::oneIsFull);
                Log::LogValue("dbg_oneFullMonsters", CortiAtbSpeed::dbg_oneFullMonsters);
                Log::LogValue("dbg_oneFullHeros", CortiAtbSpeed::dbg_oneFullHeros);
                Log::LogValue("dbg_oneFullSlowSwitches", CortiAtbSpeed::dbg_oneFullSlowSwitches);
                Log::LogValue("dbg_oneFullWithinTurn", CortiAtbSpeed::dbg_oneFullWithinTurn);

                for ( unsigned int x = 0; x < CortiAtbSpeedConfig::slowSwitchesVector.size(); x++ )
                {
                    if ( RPG::switches[CortiAtbSpeedConfig::slowSwitchesVector[x]] == true )
                    {
                        Log::LogValue("SlowSwitch ID set:", CortiAtbSpeedConfig::slowSwitchesVector[x]);
                    }
                }

                Log::LogLine(" ");
                Log::LogClose();

                Helper::ShowInfoBoxString("Content added to logfile.","[CortiAtbSpeed] Debug Mode");
                RPG::switches[fileSwitch] = false;
            }
        }

    }
    lastScene = scene;
}

// Passiert wenn der Akteur entschieden hat etwas zu tun.
bool onDoBattlerAction ( RPG::Battler *battler ) // Mehrfacher Aufruf, aber unproblematisch
{
    if(battler->action->kind == RPG::AK_BASIC && (battler->action->basicActionId == RPG::BA_DEFEND))
    {
        CortiAtbSpeed::withinActionSlowdown = CortiAtbSpeedConfig::WithinActionSlowdownDefenseMax;
    }
    else
    {
        CortiAtbSpeed::withinActionSlowdown = CortiAtbSpeedConfig::WithinActionSlowdownMax;
    }



    return true;
}

// Passiert nach dem eine Kampfhandlung durchgeführt wurde.
bool onBattlerActionDone ( RPG::Battler *battler, bool success )
{
    // wird mehrfach aufgerufen, allerdings nur einmal mit "success = true"
    if ( !success )
    {
        return true;
    }

    if(battler->action->kind == RPG::AK_BASIC && (battler->action->basicActionId == RPG::BA_DEFEND))
    {
        CortiAtbSpeed::withinActionSlowdown = CortiAtbSpeedConfig::WithinActionSlowdownDefenseMax;
    }
    else
    {
        CortiAtbSpeed::withinActionSlowdown = CortiAtbSpeedConfig::WithinActionSlowdownMaxDone;
    }

    return true;
}

bool onBattleStatusWindowDrawn (
    int  x,                  // The current X coordinate of the left side of the window
    int selection,           // The zero-based party member ID of the currently selecter actor
    bool selActive,          // true if the selection parameter contains a valid value and a choice bar is drawn
    bool isTargetSelection,  // true if it is the target selection window, false if it is the "normal" status window
    bool isVisible)          // true if the window is visible
{
    if(isVisible && selActive)
    {
        CortiAtbSpeed::selectedHeroIndexZb = selection;
        //Helper::ShowInfoBox(selection,"onBattleStatusWindowDrawn - selection");
    }

    return true;
}

// Zeichnet das Fenster für die Handlungsauswahl
bool onDrawBattleActionWindow ( int * x, int * y, int selection, bool selActive, bool isVisible)
{
    // Überspringen des irregulären ersten Aufrufes des Callbacks
    if(!skipFlag)
    {
        skipFlag = true;
        return true;
    }
    // Mit Info aus "onBattleStatusWindowDrawn" verwenden um eigene Heldenbefehlsfenster zu machen
    if(isVisible)
    {

        if(selActive) // (true)Handlungsauswahl oder (false)Heldenauswahl
        {
            CortiAtbSpeed::chosenMenuIsShown = true;
        }
        else
        {
            CortiAtbSpeed::unChosenMenuIsShown = true;
        }
        return true;
    }
    else
    {
        // Helper::ShowInfoBox("IN VISIBLE BaWINDOW","AtbSpeed");
    }
    return true;
}
