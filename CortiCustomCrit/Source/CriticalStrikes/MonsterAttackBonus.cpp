namespace MonsterAttackBonus
{
//! ATK values added to the Monsters.
int monsterAtkValues[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

//! Add an atk-bonus to the monster with the given monsterPartyIndex ( 0 - 7 ).
void AddCritBonus(int monsterPartyIndex)
{
    if(!ConfigMonsterCrit::isMonsterCritEnabled || monsterPartyIndex < 0 || monsterPartyIndex >= 8)
    {
        return;
    }

    RPG::Monster *monPtr = RPG::monsters[monsterPartyIndex];
    if(monPtr == null)
    {
        return;
    }

    if(monsterAtkValues[monsterPartyIndex] == 0)
    {
        if(ConfigMonsterCrit::monsterCritAttackBonus == 1)
        {
            // 1 = Increase ATK by N% of the MonsterDatabaseATK value.
            RPG::DBMonster *dbMonPtr = RPG::dbMonsters[monPtr->databaseId];
            int atkBonus = (dbMonPtr->attack * ConfigMonsterCrit::monsterCritAttackBonusPercentage) / 100;
            monsterAtkValues[monsterPartyIndex] = atkBonus;
        }
        else if ( ConfigMonsterCrit::monsterCritAttackBonus == 2)
        {
            // 2 = Increase ATK by N% of the ATK of a hero in the database at a calculated level
            RPG::DBActor *dbActor = RPG::dbActors[ConfigMonsterCrit::monsterCritAttackBonusHeroDbId];
            if(dbActor != null)
            {
                int level = LevelInfluence::GetMonsterLevel(monsterPartyIndex);
                int atkBonus = dbActor->attack[level]; // gets ATK value from the dbHeros Attack-Curve.
                monsterAtkValues[monsterPartyIndex] = atkBonus;
            }
        }

        LOGINFO("MonsterIndex " << monsterPartyIndex << " Add Critbonus: ATK Bonus " << monsterAtkValues[monsterPartyIndex]);
        monPtr->attackDiff += monsterAtkValues[monsterPartyIndex];
    }
    else
    {
        LOGINFO("MonsterIndex " << monsterPartyIndex << " Add Critbonus: ATK Bonus already set " << monsterAtkValues[monsterPartyIndex]);
    }
}

//! Remove the added atk-bonus from the monster with the given monsterPartyIndex ( 0 - 7 ).
void ResetCritBonus(int monsterPartyIndex)
{
    if(monsterAtkValues[monsterPartyIndex] > 0)
    {
        RPG::Monster *monPtr = RPG::monsters[monsterPartyIndex];
        monPtr->attackDiff -= monsterAtkValues[monsterPartyIndex];
        monsterAtkValues[monsterPartyIndex] = 0;
        LOGINFO("MonsterIndex " << monsterPartyIndex << " Reset ATK Bonus");
    }
}

//! Gets a value that describes if the monster with the given monsterPartyIndex ( 0 - 7 ) has it's critical strike bonus active.
bool GetAtkStatus(int monsterPartyIndex)
{
    return monsterAtkValues[monsterPartyIndex] > 0 ? true : false;
}

// Passiert wenn das Spiel resettet wurde im Testmodus.
// Unterschied zwischen OnResetGame und OnSceneChange:
// in OnResetGame wird nur das Kritbonus-Flag resettet, das reduzieren der Attack-Werte passiert durch den Spielreset von selbst.
void OnResetGame()
{
    for(int monsterPartyIndex = 0; monsterPartyIndex < 8; monsterPartyIndex++)
    {
        monsterAtkValues[monsterPartyIndex] = 0;
    }
}

// Aufgerufen bei Szenenwechsel zum Kampf oder vom Kampf weg. In dem Fall alle Kritboni entfernen und Animationen abbrechen
void OnSceneChange()
{
    for(int monsterPartyIndex = 0; monsterPartyIndex < 8; monsterPartyIndex++)
    {
        ResetCritBonus(monsterPartyIndex);
    }
}
}
