namespace CritCalcType1
{
//! Typ 1 ->Heroes have a fixed critical strike chance
int CalculateCritFix(RPG::Battler *battler)
{
    // Helden haben auf jeden Fall Defaultchance
    int currentCritChance = ConfigType1::parDefaultCritchance;

    // Prüfen, ob der Held für eine Variablenquelle registriert ist
    if(ConfigType1::parIdAndVariable.count(battler->id))
    {
        int varReference = ConfigType1::parIdAndVariable[battler->id];
        currentCritChance = RPG::variables[varReference];
        LOGINFO("HeroId " << battler->id << " CritType1.Critchance.FromVariable: " << currentCritChance);
    }
    else if(ConfigType1::parIdAndCritFix.count(battler->id))
    {
        // Prüfen, ob der Held für einen eigenen Fixwert besitzt
        currentCritChance = ConfigType1::parIdAndCritFix[battler->id];
        LOGINFO("HeroId " << battler->id << " CritType1.Critchance.Setting: " << currentCritChance);
    }
    else
    {
        LOGINFO("HeroId " << battler->id << " CritType1.Critchance.Default: " << currentCritChance);
    }

    //Grundcritwert vorhanden, nun im Falle eins Levelunterschiedes den Wert anpassen
    currentCritChance = LevelInfluence::HeroCritAdaptToLevel(currentCritChance, battler);
    LOGINFO("HeroId " << battler->id << " CritType1.Critchance.LevelAdapted: " << currentCritChance);
    return currentCritChance;
}
}
