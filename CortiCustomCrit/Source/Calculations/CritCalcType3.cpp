namespace CritCalcType3
{
//! Typ3 -> The INT- or AGI-Value is a rating-value, that is converted into a chance.
int CalculateCritByRating(RPG::Battler *battler)
{
    // Kritchance% = (Rating des Helden * 100 )  / Levelkonstante[Kampfstufe]
    int currentRating = ConfigType3::critSourceStat == 1
        ? battler->getAgility()
        : battler->getIntelligence();

    int currentLevel = LevelInfluence::GetHeroTargetLevel(battler); // Rating
    int hpMaxAkaCoefficient = RPG::dbActors[ConfigType3::ratingCoefficientHeroId]->maxHp[currentLevel];

    int currentCritChance = (currentRating * 100 ) / hpMaxAkaCoefficient;
    LOGINFO("HeroId " << battler->id << " CritType3.RatingValue: " << currentRating << ( ConfigType3::critSourceStat == 1 ? " from AGI" : " from INT"));
    LOGINFO("HeroId " << battler->id << " CritType3.Level:       " << currentLevel);
    LOGINFO("HeroId " << battler->id << " CritType3.Critchance:  " << currentCritChance);
    return currentCritChance;
}
}
