#define AUTO_DLLMAIN
#include <DynRPG/DynRPG.h>

#include <iostream>
#include <fstream>
#include <sstream> // For std::stringstream
#include <algorithm>
#include "helper.cpp"
#include <tgmath.h>

//! Deaktivierung der Skillersetzens bei HeroSelftarget
bool disableHeroSelftarget(false);
//! Deaktivierung der Skillersetzens bei MonsterSelftarget
bool disableMonsterSelftarget(false);

//! Enthält Configuration
std::map<std::string, std::string> configMap;
//! Enthält zu ersetzende Skill Ids und die Id mit der sie zu ersetzen sind
std::map<int,int>skillReplaceMap;

// Aufgerufen bei Spielstart, hier wird die Liste zu ersetzender Skills aus der Konfigfile gelesen.
bool onStartup(char *pluginName)
{
    // We load the configuration from the DynRPG.ini file here
    configMap = RPG::loadConfiguration(pluginName);
    // Die dem Konstruieren der "Skill1", "Skill2", "SkillReplace1",-Strings
    int countUp = 1;

    /* Durchsuchen der  ConfigMap nach validen Ersatzeinträgen */

    // Nach Keys des Namens "SkillX" suchen, wobei X solange erhöht wird bis ein Eintrag nicht gefunden wurde.
    while(true)
    {
        std::stringstream keyName;
        keyName << "Skill" << countUp;

        // Check ob Key "SkillX" vorhanden ist
        if(configMap.count(keyName.str()))
        {
            std::stringstream keyReplaceName;
            keyReplaceName << "SkillReplace" << countUp;

            // Check, ob passender Key "SkillReplaceX" vorhanden ist
            if(configMap.count(keyReplaceName.str()))
            {
                int skillId = atoi(configMap[keyName.str()].c_str());
                if( (skillId > 0 ) && ( skillId < 9000) )
                {
                    //Helper::ShowInfoBox(skillId,"Skill ID is in okey range");

                    int skillReplaceId = atoi(configMap[keyReplaceName.str()].c_str());
                    if( (skillReplaceId > 0 ) && ( skillReplaceId < 9000) )
                    {
                        //Helper::ShowInfoBox(countUp,"all fine");
                        skillReplaceMap[skillId] = skillReplaceId;
                    }
                    else
                    {
                        Helper::ShowInfoBoxString(keyReplaceName.str(),"SkillReplaceX is in bad range, must be >0 & <9000");
                    }
                }
                else
                {
                    Helper::ShowInfoBoxString(keyName.str(),"SkillX is in bad range, must be >0 & <9000");
                }
            }
            else
            {
                Helper::ShowInfoBoxString(keyName.str(),"SkillX ~ no matching SkillReplaceX");
            }
        }
        else
        {
            // SKillX nicht gefunden, Schleife beenden.
            //Helper::ShowInfoBox(countUp,"Skill NOT Found");
            break;
        }

        countUp++;
    }

    // Auslesen der Konfigzeilen zur Deaktivierung von Selftarget

    // DisableMonsterSelftarget=0
    if(configMap.count("DisableMonsterSelftarget"))
    {
        int disMonsterSelf = atoi(configMap["DisableMonsterSelftarget"].c_str());

        if(disMonsterSelf > 0)
        {
            // Wenn > "0" -> deaktivieren
            disableMonsterSelftarget = true;
        }
    }

    // DisableHeroSelftarget=0
    if(configMap.count("DisableHeroSelftarget"))
    {
        int disHeroSelf = atoi(configMap["DisableHeroSelftarget"].c_str());

        if(disHeroSelf > 0)
        {
            // Wenn > "0" -> deaktivieren
            disableHeroSelftarget = true;
        }
    }

    return true;
}

// Passiert wenn der Akteur entschieden hat etwas zu tun.
// Hier passiert das Ersetzen der SkillIds
bool onDoBattlerAction ( RPG::Battler *battler )
{
    // Es können nur Skills vertauscht werden.
    if(battler->action->kind == RPG::AK_SKILL)
    {
        if(skillReplaceMap.count(battler->action->skillId)) // Skill Id in ErsatzListe vorhanden
        {
            // Zusatzfunktion: Nichtersetzen wenn auslösender Battler == ZielBattler.

            // Check auf Selftarget setzt vorraus, dass der Ziel Typ einem Einzelzielskill enspricht.
            /* Possible values for the RPG::Action::target member.
                Enumerator:
                    TARGET_NONE 	                    No target (the sounds of the battle animation will still be audible)
                    TARGET_ACTOR 	                    Target is an actor, specified in the RPG::Action::targetId member.
                    TARGET_ALL_ACTORS 	        Target are all actors at once.
                    TARGET_MONSTER 	            Target is a monster, specified in the RPG::Action::targetId member.
                    TARGET_ALL_MONSTERS 	    Target are all monsters at once.     */

            // Erst prüfen darauf, ob ein Held von einem Helden angewählt wurde
            if(battler->action->target == RPG::TARGET_ACTOR && !(battler->isMonster()))
            {
                // Wenn ja, check ob ausführender Held = Zielheld
                // Die targetId ist die zeroBased PartyPosition, also bei Helden 0 bis 3. Die battler->id ist die Datenbank-Id des Helden, also 1 bis irgendwas.
                // Die Actor-objekte aus partyMember erben von der Battler-Klasse, somit haben sie auch die id als Datenbanb-Id
                if( (RPG::Actor::partyMember(battler->action->targetId)->id  == battler->id) && !disableHeroSelftarget ) // Vergleich der Datenbanken-Id von ausführendem- und Zielhelden.
                {
                    // Callback sofort ohne Vertauschen verlassen
                    return true;
                }
            } // Dann prüfen darauf, ob ein Monster von einem Monster angewählt wurde
            else if(battler->action->target == RPG::TARGET_MONSTER && (battler->isMonster()))
            {
                // Wenn ja, check ob ausführendes Monster = Zielmonster
                // Die targetId ist die zeroBased monsterPosition, also bei Monstern 0 bis 7.
                // Die battler->id eines Monsters ist die monsterGroupPosition + 1, also von 1 bis 8
                if( (battler->action->targetId  == (battler->id - 1)) && !disableMonsterSelftarget ) // Vergleich der monsterGroupPosition von ausführendem- und Zielmonster.
                {
                    // Callback sofort ohne Vertauschen verlassen
                    return true;
                }
            }

            // Überschreiben der Id des zu verwendenden Skills
            battler->action->skillId = skillReplaceMap[battler->action->skillId];
        }
    }

    return true;
}

