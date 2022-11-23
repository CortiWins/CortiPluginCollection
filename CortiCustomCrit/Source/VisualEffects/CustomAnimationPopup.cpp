namespace CustomAnimationPopup
{
//! Animations for all actors in the party.
CustomAnimations::CustomAnimation *hero[4] = { null, null, null, null};
//! Animations for all monsters in the monsterparty.
CustomAnimations::CustomAnimation *monster[8] = { null, null, null, null, null, null, null, null};

//! Add the CRIT!-Animation on monsters or heroes depending on the 'action''s target.
void AddEffects ( RPG::Action *action, int battlerTypeDelay )
{
    // Delay is given to the animations as a 'delay' number >= 0.
    int skilldelay = battlerTypeDelay;

    if ( action->kind == RPG::AK_SKILL )
    {
        if ( ConfigSkills::skillDelay.count ( action->skillId ) )
        {
            skilldelay = ConfigSkills::skillDelay[action->skillId];
        }
    }

    if ( action->target == RPG::TARGET_MONSTER )
    {
        monster[action->targetId]->Start ( skilldelay, true );
    }
    else if ( action->target == RPG::TARGET_ALL_MONSTERS )
    {
        // Makes sure that screen effects and sounds are only applied once.
        bool isGlobalEffectNotApplied = true;
        for ( int i = 0; i < 8; i++ )
        {
            RPG::Monster *monPtr = RPG::monsters[i];
            if ( monPtr != NULL )
            {
                if ( monPtr->notHidden && monPtr->hp > 0 )
                {
                    monster[i]->Start ( skilldelay, isGlobalEffectNotApplied );
                    isGlobalEffectNotApplied = false;
                }
            }
        }
    }
    else if ( action->target == RPG::TARGET_ALL_ACTORS )
    {
        // Makes sure that screen effects and sounds are only applied once.
        bool isGlobalEffectNotApplied = true;
        for ( int i = 0; i < 4; i++ )
        {
            RPG::Actor *actPtr = RPG::Actor::partyMember ( i );

            if ( actPtr != NULL )
            {
                if ( actPtr->hp > 0 )
                {
                    hero[i]->Start ( skilldelay, isGlobalEffectNotApplied );
                    isGlobalEffectNotApplied = false;
                }
            }
        }
    }
    else if ( action->target == RPG::TARGET_ACTOR )
    {
        hero[action->targetId]->Start ( skilldelay, true );
    }
}

//! Called in Callback 'onBattlerDrawn'. Draws Crit!-Animation for the Hero with the given datebaseId.
void OnHeroDrawn ( int databaseId, RPG::Battler *batPtr )
{
    int index = RPG::inventory->getPartyIndex ( databaseId );
    if ( index == -1 )
    {
        return;
    }

    if ( hero[index]->isEnabled )
    {
        hero[index]->Draw ( ( RPG::Actor* ) batPtr );
    }
}

//! Called in Callback 'onBattlerDrawn'. Draws Crit!-Animation for the Monster with the given 0-based PartyIndex.
void OnMonsterDrawn ( int monsterGroupIndex, RPG::Battler *batPtr ) // zB Group ID
{
    if ( monster[monsterGroupIndex]->isEnabled )
    {
        monster[monsterGroupIndex]->Draw ( ( RPG::Monster* ) batPtr );
    }
}

void ResetFrames()
{
    if ( ConfigVisualEffects::isCustomAnimationEnabled )
    {
        for ( int i = 0; i < 4; i++ )
        {
            if ( hero[i] != null )
            {
                hero[i]->Reset();
            }
        }

        for ( int i = 0; i < 8; i++ )
        {
            if ( monster[i] != null )
            {
                monster[i]->Reset();
            }
        }
    }
}

//! Called by the 'onInitFinished' callback.
void OnInit()
{
    if ( ConfigVisualEffects::isCustomAnimationEnabled )
    {
        for ( int i = 0; i < 4; i++ )
        {
            hero[i] = new CustomAnimations::CustomAnimation ( ConfigVisualEffects::visualEffectAnimationDatabaseId );
        }

        for ( int i = 0; i < 8; i++ )
        {
            monster[i] = new CustomAnimations::CustomAnimation ( ConfigVisualEffects::visualEffectAnimationDatabaseId );
        }
    }
}

//! Called by the 'onExit' callback.
void OnExit()
{
    if ( ConfigVisualEffects::isCustomAnimationEnabled )
    {
        for ( int i = 0; i < 4; i++ )
        {
            delete hero[i];
            hero[i] = null;
        }

        for ( int i = 0; i < 8; i++ )
        {
            delete monster[i];
            monster[i] = null;
        }
    }
}
}
