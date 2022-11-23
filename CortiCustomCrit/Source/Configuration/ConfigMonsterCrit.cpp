namespace ConfigMonsterCrit
{
//! Is only set if all values are configured validly.
bool isMonsterCritEnabled = false;
int monsterCritSourceStat = 0;
int monsterCritOnAttack = 0;
int monsterCritOnSkills = 0;
int monsterCritAttackBonus = 0;

int monsterCritAttackBonusPercentage = 0;
int monsterCritAttackBonusHeroDbId = 0;

void Load()
{
    isMonsterCritEnabled = true;

    // Determines which stat is chosen for monster crit chance calculations
    // 1 = int is used.
    // 2 = agi is used.
    // 3 = MonsterCrit is used as a 1 in N calculation
    // 4 = MonsterCrit is used as a percentage
    monsterCritSourceStat = Helper::GetValueFromConfig ( "MonsterCritSourceStat" );
    if ( monsterCritSourceStat <= 0 || monsterCritSourceStat > 4 )
    {
        LOGERROR ( "MonsterCritSourceStat: " << monsterCritSourceStat << " Invalid Value. Consult readme for valid settings." );
        isMonsterCritEnabled = false;
    }
    if ( monsterCritSourceStat == 1 && Configuration::critCalcWithLevel == 1 )
    {
        LOGERROR ( "MonsterCritSourceStat setting uses int as monster crit source while 'CritCalcWithLevel' uses int for the monster level." );
        isMonsterCritEnabled = false;
    }
    else
    {
        LOGINFO ( "MonsterCritSourceStat: " << monsterCritSourceStat );
    }

    // MonsterCritOnAttack
    // 1 = No Plugin-Crits for Monster-Standard-Attacks
    // 2 = Plugin-Crits for Monster-Standard-Attacks active. 2k3 standard crits deactived by memory-hack.
    // 3 = Plugin-Crits for Monster-Standard-Attacks active. 2k3 standard crits stay active.
    monsterCritOnAttack = Helper::GetValueFromConfig ( "MonsterCritOnAttack" );
    if ( monsterCritOnAttack <= 0 || monsterCritOnAttack > 3 )
    {
        LOGERROR ( "MonsterCritOnAttack: " << monsterCritOnAttack << " Invalid Value. Consult readme for valid settings." );
        isMonsterCritEnabled = false;
    }
    else
    {
        if ( monsterCritOnAttack == 2 )
        {
            Configuration::DisableStandardMonsterCritInMemory();
            LOGINFO ( "MonsterCritOnAttack: " << monsterCritOnAttack << " 2k3 standard crits deactived by memory-hack" );
        }
        else
        {
            LOGINFO ( "MonsterCritOnAttack: " << monsterCritOnAttack << " 2k3 standard crits active" );
        }
    }

    // MonsterCritOnSkills
    // 1 = No Plugin-Crits for Monster Skills.
    // 2 = Plugin-Crits for Monster Skills but only attacks.
    // 3 = Plugin-Crits for Monster Skills both attacks and healing.
    monsterCritOnSkills = Helper::GetValueFromConfig ( "MonsterCritOnSkills" );
    if ( monsterCritOnSkills <= 0 || monsterCritOnSkills > 3 )
    {
        LOGERROR ( "MonsterCritOnSkills: " << monsterCritOnAttack << " Invalid Value. Consult readme for valid settings." );
        isMonsterCritEnabled = false;
    }
    else
    {
        LOGINFO ( "MonsterCritOnSkills: " << monsterCritOnAttack );
    }

    // MonsterCritAttackBonus
    // 1 = Increase ATK by N% of the MonsterDatabaseATK value.
    // 2 = Increase ATK by N% of the ATK of a hero in the database at a calculated level ( see other Configuration::CritCalcWithLevel setting )
    monsterCritAttackBonus = Helper::GetValueFromConfig ( "MonsterCritAttackBonus" );
    if ( monsterCritAttackBonus <= 0 || monsterCritAttackBonus > 2 )
    {
        LOGERROR ( "MonsterCritAttackBonus: " << monsterCritAttackBonus << " Invalid Value. Consult readme for valid settings." );
        isMonsterCritEnabled = false;
    }
    else
    {
        LOGINFO ( "MonsterCritAttackBonus: " << monsterCritAttackBonus );

        if ( monsterCritAttackBonus == 1 )
        {
            monsterCritAttackBonusPercentage = Helper::GetValueFromConfig ( "MonsterCritAttackBonusPercentage" );
            if ( monsterCritAttackBonusPercentage <= 0 )
            {
                LOGERROR ( "MonsterCritAttackBonusPercentage: " << monsterCritAttackBonusPercentage << " invalid value." );
                isMonsterCritEnabled = false;
            }
            else
            {
                LOGINFO ( "MonsterCritAttackBonusPercentage: " << monsterCritAttackBonusPercentage );
            }
        }
        else if ( monsterCritAttackBonus == 2 )
        {
            int numberOfActors = RPG::actors.count();
            monsterCritAttackBonusHeroDbId = Helper::GetValueFromConfig ( "MonsterCritAttackBonusHeroDbId" );
            if ( monsterCritAttackBonusHeroDbId < 1 || monsterCritAttackBonusHeroDbId > numberOfActors )
            {
                LOGERROR ( "MonsterCritAttackBonusHeroDbId: " << monsterCritAttackBonusHeroDbId << " invalid value." );
                isMonsterCritEnabled = false;
            }
            else
            {
                LOGINFO ( "MonsterCritAttackBonusHeroDbId: " << monsterCritAttackBonusHeroDbId );
            }

            if ( Configuration::critCalcWithLevel == 0 )
            {
                LOGERROR ( "MonsterCritAttackBonus: " << monsterCritAttackBonus << " Requires a monsterLevel." );
            }
        }
    }
}
}
