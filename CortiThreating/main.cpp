#define AUTO_DLLMAIN

// Allgemeine Includes
#include <DynRPG/DynRPG.h>

#include <algorithm>    // Helper
#include <fstream>      // Helper

#include "helper.cpp"
#include "Threattings.cpp"
#include "CortiThreating.cpp"
#include "OnFrameBattle.cpp"
#include "OnDrawMonster.cpp"
#include "OnMonsterDrawn.cpp"
#include "OnMonsterAction.cpp"
#include "OnMonsterActionDone.cpp"
#include "OnHeroActionDone.cpp"

// Zuletzt gezeigte Scene.
RPG::Scene lastScene = RPG::SCENE_GAME_OVER;

// Initialize pose types on-startup
bool onStartup (char *pluginName)
{
    // We load the configuration from the DynRPG.ini file here
    Threattings::configuration = RPG::loadConfiguration(pluginName);
    return true;
}

// Ausgelöst bei Spielstart nachdem Makerdaten vorhanden sind.
void onInitFinished()
{

}

// Aufgerufen wenn das Spiel beendet wird.
void onExit()
{

}

// This function is called after every frame
void onFrame(RPG::Scene scene)
{
    if(scene == RPG::SCENE_BATTLE)
    {
        if((lastScene != RPG::SCENE_BATTLE) && (lastScene != RPG::SCENE_DEBUG))
        {
            // Szenenwechsel
        }

        OnFrameBattle();
    }
}

// Passiert wenn der Akteur entschieden hat etwas zu tun.
bool onDoBattlerAction ( RPG::Battler *battler )
{
    if ( battler->isMonster() == true )
    {
        OnMonsterAction(battler);
        return true;
    }
    else
    {
        return true;
    }
}

// Passiert nach dem eine Kampfhandlung durchgeführt wurde.
bool onBattlerActionDone ( RPG::Battler *battler, bool success )
{
    // wird mehrfach aufgerufen, allerdings nur einmal mit "success = true"
    if(!success)
    {
        return true;
    }

    if ( battler->isMonster() == true )
    {
        OnMonsterActionDone(battler);
        return true;
    }
    else
    {
        OnHeroActionDone(battler);
        return true;
    }

    return true;
}

// after the battler is drawn, we need to set the monster's default image to point back to the saved off image
bool onBattlerDrawn(RPG::Battler *battler, bool isMonster, int id)
{
    if(isMonster)
    {
        OnMonsterDrawn(battler, id);
        return true;
    }

    return true;
}

#include "OnComment.cpp"
