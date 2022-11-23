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
    return CustomCrit::CallBackOnComment(parsedData);
}
