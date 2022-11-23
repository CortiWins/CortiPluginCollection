namespace LevelInfluence
{
//! Get the level of the hero with the given partyIndex ( 0 - 3 ).
int GetHeroLevel ( int heroPartyIndex )
{
    if ( heroPartyIndex > -1 && heroPartyIndex < RPG::inventory->party.size )
    {
        return RPG::actors[RPG::inventory->party[heroPartyIndex]]->level;
    }

    return -1;
}

//! Get the average actor level.
int GetAverageHeroLevel()
{
    int sumOfActors = 0;
    int sumOfLevels = 0;
    for ( int partyIndex = 0; partyIndex < RPG::inventory->party.size; partyIndex++ ) // Alle Monsterslots
    {
        sumOfLevels += RPG::actors[RPG::inventory->party[partyIndex]]->level;
        sumOfActors++;
    }

    if ( sumOfActors > 0 )
    {
        return sumOfLevels / sumOfActors;
    }

    return -1;
}

//! Gets the int value of the monster with the given monsterPartyIndex ( 0 - 7 ).
int GetMonsterIntellect ( int monsterIndex )
{
    int currentIntellect = -1;
    if ( RPG::monsters[monsterIndex] != NULL )
    {
        currentIntellect = RPG::monsters[monsterIndex]->getIntelligence();
        if ( currentIntellect > 99 ) // Warnung wenn Intwert zu hoch...
        {
            LOGERROR ( "Int-Value (used as Level) of Monster at index  " << monsterIndex << " is > 99. Value: " << currentIntellect );
            currentIntellect = 99;
        }
    }

    return currentIntellect;
}

//! Get the average int value of the monsters.
int GetAverageMonsterGroupIntellect()
{
    int sumOfMonsters = 0;
    int sumOfIntellect = 0;
    for ( int iMonsters = 0; iMonsters < 8; iMonsters++ )
    {
        if ( RPG::monsters[iMonsters] != NULL )
        {
            if ( RPG::monsters[iMonsters]->hp > 0 && RPG::monsters[iMonsters]->notHidden )
            {
                int intelligence = RPG::monsters[iMonsters]->getIntelligence();
                if ( intelligence > 99 ) // Warnung wenn Intwert zu hoch...
                {
                    LOGERROR ( "Int-Value  (used as Level) of Monster at Index " << iMonsters << " is > 99. Value: " << intelligence );
                    intelligence = 99;
                }
                else
                {
                    sumOfIntellect += intelligence;
                    sumOfMonsters++;
                }
            }
        }
    }

    if ( sumOfMonsters > 0 )
    {
        return sumOfIntellect / sumOfMonsters;
    }

    return -1;
}

//! Gets the level of the Monster with the given monsterPartyIndex ( 0 - 7 ).
int GetMonsterLevel ( int monsterPartyIndex )
{
    // 0 = keine Adaption auf Basis des Levels, für die Umrechnung in Berechnungstyp 3 wird der Heldenlevel genutzt
    // 1 = der Int-Wert des Gegners wird als dessen Levelstufe angenommen
    // 2 = eine Variable enthält den Level der Gegner, dieser Wert wird als Level für alle Gegner angenommen
    if ( Configuration::critCalcWithLevel == 1 )
    {
        return GetMonsterIntellect ( monsterPartyIndex );
    }
    else if ( Configuration::critCalcWithLevel == 2 )
    {
        int currentLevel = RPG::variables[Configuration::critCalcWithLevelVariable];
        if ( currentLevel < 1 || currentLevel > 99 )
        {
            LOGERROR ( "MonsterLevel from Variable for MonsterIndex " << monsterPartyIndex << "is invalid: " << currentLevel );
            currentLevel = 1;
        }

        return currentLevel;
    }

    return 1;
}

//! Get the level or the target/the encounter. Used by LevelInfluence.HeroCritAdaptToLevel and directly in CritCalcType3.
int GetHeroTargetLevel ( RPG::Battler * currentBattler )
{
    // Level per Default auf den Heldenlevel setzen
    RPG::Actor* actPtr = ( RPG::Actor* ) currentBattler;
    int currentLevel = actPtr->level;

    // 0 = No changes based on level, the heros own level is used as a coefficient in type 3.
    // 1 = The enemies int value is taken as his level.
    // 2 = A variable holds all enemies level.
    if ( Configuration::critCalcWithLevel == 0 )
    {
        // Keine weitere Berechnung, Heldenlevel = Kampflevel
        return currentLevel;
    }
    else if ( Configuration::critCalcWithLevel == 1 )
    {
        // Wenn nicht die beiden Varianten, dann Kampflevel aus Intwerten der Monster
        if ( currentBattler->action->target == RPG::TARGET_MONSTER )
        {
            // Intwert des Zielmonsters hinterlegen
            int currentIntellect = GetMonsterIntellect ( currentBattler->action->targetId );
            // Wenn ein valider MonsterInt-Wert gefunden wurde, dann den übernehmen
            if ( currentIntellect != -1 )
            {
                currentLevel = currentIntellect;
            }
            return currentLevel;
        }
        else if ( currentBattler->action->target == RPG::TARGET_ALL_MONSTERS )
        {
            int currentIntellect = GetAverageMonsterGroupIntellect();
            if ( currentIntellect != -1 )
            {
                currentLevel = currentIntellect;
            }

            return currentLevel;
        }
        else if ( currentBattler->action->target == RPG::TARGET_ALL_ACTORS || currentBattler->action->target == RPG::TARGET_ACTOR )
        {
            return actPtr->level;
        }
    }
    else if ( Configuration::critCalcWithLevel == 2 )
    {
        return RPG::variables[Configuration::critCalcWithLevelVariable];
    }

    return currentLevel;
}

//! Get the level or the target/the encounter. Used by LevelInfluence.MonsterCritAdaptToLevel.
int GetMonsterTargetLevel ( RPG::Battler * currentBattler )
{
    int currentLevel = GetMonsterLevel ( currentBattler->id - 1 );

    // 0 = No changes based on level.
    // 1 = The enemies int value is taken as his level.
    // 2 = A variable holds all enemies level.
    if ( Configuration::critCalcWithLevel == 0 )
    {
        return currentLevel;
    }
    else
    {
        if ( currentBattler->action->target == RPG::TARGET_ACTOR )
        {
            return GetHeroLevel ( currentBattler->action->targetId );
        }
        else  if ( currentBattler->action->target == RPG::TARGET_ALL_ACTORS )
        {
            return GetAverageHeroLevel();
        }
    }

    return currentLevel;
}

//! Modifies the critical strike chance based on the level difference between hero and target. Used by CritCalcType1 and CritCalcType2.
int HeroCritAdaptToLevel ( int currentCritChance, RPG::Battler *currentBattler )
{
    // 0 = No changes based on level, the heros own level is used as a coefficient in type 3.
    // 1 = The enemies int value is taken as his level.
    // 2 = A variable holds all enemies level.
    if ( Configuration::critCalcWithLevel == 0 )
    {
        return currentCritChance;
    }
    else if ( Configuration::critCalcWithLevel == 1 || Configuration::critCalcWithLevel == 2 )
    {
        RPG::Actor* actPtr = ( RPG::Actor* ) currentBattler;
        int currentEncounterLevel = GetHeroTargetLevel ( currentBattler );
        int differenceLevel = actPtr->level - currentEncounterLevel;

        if ( differenceLevel > 0 ) // Positive Value -> Hero does have a higher level.
        {
            // Increase by 10% for each level of difference
            currentCritChance += ( currentCritChance * ( differenceLevel * 10 ) ) / 100;
        }
        else if ( differenceLevel < 0 ) // Negative Value -> Monsters do have a higher level.
        {
            // Reduce by 5% for each level of difference
            currentCritChance += ( currentCritChance * ( differenceLevel * 5 ) ) / 100;
            if ( currentCritChance < 0 )
            {
                currentCritChance = 0; // Smaller 0 is not possible.
            }
        }

        return currentCritChance;
    }

    return currentCritChance;
}

//! Modifies the critical strike chance based on the level difference between monster and target.
int MonsterCritAdaptToLevel ( int currentCritChance, RPG::Battler *currentBattler )
{
    // 0 = No changes based on level, the heros own level is used as a coefficient in type 3.
    // 1 = The enemies int value is taken as his level.
    // 2 = A variable holds all enemies level.
    if ( Configuration::critCalcWithLevel == 0 )
    {
        return currentCritChance;
    }
    else if ( Configuration::critCalcWithLevel == 1 || Configuration::critCalcWithLevel == 2 )
    {
        // MonsterLevel from Int or Variable
        int currentMonsterLevel = GetMonsterLevel ( currentBattler->id - 1 );
        int currentEncounterLevel = GetMonsterTargetLevel ( currentBattler );

        int differenceLevel = currentMonsterLevel - currentEncounterLevel;
        if ( differenceLevel > 0 ) // Positive Value -> Hero does have a higher level.
        {
            // Increase by 10% for each level of difference
            currentCritChance += ( currentCritChance * ( differenceLevel * 10 ) ) / 100;
        }
        else if ( differenceLevel < 0 ) // Negative Value -> Monsters do have a higher level.
        {
            // Reduce by 5% for each level of difference
            currentCritChance += ( currentCritChance * ( differenceLevel * 5 ) ) / 100;
            if ( currentCritChance < 0 )
            {
                currentCritChance = 0; // Smaller 0 is not possible.
            }
        }
    }

    return currentCritChance;
}
}
