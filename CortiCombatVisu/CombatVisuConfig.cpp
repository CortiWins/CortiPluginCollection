namespace Config
{
// Konstanten
const int MAXNUMSLOTS = 20;

// Anzeigepositionen ( vorberechnet )
int slotDrawPositionX[MAXNUMSLOTS];
int slotDrawPositionY[MAXNUMSLOTS];

// Enthält Configuration
std::map<std::string, std::string> configMap;

// Anzahl gleichzeitig gezeigter Icons
int numberOfShown = 8;

// Ursprungsposition
int drawPositionXOriginal = 297;
int drawPositionYOriginal = 1;

// Anordnung

// Verschiebung des ersten Icons in X zu den anderen
int iconOffsetX = 0;
// Verschiebung des ersten Icons in Y zu den anderen
int iconOffsetY = 0;
// Abstand zwischen den Icons in X
int iconSpaceBetweenX = 17;
// Abstand zwischen den Icons in X
int iconSpaceBetweenY = 17;
// Icongröße der Helden- und Monstericons
int HeroIconSizeX = 22;
int HeroIconSizeY = 16;
// Abstand der Heldenicons auf der Grafik in Y zueinander
int HeroIconOffsetY = 17;
// Monster Number
// Offset zur Position des Icons
int NumberOffsetToIconX = 15;
int NumberOffsetToIconY = 7;
// Ausmaße einzelner Zahlenicons in der Grafik
int NumberSizeX = 7;
int NumberSizeY = 9;
// Abstand der Zahlenicons zueinander
int NumberOffsetInImage = 8;

// Conditions die den Helden handlungsunfähig machen müssen speziell behandelt werden.
// Betroffene Helden werden in der Liste nach unten sortiert.
bool isConditionFilterEnabled = false;
std::vector<int> conditionFilterVector;

// Verschiebung der CC-Icons in X zu den anderen
int conditionAfflictedOffsetX = 0;
// Verschiebung der CC-Icons in Y zu den anderen
int conditionAfflictedOffsetY = 0;

// Gibt an, ob eine Hintergrundgrafik angezeigt wird.
bool backgroundFileActive;
std::string backgroundFile;
int backgroundPositionX;
int backgroundPositionY;

// Maximaler Wert, den sich ein Icon durch das ATb Mapping bewegen kann. Zur Zeit nicht konfigurierbar.
const int atbMappingMaxOffset = 20;
// Gibt an, ob die Kämpfericons auf Basis ihres ATB Wert verschoben sind.
bool useAtbMapping = false;
// Gibt an, ob der Verschiebungsbereich durch eine Grafik dargestellt wird.
bool useAtbMappingGradiant = false;
// Pfad zur hinterlegten Datei.
std::string atbMappingGradientFile;

// Gibt an, ob angezielte Kämpfer durch einen Selektor ausgewählt sein sollen.
bool isMonsterSelektorEnabled = false;
std::string monsterSelectorFile;
int monsterSelectorOffsetX = 0;
int monsterSelectorOffsetY = 0;
int monsterSelectorFramesMax = 0;
// Werden aus Bildgröße und monsterSelectorFramesMax berechnet.
int monsterSelectorSizeX = 0;
int monsterSelectorSizeY = 0;

// ID des Switches, dass angibt, ob die CombatVisu gezeigt werden soll.
// Wird bei Gewinnen oder Verlieren automatisch auf OFF gesetzt.
int SWI_Show = 0;

bool FileExist(std::string filename)
{
    // benötigt #include <fstream>
    std::ifstream ifile(filename.c_str()); // Try to open file for reading
    return (bool)ifile; // Casted to bool here, so true if ifile != null, i.e. it exists
}

//! Gets a value from the configuration. if the values does not exist, returns '0'
int GetValueFromConfig(std::map<std::string, std::string> configMap, std::string variableKey)
{
    if(configMap.count(variableKey))
    {
        return atoi(configMap[variableKey].c_str());
    }

    return 0;
}

// Berechnet die X und Y Position der einzelnen Slots in der Anzeige.
void PrecalcPositions()
{
    // Rücksetzen auf Originalpositionen
    int drawPositionY = drawPositionYOriginal;
    int drawPositionX = drawPositionXOriginal;

    int drawPositionXOffset = iconOffsetX;
    int drawPositionYOffset = iconOffsetY;

    for ( int iRunsFine = 0; iRunsFine < MAXNUMSLOTS; iRunsFine++ )
    {
        // Save Position
        slotDrawPositionX[iRunsFine] = drawPositionX + drawPositionXOffset;
        slotDrawPositionY[iRunsFine] = drawPositionY + drawPositionYOffset;

        drawPositionXOffset = 0;
        drawPositionYOffset = 0;

        // Offsets zwischen den einzelnen Icons
        drawPositionY += iconSpaceBetweenY;
        drawPositionX += iconSpaceBetweenX;
    }
}

// Prüft, ob Skills für den CC Filter hinterlegt sind.
void LoadCrowdControlsConditions()
{
    int countUp = 1;

    /* Durchsuchen der  ConfigMap nach validen Ersatzeinträgen */
    // Nach Keys des Namens "ConditionX" suchen, wobei X solange erhöht wird bis ein Eintrag nicht gefunden wurde.
    while(true)
    {
        std::stringstream keyName;
        keyName << "Condition" << countUp;

        // Check ob Key "ConditionX" vorhanden ist
        if(configMap.count(keyName.str()))
        {
            int condtionId = atoi(configMap[keyName.str()].c_str());
            if( (condtionId > 0 ) && ( condtionId < 500) )
            {
                // ConditionId gefunden -> in Vektor hinterlegen
                conditionFilterVector.push_back(condtionId);
            }
        }
        else
        {
            // ConditionX nicht gefunden, Schleife beenden.
            break;
        }

        countUp++;
    }

    // Wenn Conditions vorhanden, Filterung aktivieren
    if(conditionFilterVector.empty())
    {
        isConditionFilterEnabled = false;
    }
    else
    {
        isConditionFilterEnabled = true;
    }
}

void LoadConfig()
{
    numberOfShown = GetValueFromConfig(configMap,"NumberOfShownIcons" );
    if(numberOfShown<6 || numberOfShown > MAXNUMSLOTS) // Prüfen auf Minimum und Maximum
    {
        Dialog::Show(numberOfShown,"CortiCombatVisu: Value of NumberOfShownIcons Invalid.");
        numberOfShown = 8;
    }

    SWI_Show = GetValueFromConfig(configMap,"VisibilitySwitch" );

    // Die Ursprungsposition der Leiste
    drawPositionXOriginal = GetValueFromConfig(configMap,"PositionXOriginal" );
    drawPositionYOriginal = GetValueFromConfig(configMap,"PositionYOriginal" );

    iconOffsetX = GetValueFromConfig(configMap,"IconsOffsetX" );
    iconOffsetY = GetValueFromConfig(configMap,"IconsOffsetY" );

    // Abstand zwischen den Icons in X
    iconSpaceBetweenX = GetValueFromConfig(configMap,"IconSpaceBetweenX" );
    iconSpaceBetweenY = GetValueFromConfig(configMap,"IconSpaceBetweenY" );

    // Ausmaße einzelner Zahlenicons in der Grafik
    NumberSizeX = GetValueFromConfig(configMap,"NumberSizeX" );
    NumberSizeY = GetValueFromConfig(configMap,"NumberSizeY" );

    // Abstand der Zahlenicons zueinander in der 'MonsterNumbers.png' in X
    NumberOffsetInImage = GetValueFromConfig(configMap,"NumberOffsetInImage" );

    // Offset zur Position des Icons
    NumberOffsetToIconX = GetValueFromConfig(configMap,"NumberOffsetToIconX" );
    NumberOffsetToIconY = GetValueFromConfig(configMap,"NumberOffsetToIconY" );


    HeroIconSizeX = GetValueFromConfig(configMap,"HeroIconSizeX" );
    HeroIconSizeY = GetValueFromConfig(configMap,"HeroIconSizeY" );
    HeroIconOffsetY = GetValueFromConfig(configMap,"HeroIconOffsetY" );

    // Verschiebung der CC-Icons zu den anderen
    conditionAfflictedOffsetX = GetValueFromConfig(configMap,"ConditionAfflictedOffsetX" );
    conditionAfflictedOffsetY = GetValueFromConfig(configMap,"ConditionAfflictedOffsetY" );

    // Hintergrundbild
    backgroundFileActive = false;
    backgroundPositionX = 0;
    backgroundPositionY = 0;

    // Dateiname der Datei, die als Hintergrund dienen soll
    backgroundPositionX = GetValueFromConfig(configMap,"BackgroundPositionX" );
    backgroundPositionY = GetValueFromConfig(configMap,"BackgroundPositionY" );
    if(configMap.count("BackgroundFile"))
    {
        backgroundFile = configMap["BackgroundFile"];
        if(FileExist(backgroundFile))
        {
            backgroundFileActive = true;

        }
        else
        {
            Dialog::Show(backgroundFile,"[CortiCombatVisu] BackgroundFile does not exist:");
        }
    }

    // Gibt an, ob angezielte Kämpfer durch einen Selektor ausgewählt sein sollen.

    if(configMap.count("MonsterSelectorFile"))
    {
        monsterSelectorFile  = configMap["MonsterSelectorFile"];
        if(FileExist(monsterSelectorFile))
        {
            isMonsterSelektorEnabled = true;
            monsterSelectorFramesMax = std::max(1, GetValueFromConfig(configMap,"MonsterSelectorFramesMax" ));
            monsterSelectorOffsetX = GetValueFromConfig(configMap,"MonsterSelectorOffsetX" );
            monsterSelectorOffsetY = GetValueFromConfig(configMap,"MonsterSelectorOffsetY" );
        }
        else
        {
            Dialog::Show("Parameter: Configured file MonsterSelectorFile is missing.", "[CortiCombatVisu] Warning:");
        }
    }

    useAtbMapping = GetValueFromConfig(configMap,"AtbMapping" ) > 0;
    if(configMap.count("AtbMappingGradiant"))
    {
        atbMappingGradientFile  = configMap["AtbMappingGradiant"];
        if(FileExist(atbMappingGradientFile))
        {
            useAtbMappingGradiant = true;
        }
        else
        {
            Dialog::Show("Parameter: File AtbMappingGradiant is missing.","Warning: CortiCombatVisu");
        }
    }
}
}
