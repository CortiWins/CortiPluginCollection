// Handler called on startup, dont use for gamespecific things.
bool onStartup ( char *pluginName )
{
    std::map<std::string, std::string> configMap = RPG::loadConfiguration(pluginName);

    if(configMap.size()<1)
    {
        // Keine Konfigeinstellungen
        Helper::ShowInfoBoxString("Error. No settings found in DynRPG.ini. Use the readme or the example project to get working settings.","CortiMonsterHud Plugin");
        return true;
    }

    // Analysis Required
    if(configMap.count("AnalysisRequiredSwitchId"))
    {
        MonsterHud::analysisSwitchArrayBeginIndex = (atoi(configMap["AnalysisRequiredSwitchId"].c_str()));

        if(MonsterHud::analysisSwitchArrayBeginIndex>0)
        {
            MonsterHud::analysisSwitchArrayBeginIndex--; // MonsterDBIndices beginnen ab 1, daher um 1 reduzieren
            MonsterHud::parAnalysisRequired = true;
        }
        else
        {
            MonsterHud::parAnalysisRequired = false;
        }
    }

    // Selection Required
    MonsterHud::parSelectedRequired = false;
    if(configMap.count("SelectionRequired"))
    {
        int value = (atoi(configMap["SelectionRequired"].c_str()));

        if(value>0)
        {
            MonsterHud::parSelectedRequired = true;
        }
    }

    MonsterHud::parDrawOnMonsters = false;
    if(configMap.count("DrawOnMonsters"))
    {
        int value = (atoi(configMap["DrawOnMonsters"].c_str()));

        if(value>0)
        {
            MonsterHud::parDrawOnMonsters = true;
        }
    }

    if(configMap.count("BarPartFrameChangeDelay"))
    {
        MonsterHud::parBarPartFrameChangeDelay = (atoi(configMap["BarPartFrameChangeDelay"].c_str()));
    }

    // Global Settings
    if(configMap.count("GlobalOffsetX"))
    {
        MonsterHud::parGlobalOffsetX = (atoi(configMap["GlobalOffsetX"].c_str()));
    }

    if(configMap.count("GlobalOffsetY"))
    {
        MonsterHud::parGlobalOffsetY = (atoi(configMap["GlobalOffsetY"].c_str()));
    }

    if(configMap.count("GlobalOffsetPercOfSizeX"))
    {
        MonsterHud::parGlobalOffsetPercOfSizeX = (atoi(configMap["GlobalOffsetPercOfSizeX"].c_str()));
    }

    if(configMap.count("GlobalOffsetPercOfSizeY"))
    {
        MonsterHud::parGlobalOffsetPercOfSizeY = (atoi(configMap["GlobalOffsetPercOfSizeY"].c_str()));
    }

    // Settings Hintergrundgrafik
    if(configMap.count("GraphicsFile"))
    {

        // Prüfen ob Datei da ist.
        std::ifstream checkStream ((configMap["GraphicsFile"]).c_str() );
        if ( checkStream ) // File exists
        {
            checkStream.close();
        }
        else
        {
             Helper::ShowInfoBoxString("Error. Configured GraphicsFile does not exist. Check file, directory and settings.","CortiMonsterHud Plugin");
        }

        MonsterHud::parFileExists = true;
        MonsterHud::parGraphicsFile = configMap["GraphicsFile"];

        if(configMap.count("BackgroundPositionOffsetX"))
        {
            MonsterHud::parBackgroundPositionOffsetX = (atoi(configMap["BackgroundPositionOffsetX"].c_str()));
        }

        if(configMap.count("BackgroundPositionOffsetY"))
        {
            MonsterHud::parBackgroundPositionOffsetY = (atoi(configMap["BackgroundPositionOffsetY"].c_str()));
        }

        if(configMap.count("BackgroundXinImage"))
        {
            MonsterHud::parBackgroundXinImage = (atoi(configMap["BackgroundXinImage"].c_str()));
        }

        if(configMap.count("BackgroundYinImage"))
        {
            MonsterHud::parBackgroundYinImage = (atoi(configMap["BackgroundYinImage"].c_str()));
        }

        if(configMap.count("BackgroundWidthInImage"))
        {
            MonsterHud::parBackgroundWidthInImage = (atoi(configMap["BackgroundWidthInImage"].c_str()));
        }

        if(configMap.count("BackgroundHeightInImage"))
        {
            MonsterHud::parBackgroundHeightInImage = (atoi(configMap["BackgroundHeightInImage"].c_str()));
        }
    }
    else
    {   // Nix Graphics, nix tun
        Helper::ShowInfoBoxString("Error. No GraphicsFile set in DynRPG.ini.","CortiMonsterHud Plugin");
        return true;
    }

    // Settings für Lifebar
    if(configMap.count("ShowLife"))
    {
        MonsterHud::parShowLifebar = (atoi(configMap["ShowLife"].c_str()))>0 ? true : false;

        if(MonsterHud::parShowLifebar)
        {
            if(configMap.count("LifebarPositionOffsetX"))
            {
                MonsterHud::parLifebarPositionOffsetX = (atoi(configMap["LifebarPositionOffsetX"].c_str()));
            }

            if(configMap.count("LifebarPositionOffsetY"))
            {
                MonsterHud::parLifebarPositionOffsetY = (atoi(configMap["LifebarPositionOffsetY"].c_str()));
            }

            if(configMap.count("LifebarFilledXinImage"))
            {
                MonsterHud::parLifebarFilledXinImage = (atoi(configMap["LifebarFilledXinImage"].c_str()));
            }

            if(configMap.count("LifebarFilledYinImage"))
            {
                MonsterHud::parLifebarFilledYinImage = (atoi(configMap["LifebarFilledYinImage"].c_str()));
            }

            if(configMap.count("LifebarEmptyXinImage"))
            {
                MonsterHud::parLifebarEmptyXinImage = (atoi(configMap["LifebarEmptyXinImage"].c_str()));
            }

            if(configMap.count("LifebarEmptyYinImage"))
            {
                MonsterHud::parLifebarEmptyYinImage = (atoi(configMap["LifebarEmptyYinImage"].c_str()));
            }

            if(configMap.count("LifebarHeightInImage"))
            {
                MonsterHud::parLifebarHeightInImage = (atoi(configMap["LifebarHeightInImage"].c_str()));
            }

            if(configMap.count("LifebarPartsMax"))
            {
                MonsterHud::parLifebarPartsMax = (atoi(configMap["LifebarPartsMax"].c_str()));
            }

            if(configMap.count("LifebarPartWidthPx"))
            {
                MonsterHud::parLifebarPartWidthPx = (atoi(configMap["LifebarPartWidthPx"].c_str()));
            }
        }
    }

    // Settings für Manabar
    if(configMap.count("ShowMana"))
    {
        MonsterHud::parShowManabar = (atoi(configMap["ShowMana"].c_str()))>0 ? true : false;

        if(MonsterHud::parShowManabar)
        {
            if(configMap.count("ManabarPositionOffsetX"))
            {
                MonsterHud::parManabarPositionOffsetX = (atoi(configMap["ManabarPositionOffsetX"].c_str()));
            }

            if(configMap.count("ManabarPositionOffsetY"))
            {
                MonsterHud::parManabarPositionOffsetY = (atoi(configMap["ManabarPositionOffsetY"].c_str()));
            }

            if(configMap.count("ManabarFilledXinImage"))
            {
                MonsterHud::parManabarFilledXinImage = (atoi(configMap["ManabarFilledXinImage"].c_str()));
            }

            if(configMap.count("ManabarFilledYinImage"))
            {
                MonsterHud::parManabarFilledYinImage = (atoi(configMap["ManabarFilledYinImage"].c_str()));
            }

            if(configMap.count("ManabarEmptyXinImage"))
            {
                MonsterHud::parManabarEmptyXinImage = (atoi(configMap["ManabarEmptyXinImage"].c_str()));
            }

            if(configMap.count("ManabarEmptyYinImage"))
            {
                MonsterHud::parManabarEmptyYinImage = (atoi(configMap["ManabarEmptyYinImage"].c_str()));
            }

            if(configMap.count("ManabarHeightInImage"))
            {
                MonsterHud::parManabarHeightInImage = (atoi(configMap["ManabarHeightInImage"].c_str()));
            }

            if(configMap.count("ManabarPartsMax"))
            {
                MonsterHud::parManabarPartsMax = (atoi(configMap["ManabarPartsMax"].c_str()));
            }

            if(configMap.count("ManabarPartWidthPx"))
            {
                MonsterHud::parManabarPartWidthPx = (atoi(configMap["ManabarPartWidthPx"].c_str()));
            }
        }
    }

    // Settings für AtbBar
    if(configMap.count("ShowAtb"))
    {
        MonsterHud::parShowAtbbar = (atoi(configMap["ShowAtb"].c_str()))>0 ? true : false;

        if(MonsterHud::parShowAtbbar)
        {
            if(configMap.count("AtbbarPositionOffsetX"))
            {
                MonsterHud::parAtbbarPositionOffsetX = (atoi(configMap["AtbbarPositionOffsetX"].c_str()));
            }

            if(configMap.count("AtbbarPositionOffsetY"))
            {
                MonsterHud::parAtbbarPositionOffsetY = (atoi(configMap["AtbbarPositionOffsetY"].c_str()));
            }

            if(configMap.count("AtbbarFilledXinImage"))
            {
                MonsterHud::parAtbbarFilledXinImage = (atoi(configMap["AtbbarFilledXinImage"].c_str()));
            }

            if(configMap.count("AtbbarFilledYinImage"))
            {
                MonsterHud::parAtbbarFilledYinImage = (atoi(configMap["AtbbarFilledYinImage"].c_str()));
            }

            if(configMap.count("AtbbarEmptyXinImage"))
            {
                MonsterHud::parAtbbarEmptyXinImage = (atoi(configMap["AtbbarEmptyXinImage"].c_str()));
            }

            if(configMap.count("AtbbarEmptyYinImage"))
            {
                MonsterHud::parAtbbarEmptyYinImage = (atoi(configMap["AtbbarEmptyYinImage"].c_str()));
            }

            if(configMap.count("AtbbarHeightInImage"))
            {
                MonsterHud::parAtbbarHeightInImage = (atoi(configMap["AtbbarHeightInImage"].c_str()));
            }

            if(configMap.count("AtbbarPartsMax"))
            {
                MonsterHud::parAtbbarPartsMax = (atoi(configMap["AtbbarPartsMax"].c_str()));
            }

            if(configMap.count("AtbbarPartWidthPx"))
            {
                MonsterHud::parAtbbarPartWidthPx = (atoi(configMap["AtbbarPartWidthPx"].c_str()));
            }
        }
    }


    if((MonsterHud::parShowAtbbar == false)&&(MonsterHud::parShowLifebar == false)&&(MonsterHud::parShowManabar == false))
    {
        Helper::ShowInfoBoxString("Error. All three bars disabled. Do you really need that plugin? ","CortiMonsterHud Plugin");
    }

    return true;
}
