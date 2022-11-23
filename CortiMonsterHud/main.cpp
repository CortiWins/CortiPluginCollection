#include <DynRPG/DynRPG.h>
#include <algorithm>

#include <fstream>
#include "helper.cpp"
#include "MonsterHud.cpp"
#include "OnStartup.cpp"

// Zuletzt in OnFrame gezeigte Scene.
RPG::Scene currentScene = RPG::SCENE_TITLE;
// Dient dafür zu erkennen, welche Variante des BattleActionWindow angezeigt wird.
bool skipFlag = false;

void onInitFinished()
{
    MonsterHud::OnLoad();
}

// This handler is called when the game exits
void onExit()
{
    MonsterHud::OnExit();
}

// Called after a battler was drawn (or supposed to be drawn)
bool onBattlerDrawn ( RPG::Battler *battler, bool isMonster, int id ) // id is Zero-based
{
    if ( isMonster )
    {
        // Abbruch, wenn keine Grafiken vorhanden sind.
        if(!MonsterHud::parFileExists)
        {
            return true;
        }

        MonsterHud::currentMonster = (RPG::Monster*)battler;

        // Prüfen, ob Monster analysiert ist, wenn nur bei analysierten angezeigt werden soll.
        if(MonsterHud::parAnalysisRequired)
        {
            bool thisIsAnalysed = RPG::switches[MonsterHud::analysisSwitchArrayBeginIndex + MonsterHud::currentMonster->databaseId];
            if(!thisIsAnalysed)
            {
                return true;
            }
        }

        // Abbruch, wenn nur für selektierte Monster das HUD gezeigt werden soll und dieses nicht selektiert ist.
        if( MonsterHud::parSelectedRequired && (RPG::getSelectedMonsterIndex() != (MonsterHud::currentMonster->id - 1)) )
        {
            return true;
        }

        // HUD soll direkt auf das Monster gezeichnet werden
        if(MonsterHud::parDrawOnMonsters)
        {
            MonsterHud::currentMonsterId = id;
            MonsterHud::OnMonsterDrawn();
        }
        else // HUD soll als Overlay über alle Monster gezeichnet werden
        {
            //Helper::ShowInfoBox(id,"entry");
            // ID merken.
            MonsterHud::monstersToOverlay[MonsterHud::numberToDraw] = id;
            MonsterHud::numberToDraw++; // Anzahl erhöhen
        }
    }

    return true;
}

// Zeichnet das Fenster für die Handlungsauswahl
bool onDrawBattleActionWindow ( int * x, int * y, int selection, bool selActive, bool isVisible)
{
    // Überspringen des irregulären ersten Aufrufes des Callbacks
    if(!skipFlag)
    {
        // Anzeigreihenfolge 1/5
        skipFlag = true;

        // Helper::ShowInfoBoxString("???","entry");

        if(MonsterHud::numberToDraw>0)
        {
            for(int i = 0; i < MonsterHud::numberToDraw; i++)
            {
                MonsterHud::currentMonsterId = MonsterHud::monstersToOverlay[i];
                MonsterHud::currentMonster = RPG::monsters[MonsterHud::currentMonsterId];
                MonsterHud::OnMonsterDrawn();
            }
        }

        MonsterHud::numberToDraw = 0;

        return true;
    }
    else
    {
        // Anzeigreihenfolge 3/5
    }

    return true;
}

// Ausgelöst, wenn das BattleStatusWindow gezeichnet wurde.
bool onBattleStatusWindowDrawn (
    int  x,                  // The current X coordinate of the left side of the window
    int selection,           // The zero-based party member ID of the currently selecter actor
    bool selActive,          // true if the selection parameter contains a valid value and a choice bar is drawn
    bool isTargetSelection,  // true if it is the target selection window, false if it is the "normal" status window
    bool isVisible)          // true if the window is visible
{
    if(isTargetSelection)
    {
        // Anzeigreihenfolge 4/5
    }
    else
    {
        // Anzeigreihenfolge 2/5
    }

    return true;
}

// This function is called after every frame (see details below!)
void onFrame ( RPG::Scene scene )
{
    // Anzeigreihenfolge 5/5
    skipFlag = false;

    // Jetzt Battle, vorher nicht Debug
    if((scene == RPG::SCENE_BATTLE) && (currentScene != RPG::SCENE_DEBUG) && (currentScene != RPG::SCENE_BATTLE))
    {
        // Szenenwechsel zu Kampf
        MonsterHud::OnSceneChange(true);
    } // Jetzt nicht Debug, vorher aber Battle
    else if((scene != RPG::SCENE_BATTLE) && (scene != RPG::SCENE_DEBUG) && (currentScene == RPG::SCENE_BATTLE))
    {
        // Szenenwechsel vom Kampf weg
        MonsterHud::OnSceneChange(false);
    }

    // Bei jedem Frame im Kampf
    if((scene == RPG::SCENE_BATTLE))
    {
        MonsterHud::OnFrame();
    }

    // Aktuelle Szene festhalten
    currentScene = scene;
}
