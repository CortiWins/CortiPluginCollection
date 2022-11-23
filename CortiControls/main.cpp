#include <DynRPG/DynRPG.h>

void SetMode(RPG::HeroControlMode cModeToSet)
{
    if(RPG::hero->getControlMode() != cModeToSet)
    {
        RPG::hero->setControlMode(cModeToSet);
    }
}

bool onComment(
    const char *text,
    const RPG::ParsedCommentData *parsedData,
    RPG::EventScriptLine *nextScriptLine,
    RPG::EventScriptData *scriptData,
    int	eventId,
    int pageId,
    int lineId,
    int *nextLineId)
{
    if(!strcmp(parsedData->command, "setcontrol_normal"))
    {
        // Everything works normally.
        SetMode(RPG::CONTROL_EVERYTHING);
        return false;
    }
    else if(!strcmp(parsedData->command, "setcontrol_nomove"))
    {
        // Opening menu and activating events works, but movement is disabled.
        SetMode(RPG::CONTROL_EVERYTHING_EXCEPT_MOVEMENT);
        return false;
    }
    else if(!strcmp(parsedData->command, "setcontrol_nothing"))
    {
        // No control possible (checking key state still works, of course)
        SetMode(RPG::CONTROL_NOTHING);
        return false;
    }
    return true;
}

int frames = 0;

/* This function is called after every frame (see details below!),
right after the current game scene was drawn, but before it becomes visible to the player.
You may draw on the screen in this function and it will appear on top of the normal graphics. */
void onFrame ( RPG::Scene scene )
{
    if(RPG::system->frameCounter < frames)
    {
         // Everything works normally.
        SetMode(RPG::CONTROL_EVERYTHING);
    }

    frames = RPG::system->frameCounter;
}



