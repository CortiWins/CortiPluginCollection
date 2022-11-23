namespace DrawCritSplash
{
//! Max frames used to show the CritSplash!-animation. If that value is reached, the animation is done.
const int MaxFrames = 70;
//! Framecounter for the CRIT!-Animation on Monsters
int monsterCritFrames[8] = { 0, 0, 0, 0, 0, 0, 0, 0};
//! Framecounter for the CRIT!-Animation on Heroes
int heroCritFrames[4] = { 0, 0, 0, 0};

//! Image contains the Splash-Crit!-Symbol.
RPG::Image *critSymbolImage;

//! Add the CRIT!-Animation on monsters or heroes depending on the 'action''s target.
void AddEffects ( RPG::Action *action, int battlerTypeDelay  )
{
    // Delay is given to the animations as a negative startFrame.
    int startFrame = 1 - battlerTypeDelay;
    if ( action->kind == RPG::AK_SKILL )
    {
        if ( ConfigSkills::skillDelay.count ( action->skillId ) )
        {
            startFrame = -ConfigSkills::skillDelay[action->skillId];
        }
    }

    if ( action->target == RPG::TARGET_MONSTER )
    {
        monsterCritFrames[action->targetId] = startFrame;
    }
    else if ( action->target == RPG::TARGET_ALL_MONSTERS )
    {
        for ( int i = 0; i < 8; i++ )
        {
            RPG::Monster *monPtr = RPG::monsters[i];
            if ( monPtr != NULL )
            {
                if ( monPtr->notHidden && monPtr->hp > 0 )
                {
                    monsterCritFrames[i] = startFrame;
                }
            }
        }
    }
    else if ( action->target == RPG::TARGET_ALL_ACTORS )
    {
        for ( int i = 0; i < 4; i++ )
        {
            RPG::Actor *actPtr = RPG::Actor::partyMember ( i );
            if ( actPtr != NULL )
            {
                if ( actPtr->hp > 0 )
                {
                    heroCritFrames[i] = startFrame;
                }
            }
        }
    }
    else if ( action->target == RPG::TARGET_ACTOR )
    {
        heroCritFrames[action->targetId] = startFrame;
    }
}

void DrawImage ( int alpha, int x, int y )
{
    critSymbolImage->alpha = alpha;
    RPG::screen->canvas->draw ( x - critSymbolImage->width,  y - critSymbolImage->height,  critSymbolImage );
}

//! Called in Callback 'onBattlerDrawn'. Draws Crit!-Animation for the Hero with the given datebaseId.
void OnHeroDrawn ( int databaseId, RPG::Battler *batPtr )
{
    int index = RPG::inventory->getPartyIndex ( databaseId );
    if ( index == -1 )
    {
        Dialog::Show ( databaseId, "DrawCritSplash.OnHeroDrawn: Database ID does not match hero in party" );
        return;
    }

    if ( heroCritFrames[index] < MaxFrames )
    {
        if ( heroCritFrames[index] < 20 )
        {
            // erste 20 Frames: nix
        }
        else if ( heroCritFrames[index] < 40 ) // 20 bis 40
        {
            // weitere 20 Frames: einblenden
            DrawImage ( 255 * ( heroCritFrames[index] - 20 ) / 20, batPtr->x,  batPtr->y );
        }
        else if ( heroCritFrames[index] < 50 ) // 40 bis 49
        {
            DrawImage ( 255, batPtr->x,  batPtr->y );
        }
        else if ( heroCritFrames[index] < 70 ) // 50 bis MaxFrames (70)
        {
            // Ausfaden:
            // Frames Minus 50 bei Werten zwischen 50 und 69 ergibt 0 bis 19.
            // 255 * (0 bis 19) / 20 bedeutet also von 0 bis fast 100% von 255 im Verlauf von 0 bis 19.
            DrawImage ( 255 - ( 255 * ( heroCritFrames[index] - 50 ) / 20 ), batPtr->x,  batPtr->y );
        }

        heroCritFrames[index]++;
    }
}

//! Called in Callback 'onBattlerDrawn'. Draws Crit!-Animation for the Monster with the given 0-based PartyIndex.
void OnMonsterDrawn ( int monsterGroupIndex, RPG::Battler *batPtr ) // zB Group ID
{
    if ( monsterCritFrames[monsterGroupIndex] < MaxFrames )
    {
        const int offsetX = 16;
        const int offsetY = 16;

        if ( monsterCritFrames[monsterGroupIndex] < 20 )
        {
            // erste 20 Frames: nix
        }
        else if ( monsterCritFrames[monsterGroupIndex] < 40 ) // 20 bis 39
        {
            // weitere 20 Frames: einblenden
            DrawImage ( 255 * ( monsterCritFrames[monsterGroupIndex] - 20 ) / 20, batPtr->x + offsetX,  batPtr->y + offsetY );
        }
        else if ( monsterCritFrames[monsterGroupIndex] < 50 ) // 40 bis 49
        {
            DrawImage ( 255, batPtr->x + offsetX,  batPtr->y + offsetY );
        }
        else if ( monsterCritFrames[monsterGroupIndex] < MaxFrames ) // 50 bis MaxFrames (70)
        {
            DrawImage ( 255 - ( 255 * ( monsterCritFrames[monsterGroupIndex] - 50 ) / 20 ), batPtr->x + offsetX,  batPtr->y + offsetY );
        }

        monsterCritFrames[monsterGroupIndex]++;
    }
}

void ResetFrames()
{
    for ( int iMonsters = 0; iMonsters < 8; iMonsters++ )
    {
        monsterCritFrames[iMonsters] = MaxFrames;
    }

    for ( int iHeroes = 0; iHeroes < 4; iHeroes++ )
    {
        heroCritFrames[iHeroes] = MaxFrames;
    }
}

//! Called by the 'onInitFinished' callback.
void OnInit()
{
    ResetFrames();
    critSymbolImage = null;
    if ( ConfigVisualEffects::isSplashEffectEnabled )
    {
        critSymbolImage = RPG::Image::create();
        critSymbolImage->useMaskColor = true;
        critSymbolImage->alpha = 255;
        if ( Helper::FileExist ( "DynRessource\\Splash.png" ) )
        {
            critSymbolImage->loadFromFile ( "DynRessource\\Splash.png", false );
        }
        else
        {
            Dialog::Show ( "DynRessource\\Splash.png", "File does not exist." );
        }
    }
}

//! Called by the 'onExit' callback.
void OnExit()
{
    if ( critSymbolImage != null )
    {
        RPG::Image::destroy ( critSymbolImage );
        critSymbolImage = null;
    }
}
}
