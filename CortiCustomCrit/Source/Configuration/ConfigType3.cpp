namespace ConfigType3
{
// Determines which stat is chosen for Type 3 calculations
// 1 = Plugin uses intellect for Type 3 calculations ( Default )
// 2 = Plugin uses agility for Type 3 calculations
int critSourceStat = 0;

// Datenbank-ID des Helden, dessen Kurvenverlauf als Daten für die Umrechnung angenommen werden
int ratingCoefficientHeroId = 0;

// Laden der Einstellungen für Kritberechnung Typ 3
// Typ 3 -> Der Intwert ist ein Ratingwert, der in eine Chance umgewandelt wird.
void Load()
{

    critSourceStat = Helper::GetValueFromConfig("t3CritSourceStat");
    if(critSourceStat <= 0 || critSourceStat > 2 )
    {
        LOGERROR("t3CritSourceStat:" << critSourceStat << ". This replaced the parameter 'critSource' from older versions.");
        Configuration::isValidSettings = false;
    }
    else
    {
        LOGINFO("t3CritSourceStat:" << critSourceStat);
    }

    // Anzahl Helden in der Datenbank
    int numberOfActors= RPG::actors.count();
    ratingCoefficientHeroId = Helper::GetValueFromConfig("t3RatingCoefficientHeroId");
    if(ratingCoefficientHeroId <= 0)
    {
        LOGERROR("t3RatingCoefficientHeroId '" << ratingCoefficientHeroId << "'. Not configured. See readme.");
        Configuration::isValidSettings = false;

    }
    else if(ratingCoefficientHeroId>numberOfActors)
    {
        LOGERROR("t3RatingCoefficientHeroId '" << ratingCoefficientHeroId << "' exceeds number of actors. See readme.");
        Configuration::isValidSettings = false;
    }
}
}
