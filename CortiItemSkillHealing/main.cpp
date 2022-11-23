#include <DynRPG/DynRPG.h>

#include <iostream>
#include <fstream>
#include <algorithm>
#include "helper.cpp"

// We store the configuration here
std::map<std::string, std::string> cfgFile;

int configHealIdColor =18 ;
int configManaIdColor = 1;

// Handler called on startup, dont use for gamespecific things.
bool onStartup(char *pluginName)
{
    // We load the configuration from the DynRPG.ini file here
    cfgFile = RPG::loadConfiguration(pluginName);
    if( cfgFile.count("HealColor") > 0)
    {
        int healColorId = atoi(cfgFile["HealColor"].c_str());
        if( (healColorId <0 ) || (healColorId > 19) )
        {
            Helper::ShowInfoBoxString("HealColor Parameter Value bad. Chose 0 to 19.","CortiItemSkillHealingPlugin");
            return false;
        }
        configHealIdColor = healColorId;
    }

    if( cfgFile.count("ManaColor") > 0)
    {
        int manaColorId = atoi(cfgFile["ManaColor"].c_str());
        if( (manaColorId <0 ) || (manaColorId > 19) )
        {
            Helper::ShowInfoBoxString("ManaColor Parameter Value bad. Chose 0 to 19.","CortiItemSkillHealingPlugin");
            return false;
        }
        configManaIdColor = manaColorId;
    }

    return true;
}

// Text in der SkillDescription
std::string skillDescription;
// Ziffernstring nach Codestrings im DescriptionString
std::string skillNumberSubString;
// Stelle im DescriptionString an der ein Codestrings gefunden wurde
unsigned int found;
// Id des Skills, der vom verwendeten Item ausgeführt wird
int skillId;
// Anteil in % der Gesamtlebenspunkte um die das Ziel/die Ziele geheilt werden
int healingPercentage;
// Anteil in % der Gesamtmanapunkte um die das Ziel/die Ziele regeneriert werden
int manaPercentage;
// Gibt an, ob ein Held oder die ganze Gruppe angezielt wird
bool targetGroup = false;
// id des Helden auf den angewendet wird, entweder gesetzt anhand der action->targetId oder für die Schleife über alle Helden
int targetId;
// Held auf den angewendet wird
RPG::Actor *actor;
// Menge an Mana und Leben, die zu regenerieren sind
int healingAmount;
int manaAmount;

// Wendet die Regeneration auf den Helden entsprechend aktueller "targetId" an
void ApplyRegeneration()
{
    healingAmount = 0;
    manaAmount = 0;
    // Partymitglied holen anhand seines Slots in der Party ( 0 bis 3 )
    actor = RPG::Actor::partyMember(targetId);

    if(actor != NULL) // Wenn an der Position ein held vorhanden ist...
    {
        // Prüfen ob Heilungsanteil vorhanden und dem Ziel Leben fehlt
        if(healingPercentage > 0 && ( actor->hp < actor->getMaxHp() ) )
        {
            // Prüfen ob die Menge an Heilung nicht über die maximalen Lebenspunkte hinaus gehen würde
            if( ( ( ( actor->getMaxHp() * healingPercentage )  / 100  ) + actor->hp )  <= actor->getMaxHp()  )
            {
                // Leben entsprechend des eingestellten Anteils regenerieren
                healingAmount = ( ( actor->getMaxHp() * healingPercentage )  / 100  );
                actor->hp = (  healingAmount + actor->hp );
            }
            else
            {
                // Lebenspunkte vollständig heilen
                healingAmount = actor->getMaxHp() - actor->hp;
                actor->hp = actor->getMaxHp();
            }

            // Wenn Heilung zugefügt wurde: Grüne Zahlen mit Heilmenge anzeigen
            if(healingAmount>0)
            {
                actor->damagePopup(healingAmount,configHealIdColor);
            }
        }

        // Prüfen ob Manaregsanteil vorhanden und dem Ziel Mana fehlt
        if(manaPercentage > 0 && ( actor->mp < actor->getMaxMp() ) )
        {
            // Prüfen ob die Menge an Mana über das maximalen Mana hinaus gehen würde
            if( ( ( ( actor->getMaxMp() * manaPercentage )  / 100  ) + actor->mp )  <= actor->getMaxMp()  )
            {
                // Mana entsprechend des eingestellten Anteils regenerieren
                manaAmount = ( ( actor->getMaxMp() * manaPercentage )  / 100  );
                actor->mp = (  manaAmount + actor->mp );
            }
            else
            {
                // Mana vollständig regenerieren
                manaAmount = actor->getMaxMp() - actor->mp;
                actor->mp = actor->getMaxMp();
            }

            // Wenn Mana zugefügt wurde: Blaue Zahlen mit Manamenge anzeigen
            // Wenn bereits Leben regeneriert wurde, Zahl nicht anzeigen da sie die andere überschreibt und Leben wichtiger ist
            if(manaAmount>0 && healingAmount <= 0 )
            {
                actor->damagePopup(manaAmount,configManaIdColor);
            }
        }
    }
}

void CalculateRegeneration()
{
    healingPercentage = 0;
    manaPercentage = 0;
    // Beschreibung des Skills auslesen, kann Codestrings enthalten.
    skillDescription = RPG::getSkillDescription(skillId);

    // Codestring: "DAVHP666"   : Heilung entsprechend 666% der Gesamtlebenspunkte ( 3 Ziffern )
    found = skillDescription.find("DAVHP");
    if(found != std::string::npos) // npos = "Nicht gefunden"
    {
        // Wenn gefunden, dann aus den drei Zeichen hinter der Position die Ziffern für den Wert auslesen
        skillNumberSubString = skillDescription.substr(found+5,3);
        healingPercentage = atoi(skillNumberSubString.c_str());
    }

    // Codestring: "DAVMP666"   : Regeneration entsprechend 666% des Gesamtmanas ( 3 Ziffern )
    found = skillDescription.find("DAVMP");
    if(found != std::string::npos) // npos = "Nicht gefunden"
    {
        skillNumberSubString = skillDescription.substr(found+5,3);
        manaPercentage = atoi(skillNumberSubString.c_str());
    }

    // Wenn weder Mana noch Heilung zu regenerieren sind, kthxbye
    if((healingPercentage == 0)
        && (manaPercentage == 0))
    {
        return;
    }

    if(targetGroup == false)
    {
        // Einzelziel: targedId ist bereits gesetzt
        ApplyRegeneration();
    }
    else
    {
        // Alle in der Gruppe
        for(targetId = 0; targetId <4; targetId++)
        {
            ApplyRegeneration();
        }
    }
}

// Passiert nach dem eine Kampfhandlung durchgeführt wurde.
bool onBattlerActionDone (RPG::Battler *battler, bool success)
{
    if( ( battler->isMonster() == false ) && ( success == true  ))
    {
        // Passiert wenn Spielercharaktere erfolgreich eine Kampfhandlung abschliessen.
        if((battler->action->kind == RPG::AK_ITEM))
        {
            // Item wurde verwendet, Ziel des Items festhalten
            if(battler->action->target == RPG::TARGET_ACTOR)
            {
                targetGroup = false;
                targetId = battler->action->targetId; // Wenn Einzelziel, id des Ziels merken
            }
            else if(battler->action->target == RPG::TARGET_ALL_ACTORS)
            {
                targetGroup = true;
            }
            else
            {
                // Item zielt auf Feinde
                return true;
            }
            // Weitere Verarbeitung wenn das Item eines mit verlinktem Skill ist
            skillId = battler->action->skillId;
            if(skillId > 0)
            {
                CalculateRegeneration();
            }
        }
    }
    return true;
}
