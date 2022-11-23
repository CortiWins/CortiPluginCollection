// Allgemeine Includes
#include <DynRPG/DynRPG.h>

#include <sstream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <cmath>
#include <deque>

#include "helper.cpp"

// We store the configuration here
std::map<std::string, std::string> configuration;

// Initialize pose types on-startup
bool onStartup (char *pluginName)
{
    // We load the configuration from the DynRPG.ini file here
    configuration = RPG::loadConfiguration(pluginName);
    return true;
}

// Ausgelöst bei Spielstart nachdem Makerdaten vorhanden sind.
void onInitFinished()
{

}

// Aufgerufen wenn das Spiel beendet wird.
void onExit()
{

}

void OnGetProperty(const RPG::ParsedCommentData *parsedData)
{
        if(parsedData->parametersCount < 3)
        {
            Helper::ShowInfoBoxString("Missing parameters.","[Error] on command: get_item_property");
            return;
        }

        if(parsedData->parameters[0].type != RPG::PARAM_STRING)
        {
            Helper::ShowInfoBoxString("First parameter needs to be a string with the name of the property."
                                      ,"[Error] on command get_item_property");
            return;
        }

        if(parsedData->parameters[1].type != RPG::PARAM_NUMBER)
        {
            Helper::ShowInfoBoxString("Second parameter needs to be a number with the id of the item."
                                      ,"[Error] on command get_item_property");
            return;
        }

        std::string propertyName(parsedData->parameters[0].text);
        int itemId = (int)parsedData->parameters[1].number;

        RPG::Item *itemPtr = RPG::items[itemId];

        if(itemPtr == NULL)
        {
            Helper::ShowInfoBoxString("itemArray returned NULL. Check if itemId is within bounds."
                                      ,"[Error] on command get_item_property");
            return;
        }

        if(!strcmp(propertyName.c_str(), "attributes"))
        {
            if(parsedData->parametersCount < 4)
            {
                Helper::ShowInfoBoxString("Requires 4 parameters. ","[Error] on command: get_item_property attributes");
                return;
            }

            if(parsedData->parameters[2].type != RPG::PARAM_NUMBER)
            {
                Helper::ShowInfoBoxString("Third parameter needs to be a number with the id of the attribute."
                                          ,"[Error] on command get_item_property");
                return;
            }

            if(parsedData->parameters[3].type != RPG::PARAM_NUMBER)
            {
                Helper::ShowInfoBoxString("Fourth parameter needs to be the variable ID as a number."
                                          ,"[Error] on command get_item_property");
                return;
            }


            int attributeId = (int)parsedData->parameters[2].number;
            int variableId = (int)parsedData->parameters[3].number;

            if(itemPtr->attributes.size < attributeId)
            {
                itemPtr->attributes.resize(attributeId);
            }

            RPG::variables[variableId] =  itemPtr->attributes[attributeId] == true ? 1 : 0;

            return;
        }
        else if(!strcmp(propertyName.c_str(), "conditions"))
        {
            if(parsedData->parametersCount < 4)
            {
                Helper::ShowInfoBoxString("Requires 4 parameters. ","[Error] on command: get_item_property conditions");
                return;
            }

            if(parsedData->parameters[2].type != RPG::PARAM_NUMBER)
            {
                Helper::ShowInfoBoxString("Third parameter needs to be a number with the id of the condition."
                                          ,"[Error] on command get_item_property");
                return;
            }

            if(parsedData->parameters[3].type != RPG::PARAM_NUMBER)
            {
                Helper::ShowInfoBoxString("Fourth parameter needs to be the variable ID as a number. "
                                          ,"[Error] on command get_item_property");
                return;
            }

            int conditionId = (int)parsedData->parameters[2].number;
            int variableId = (int)parsedData->parameters[3].number;

            if(itemPtr->conditions.size < conditionId)
            {
                itemPtr->conditions.resize(conditionId);
            }

            RPG::variables[variableId] =  itemPtr->conditions[conditionId] == true ? 1 : 0;

            return;
        }

        if(parsedData->parameters[2].type != RPG::PARAM_NUMBER)
        {
            Helper::ShowInfoBoxString("Third parameter needs to be a number. Use 1/0 for boolean properties. "
                                          ,"[Error] on command get_item_property");
            return;
        }

        // zu setzender Wert.
        int variableId = (int)parsedData->parameters[2].number;

        if(!strcmp(propertyName.c_str(), "price"))
        {
            RPG::variables[variableId] = itemPtr->price;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "numUses"))
        {
            RPG::variables[variableId] = itemPtr->numUses;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "str"))
        {
            RPG::variables[variableId] = itemPtr->str;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "def"))
        {
            RPG::variables[variableId] = itemPtr->def;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "intl"))
        {
            RPG::variables[variableId] = itemPtr->intl;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "agl"))
        {
            RPG::variables[variableId] = itemPtr->agl;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "twoHanded"))
        {
            RPG::variables[variableId] = itemPtr->twoHanded ? 1 : 0;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "mpCost"))
        {
            RPG::variables[variableId] = itemPtr->mpCost;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "hitProb"))
        {
            RPG::variables[variableId] = itemPtr->hitProb;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "critBonus"))
        {
            RPG::variables[variableId] = itemPtr->critBonus;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "battleAnimId"))
        {
            RPG::variables[variableId] = itemPtr->battleAnimId;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "alwaysAttackFirst"))
        {
            RPG::variables[variableId] = itemPtr->alwaysAttackFirst ? 1 : 0;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "attackTwice"))
        {
            RPG::variables[variableId] = itemPtr->attackTwice ? 1 : 0;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "attackAll"))
        {
            RPG::variables[variableId] = itemPtr->attackAll ? 1 : 0;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "ignoreEvasion"))
        {
            RPG::variables[variableId] = itemPtr->ignoreEvasion ? 1 : 0;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "preventCrit"))
        {
            RPG::variables[variableId] = itemPtr->preventCrit ? 1 : 0;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "increaseEvasion"))
        {
            RPG::variables[variableId] = itemPtr->increaseEvasion ? 1 : 0;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "halfMpCost"))
        {
            RPG::variables[variableId] = itemPtr->halfMpCost ? 1 : 0;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "noTerrainDmg"))
        {
            RPG::variables[variableId] = itemPtr->noTerrainDmg ? 1 : 0;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "conditionFlag"))
        {
            RPG::variables[variableId] = itemPtr->target  == RPG::ITEM_TARGET_SINGLE? 1 : 0;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "hpRestorePercent"))
        {
            RPG::variables[variableId] = itemPtr->hpRestorePercent;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "hpRestoreUnits"))
        {
            RPG::variables[variableId] = itemPtr->hpRestoreUnits;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "mpRestorePercent"))
        {
            RPG::variables[variableId] = itemPtr->mpRestorePercent;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "mpRestoreUnits"))
        {
            RPG::variables[variableId] = itemPtr->mpRestoreUnits;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "onlyInField"))
        {
            RPG::variables[variableId] = itemPtr->onlyInField ? 1 : 0;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "onlyOnDead"))
        {
            RPG::variables[variableId] = itemPtr->onlyOnDead ? 1 : 0;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "addMaxHp"))
        {
            RPG::variables[variableId] = itemPtr->addMaxHp;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "addMaxMp"))
        {
            RPG::variables[variableId] = itemPtr->addMaxMp;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "addStr"))
        {
            RPG::variables[variableId] = itemPtr->addStr;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "addDef"))
        {
            RPG::variables[variableId] = itemPtr->addDef;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "addInt"))
        {
            RPG::variables[variableId] = itemPtr->addInt;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "addAgl"))
        {
            RPG::variables[variableId] = itemPtr->addAgl;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "skillId"))
        {
            RPG::variables[variableId] = itemPtr->skillId;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "switchId"))
        {
            RPG::variables[variableId] = itemPtr->switchId;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "useInField"))
        {
            RPG::variables[variableId] = itemPtr->useInField ? 1 : 0;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "useInBattle"))
        {
            RPG::variables[variableId] = itemPtr->useInBattle ? 1 : 0;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "conditionPercentage"))
        {
            RPG::variables[variableId] = itemPtr->conditionPercentage;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "invokeSkill"))
        {
            RPG::variables[variableId] = itemPtr->invokeSkill ? 1 : 0;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "isCursed"))
        {
            RPG::variables[variableId] = itemPtr->isCursed ? 1 : 0;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "conditionFlag"))
        {
            RPG::variables[variableId] = itemPtr->conditionFlag  == RPG::ITEM_CONDITION_INFLICT? 1 : 0;
            return;
        }

        Helper::ShowInfoBoxString("Unknown property. Check your parameters. Contact me.","[Error] on command get_item_property");
}

void OnSetProperty(const RPG::ParsedCommentData *parsedData)
{
        if(parsedData->parametersCount < 3)
        {
            Helper::ShowInfoBoxString("Missing parameters.","[Error] on command: set_item_property");
            return;
        }

        if(parsedData->parameters[0].type != RPG::PARAM_STRING)
        {
            Helper::ShowInfoBoxString("First parameter needs to be a string with the name of the property."
                                      ,"[Error] on command set_item_property");
            return;
        }

        if(parsedData->parameters[1].type != RPG::PARAM_NUMBER)
        {
            Helper::ShowInfoBoxString("Second parameter needs to be a number with the id of the item."
                                      ,"[Error] on command set_item_property");
            return;
        }

        std::string propertyName(parsedData->parameters[0].text);
        int itemId = (int)parsedData->parameters[1].number;

        RPG::Item *itemPtr = RPG::items[itemId];

        if(itemPtr == NULL)
        {
            Helper::ShowInfoBoxString("itemArray returned NULL. Check if itemId is within bounds."
                                      ,"[Error] on command set_item_property");
            return;
        }

        if(!strcmp(propertyName.c_str(), "attributes"))
        {
            if(parsedData->parametersCount < 4)
            {
                Helper::ShowInfoBoxString("Requires 4 parameters. ","[Error] on command: set_item_property attributes");
                return;
            }

            if(parsedData->parameters[2].type != RPG::PARAM_NUMBER)
            {
                Helper::ShowInfoBoxString("Third parameter needs to be a number with the id of the attribute."
                                          ,"[Error] on command set_item_property");
                return;
            }

            if(parsedData->parameters[3].type != RPG::PARAM_NUMBER)
            {
                Helper::ShowInfoBoxString("Fourth parameter needs to be a number. 1 to set attribute 0 to uncheck. "
                                          ,"[Error] on command set_item_property");
                return;
            }


            int attributeId = (int)parsedData->parameters[2].number;
            int setValue = (int)parsedData->parameters[3].number;

            if(itemPtr->attributes.size < attributeId)
            {
                itemPtr->attributes.resize(attributeId);
            }

            itemPtr->attributes[attributeId] = setValue > 0 ? true : false;

            return;
        }
        else if(!strcmp(propertyName.c_str(), "conditions"))
        {
            if(parsedData->parametersCount < 4)
            {
                Helper::ShowInfoBoxString("Requires 4 parameters. ","[Error] on command: set_item_property conditions");
                return;
            }

            if(parsedData->parameters[2].type != RPG::PARAM_NUMBER)
            {
                Helper::ShowInfoBoxString("Third parameter needs to be a number with the id of the condition."
                                          ,"[Error] on command set_item_property");
                return;
            }

            if(parsedData->parameters[3].type != RPG::PARAM_NUMBER)
            {
                Helper::ShowInfoBoxString("Fourth parameter needs to be a number. 1 to set condition 0 to uncheck. "
                                          ,"[Error] on command set_item_property");
                return;
            }

            int conditionId = (int)parsedData->parameters[2].number;
            int setValue = (int)parsedData->parameters[3].number;

             if(itemPtr->conditions.size < conditionId)
            {
                itemPtr->conditions.resize(conditionId);
            }

            itemPtr->conditions[conditionId] = setValue > 0 ? true : false;

            return;
        }

        if(parsedData->parameters[2].type != RPG::PARAM_NUMBER)
        {
            Helper::ShowInfoBoxString("Third parameter needs to be a number. Use 1/0 for boolean properties. "
                                          ,"[Error] on command set_item_property");
            return;
        }

        // zu setzender Wert.
        int setValue = (int)parsedData->parameters[2].number;
        bool  isTrue = setValue > 0 ? true : false;

        if(!strcmp(propertyName.c_str(), "price"))
        {
            itemPtr->price = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "numUses"))
        {
            itemPtr->numUses = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "str"))
        {
            itemPtr->str = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "def"))
        {
            itemPtr->def = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "intl"))
        {
            itemPtr->intl = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "agl"))
        {
            itemPtr->agl = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "twoHanded"))
        {
            itemPtr->twoHanded = isTrue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "mpCost"))
        {
            itemPtr->mpCost = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "hitProb"))
        {
            itemPtr->hitProb = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "critBonus"))
        {
            itemPtr->critBonus = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "battleAnimId"))
        {
            itemPtr->battleAnimId = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "alwaysAttackFirst"))
        {
            itemPtr->alwaysAttackFirst = isTrue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "attackTwice"))
        {
            itemPtr->attackTwice = isTrue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "attackAll"))
        {
            itemPtr->attackAll = isTrue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "ignoreEvasion"))
        {
            itemPtr->ignoreEvasion = isTrue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "preventCrit"))
        {
            itemPtr->preventCrit = isTrue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "increaseEvasion"))
        {
            itemPtr->increaseEvasion = isTrue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "halfMpCost"))
        {
            itemPtr->halfMpCost = isTrue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "noTerrainDmg"))
        {
            itemPtr->noTerrainDmg = isTrue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "conditionFlag"))
        {
            itemPtr->target = isTrue ? RPG::ITEM_TARGET_SINGLE : RPG::ITEM_TARGET_ALL ;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "hpRestorePercent"))
        {
            itemPtr->hpRestorePercent = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "hpRestoreUnits"))
        {
            itemPtr->hpRestoreUnits = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "mpRestorePercent"))
        {
            itemPtr->mpRestorePercent = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "mpRestoreUnits"))
        {
            itemPtr->mpRestoreUnits = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "onlyInField"))
        {
            itemPtr->onlyInField = isTrue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "onlyOnDead"))
        {
            itemPtr->onlyOnDead = isTrue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "addMaxHp"))
        {
            itemPtr->addMaxHp = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "addMaxMp"))
        {
            itemPtr->addMaxMp = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "addStr"))
        {
            itemPtr->addStr = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "addDef"))
        {
            itemPtr->addDef = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "addInt"))
        {
            itemPtr->addInt = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "addAgl"))
        {
            itemPtr->addAgl = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "skillId"))
        {
            itemPtr->skillId = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "switchId"))
        {
            itemPtr->switchId = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "useInField"))
        {
            itemPtr->useInField = isTrue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "useInBattle"))
        {
            itemPtr->useInBattle = isTrue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "conditionPercentage"))
        {
            itemPtr->conditionPercentage = setValue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "invokeSkill"))
        {
            itemPtr->invokeSkill = isTrue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "isCursed"))
        {
            itemPtr->isCursed = isTrue;
            return;
        }
        else if(!strcmp(propertyName.c_str(), "conditionFlag"))
        {
            itemPtr->conditionFlag = isTrue ? RPG::ITEM_CONDITION_INFLICT  : RPG::ITEM_CONDITION_REMOVE;
            return;
        }

        Helper::ShowInfoBoxString("Unknown property. Check your parameters. Contact me.","[Error] on command set_item_property");
}

// Ausgelöst, wenn ein Kommentarkommando gefunden wurde
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
    if(!strcmp(parsedData->command, "set_item_property"))
    {
        OnSetProperty(parsedData);
        return false;
    }
    else if(!strcmp(parsedData->command, "get_item_property"))
    {
        OnGetProperty(parsedData);
        return false;
    }
    return true;
}
