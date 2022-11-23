namespace ConfigSkills
{
// SKILLSPECIFIC BONUSES
// < SkillId , Konstanter Critchancebonus additiv in % > Wertepaar welcher Skill um wieviel erhöht wird
std::map<int, int> skillAddConstant;
// < SkillId , Konstanter Critchancebonus multiplikativ in % > Wertepaar welcher Skill um wieviel erhöht wird
std::map<int, int> skillMulConstant;
// < SkillId , Aus Variable Critchancebonus additiv in % > Wertepaar welcher Skill um wieviel erhöht wird
std::map<int, int> skillAddVariable;
// < SkillId , Aus Variable Critchancebonus multiplikativ in % > Wertepaar welcher Skill um wieviel erhöht wird
std::map<int, int> skillMulVariable;
// < SkillId , Delay > Wertepaar um wieviel Frames die Animation verzögert wird.
std::map<int, int> skillDelay;

bool LoadSkillEntry(int index)
{
    int skillId = Helper::GetValueFromConfig("SkillId", index );
    if(skillId > 0)
    {
        LOGINFO("SkillId: " << skillId << " Settings ");

        // ADDITIV CONSTANT
        {
            int value = Helper::GetValueFromConfig("SkillAddCon", index );
            if((value > 0))
            {
                LOGINFO("SkillId: " << skillId << " Crit%-Add Const " << value);
                skillAddConstant[skillId] = value;
            }
        }

        // MULTIPLKATIV CONSTANT
        {
            int value = Helper::GetValueFromConfig("SkillMulCon", index );
            if((value >= 0))
            {
                LOGINFO("SkillId: " << skillId << " Crit%-Mul Const " << value);
                skillMulConstant[skillId] = value;
            }
        }

        // ADDITIV from VARIABLE
        {
            int value = Helper::GetValueFromConfig("SkillAddVar", index );
            if((value > 0))
            {
                LOGINFO("SkillId: " << skillId << " Crit%-Add From Var Id " << value);
                skillAddVariable[skillId] = value;
            }
        }

        // MULTIPLKATIV from VARIABLE
        {
            int value = Helper::GetValueFromConfig("SkillMulVar", index );
            if((value > 0))
            {
                LOGINFO("SkillId: " << skillId << " Crit%-Mul From Var Id " << value);
                skillMulVariable[skillId] = value;
            }
        }

        // SKILL DELAY
        {
            int value = Helper::GetValueFromConfig("SkillDelay", index );
            if((value > 0))
            {
                LOGINFO("SkillId: " << skillId << " Delay " << value << " frames");
                skillDelay[skillId] = value;
            }
        }

        return true;
    }
    else
    {
        // Wertepaar nicht vorhanden. Auslesen dieser Daten stoppen.
        return false;
    }
}

// Lädt die Einstellungen für spezielle Skills
void Load()
{
    // Leeren und Rücksetzen der Maps
    skillAddConstant.clear();
    skillMulConstant.clear();
    skillAddVariable.clear();
    skillMulVariable.clear();
    skillDelay.clear();

    bool endChecking = false;
    int increasingValue = 1;
    do
    {
        if(LoadSkillEntry(increasingValue))
        {
            // Wertepaar gefunden, nächsten Index versuchen.
            increasingValue++;
        }
        else
        {
            // Wertepaar nicht vorhanden. Auslesen dieser Daten stoppen.
            endChecking = true;
        }
    }
    while(!endChecking);
}
}
