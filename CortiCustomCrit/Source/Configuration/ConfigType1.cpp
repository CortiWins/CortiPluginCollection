namespace ConfigType1
{
// Defaultcritchance f�r Helden, die keine Customchance bekommen haben
int parDefaultCritchance = 20;
// Mapping Helden-ID und Fixer Critwert
std::map<int, int> parIdAndCritFix;
// Mapping Helden-ID und Quellvarible f�r Critwert
std::map<int, int> parIdAndVariable;

// Laden der Einstellungen f�r Kritberechnung Typ 1
// Typ 1 ->Helden haben eine vom Int-Wert unabh�ngige Kritchance.
void Load()
{
    parDefaultCritchance = Helper::GetValueFromConfig("t1CritChanceDefault");
    if(parDefaultCritchance < 0 || parDefaultCritchance > 100)
    {
        LOGERROR("t1CritChanceDefault: " << parDefaultCritchance << "% Ung�nstig");
        Configuration::isValidSettings = false;
    }
    else
    {
        LOGINFO("t1CritChanceDefault: " << parDefaultCritchance << "%");
    }

    bool stopRead = false;
    int index = 1;
    while(!stopRead)
    {
        int heroId = Helper::GetValueFromConfig("t1HeroCritHero_", index, "_Id" );
        if(heroId > 0)
        {
            int critSourceFix = Helper::GetValueFromConfig("t1HeroCritHero_", index, "_FixCrit" );
            int critSourceVariableId = Helper::GetValueFromConfig("t1HeroCritHero_", index, "_Variable" );

            if(critSourceFix >= 0)
            {
                parIdAndCritFix[heroId] = critSourceFix;
                LOGINFO("Hero Id" << heroId << " Constant Critchance: " << critSourceFix << "%");
            }
            else if(critSourceVariableId > 0)
            {
                parIdAndVariable[heroId] = critSourceVariableId;
                LOGINFO("Hero Id" << heroId << " Critchance from Variable ID: " << critSourceVariableId);
            }

            index++;
        }
        else
        {
            stopRead = true;
        }
    }
}
}
