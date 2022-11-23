// Enthält Hintergrundgrafik
RPG::Image *background = null;
// Enthält die Icons aller Helden
RPG::Image *heroIcons = null;
// Enthält die Ziffern auf den Monstericons
RPG::Image *monsterNumber = null;
// Enthält Hintergrund für die Atb-Verschiebung
RPG::Image *atbMappingGradiant = null;

// Grafik des Monster-Selektors
RPG::Image *monsterSelectorIcon = null;
// Enthält für jedes Monster im Kampf dessen Icon
RPG::Image *monsterIcons[8];

// Gezeigter Frame für Animation
int monsterSelectorFrame = 0;
// Enthält für jedes Monster im Kampf dessen Datenbank-ID
int monsterIconsId[8] = {0,0,0,0,0,0,0,0};

// Lädt für das aktuelle Monster das Icon wenn vorhanden
void LoadMonsterIcon(int fastestId, int fastestIdDatabase)
{
    // MonsterIcon laden wenn nicht bereits geschehen oder sich die Datenbank-ID geändert hat
    if(monsterIcons[fastestId] == NULL || (monsterIconsId[fastestId] != getFastestIdDatabase))
    {
        if(monsterIcons[fastestId] != NULL)
        {
            RPG::Image::destroy ( monsterIcons[fastestId] );
        }

        monsterIcons[fastestId] = RPG::Image::create();
        monsterIcons[fastestId]->useMaskColor = true;
        monsterIcons[fastestId]->alpha = 255;

        std::stringstream keyName;
        keyName << "DynRessource\\CortiCombatVisu\\Monster\\Mon" << fastestIdDatabase <<".png";

        if(Config::FileExist(keyName.str()))
        {
            monsterIcons[fastestId]->loadFromFile (keyName.str(), false );
        }
        else
        {
            monsterIcons[fastestId]->loadFromFile ("DynRessource\\CortiCombatVisu\\MonsterDefault.png", false );
        }

        monsterIconsId[fastestId] = fastestIdDatabase;
    }
}

void LoadGraphics()
{
    heroIcons = RPG::Image::create();
    heroIcons->useMaskColor = true;
    heroIcons->alpha = 255;

    if(Config::FileExist("DynRessource\\CortiCombatVisu\\HeldenCombatVisu.png"))
    {
        heroIcons->loadFromFile ( "DynRessource\\CortiCombatVisu\\HeldenCombatVisu.png", false );
    }
    else
    {
        Dialog::Show("DynRessource\\CortiCombatVisu\\HeldenCombatVisu.png","CortiCombatVisu - File does not exist:");
    }


    if(Config::useAtbMappingGradiant)
    {
        atbMappingGradiant = RPG::Image::create();
        atbMappingGradiant->useMaskColor = false;
        atbMappingGradiant->alpha = 255;
        atbMappingGradiant->loadFromFile ( Config::atbMappingGradientFile, false );
    }

    if(Config::isMonsterSelektorEnabled)
    {
        monsterSelectorIcon = RPG::Image::create();
        monsterSelectorIcon->useMaskColor = true;
        monsterSelectorIcon->alpha = 255;
        monsterSelectorIcon->loadFromFile ( Config::monsterSelectorFile, false );

        Config::monsterSelectorSizeX = monsterSelectorIcon->width;
        if(Config::monsterSelectorFramesMax>0)
        {
            Config::monsterSelectorSizeY = monsterSelectorIcon->height / Config::monsterSelectorFramesMax;
        }
        else
        {
            Config::monsterSelectorSizeY = monsterSelectorIcon->height;
        }
    }

    monsterNumber = RPG::Image::create();
    monsterNumber->useMaskColor = true;
    monsterNumber->alpha = 255;

    if(Config::FileExist("DynRessource\\CortiCombatVisu\\MonsterNumbers.png"))
    {
        monsterNumber->loadFromFile ( "DynRessource\\CortiCombatVisu\\MonsterNumbers.png", false );
    }
    else
    {
        Dialog::Show("DynRessource\\CortiCombatVisu\\MonsterNumbers.png","CortiCombatVisu - File does not exist:");
    }

    if(Config::backgroundFileActive)
    {
        background = RPG::Image::create();
        background->useMaskColor = true;
        background->alpha = 255;
        background->loadFromFile ( Config::backgroundFile, false );
    }
}

void UnloadGraphics()
{
    RPG::Image::destroy ( heroIcons );
    RPG::Image::destroy ( monsterNumber );

    if(Config::useAtbMappingGradiant)
    {
        RPG::Image::destroy ( atbMappingGradiant );
    }

    if(Config::isMonsterSelektorEnabled)
    {
        RPG::Image::destroy ( monsterSelectorIcon );
    }

    for ( int iRun = 0; iRun < 8; iRun++ )
    {
        if(monsterIcons[iRun] !=NULL)
        {
            RPG::Image::destroy ( monsterIcons[iRun] );
        }
    }

    if(Config::backgroundFileActive)
    {
        RPG::Image::destroy ( background );
    }
}
