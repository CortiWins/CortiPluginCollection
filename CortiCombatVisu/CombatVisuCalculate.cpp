int fullArrayIndex;          // Enthält die Anzahl der Kampfteilnehmer, die in den DatenArrays gespeichert sind.
int arrayId[12];                // Enthält die IDs der Kampfteilnehmer
double arrayTime[12];   // Enthält zu jedem Kampfteilnehmer die Zeit bis zum Zug nach denen sortiert wird
int arrayAgi[12];              // Enthält die Agilität der Kampfteilnehmer um nach Zeichnen den nächsten Zug zu berechnen
int arrayDbId[12];           // Enthält die Datenbank-IDs der Kampfteilnehmer
int arrayAtbValue[12];    // Enthält die Datenbank-IDs der Kampfteilnehmer

int arrayCCHeroes[4];     // Enthält die IDs in CC befindlicher Helden
int ccAfflictedNumber;    // Anzahl Helden in CC

// Die GetFastest-Funktion liefert in diese Variablen
int getFastestId;                // Die ID des aktuell schnellsten Kampfteilnehmers
int getFastestIdDatabase;// Die Datenbank-ID des aktuell schnellsten Kampfteilnehmers
int fastestIdArrayTime;     // Der Restzeitwert des aktuell schnellsten Kampfteilnehmers
int fastestAtbValue;          // ATB Wert des  aktuell schnellsten Kampfteilnehmers

// Geht alle Kampfteilnehmer durch und sortiert sie in die Arrays, wenn sie gerade am Leben und im Kampf sind.
void FillArrays()
{
    arrayCCHeroes[0] = 0;
    arrayCCHeroes[1] = 0;
    arrayCCHeroes[2] = 0;
    arrayCCHeroes[3] = 0;
    ccAfflictedNumber = 0;

    fullArrayIndex = 0;
    // Alle Helden
    for ( int iRun = 0; iRun < 4; iRun++ )
    {
        RPG::Actor *actPtr = RPG::Actor::partyMember(iRun);
        if(RPG::Actor::partyMember(iRun) !=NULL)
        {
            if(actPtr->hp>0)
            {
                bool skipThisActor = false;
                // Hier abfragen, ob in CC
                if ( Config::isConditionFilterEnabled) // Filterflag gesetzt
                {
                    for ( unsigned int x = 0; x < Config::conditionFilterVector.size(); x++ ) // Alle Filterconditions prüfen
                    {
                        // Vector enthält Conditions-IDs
                        if ( actPtr->conditions[Config::conditionFilterVector[x] ] > 0 ) // Check ob Condition des Helden mit der ID aktiv ist.
                        {
                            skipThisActor = true;
                            ccAfflictedNumber++;
                            arrayCCHeroes[4-ccAfflictedNumber] = actPtr->id; // Datenbank-ID
                        }
                    }
                }

                if(!skipThisActor)
                {
                    arrayId[fullArrayIndex] = iRun + 1;
                    arrayTime[fullArrayIndex] = (300000 - actPtr->atbValue) / actPtr->getAgility();
                    arrayAgi[fullArrayIndex] = actPtr->getAgility();
                    arrayDbId[fullArrayIndex] = actPtr->id; // Datenbank-ID
                    arrayAtbValue[fullArrayIndex] = actPtr->atbValue;
                    // hmh = km / h
                    // agi = atb / t    -> ? * agi = atb -> t = atb/agi
                    fullArrayIndex++;
                }
            }
        }
    }

    // Alle Monster
    for ( int iRun = 0; iRun < 8; iRun++ )
    {
        if(RPG::monsters[iRun] !=NULL)
        {
            RPG::Monster *monPtr = RPG::monsters[iRun];
            if(monPtr->notHidden && (monPtr->hp > 0) )
            {
                arrayId[fullArrayIndex] = iRun + 100;
                arrayTime[fullArrayIndex] = (300000 - monPtr->atbValue) / monPtr->getAgility();
                arrayAgi[fullArrayIndex] = monPtr->getAgility();
                arrayDbId[fullArrayIndex] = monPtr->databaseId; // Datenbank-ID
                arrayAtbValue[fullArrayIndex] = monPtr->atbValue;
                fullArrayIndex++;
            }
        }
    }
}

// Sucht den Kampfteilnehmer, der als nächster am Zug sein wird und berechnet danach dessen darauf folgenden Zieldurchlauf
void GetFastest()
{
    float value = 30000000;
    getFastestId = 0;
    fastestIdArrayTime = 0;
    fastestAtbValue = 0;
    int indexFound = -1;

    for ( int iRun = 0; iRun < fullArrayIndex; iRun++ )
    {
        if(arrayTime[iRun] < value)
        {
            value = arrayTime[iRun];
            getFastestId = arrayId[iRun];
            getFastestIdDatabase = arrayDbId[iRun];
            indexFound = iRun;
        }
    }

    if(indexFound>=0)
    {
        fastestIdArrayTime =  arrayTime[indexFound];
        fastestAtbValue = arrayAtbValue[indexFound];
        // Nächsten Durchlauf berechnen
        arrayTime[indexFound] += (300000 / arrayAgi[indexFound]);
        arrayAtbValue[indexFound] = 0;
    }

    return;
}
