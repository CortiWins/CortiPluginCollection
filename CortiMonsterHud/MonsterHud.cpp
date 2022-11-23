namespace MonsterHud
{
    /// SETTINGS

    // Gibt ab, ob die HP Leiste gezeigt werden soll.
    bool parShowLifebar = true;
    // Gibt ab, ob die Mana Leiste gezeigt werden soll.
    bool parShowManabar = true;
    // Gibt ab, ob die Atb Leiste gezeigt werden soll.
    bool parShowAtbbar = true;

    // Pfad zur Grafikdatei.
    std::string parGraphicsFile;// = "DynRessource\\MonsterHudPlugin.png";
    // Gibt ab, ob eine MonsterHud-Grafik parametriert und geladen wurde.
    bool parFileExists = false;

    // Gibt ab, ob das HUD nur für analysierte Monster gezeigt werden soll. Funktioniert mit CortiAnalysis-Plugin.
    bool parAnalysisRequired = false;
    // SwitchIndex für Array der analysierten Monster. Funktioniert mit CortiAnalysis-Plugin.
    int analysisSwitchArrayBeginIndex = 0;
    // Gibt ab, ob das HUD nur für angewählte Monster gezeigt werden soll.
    bool parSelectedRequired = false;
    // Gibt ab, ob das HUD direkt auf den Monstern oder im OnDrawBattleWindow gezeichnet werden soll.
    bool parDrawOnMonsters = false;

    // Global Position
    int parGlobalOffsetX = 0;
    int parGlobalOffsetY = 0;
    int parGlobalOffsetPercOfSizeX = 20;
    int parGlobalOffsetPercOfSizeY = 20;

    // Hintergrund
    int parBackgroundPositionOffsetX = 0;
    int parBackgroundPositionOffsetY = 0;
    int parBackgroundXinImage = 0;
    int parBackgroundYinImage = 5;
    int parBackgroundWidthInImage = 1;
    int parBackgroundHeightInImage = 13;

    // Lifebar
    int parLifebarPartsMax = 15;
    int parLifebarPartWidthPx = 3;

    int parLifebarPositionOffsetX = 1;
    int parLifebarPositionOffsetY = 0;
    int parLifebarFilledXinImage = 1;
    int parLifebarFilledYinImage = 5;
    int parLifebarEmptyXinImage = 1;
    int parLifebarEmptyYinImage = 0;
    int parLifebarHeightInImage = 4;

    // Manabar
    int parManabarPartsMax = 15;
    int parManabarPartWidthPx = 3;

    int parManabarPositionOffsetX = 1;
    int parManabarPositionOffsetY = 5;
    int parManabarFilledXinImage = 1;
    int parManabarFilledYinImage = 10;
    int parManabarEmptyXinImage = 1;
    int parManabarEmptyYinImage = 0;
    int parManabarHeightInImage = 4;

    // AtbBar
    int parAtbbarPartsMax = 15;
    int parAtbbarPartWidthPx = 3;

    int parAtbbarPositionOffsetX = 1;
    int parAtbbarPositionOffsetY = 10;
    int parAtbbarFilledXinImage = 1;
    int parAtbbarFilledYinImage = 15;
    int parAtbbarEmptyXinImage = 1;
    int parAtbbarEmptyYinImage = 0;
    int parAtbbarHeightInImage = 4;

    /// VISUALS
    // Anzahl Frames zwischen barPart-Änderungen
    int parBarPartFrameChangeDelay = 3;
    // Zähler für Framewechsel
    int frameChangeCounter = 0;
    // Gibt an, ob in diesem Frame die Füllstandsanimation angewandt wird.
    bool isAnimationFrame = false;
    // Enthält grafisches Material
    RPG::Image *hudGraphics;
    // Position des Huds auf dem Bildschirm
    int hudPositionX;
    int hudPositionY;

    /// MONSTERDATEN
    // (Leben) Enthält "barPart"-Wert, der angenommen werden soll
    int targetHpParts[8];
    // (Leben) Enthält "barPart"-Wert, der aktuell gezeigt wird
    int currentHpParts[8];
    // (Mana) Enthält "barPart"-Wert, der angenommen werden soll
    int targetMpParts[8];
    // (Mana) Enthält "barPart"-Wert, der aktuell gezeigt wird
    int currentMpParts[8];
     // Sichtbarkeit des HUDs der einzelnen Monster.
    int targetVisibility[8]; // 255 = Vis, 0 is inVis

    int monstersToOverlay[8];
    int numberToDraw = 0;


    /// AKTUELLES MONSTER
    // Aktuelles Monster
    RPG::Monster *currentMonster;
    // PartyId des Monsters , ZeroBased
    int currentMonsterId;
    // Füllstand des HP/MP/Atb-Balkens für diesen HP/MP/Atb-Stand
    int currentBarPart;

    /// METHODEN

    inline void LifeBarpartFrameupdate()
    {
        if(isAnimationFrame)
        {
            if(targetHpParts[currentMonsterId] < currentHpParts[currentMonsterId])
            {
                currentHpParts[currentMonsterId]--;
            }
            else if(targetHpParts[currentMonsterId] > currentHpParts[currentMonsterId])
            {
                currentHpParts[currentMonsterId]++;
            }
        }
    }

    inline void ManaBarpartFrameupdate()
    {
        if(isAnimationFrame)
        {
            if(targetMpParts[currentMonsterId] < currentMpParts[currentMonsterId])
            {
                currentMpParts[currentMonsterId]--;
            }
            else if(targetMpParts[currentMonsterId] > currentMpParts[currentMonsterId])
            {
                currentMpParts[currentMonsterId]++;
            }
        }
    }

    // Anzeigen des Lebenspunktebalkens für das aktuelle Monster
    void DrawLifebar()
    {
        // Füllstand des HP-Balkens für diesen HP-Stand
        currentBarPart = ( currentMonster->hp * parLifebarPartsMax ) / currentMonster->getMaxHp();
        // Zielstand der Lifebar setzen
        targetHpParts[currentMonsterId] = currentBarPart;
        // Wenn in diesem Frame ein Wechsel stattfindet, den Istwert dem Zielwert annähern
        LifeBarpartFrameupdate();

        // Pixelbereich der gefüllt ist
        int pixelsFull = parLifebarPartWidthPx * currentHpParts[currentMonsterId];
        // Pixelbereich der leer ist
        int pixelsEmpty = parLifebarPartWidthPx * (parLifebarPartsMax - currentHpParts[currentMonsterId]);

        // Gefüllten Pixelbereich zeichnen
        if(pixelsFull>0)
        {
            RPG::screen->canvas->draw(
                hudPositionX + parLifebarPositionOffsetX,           // Position.X  Target
                hudPositionY + parLifebarPositionOffsetY,           // Position.Y Target
                hudGraphics,                // ImageObject
                parLifebarFilledXinImage,                          // X. in Image
                parLifebarFilledYinImage,                          // Y. in Image
                pixelsFull,                 // Width in Image
                parLifebarHeightInImage);                         // Height in Image
        }

        // Leeren Pixelbereich zeichnen
        if(pixelsEmpty>0)
        {
            RPG::screen->canvas->draw(
                hudPositionX + pixelsFull + parLifebarPositionOffsetX ,// Position.X  Target
                hudPositionY + parLifebarPositionOffsetY,              // Position.Y Target
                hudGraphics,                                           // ImageObject
                pixelsFull + parLifebarEmptyXinImage,                  // X. in Image
                parLifebarEmptyYinImage,                               // Y. in Image
                pixelsEmpty,                                           // Width in Image
                parLifebarHeightInImage);                              // Height in Image
        }
    }

    // Anzeigen des Manapunktebalkens für das aktuelle Monster
    void DrawManabar()
    {
        if(currentMonster->getMaxMp() > 0)
        {
            // Füllstand des HP-Balkens für diesen HP-Stand
            currentBarPart = ( currentMonster->mp * parManabarPartsMax ) / currentMonster->getMaxMp();
        }
        else
        {
            currentBarPart = 0;
        }

        // Zielstand der Lifebar setzen
        targetMpParts[currentMonsterId] = currentBarPart;
        // Wenn in diesem Frame ein Wechsel stattfindet, den Istwert dem Zielwert annähern
        ManaBarpartFrameupdate();

        // Pixelbereich der gefüllt ist
        int pixelsFull = parManabarPartWidthPx * currentMpParts[currentMonsterId];
        // Pixelbereich der leer ist
        int pixelsEmpty = parManabarPartWidthPx * (parManabarPartsMax - currentMpParts[currentMonsterId]);

        // Gefüllten Pixelbereich zeichnen
        if(pixelsFull>0)
        {
            RPG::screen->canvas->draw(
                hudPositionX + parManabarPositionOffsetX ,              // Position.X  Target
                hudPositionY + parManabarPositionOffsetY,              // Position.Y Target
                hudGraphics,                // ImageObject
                parManabarFilledXinImage,                          // X. in Image
                parManabarFilledYinImage,                          // Y. in Image
                pixelsFull,                 // Width in Image
                parManabarHeightInImage);                         // Height in Image
        }

        // Leeren Pixelbereich zeichnen
        if(pixelsEmpty>0)
        {
            RPG::screen->canvas->draw(
                hudPositionX + pixelsFull + parManabarPositionOffsetX,  // Position.X  Target
                hudPositionY + parManabarPositionOffsetY,              // Position.Y Target
                hudGraphics,                // ImageObject
                parManabarEmptyXinImage,                          // X. in Image
                parManabarEmptyYinImage,                          // Y. in Image
                pixelsEmpty,                 // Width in Image
                parManabarHeightInImage);                         // Height in Image
        }
    }

    // Anzeigen des Manapunktebalkens für das aktuelle Monster
    void DrawAtbbar()
    {
        // Füllstand des HP-Balkens für diesen HP-Stand
        currentBarPart = ( currentMonster->atbValue * parAtbbarPartsMax ) / 300000;

        // Pixelbereich der gefüllt ist
        int pixelsFull = parAtbbarPartWidthPx * currentBarPart;
        // Pixelbereich der leer ist
        int pixelsEmpty = parAtbbarPartWidthPx * (parAtbbarPartsMax - currentBarPart);

        // Gefüllten Pixelbereich zeichnen
        if(pixelsFull>0)
        {
            RPG::screen->canvas->draw(
                hudPositionX + parAtbbarPositionOffsetX,              // Position.X  Target
                hudPositionY + parAtbbarPositionOffsetY,              // Position.Y Target
                hudGraphics,                // ImageObject
                parAtbbarFilledXinImage,                          // X. in Image
                parAtbbarFilledYinImage,                          // Y. in Image
                pixelsFull,                 // Width in Image
                parAtbbarHeightInImage);                         // Height in Image
        }

        // Leeren Pixelbereich zeichnen
        if(pixelsEmpty>0)
        {
            RPG::screen->canvas->draw(
                hudPositionX + pixelsFull + parAtbbarPositionOffsetX ,  // Position.X  Target
                hudPositionY + parAtbbarPositionOffsetY,              // Position.Y Target
                hudGraphics,                // ImageObject
                parAtbbarEmptyXinImage,                          // X. in Image
                parAtbbarEmptyYinImage,                          // Y. in Image
                pixelsEmpty,                 // Width in Image
                parAtbbarHeightInImage);                         // Height in Image
        }
    }

    void OnMonsterDrawn()
    {
        //Koordinaten beschreiben Punkt oben links, HP-Leiste wird auf diesen Basiskoordianten gezeichnet, alles andere relativ dazu
        hudPositionX = ( currentMonster->x ) - ( currentMonster->image->width / 2 ) + parGlobalOffsetX;
        hudPositionY = ( currentMonster->y ) - ( currentMonster->image->height / 2) + parGlobalOffsetY;

        if(parGlobalOffsetPercOfSizeX>0)
        {
            hudPositionX +=(currentMonster->image->width * parGlobalOffsetPercOfSizeX)/100;
        }

        if(parGlobalOffsetPercOfSizeY>0)
        {
            hudPositionY +=(currentMonster->image->height* parGlobalOffsetPercOfSizeY)/100;
        }

        // Ein- und Ausblenden der HUD Elemente: Alphawert verändern.
        if((currentMonster->hp>0) && (targetVisibility[currentMonsterId]<255))
        {
            targetVisibility[currentMonsterId]+=5;
        }
        else if((currentMonster->hp==0)&&(targetVisibility[currentMonsterId]>0))
        {
            targetVisibility[currentMonsterId]-=15;
        }

        // Ein- und Ausblenden der HUD Elemente: Alphawert zuweisen
        hudGraphics->alpha = targetVisibility[currentMonsterId];

        // Hintergrund zeichnen
        RPG::screen->canvas->draw(
                hudPositionX + parBackgroundPositionOffsetX,// Position.X  Target
                hudPositionY + parBackgroundPositionOffsetY,// Position.Y Target
                hudGraphics,                                // ImageObject
                parBackgroundXinImage,                      // X. in Image
                parBackgroundYinImage,                      // Y. in Image
                parBackgroundWidthInImage,                  // Width in Image
                parBackgroundHeightInImage);                // Height in Image

        if(parShowLifebar)
        {
            DrawLifebar();
        }

        if(parShowManabar)
        {
            DrawManabar();
        }

        if(parShowAtbbar)
        {
            DrawAtbbar();
        }
    }

    void OnFrame()
    {
        if(frameChangeCounter>=parBarPartFrameChangeDelay)
        {
            frameChangeCounter = 0;
            isAnimationFrame = true;
        }
        else
        {
            frameChangeCounter++;
            isAnimationFrame = false;
        }
    }

    void Reset()
    {
        for(int i=0;i<8;i++)
        {
            targetHpParts[i] = 0;
            currentHpParts[i] = 0;
            targetMpParts[i] = 0;
            currentMpParts[i] = 0;
            targetVisibility[i] = 0;
            monstersToOverlay[i] = 0;
        }

        numberToDraw = 0;
    }

    // Aufgerufen wenn Scene zu Kampf wechselt.
    void OnSceneChange(bool enteringBattle)
    {
        Reset();
    }

    // Aufgerufen nach erfolgreicher Initialisierung. Grafiken laden.
    void OnLoad()
    {
        Reset();
        if(parFileExists)
        {
            hudGraphics = RPG::Image::create();
            hudGraphics->useMaskColor = true;
            hudGraphics->alpha = 255;
            hudGraphics->loadFromFile(parGraphicsFile, false);
        }
    }

    // Aufgerufen bei Beenden des Spieles. Grafiken freigeben.
    void OnExit()
    {
        if(parFileExists)
        {
            RPG::Image::destroy(hudGraphics);
        }
    }
}
