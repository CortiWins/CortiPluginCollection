namespace CritCommands
{
// 1 @ccrit_skill_addcon
// 2 @ccrit_skill_addvar
// 3 @ccrit_skill_mulcon
// 4 @ccrit_skill_mulvar
// 5 @ccrit_skill_delay
void AddSkillData ( const RPG::ParsedCommentData *parsedData, int type )
{
    if ( parsedData->parametersCount != 2 )
    {
        LOGERROR ( "CommentCommand: ccrit_skill_*: invalid number of parameters " << parsedData->parametersCount );
        return;
    }

    // Parameter 1 the ID of the skill
    int skillId = ( ( int ) parsedData->parameters[0].number );
    // Parameter 2 is CritValue, MultiplicationFactor, DelayFrames according to command
    int value = ( int ) parsedData->parameters[1].number;

    if ( type == 1 ) // @ccrit_skill_addcon
    {
        ConfigSkills::skillAddConstant[skillId] = value;
        LOGINFO ( "CommentCommand: 'ccrit_skill_addcon' skill: '" << skillId << "' Value: '" << value << "'" );
    }
    else if ( type == 2 ) // @ccrit_skill_addvar
    {
        ConfigSkills::skillAddVariable[skillId] = value;
        LOGINFO ( "CommentCommand: 'ccrit_skill_addvar' skill: '" << skillId << "' Value: '" << value << "'" );
    }
    else if ( type == 3 ) //  @ccrit_skill_mulcon
    {
        ConfigSkills::skillMulConstant[skillId] = value;
        LOGINFO ( "CommentCommand: 'ccrit_skill_mulcon' skill: '" << skillId << "' Value: '" << value << "'" );
    }
    else if ( type == 4 ) // @ccrit_skill_mulvar
    {
        ConfigSkills::skillMulVariable[skillId] = value;
        LOGINFO ( "CommentCommand: 'ccrit_skill_mulvar' skill: '" << skillId << "' Value: '" << value << "'" );
    }
    else if ( type == 5 ) // @ccrit_skill_delay
    {
        ConfigSkills::skillDelay[skillId] = value;
        LOGINFO ( "CommentCommand: 'ccrit_skill_delay' skill: '" << skillId << "' Value: '" << value << "'" );
    }
}

void HeroGetStatus ( const RPG::ParsedCommentData *parsedData )
{
    if ( parsedData->parametersCount != 2 )
    {
        LOGERROR ( "CommentCommand: ccrit_getstatus: invalid number of parameters " << parsedData->parametersCount );
        return;
    }

    // Parameter 1 is the hero database ID.
    int databaseId = ( ( int ) parsedData->parameters[0].number );
    if ( ( databaseId < 1 ) || ( databaseId >= RPG::actors.count() ) )
    {
        LOGERROR ( "CommentCommand: ccrit_getstatus: invalid hero databaseId " << databaseId );
        return;
    }

    // Parameter 2 is the ID of the switch that is set by the command
    int switchId = ( int ) parsedData->parameters[1].number;
    if ( switchId < 1 )
    {
        LOGERROR ( "CommentCommand: ccrit_getstatus: invalid switchId " << switchId );
        return;
    }

    // Write crit-status to switch.
    bool status = HeroAttackBonus::GetAtkStatus ( databaseId );
    RPG::switches[switchId] = status;
    LOGINFO ( "CommentCommand: 'ccrit_getstatus' called for hero '" << databaseId << "' -> switch[" << switchId << "] Value:" << status );
}

void HeroResetStatus ( const RPG::ParsedCommentData *parsedData )
{
    if ( parsedData->parametersCount != 1 )
    {
        LOGERROR ( "CommentCommand: ccrit_resetstatus: invalid number of parameters " << parsedData->parametersCount );
        return;
    }

    // Parameter 1 is the hero database ID.
    int databaseId = ( ( int ) parsedData->parameters[0].number );
    if ( ( databaseId < 1 ) || ( databaseId >= RPG::actors.count() ) )
    {
        LOGERROR ( "CommentCommand: ccrit_resetstatus: invalid hero databaseId " << databaseId );
        return;
    }

    LOGINFO ( "CommentCommand: 'ccrit_resetstatus' called for hero '" << databaseId << "'" );
    HeroAttackBonus::ResetCritBonus ( databaseId );
}


void MonsterGetStatus ( const RPG::ParsedCommentData *parsedData )
{
    if ( parsedData->parametersCount != 2 )
    {
        LOGERROR ( "CommentCommand: ccrit_monster_getstatus: invalid number of parameters " << parsedData->parametersCount );
        return;
    }

    // Parameter 1 is the monsterGroupId ( 1 - 8 ).
    int monsterGroupId = ( ( int ) parsedData->parameters[0].number );
    if ( ( monsterGroupId < 1 ) || monsterGroupId > 8 )
    {
        LOGERROR ( "CommentCommand: ccrit_monster_getstatus: invalid monster Group Id " << monsterGroupId );
        return;
    }

    // Parameter 2 is the ID of the switch that is set by the command
    int switchId = ( int ) parsedData->parameters[1].number;
    if ( switchId < 1 )
    {
        LOGERROR ( "CommentCommand: ccrit_monster_getstatus: invalid switchId " << switchId );
        return;
    }

    bool status = MonsterAttackBonus::GetAtkStatus ( monsterGroupId - 1 ); // Function takes the partyindex 0 - 7
    RPG::switches[switchId] = status;
    LOGINFO ( "CommentCommand: 'ccrit_monster_getstatus' called for monster '" << monsterGroupId << "' -> switch[" << switchId << "] Value:" << status );
}

void MonsterResetStatus ( const RPG::ParsedCommentData *parsedData )
{
    if ( parsedData->parametersCount != 2 )
    {
        LOGERROR ( "CommentCommand: ccrit_monster_resetstatus: invalid number of parameters " << parsedData->parametersCount );
        return;
    }

    // Parameter 1 is the monsterGroupId ( 1 - 8 ).
    int monsterGroupId = ( ( int ) parsedData->parameters[0].number );
    if ( ( monsterGroupId < 1 ) || monsterGroupId > 8 )
    {
        LOGERROR ( "CommentCommand: ccrit_monster_resetstatus: invalid monster Group Id " << monsterGroupId );
        return;
    }

    MonsterAttackBonus::ResetCritBonus ( monsterGroupId - 1 ); // Function takes the partyindex 0 - 7
    LOGINFO ( "CommentCommand: 'ccrit_monster_resetstatus' called for monster '" << monsterGroupId);
}
}
