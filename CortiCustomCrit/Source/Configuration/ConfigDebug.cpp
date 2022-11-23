namespace ConfigDebug
{

/*
void ShowError(int value, std::string valueName)
{
    if(CortiLog::isLogToConsole)
    {
        LOGLINE("ERROR: Invalid Value '" << valueName << "' is " << value);
    }
    else
    {
        std::stringstream stream;
        stream << "ERROR: Invalid Value '" << valueName << "' is " << value << "\n";
        Dialog::Show(stream.str(),"[CortiCustomCrit] Debug Configuration Data");
    }
}

// Debugparameter, jedes Setting wird per Textbox bestätigt.
bool debugParams = false;

// ID des ausführenden Helden
int debugHeroIdVariable = 0;
// Angewandter Angriffsbonus
int debugAppliedAttackBonusVariable = 0;
// Unveränderte Kritchance des Angriffes
int debugRawCritVariable = 0;
// Berechneter Level des Zieles
int debugTargetLevelVariable = 0;
// Nach Leveladaption errechnete kritische Trefferchance ( Typ 1 und 2)
int debugAdeptedCritVariable = 0;

void DebugAdeptedCritVariable(int value)
{
    if(debugAdeptedCritVariable>0)
    {
        RPG::variables[debugAdeptedCritVariable] = value;
    }
}

void DebugTargetLevelVariable(int value)
{
    if(debugTargetLevelVariable>0)
    {
        RPG::variables[debugTargetLevelVariable] = value;
    }
}

void DebugRawCritVariable(int value)
{
    if(debugRawCritVariable>0)
    {
        RPG::variables[debugRawCritVariable] = value;
    }
}


void DebugAppliedAttackBonusVariable(int value)
{
    if(debugAppliedAttackBonusVariable>0)
    {
        RPG::variables[debugAppliedAttackBonusVariable] = value;
    }
}

void DebugHeroIdToVariable(int value)
{
    if(debugHeroIdVariable>0)
    {
        RPG::variables[debugHeroIdVariable] = value;
    }
}

void ShowDebugValue(int value, std::string valueName)
{
    if(ConfigDebug::debugParams)
    {
        std::stringstream stream;
        stream << "Parameter: " << valueName << "\n";
        stream << "Value" << value << "\n";
        Dialog::Show(stream.str(),"[CortiCustomCrit] Debug Configuration Data");
    }
}

void ShowDebugValue(std::string value, std::string valueName)
{
    if(ConfigDebug::debugParams)
    {
        std::stringstream stream;
        stream << "Parameter: " << valueName << "\n";
        stream << "Value" << value << "\n";
        Dialog::Show(stream.str(),"[CortiCustomCrit] Debug Configuration Data");
    }
}
*/
void Load()
{


    /*
    // Debugparameter, jedes Setting wird per Textbox bestätigt.
    if(configMap.count("DebugParams"))
    {
        int debug = (atoi(configMap["DebugParams"].c_str()));
        debugParams = debug > 0 ? true :false;
    }

    // ID des ausführenden Helden in Variable 21
    if(configMap.count("DebugHeroIdVariable"))
    {
        int temp = (atoi(configMap["DebugHeroIdVariable"].c_str()));
        if(temp<0)
        {
            Dialog::Show(temp, "Invalid DebugHeroIdVariable");
            debugHeroIdVariable = 0;
        }
        else if(temp>0)
        {
            debugHeroIdVariable = temp;
        }
    }

    // Unveränderte Kritchance des Angriffes
    if(configMap.count("DebugRawCritVariable"))
    {
        int temp = (atoi(configMap["DebugRawCritVariable"].c_str()));
        if(temp<0)
        {
            Dialog::Show(temp, "Invalid DebugRawCritVariable");
            debugRawCritVariable = 0;
        }
        else if(temp>0)
        {
            debugRawCritVariable = temp;
        }
    }


    // Berechneter Level des Zieles
    if(configMap.count("DebugTargetLevelVariable"))
    {
        int temp = (atoi(configMap["DebugTargetLevelVariable"].c_str()));
        if(temp<0)
        {
            Dialog::Show(temp, "Invalid DebugTargetLevelVariable");
            debugTargetLevelVariable = 0;
        }
        else if(temp>0)
        {
            debugTargetLevelVariable = temp;
        }
    }

    // Nach Leveladaption errechnete kritische Trefferchance ( Typ 1 und 2)

    if(configMap.count("DebugAdeptedCritVariable"))
    {
        int temp = (atoi(configMap["DebugAdeptedCritVariable"].c_str()));
        if(temp<0)
        {
            debugAdeptedCritVariable = 0;
            Dialog::Show(temp, "Invalid DebugAdeptedCritVariable");
        }
        else if(temp>0)
        {
            debugAdeptedCritVariable = temp;
        }
    }

    // Angewandter Angriffsbonus
    if(configMap.count("DebugAppliedAttackBonusVariable"))
    {
        int temp = (atoi(configMap["DebugAppliedAttackBonusVariable"].c_str()));
        if(temp<0)
        {
            Dialog::Show(temp, "Invalid DebugAppliedAttackBonusVariable");
            debugAppliedAttackBonusVariable = 0;
        }
        else if(temp>0)
        {
            debugAppliedAttackBonusVariable = temp;
        }
    }
    */
}




}
