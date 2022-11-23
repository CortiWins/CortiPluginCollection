namespace CritCalcType2
{
//! Typ 2 ->Heroes have a configured value as crit-chance.
int CalculateCritRaw(RPG::Battler *battler)
{
    // 1 = int is used.
    // 2 = agi is used.
    // 3 = HeroCrit is used as a 1 in N calculation
    // 4 = HeroCrit is used as a percentage
    int currentCritChance = 0;
    if(ConfigType2::critSourceStat == 1)
    {
        currentCritChance = battler->getIntelligence();
        LOGINFO("HeroId " << battler->id << " CritType2.Critchance.FromInt: " << currentCritChance);
    }
    else if(ConfigType2::critSourceStat == 2)
    {
        currentCritChance = battler->getAgility();
        LOGINFO("HeroId " << battler->id << " CritType2.Critchance.FromAgi: " << currentCritChance);
    }
    else if(ConfigType2::critSourceStat == 3)
    {
        RPG::DBActor *actPtr = battler->isMonster() ? null : RPG::dbActors[battler->id];
        if(actPtr != null && actPtr->allowCriticalHit)
        {
            currentCritChance = 100 / actPtr->criticalHitProbability;
        }

        LOGINFO("HeroId " << battler->id << " CritType2.Critchance.FromDbCrit 1/N: " << currentCritChance);
    }
    else if(ConfigType2::critSourceStat == 4)
    {
        RPG::DBActor *actPtr = battler->isMonster() ? null : RPG::dbActors[battler->id];
        if(actPtr != null && actPtr->allowCriticalHit)
        {
            currentCritChance = actPtr->criticalHitProbability;
        }

        LOGINFO("HeroId " << battler->id << " CritType2.Critchance.FromDbCrit as %: " << currentCritChance);
    }

    //Grundcritwert vorhanden, nun im Falle eins Levelunterschiedes den Wert anpassen
    currentCritChance = LevelInfluence::HeroCritAdaptToLevel(currentCritChance, battler);
    LOGINFO("HeroId " << battler->id << " CritType2.Critchance.LevelAdapted: " << currentCritChance);
    return currentCritChance;
}
}
