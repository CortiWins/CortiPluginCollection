namespace CortiAtbSpeedConfig
{
// O N E   F I L L E D
bool DisableSlowWhenFilled ( false );

// C O N D I T I O N S
bool conditionFilter ( false );
std::vector<int> conditionVector;

// S L O W - S W I T C H E S
bool slowSwitchesPresend = false;
std::vector<int> slowSwitchesVector;

// S P E E D A D J U S T M E N T
//! Wert für ATB-Speed pro Battler im Fastmode
int SpeedPerBattler = 150;

// A C C E L E R A T I O N
bool AccelerationAfterTurnEnable ( true );
//! Anzahl Frames, nach Handlung, die das Atb langsam bleibt
int AccelerationAfterTurnFrames ( 60 );

// B R A K E
// Feature: Bremswirkung zum Ende der Atb-Leiste. Verhindern, dass multiple Teilnehmer gleichzeitig  ihre Kampfhandlung  beginnen
bool BrakeBeforeTurnEnable ( true );
//! Abschnitt vor "voll" ab dem der AtbSpeed gebremst wird
int BrakePart ( 15000 );
//! Atb-Wert ab dem der AtbSpeed gebremst wird
int BrakePartInverse ( 300000 - BrakePart );

// W I T H I N   T U R N S
bool SlowWithinTurnsEnable ( true );

// A C T I O N   S L O W D O W N
int WithinActionSlowdownDefenseMax ( 30 ); // 30
int WithinActionSlowdownMax ( 60 ); // 70
int WithinActionSlowdownMaxDone ( 40 ); // 60
int HitsFullSlowdownMax ( 25 ); // 30

// A U T O - E N T E R
bool useSimulateReturnKey ( false );

// A T B - E N T Z E R R E N
bool useDifferentAtbInit = true;
}

namespace CortiAtbSpeed
{
//! Konstante für maximale Anzahl Monster
const int kNumberOfMonsters = 8;
//! Konstante für maximale Anzahl Helden
const int kNumberOfHeros = 4;
//! Konstante für ATB-Speed im SemiFreeze Mode, also während der Züge.
const int kSpeedSemiFreeze = 1; // 1
//! Konstante des maximalen Atb-Wertes
const int kAtbMax = 300000;

// Feature: Verlangsamen bei Handlung sowie Beschleunigung nach Abschließen der Kampfhandlungen
//! Aktuelle Anzahl Frames seit der letzten Handlung
int actionSlowDownFrames = 0;
//! Flag ob ein Kampfteilnehmer eine gefüllte Atb-Leiste hat für Slowdown-Effekt
bool oneIsFull = false;

bool dbg_oneFullMonsters = false;
bool dbg_oneFullHeros = false;
bool dbg_oneFullSlowSwitches = false;
bool dbg_oneFullWithinTurn = false;

//! Gesetzt wenn das ActionCommand-Menü im "Chose Hero Command"-State gezeigt wird. Resettet in jedem OnFrame.
bool chosenMenuIsShown = false;

// Max. Atb-Wert eines Teilnehmers zum Bremsverhalten
int maximumAtbValue = 0;
int numBattlers = 0;

// Debug:
int numMonstersInGroup = 0;
int numMonstersHidden = 0;
int numMonstersNotHidden = 0;
int numHeros = 0;
int numTellingToWaitHero = 0;
int numTellingToWaitMonster = 0;
int numAfflictedByFilter = 0;

// Gesetzt wenn das ActionCommand-Menü im "Hit Decision"-State gezeigt wird. Resettet in jedem OnFrame.
bool unChosenMenuIsShown = false;
// Totzeit zwischen Press & Release
int frames = 0;
// Index des helden, dessen ActionCommand-Menü gezeigt wird. Gesetzt in "onBattleStatusWindowDrawn"
int selectedHeroIndexZb = 0;

int withinActionSlowdown = 0;

//! Atb-Modus auf "Wait" setzen. Dadurch stoppen die Kampfhandlungen während der Spieler seine Aktion auswählt.
void SetAtbModeWait()
{
    if ( RPG::system->atbMode != RPG::ATBM_WAIT )
    {
        RPG::system->atbMode = RPG::ATBM_WAIT;
    }
}

void CountMonsters()
{
    for ( int iFor = 0; iFor < ( kNumberOfMonsters ); iFor++ )
    {
        RPG::Monster *mon = RPG::monsters[iFor];
        if ( mon != NULL )
        {
            numMonstersInGroup++;
            if ( mon->notHidden )
            {
                numMonstersNotHidden++;
                numBattlers++; // Each Monster
            }
            else
            {
                numMonstersHidden++;
            }

            if ( ( mon->atbValue == kAtbMax ) )
            {
                oneIsFull = true;
                dbg_oneFullMonsters = true;
                withinActionSlowdown = CortiAtbSpeedConfig::HitsFullSlowdownMax;
                numTellingToWaitMonster++;
            }
            else
            {
                if ( mon->atbValue > maximumAtbValue )
                {
                    maximumAtbValue = mon->atbValue;
                }
            }
        }
        else
        {
            return;
        }
    }
}

void CountHeros()
{
    bool filteredOut;
    for ( int iFor = 0; iFor < ( kNumberOfHeros ); iFor++ )
    {
        RPG::Actor *act = RPG::Actor::partyMember ( iFor );
        if ( act != NULL )
        {
            numHeros++;
            filteredOut = false;

            if ( CortiAtbSpeedConfig::conditionFilter ) // Filterflag gesetzt
            {
                for ( unsigned int x = 0; x < CortiAtbSpeedConfig::conditionVector.size(); x++ )
                {
                    if ( act->conditions[CortiAtbSpeedConfig::conditionVector[x] ] > 0 )
                    {
                        numAfflictedByFilter++;
                        filteredOut = true;
                        continue;
                    }

                }
            }

            numBattlers++; // Each Hero

            if ( ( act->atbValue == kAtbMax ) )
            {
                if ( !CortiAtbSpeedConfig::DisableSlowWhenFilled && !filteredOut )
                {
                    oneIsFull = true;
                    dbg_oneFullHeros = true;
                    numTellingToWaitHero++;
                }
            }
            else
            {
                // Not at max
                if ( ( act->atbValue > maximumAtbValue )  &&  !filteredOut  )
                {
                    maximumAtbValue = act->atbValue;
                }
            }
        }
        else
        {
            return;
        }
    }
}

void CheckSlowSwitches()
{
    if ( CortiAtbSpeedConfig::slowSwitchesPresend ) // Filterflag gesetzt
    {
        for ( unsigned int x = 0; x < CortiAtbSpeedConfig::slowSwitchesVector.size(); x++ )
        {
            if ( RPG::switches[CortiAtbSpeedConfig::slowSwitchesVector[x]] == true )
            {
                oneIsFull = true;
                dbg_oneFullSlowSwitches = true;
                return;
            }
        }
    }
}

int battleSpeedValueByNumbers;
int battleSpeedValueBySlow;

void UpdateAtbSpeed()
{
    // Resetten der Variablen vor dem erneuten Durchzählen
    numBattlers = 0;
    oneIsFull = false;
    int missingPerc = 0;
    maximumAtbValue = 0;

    dbg_oneFullMonsters = false;
    dbg_oneFullHeros = false;
    dbg_oneFullSlowSwitches = false;
    dbg_oneFullWithinTurn = false;

    numMonstersInGroup = 0;
    numMonstersHidden = 0;
    numMonstersNotHidden = 0;
    numHeros = 0;
    numTellingToWaitHero = 0;
    numTellingToWaitMonster = 0;
    numAfflictedByFilter = 0;

    // Zählen anwesender Monster und Helden sowie prüfen, ob ein Monster oder Held gerade seinen Zug macht.
    CountMonsters();
    CountHeros();
    if(!oneIsFull)
    {
        CheckSlowSwitches();
    }

    if ( withinActionSlowdown > 0 )
    {
        withinActionSlowdown--;
        if(CortiAtbSpeedConfig::SlowWithinTurnsEnable)
        {
            oneIsFull = true;
            dbg_oneFullWithinTurn = true;
        }
    }

    if ( chosenMenuIsShown )
    {
        actionSlowDownFrames = CortiAtbSpeedConfig::AccelerationAfterTurnFrames;
        RPG::battleSpeed = 0;
    }
    else if ( oneIsFull )  // No Maxspeed,somit einmal slowen
    {
        actionSlowDownFrames = CortiAtbSpeedConfig::AccelerationAfterTurnFrames;
        RPG::battleSpeed = kSpeedSemiFreeze;
    }
    else // no Atbbar filled and no hero ist within turn -> fast mode
    {
        // Es werden drei Speedwerte errechnet.
        // * Speed auf Basis der Kampfteilnehmer
        // * Slowdownspeed für das Beschleunigungsverhalten zu Beginn der Atb-Leiste
        // * BrakeSpeed für das Bremsverhalten zum Ende der Atb-Leiste.
        // Beim Slowdownspeed wird die Geschwindigkeit des Systems bei einer Handlung auf Null gesetzt und dann mit jedem Frame wieder erhöht.
        // Beim Brakespeed wird die Geschwindigkeit in Abhängigkeit des Teilnehmers, der der vollen Atb-Leiste am nähesten ist auf bis zu 20% reduziert.

        // MaxSpeed auf Basis anwesender Battler
        battleSpeedValueByNumbers = CortiAtbSpeedConfig::SpeedPerBattler *  numBattlers;
        battleSpeedValueBySlow = battleSpeedValueByNumbers;

        if ( CortiAtbSpeedConfig::AccelerationAfterTurnEnable )
        {
            // Verringerter MaxSpeed auf Basis des Slowdowns nach Handlungen
            battleSpeedValueBySlow = battleSpeedValueByNumbers * ( CortiAtbSpeedConfig::AccelerationAfterTurnFrames -  actionSlowDownFrames )
                                     / CortiAtbSpeedConfig::AccelerationAfterTurnFrames;
            // Wenn sich der Atb-Wert eines Kampfteilnehmers im Bremsbereich der Atb-Leiste befindet, wird die Atb-Geschwindigkeit prozentual reduziert
        }

        if ( CortiAtbSpeedConfig::BrakeBeforeTurnEnable )
        {
            if ( maximumAtbValue > CortiAtbSpeedConfig::BrakePartInverse )
            {
                // Bei maximumAtbValue entsprechend 300k soll der Atb-Speed-Wert um 80% verringert werden
                // Das ist der Fall wenn die Diff aus maxAtb ( 300k ) und Inversem BrakeValue ( 290k) 100% des BrakeValues (10k) entspricht.
                // Diese sind dann die 80% des Atb-Speeds die entfernt werden
                missingPerc =  ( maximumAtbValue - CortiAtbSpeedConfig::BrakePartInverse ) * 99 / CortiAtbSpeedConfig::BrakePart;
                battleSpeedValueByNumbers = ( battleSpeedValueByNumbers * (     100 -  missingPerc ) ) / 100;
            }
        }

        // Setzen des neuen Atb-Wertes, minimal 1.
        RPG::battleSpeed = std::max ( 1, std::min ( battleSpeedValueByNumbers, battleSpeedValueBySlow ) );

        // Slowdown reduzieren wenn ATB-Zustand nicht in reduziertem Zustand ( Beschleunigung )
        if ( actionSlowDownFrames > 0 )
        {
            actionSlowDownFrames--;
        }
    }
}

// DifferentAtbInit: Verändern der Atb-Werte für die Helden
void ReduceAtbValuesHeros()
{
    for(int i=0; i<4; i++)
    {
        RPG::Actor *actPtr = RPG::Actor::partyMember(i);
        if(actPtr!=NULL)
        {
            if(actPtr->atbValue>100000)
            {
                actPtr->atbValue = actPtr->atbValue - ((  ( 300000 * 5 )/ 100) * (i));
            }
            else
            {
                actPtr->atbValue = actPtr->atbValue + ((  ( 300000 * 5 )/ 100) * (i));
            }
        }
        else
        {
            return;
        }
    }
}

// DifferentAtbInit: Verändern der Atb-Werte für die Monster
void ReduceAtbValuesMonster()
{
    for(int i=0; i<8; i++)
    {
        RPG::Monster *monPtr = RPG::monsters[i];
        if(monPtr!=NULL)
        {
            if(monPtr->atbValue>100000)
            {
                monPtr->atbValue = monPtr->atbValue - ((  ( 300000 * 5 )/ 100) * (monPtr->id - 1));
            }
            else
            {
                monPtr->atbValue = monPtr->atbValue + ((  ( 300000 * 5 )/ 100) * (monPtr->id - 1));
            }
        }
        else
        {
            return;
        }
    }
}

void OnFrameBattleKeys()
{
    // Wenn System inaktiv -> raus
    if(!KeyPressSimu::useSystem)
    {
        // Rücksetzen
        unChosenMenuIsShown = false;
        chosenMenuIsShown = false;
        return;
    }

    // Prüfen, ob das Deaktivierungsswitch aktiv ist
    if(KeyPressSimu::checkDeadSwitch)
    {
        if(RPG::switches[KeyPressSimu::deadSwitch] == true)
        {
            // Rücksetzen
            unChosenMenuIsShown = false;
            chosenMenuIsShown = false;
            return;
        }
    }

    // Wenn eine Taste gedrückt ist, loslassen nach zwei Frames
    if(KeyPressSimu::virtualKeyCode != 0)
    {
        if(frames==2)
        {
            //Helper::ShowInfoBoxString("RESET!!","Plastiktischler");
            KeyPressSimu::ReleaseKey();
        }
        else
        {
            frames++;
        }
    } // Wenn keine Taste gedrückt ist, und ein Nichtselektiertes Menü angezeigt wird
    else if(unChosenMenuIsShown && (KeyPressSimu::virtualKeyCode==0) )
    {
        // Helper::ShowInfoBoxString("PRFESS MAYBE!","Plastiktischler");
        RPG::Actor *actPtr = RPG::Actor::partyMember(selectedHeroIndexZb);
        if(actPtr!=NULL)
        {
            // Kontrollieren, ob der Actor bei vollem ATB ist, da das Fenster fehlerhafterweise nach LinkToEvent-Commands bestehen bleibt
            if(actPtr->atbValue == 300000)
            {
                // Helper::ShowInfoBox(selectedHeroIndexZb,"HitReturn on selection");
                KeyPressSimu::SendKey(VK_RETURN);
                frames = 0;
            }
        }
    }

    // Rücksetzen
    unChosenMenuIsShown = false;
    chosenMenuIsShown = false;
}
}
