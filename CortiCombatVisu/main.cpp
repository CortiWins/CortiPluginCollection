// DynSDK Include und Warningunterdrückungen
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wconversion-null"
#include <DynRPG/DynRPG.h>
void NeverCall()
{
    #pragma GCC diagnostic ignored "-Wunused-function"
    // Pragma funktioniert in dieser GCC nicht richtig, daher ungenutzes Aufrufen.
    RPG::goToTitle();
    RPG::quitGame();
    RPG::getAvgMonsterPartyAgl();
    RPG::getAvgPartyAgl();
}
#pragma GCC diagnostic pop

#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#define null NULL

#include "CombatVisu.cpp"

bool onStartup (char *pluginName)
{
    CortiCombatVisu::CallbackOnStartup();
    return true;
}

void onInitFinished()
{
    CortiCombatVisu::CallbackOnInitFinished();
}

//! CallbackOnFrameThis handler is called when the game exits
void onExit()
{
    CortiCombatVisu::UnloadGraphics();
}

//! Ausgelöst, wenn das BattleStatusWindow gezeichnet wurde.
bool onBattleStatusWindowDrawn (
    int  x,                  // The current X coordinate of the left side of the window
    int selection,           // The zero-based party member ID of the currently selecter actor
    bool selActive,          // true if the selection parameter contains a valid value and a choice bar is drawn
    bool isTargetSelection,  // true if it is the target selection window, false if it is the "normal" status window
    bool isVisible)          // true if the window is visible
{
    CortiCombatVisu::CallbackOnBattleStatusWindowDrawn(selection, selActive, isTargetSelection, isVisible);
    return true;
}

//! Zeichnet das Fenster für die Handlungsauswahl
bool onDrawBattleActionWindow ( int * x, int * y, int selection, bool selActive, bool isVisible)
{
    CortiCombatVisu::CallbackOnDrawBattleActionWindow();
    return true;
}

//! This function is called after every frame
void onFrame ( RPG::Scene scene )
{
    CortiCombatVisu::CallbackOnFrame(scene);
}
