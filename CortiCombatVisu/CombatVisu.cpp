namespace CortiCombatVisu
{
#include "Dialog.cpp"
#include "CombatVisuConfig.cpp"
#include "CombatVisuCalculate.cpp"
#include "CombatVisuGraphics.cpp"

// Set by first call of 'OnBattleStatusWindowDrawn', used later.
int selectedHeroID = -1;
// Set by second call of 'OnBattleStatusWindowDrawn', used later.
int windowHeroID = -1;
// Sichtbarkeit aller Elemente. 0 is invisible, 255 is fully visible.
int alphaValue = 0;
// Used to detect scene change
RPG::Scene lastScene = RPG::SCENE_DEBUG;
// Used to detect game reset
int lastFramesCount = -1;
// Used to differentiate between first and second callback of 'OnDrawBattleActionWindow'
bool skipFlag = false;

// Anzeigen eines Monstericons auf dem aktuellen Slot
void DrawIconMonster(int slotIndex, int offsetAtbMapping)
{
    // MonsterIds sind mit +100 gespeichert
    getFastestId -=100;

    LoadMonsterIcon(getFastestId, getFastestIdDatabase);

    if(Config::useAtbMappingGradiant && (offsetAtbMapping < Config::atbMappingMaxOffset ) )
    {
        RPG::screen->canvas->draw (
            Config::slotDrawPositionX[slotIndex] - Config::atbMappingMaxOffset,
            Config::slotDrawPositionY[slotIndex] ,
            atbMappingGradiant,
            0,
            Config::HeroIconSizeY * 1,
            Config::atbMappingMaxOffset + offsetAtbMapping ,
            Config::HeroIconSizeY );
    }

    monsterIcons[getFastestId]->alpha = alphaValue;

    // Anzeigen des Icons ( slotIndex ist auf aktuellem Slot )
    RPG::screen->canvas->draw (Config::slotDrawPositionX[slotIndex] + offsetAtbMapping,  Config::slotDrawPositionY[slotIndex], monsterIcons[getFastestId] );

    // Selektor anzeigen
    if(Config::isMonsterSelektorEnabled && (getFastestId == RPG::getSelectedMonsterIndex()))
    {
        // Anzeigen des Icons ( slotIndex ist auf aktuellem Slot )
        RPG::screen->canvas->draw (
            Config::slotDrawPositionX[slotIndex] + offsetAtbMapping + Config::monsterSelectorOffsetX,
            Config::slotDrawPositionY[slotIndex] + Config::monsterSelectorOffsetY, monsterSelectorIcon,
            0,
            monsterSelectorFrame * Config::monsterSelectorSizeY,
            Config::monsterSelectorSizeX,
            Config::monsterSelectorSizeY);
    }

    // Anzeigen der Nummer
    RPG::screen->canvas->draw (
        Config::slotDrawPositionX[slotIndex] + Config::NumberOffsetToIconX + offsetAtbMapping,
        Config::slotDrawPositionY[slotIndex] + Config::NumberOffsetToIconY ,
        monsterNumber,
        0 + (getFastestId * Config::NumberOffsetInImage),
        0,
        Config::NumberSizeX, Config::NumberSizeY);
}

// Anzeigen eines Heldenicons auf dem aktuellen Slot
void DrawIconHero(int slotIndex, int offsetAtbMapping)
{
    if(Config::useAtbMappingGradiant && (offsetAtbMapping < Config::atbMappingMaxOffset ) )
    {
        RPG::screen->canvas->draw (
            Config::slotDrawPositionX[slotIndex] - Config::atbMappingMaxOffset,
            Config::slotDrawPositionY[slotIndex],
            atbMappingGradiant,
            0,
            Config::HeroIconSizeY * 0,
            Config::atbMappingMaxOffset + offsetAtbMapping,
            Config::HeroIconSizeY );
    }

    // Anzeigen des Icons ( slotIndex ist auf aktuellem Slot )
    RPG::screen->canvas->draw (
        Config::slotDrawPositionX[slotIndex] + offsetAtbMapping,
        Config::slotDrawPositionY[slotIndex],
        heroIcons,
        0,
        0 + ((getFastestIdDatabase-1) * Config::HeroIconOffsetY), Config::HeroIconSizeX ,  Config::HeroIconSizeY );

    if(!Config::isMonsterSelektorEnabled || RPG::getSelectedMonsterIndex() != -1)
    {
        return;
    }

    if(getFastestIdDatabase == selectedHeroID)
    {
        // Anzeigen des Icons ( slotIndex ist auf aktuellem Slot )
        RPG::screen->canvas->draw (
            Config::slotDrawPositionX[slotIndex] + offsetAtbMapping + Config::monsterSelectorOffsetX ,
            Config::slotDrawPositionY[slotIndex] + Config::monsterSelectorOffsetY,
            monsterSelectorIcon,
            0,
            monsterSelectorFrame * Config::monsterSelectorSizeY,
            Config::monsterSelectorSizeX,
            Config::monsterSelectorSizeY);
            return;
    }
    else if(selectedHeroID != -1)
    {
        return;
    }

    if(getFastestIdDatabase == windowHeroID)
    {
        // Anzeigen des Icons ( slotIndex ist auf aktuellem Slot )
        RPG::screen->canvas->draw (
            Config::slotDrawPositionX[slotIndex] + offsetAtbMapping + Config::monsterSelectorOffsetX,
            Config::slotDrawPositionY[slotIndex] + Config::monsterSelectorOffsetY,
            monsterSelectorIcon,
            0,
            monsterSelectorFrame * Config::monsterSelectorSizeY,
            Config::monsterSelectorSizeX,
            Config::monsterSelectorSizeY);
    }
}

void DrawIconHeroInCC(int slotIndex, int ccIndex, int offsetAtbMapping)
{
    if(Config::useAtbMappingGradiant && (offsetAtbMapping < Config::atbMappingMaxOffset ) )
    {
        RPG::screen->canvas->draw (
            Config::slotDrawPositionX[slotIndex] - Config::atbMappingMaxOffset,
            Config::slotDrawPositionY[slotIndex],
            atbMappingGradiant,
            0,
            Config::HeroIconSizeY * 2 ,
            Config::atbMappingMaxOffset,
            Config::HeroIconSizeY);
    }

    // Anzeigen des Icons ( slotIndex ist auf aktuellem Slot )
    RPG::screen->canvas->draw (
        Config::slotDrawPositionX[slotIndex] + Config::conditionAfflictedOffsetX,
        Config::slotDrawPositionY[slotIndex] + Config::conditionAfflictedOffsetY,
        heroIcons,
        0,
        0 + (( (arrayCCHeroes[ccIndex])-1) * Config::HeroIconOffsetY), Config::HeroIconSizeX , Config::HeroIconSizeY);
}

void OnDrawCombatVisu()
{
    // Geht alle Kampfteilnehmer durch und sortiert sie in die Arrays, wenn sie gerade am Leben und im Kampf sind.
    FillArrays();

    monsterSelectorIcon->alpha = alphaValue;
    heroIcons->alpha = alphaValue;
    monsterNumber->alpha = alphaValue;
    if(atbMappingGradiant != null)
    {
         atbMappingGradiant->alpha = alphaValue;
    }

    if(Config::backgroundFileActive)
    {
        background->alpha = alphaValue;
        RPG::screen->canvas->draw ( Config::backgroundPositionX, Config::backgroundPositionY, background );
    }

    // Höchster Wert beim ersten Durchlauf gilt als 100% beim Offset der verbleibenden "Zeit"
    float highestValue = 0;
    for ( int iRun = 0; iRun < fullArrayIndex; iRun++ )
    {
        if(arrayTime[iRun] > highestValue)
        {
            highestValue = arrayTime[iRun] + (300000 / arrayAgi[iRun]); ;
        }
    }

    int slotIndex = 0;
    for ( slotIndex = 0; slotIndex < (Config::numberOfShown - ccAfflictedNumber); slotIndex++ ) // X im CC sind,X Slots weniger zeichnen
    {
        GetFastest(); // Sucht den Kampfteilnehmer, der als nächster am Zug sein wird und berechnet danach dessen darauf folgenden Zieldurchlauf

        int offsetAtbMapping = (Config::useAtbMapping) ? -((fastestAtbValue * Config::atbMappingMaxOffset ) / 300000) : 0;
        if(getFastestId>9) // Monster ab 100 für id 0
        {
            DrawIconMonster(slotIndex, offsetAtbMapping);
        }
        else if(getFastestId>0) // Helden ab 1 für id 0
        {
            DrawIconHero(slotIndex, offsetAtbMapping);
        }
    }

    int ccIndex = 4 - ccAfflictedNumber;
    // slotIndex ist auf dem nächsten ungenutzen Slot
    for ( int miCycle = 0; miCycle < ccAfflictedNumber; miCycle++ ) // X im CC sind,X Slots weniger zeichnen
    {
        DrawIconHeroInCC(slotIndex, ccIndex, 0);
        ccIndex++;
        slotIndex++; // Slotposition erhöhen
    }

    if(Config::monsterSelectorFramesMax>0) // Animationen nur einmal pro Draw erweitern.
    {
        monsterSelectorFrame++;
        if(monsterSelectorFrame >= Config::monsterSelectorFramesMax)
        {
            monsterSelectorFrame = 0;
        }
    }
}

//! Ausgelöst, wenn das BattleStatusWindow gezeichnet wurde.
void CallbackOnBattleStatusWindowDrawn (
    int selection,           // The zero-based party member ID of the currently selecter actor
    bool selActive,          // true if the selection parameter contains a valid value and a choice bar is drawn
    bool isTargetSelection,  // true if it is the target selection window, false if it is the "normal" status window
    bool isVisible)          // true if the window is visible
{
    if(isTargetSelection)
    {
        // Anzeigereihenfolge 4/5
        if( isVisible)
        {
            // Wenn Item-Zielauswahl aktiv, Selektorziel setzen
            if(RPG::Actor::partyMember(selection) != NULL)
            {
                selectedHeroID = RPG::Actor::partyMember(selection)->id;
            }
        }
    }
    else
    {
        // Anzeigereihenfolge 2/5
        if( isVisible)
        {
            if(RPG::Actor::partyMember(selection)->atbValue == 300000)
            {
                windowHeroID = RPG::Actor::partyMember(selection)->id;
            }
        }
    }

    return;
}

// Zeichnet das Fenster für die Handlungsauswahl
void CallbackOnDrawBattleActionWindow()
{
    // Überspringen des irregulären ersten Aufrufes des Callbacks
    if(!skipFlag)
    {
        bool showVisu = true;
        if((RPG::system->scene != lastScene) || (RPG::system->frameCounter < lastFramesCount))
        {
            // Wechsel in den Kampf
            alphaValue = 0;
        }

        if(RPG::battleData->isDefeat || RPG::battleData->isVictory )
        {
            // Kampfende
            showVisu = false;
            if(CortiCombatVisu::Config::SWI_Show > 0)
            {
                 RPG::switches[CortiCombatVisu::Config::SWI_Show] = false;
            }
        }

        // False ist dominant. Wenn angezeigt werden soll, prüfen ob Switcheinstellung das auch so sieht.
        if( showVisu && (CortiCombatVisu::Config::SWI_Show > 0))
        {
            showVisu = RPG::switches[CortiCombatVisu::Config::SWI_Show];
        }

        if(showVisu )
        {
            alphaValue = std::min(alphaValue+ 10, 255); // Einblenden
        }
        else
        {
            alphaValue = std::max(alphaValue- 15, 0); // Ausblenden
        }

        // Anzeigereihenfolge 1/5
        OnDrawCombatVisu();
        selectedHeroID = -1;
        windowHeroID = -1;
        skipFlag = true;
        return;
    }
    else
    {
        // Anzeigereihenfolge 3/5
        return;
    }
}

//! This function is called after every frame
void CallbackOnFrame(RPG::Scene scene)
{
    // Switching to debug scene should not reset the CombatVisu.
    if(scene == RPG::SCENE_DEBUG)
    {
        return;
    }

    lastScene = scene;
    lastFramesCount = RPG::system->frameCounter;
    // Anzeigereihenfolge 5/5
    skipFlag = false;
}

void CallbackOnStartup()
{
    // We load the configuration from the DynRPG.ini file here
    Config::configMap = RPG::loadConfiguration((char *)"CortiCombatVisu");
}

void CallbackOnInitFinished()
{
    // WAIT setzen. Notwendig.
    if ( RPG::system->atbMode != RPG::ATBM_WAIT )
    {
        RPG::system->atbMode = RPG::ATBM_WAIT;
    }
    Config::LoadConfig();
    Config::LoadCrowdControlsConditions();
    Config::PrecalcPositions();
    LoadGraphics();
}

} // Namespace End
