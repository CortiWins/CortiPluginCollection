// Framecounter state on last onFrame call. Used to detect resets.
int currentFrameCounter = 0;
// Last drawn scene. Used to detect scene changes.
RPG::Scene currentScene =  RPG::SCENE_DEBUG;

// This function is called after every frame
void onFrame ( RPG::Scene scene )
{
    // Framecounter is less than before, means game has been reset
    if ( ( RPG::system->frameCounter ) < currentFrameCounter )
    {
        CustomCrit::OnResetGame();
    }

    // Scene change
    if ( scene != currentScene )
    {
        if ( scene == RPG::SCENE_BATTLE && ( currentScene != RPG::SCENE_DEBUG && currentScene != RPG::SCENE_OGL_OPTIONS ) )
        {
            // Player has entered a battle.
            CustomCrit::OnSceneChange();
        }
        else if ( ( scene != RPG::SCENE_DEBUG && scene != RPG::SCENE_OGL_OPTIONS ) && currentScene == RPG::SCENE_BATTLE )
        {
            // Player has left a battle.
            CustomCrit::OnSceneChange();
        }
        else if ( scene == RPG::SCENE_TITLE )
        {
            CustomCrit::OnResetGame();
        }

        // Remember scene and frameCounter
        currentScene = scene;
        currentFrameCounter = RPG::system->frameCounter;
    }
}
