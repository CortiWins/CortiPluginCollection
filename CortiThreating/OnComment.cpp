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
    if(!strcmp(parsedData->command, "le_schnue"))
    {
        // int cnt = parsedData->parametersCount;
        Helper::ShowInfoBoxString("le_schnue","CortiThreading");

        // D:\Daten\Privat\CortiPluginsTest\DynPlugins\CortiTrace\main.cpp|72|error: invalid conversion from 'void (*)(std::string, std::string)' to 'int'|
        //RPG::variables[124] = (int)&CortiFile::LogLine;


/*
        void (*foo)(std::string, std::string);
        foo = (void(*)(std::string, std::string))RPG::variables[124];
        foo("whatthe","fuck");


        // This function is called after every frame
void onFrame(RPG::Scene scene)
{
    // D:\Daten\Privat\CortiPluginsTest\DynPlugins\CortiTrace\main.cpp|72|error: invalid conversion from 'void (*)(std::string, std::string)' to 'int'|
    RPG::variables[124] = (int)&CortiFile::LogLine;
    void (*foo)(std::string, std::string);
    foo = &CortiFile::LogLine;
}
*/
        // Angriffswert eines Monsters in eine Variable speichern
        // GetMonsterAttack(parsedData);
        return false;
    }

    return true;
}
