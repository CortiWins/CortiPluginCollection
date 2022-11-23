namespace ConfigType2
{
// Determines which stat is chosen for Type 2 calculations
// 1 = int is used.
// 2 = agi is used.
// 3 = HeroCrit is used as a 1 in N calculation
// 4 = HeroCrit is used as a percentage
int critSourceStat = 0;

void Load()
{
    critSourceStat = Helper::GetValueFromConfig("t2CritSourceStat");
    if(critSourceStat <= 0 || critSourceStat > 4 )
    {
        LOGERROR("t2CritSourceStat:" << critSourceStat << ". This replaced the parameter 'critSource' from older versions.");
        Configuration::isValidSettings = false;
    }
    else
    {
        LOGINFO("t2CritSourceStat:" << critSourceStat);
    }
}
}
