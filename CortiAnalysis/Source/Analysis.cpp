namespace CortiAnalysis
{

bool analysisSkillsPresent = false;
std::vector<int> analysisSkills;

// automatisches Analysieren von Monstern ->sync.in Datenarray
bool monsterSwitchesAutoset = false;
int monsterSwitchesArray = 0;

// onAction -> Switch setzen
bool setSwitchBattlePage = false;
int setSwitchBattlePageId = 0;

// onAction -> track Skill.ID
bool trackSkillId = false;
int trackSkillIdVariable = 0;

// onAction -> track Item.ID
bool trackItemId = false;
int trackItemIdVariable = 0;

// onAction -> track GroupTarget.ID
bool trackGroupTargetId = false;
int trackGroupTargetIdVariable = 0;

// onAction -> track Database.ID
bool trackDatabaseId = false;
int trackDatabaseIdVariable = 0;

// onAction -> track DatabaseArray.ID
bool trackDatabaseIdArray = false;
int trackDatabaseIdArrayVariable = 0;


bool VectorContainsSkill(int id)
{
    // find id
    std::vector<int>::iterator i = find(analysisSkills.begin(), analysisSkills.end(), id);

    if (i != analysisSkills.end())
    {
        // found it
        return true;
    }
    else
    {
        // doesn't exist
        return false;
    }
}

void AnalyseMonsterAutoset(int databaseId)
{
    RPG::switches[monsterSwitchesArray + databaseId] = true;
}

void UsedAnalysisSkill(RPG::Action *action)
{
    // Nur Skills, die auf Monster oder alleMonster gehen
    if((action->target == RPG::TARGET_MONSTER )||(action->target == RPG::TARGET_ALL_MONSTERS ))
    {
        if(VectorContainsSkill(action->skillId))
        {
            //Helper::ShowInfoBox(action->skillId,"Skill Id in analysisVector");
            if(monsterSwitchesAutoset)
            {
                if(action->target == RPG::TARGET_MONSTER )
                {
                    int monsterTargetId = action->targetId; // 0 bis 7
                    // Helper::ShowInfoBox(monsterTargetId,"SingleTarget");
                    RPG::Monster *monPtr =  RPG::monsters[monsterTargetId];
                    if(monPtr!=NULL)
                    {
                        AnalyseMonsterAutoset(monPtr->databaseId);
                    }
                }
                else if(action->target == RPG::TARGET_ALL_MONSTERS )
                {
                    for(int iMonster = 0; iMonster < 8; iMonster++)
                    {
                        RPG::Monster *monPtr =  RPG::monsters[iMonster];
                        if(monPtr!=NULL)
                        {
                            if(monPtr->notHidden)
                            {
                                AnalyseMonsterAutoset(monPtr->databaseId);
                            }
                        }
                    }
                }
            }

            if(trackSkillId)
            {
                RPG::variables[trackSkillIdVariable] = action->skillId;
            }

            if(trackItemId)
            {
                if( action->kind == RPG::AK_ITEM)
                {
                    RPG::variables[trackItemIdVariable] = action->itemId;
                }
                else
                {
                    RPG::variables[trackItemIdVariable] = 0;
                }
            }

            if(trackGroupTargetId)
            {
                if(action->target == RPG::TARGET_MONSTER )
                {
                    RPG::variables[trackGroupTargetIdVariable] = action->targetId + 1;
                }
                else if(action->target == RPG::TARGET_ALL_MONSTERS)
                {
                    RPG::variables[trackGroupTargetIdVariable] = 99;
                }
                else
                {
                    RPG::variables[trackGroupTargetIdVariable] = 0;
                }
            }

            if(trackDatabaseId && action->target == RPG::TARGET_MONSTER )
            {
                RPG::Monster *monPtr = RPG::monsters[action->targetId];

                if(monPtr != NULL)
                {
                    RPG::variables[trackDatabaseIdVariable] = monPtr->databaseId;
                }
            }
            else if( trackDatabaseIdArray && action->target == RPG::TARGET_ALL_MONSTERS)
            {
                int index = 0;
                for(int iMonster = 0; iMonster < 8; iMonster++)
                {
                    RPG::Monster *monPtr =  RPG::monsters[iMonster];
                    if(monPtr!=NULL)
                    {
                        if(monPtr->notHidden)
                        {
                            RPG::variables[trackDatabaseIdArrayVariable + index] = monPtr->databaseId;
                            index++;
                        }
                    }
                }

                while(index<8)
                {
                    RPG::variables[trackDatabaseIdArrayVariable + index] = 0;
                    index++;
                }
            }

            if(setSwitchBattlePage)
            {
                RPG::switches[setSwitchBattlePageId] = true;
            }
        }
        else
        {
            //Helper::ShowInfoBox(action->skillId,"Skill Id NOT in analysisVector");
        }
    }
}

void OnActionDone(RPG::Battler *battler)
{
    if ( battler->action->kind == RPG::AK_ITEM )
    {
        if(battler->action->skillId > 0)
        {
            UsedAnalysisSkill(battler->action);
        }
    }
    else if ( battler->action->kind == RPG::AK_SKILL )
    {
        if(battler->action->skillId > 0)
        {
            UsedAnalysisSkill(battler->action);
        }
    }
}

}
