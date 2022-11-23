bool onStartup (char *pluginName)
{
    CortiLog::OnStartup();
    CustomCrit::CallbackOnStartup();
    return true;
}

void onInitFinished()
{
    RPG::system->atbMode = RPG::ATBM_WAIT;
    CustomCrit::CallbackOnInitFinished();
    return;
}

// This handler is called when the game exits
void onExit()
{
    CustomCrit::CallbackOnExit();
    CortiLog::OnExit();
}
