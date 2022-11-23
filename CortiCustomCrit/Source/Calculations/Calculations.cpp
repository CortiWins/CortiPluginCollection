namespace Calculations
{
//! Checks if the skill with the given id has the ability to deal damage or heal.
bool CanSkillDamageOrHeal ( int skillId )
{
    if ( skillId > 0 && skillId < RPG::skills.count() )
    {
        RPG::Skill *skillPtr = RPG::skills[skillId];
        if ( skillPtr->affectHp )
        {
            return true;
        }

        return false;
    }

    return false;
}

//! Modifies the critical strice chance for the given skill. Returns the modifies crit chance.
int ApplySkillspecific ( int currentCritChance, int skillId )
{
    // MULTIPLIKATIV KONSTANT
    if ( ConfigSkills::skillMulConstant.count ( skillId ) )
    {
        // Multiplikative Chance zu dem Skill in Map hinterlegt
        int bonus = ConfigSkills::skillMulConstant[skillId];
        currentCritChance = ( currentCritChance * bonus ) / 100;
        LOGINFO ( "SkillId: " << skillId << " Multiply.Constant '" << bonus << "' NewTotal: " << currentCritChance << "%" );
    }
    else if ( Configuration::disabledSkillCrit == true )
    {
        // If this skill is not set to be enabled, and all skills are meant to be disabled, the chance is set to zero here.
        currentCritChance = 0;
        LOGINFO ( "SkillId: " << skillId << " Critical Chance for all Skills disabled" );
    }

    // MULTIPLIKATIV VARIABLE
    if ( ConfigSkills::skillMulVariable.count ( skillId ) )
    {
        // Multiplikative Chance zu dem Skill in Map hinterlegt
        int variableId = ConfigSkills::skillMulVariable[skillId];
        int bonus = RPG::variables[variableId];
        currentCritChance = ( currentCritChance * bonus ) / 100;
        LOGINFO ( "SkillId: " << skillId << " Multiply.FromVariable '" << bonus << "' NewTotal: " << currentCritChance << "%" );
    }

    // ADDITIV VARIABLE
    if ( ConfigSkills::skillAddVariable.count ( skillId ) )
    {
        // Additive Chance zu dem Skill in Map hinterlegt
        int variableId = ConfigSkills::skillAddVariable[skillId];
        int bonus =  RPG::variables[variableId];
        currentCritChance = currentCritChance + bonus;
        LOGINFO ( "SkillId: " << skillId << " Additiv.Constant '" << bonus << "' NewTotal: " << currentCritChance << "%" );
    }

    // ADDITIV KONSTANT
    if ( ConfigSkills::skillAddConstant.count ( skillId ) )
    {
        // Additive Chance zu dem Skill in Map hinterlegt
        int bonus = ConfigSkills::skillAddConstant[skillId];
        currentCritChance = currentCritChance + bonus;
        LOGINFO ( "SkillId: " << skillId << " Additiv.Constant '" << bonus << "' NewTotal: " << currentCritChance << "%" );
    }

    return currentCritChance;
}

//! Returns the critical strike bonus of the equipped weapons.
int ApplyWeaponCritBonus ( RPG::Battler *battler )
{
    if ( !battler->isMonster() )
    {
        // If Weapon crit is only applied to weapon attacks, quit here.
        if ( battler->action->kind == RPG::AK_SKILL && Configuration::critCalcWeaponCritBonusApplication == 2 )
        {
            return 0;
        }

        int weaponCrit = 0;
        RPG::Actor *actPtr = ( RPG::Actor * ) battler;
        int weaponId1 = actPtr->weaponId;
        int weaponId2 = actPtr->shieldId;

        RPG::Item *weapon1Ptr = weaponId1 > 0 ? RPG::items[weaponId1] : null;
        if ( weapon1Ptr != null && weapon1Ptr->type == RPG::ITEM_WEAPON && weapon1Ptr->critBonus > 0 )
        {
            weaponCrit += weapon1Ptr->critBonus;
            LOGINFO ( "HeroId " << battler->id << " WeaponSlot.1: ID"  << weaponId1 << " CritBonus" << weapon1Ptr->critBonus << "%" );
        }

        RPG::Item *weapon2Ptr = weaponId1 > 0 ? RPG::items[weaponId2] : null;
        if ( weapon2Ptr != null && weapon2Ptr->type == RPG::ITEM_WEAPON && weapon2Ptr->critBonus > 0 )
        {
            weaponCrit += weapon2Ptr->critBonus;
            LOGINFO ( "HeroId " << battler->id << " WeaponSlot.2: ID"  << weaponId2 << " CritBonus" << weapon2Ptr->critBonus << "%" );
        }

        return weaponCrit;
    }

    return 0;
}

//! Returns if the heros action can crit.
bool CanHeroCrit ( RPG::Battler *battler )
{
    if ( battler->action->kind == RPG::AK_SKILL )
    {
        if ( !CanSkillDamageOrHeal ( battler->action->skillId ) )
        {
            return false;
        }

        // Crit on Skills is disabled and there is no exception for this particular skillId.
        if ( ( Configuration::disabledSkillCrit == true ) && ( ConfigSkills::skillMulConstant.count ( battler->action->skillId ) == 0 ) )
        {
            return false;
        }

        // Critical strikes on healing skills is disabled and this is a defensive skill.
        if ( Configuration::critCalcOnHerosDisabled && ( ( battler->action->target == RPG::TARGET_ALL_ACTORS ) || ( battler->action->target == RPG::TARGET_ACTOR ) ) )
        {
            return false;
        }

        return true;
    }
    else if ( battler->action->kind == RPG::AK_BASIC )
    {
        // Weapon attacks can crit.
        if ( battler->action->basicActionId == RPG::BA_ATTACK || battler->action->basicActionId == RPG::BA_DOUBLE_ATTACK )
        {
            // 1 = Use plugin criticals. The standard crit system is disabled with a memory-hack.
            // 2 = Use plugin criticals. The standard crit system will not be disabled.
            // 3 = The plugin does not work on weapon attacks.
            if ( ( Configuration::critCalcWeaponCriticalType == 1 ) || ( Configuration::critCalcWeaponCriticalType == 2 ) )
            {
                return true;
            }
        }
    }

    return false;
}

//! Returns if the monsters action can crit.
bool CanMonsterCrit ( RPG::Battler *battler )
{
    if ( battler->action->kind == RPG::AK_SKILL )
    {
        if ( !CanSkillDamageOrHeal ( battler->action->skillId ) )
        {
            return false;
        }

        // Crit on Skills is disabled and there is no exception for this particular skillId.
        if ( ( ConfigMonsterCrit::monsterCritOnSkills == 1 )
                && ( ConfigSkills::skillMulConstant.count ( battler->action->skillId ) == 0 ) )
        {
            return false;
        }

        // Critical strikes on healing skills is disabled and this is a defensive skill.
        if ( ConfigMonsterCrit::monsterCritOnSkills == 2
                && ( ( battler->action->target == RPG::TARGET_ALL_MONSTERS ) || ( battler->action->target == RPG::TARGET_MONSTER ) ) )
        {
            return false;
        }

        return true;
    }
    else if ( battler->action->kind == RPG::AK_BASIC )
    {
        // Weapon attacks can crit.
        if ( battler->action->basicActionId == RPG::BA_ATTACK || battler->action->basicActionId == RPG::BA_DOUBLE_ATTACK )
        {
            // monsterCritOnAttack
            // 1 = No Plugin-Crits for Monster-Standard-Attacks
            // 2 = Plugin-Crits for Monster-Standard-Attacks active. 2k3 standard crits deactived by memory-hack.
            // 3 = Plugin-Crits for Monster-Standard-Attacks active. 2k3 standard crits stay active.
            if ( ( ConfigMonsterCrit::monsterCritOnAttack == 2 ) || ( ConfigMonsterCrit::monsterCritOnAttack == 3 ) )
            {
                return true;
            }
        }
    }

    return false;
}

//! Calculates the critical strike chance of a given monster.
int CalculateMonsterCrit ( RPG::Battler *battler )
{
    // 1 = int is used.
    // 2 = agi is used.
    // 3 = MonsterCrit is used as a 1 in N calculation
    // 4 = MonsterCrit is used as a percentage
    int currentCritChance = 0;

    if ( ConfigMonsterCrit::monsterCritSourceStat == 1 )
    {
        currentCritChance = battler->getIntelligence();
        LOGINFO ( "Monster " << battler->id << " Monster.Critchance.FromInt: " << currentCritChance );
    }
    else if ( ConfigMonsterCrit::monsterCritSourceStat == 2 )
    {
        currentCritChance = battler->getAgility();
        LOGINFO ( "Monster " << battler->id << " Monster.Critchance.FromAgi: " << currentCritChance );
    }
    else if ( ConfigMonsterCrit::monsterCritSourceStat == 3 )
    {
        RPG::Monster *monPtr = ( RPG::Monster* ) battler;
        RPG::DBMonster *dbMonPtr = RPG::dbMonsters[monPtr->databaseId];
        if ( dbMonPtr->critFlag )
        {
            currentCritChance = 100 / dbMonPtr->critPercentage;
        }

        LOGINFO ( "Monster " << battler->id << " Monster.Critchance.FromDbCrit 1/N: " << currentCritChance );
    }
    else if ( ConfigMonsterCrit::monsterCritSourceStat == 4 )
    {
        RPG::Monster *monPtr = ( RPG::Monster* ) battler;
        RPG::DBMonster *dbMonPtr = RPG::dbMonsters[monPtr->databaseId];
        if ( dbMonPtr->critFlag )
        {
            currentCritChance = dbMonPtr->critPercentage;
        }

        LOGINFO ( "Monster " << battler->id << " Monster.Critchance.FromDbCrit as %: " << currentCritChance );
    }

    //Grundcritwert vorhanden, nun im Falle eins Levelunterschiedes den Wert anpassen
    currentCritChance = LevelInfluence::MonsterCritAdaptToLevel ( currentCritChance, battler );
    LOGINFO ( "Monster " << battler->id << " Monster.Critchance.LevelAdapted: " << currentCritChance );
    return currentCritChance;
}

//! Return a values that describes if the item with the give databaseId has its "prevntCrit"-Flag set.
bool IsItemPreventCritEnabled ( int itemDbId )
{
    if ( itemDbId > 0 )
    {
        RPG::Item *itemPtr = RPG::items[itemDbId];
        if ( itemPtr->type != RPG::ITEM_WEAPON )
        {
            return itemPtr->preventCrit;
        }
    }

    return false;
}

//! Return a values that describes if the given actor is immune to critical strikes based on his equipped items.
bool IsHeroPreventCritEnabled ( RPG::Actor* actPtr )
{
    bool isHeroPreventCritEnabled = IsItemPreventCritEnabled ( actPtr->shieldId );
    isHeroPreventCritEnabled = IsItemPreventCritEnabled ( actPtr->armorId ) || isHeroPreventCritEnabled;
    isHeroPreventCritEnabled = IsItemPreventCritEnabled ( actPtr->helmetId )  || isHeroPreventCritEnabled;
    isHeroPreventCritEnabled = IsItemPreventCritEnabled ( actPtr->accessoryId )  || isHeroPreventCritEnabled;
    return isHeroPreventCritEnabled;
}

//! Reduces the critical strike chance based on the items the targeted actors are wearing.
int ApplyAntiCrit ( int currentCritChance, RPG::Action *actionPtr )
{
    if ( actionPtr->target == RPG::TARGET_ALL_ACTORS )
    {
        // Action targets all actors.
        // Iterate over party and count number of Actors with PreventCrit-Attribute.
        int actorCountLiving = RPG::inventory->party.size;
        int actorCountUnProtected = 0;
        for ( int partyIndex = 0; partyIndex < RPG::inventory->party.size; partyIndex++ )
        {
            RPG::Actor* actPtr = RPG::actors[RPG::inventory->party[partyIndex]];
            if ( actPtr->hp > 0 )
            {
                actorCountLiving++;
                if ( !IsHeroPreventCritEnabled ( actPtr ) )
                {
                    actorCountUnProtected++;
                }
            }
        }

        // Reduce crit by a part based on the number of actors with "PreventCrit"-Items.
        if ( actorCountLiving > 0 )
        {
            currentCritChance = ( currentCritChance * actorCountUnProtected ) / actorCountLiving;
        }
    }
    else if ( actionPtr->target == RPG::TARGET_ACTOR )
    {
        // Action targets one target that is protected by "preventCrit"-Setting on one of the items.
        RPG::Actor* actPtr = RPG::actors[RPG::inventory->party[actionPtr->targetId]];
        if ( actPtr != null && actPtr->hp > 0 && IsHeroPreventCritEnabled ( actPtr ) )
        {
            return 0;
        }
    }

    return currentCritChance;
}

}
