#define AUTO_DLLMAIN
#include <DynRPG/DynRPG.h>

#include <cmath>
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
    // Alle Rechenbefehle haben minimum 2 Parameter. Den Wert der Funktion und die ID der Zielvariable
    if((parsedData->parametersCount >= 2) &&
            (parsedData->parameters[0].type == RPG::PARAM_NUMBER) && (parsedData->parameters[1].type == RPG::PARAM_NUMBER))
    {
        if(!strcmp(parsedData->command, "sin"))
        {
            // Parameter 0 enthält den Rechenwert in Grad
            int degree = (int)parsedData->parameters[0].number;
            // ID der Variable in die das Ergebnis kopiert werden soll
            int targetVariableId = (int)parsedData->parameters[1].number;
            // Umrechnen in Bogenmaß
            float result = (degree * 3.141592)/180;
            result = sin(result);
            RPG::variables[targetVariableId] = result *1000000;
        }
        else if(!strcmp(parsedData->command, "cos"))
        {
            int degree = (int)parsedData->parameters[0].number;
            int targetVariableId = (int)parsedData->parameters[1].number;
            float result = (degree * 3.141592)/180;
            result = cos(result);
            RPG::variables[targetVariableId] = result *1000000;
        }
        else if(!strcmp(parsedData->command, "tan"))
        {
            int degree = (int)parsedData->parameters[0].number;
            int targetVariableId = (int)parsedData->parameters[1].number;
            float result = (degree * 3.141592)/180;
            result = tan(result);
            RPG::variables[targetVariableId] = result *1000000;
        }
        else if(!strcmp(parsedData->command, "sqrt"))
        {
            // Rechenwert
            int value = (int)parsedData->parameters[0].number;
            int targetVariableId = (int)parsedData->parameters[1].number;
            float result = sqrt(value);
            RPG::variables[targetVariableId] = result;
        }
        else if(!strcmp(parsedData->command, "atan2"))
        {
            // atan2 hat drei Parameter. Der zweite Rechenwert kommt hinzu
            if((parsedData->parametersCount == 3) &&(parsedData->parameters[2].type == RPG::PARAM_NUMBER))
            {
                int valueOne = (int)parsedData->parameters[0].number;
                int valueTwo = (int)parsedData->parameters[2].number;
                int targetVariableId = (int)parsedData->parameters[1].number;
                float result = atan2(valueOne,valueTwo);
                RPG::variables[targetVariableId] = result *1000000;
            }
        }

    }
    return true;
}
