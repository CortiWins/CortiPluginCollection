namespace HeroAttackBonus
{
// Anzahl der Helden in der Datenbank
int numberOfActors = 0;
// Zeiger auf Array für Helden-Attackbonuswerte. Wird in Größe angemessen zu Helden-DB erstellt.
int* heroAtkValues = NULL;   // Pointer to int, initialize to nothing.

// Dem Helden mit der gegebenen Datenbank-ID wird Crit-Atk zugefügt
void AddCritBonus(int heroDatabaseId)
{
    if(!Configuration::isValidSettings)
    {
        return;
    }

    if(heroAtkValues[heroDatabaseId - 1] == 0)
    {
        RPG::Actor *actPtr = RPG::actors[heroDatabaseId];
        if(Configuration::critAttackBonusType == 1)
        {
            // 1 = Es wird ein Prozentsatz der aktuellen ATK als Bonus hinzugefügt. Der Prozentsatz ist im Value-Parameter eingestellt.
            heroAtkValues[heroDatabaseId - 1] = (actPtr->getAttack() *  Configuration::critAttackBonusTypeValue) / 100;
        }
        else if(Configuration::critAttackBonusType == 2)
        {
            // 2 = Es wird ein ATK Wert der Statkurve eines Helden entnommen.
            // Die Datenkbank-ID des Helden ist im Value-Parameter eingestellt. Die ATK-Kurve wird verwendet.
            heroAtkValues[heroDatabaseId - 1] = RPG::dbActors[Configuration::critAttackBonusTypeValue]->attack[actPtr->level];
        }

        LOGINFO("Hero " << heroDatabaseId << " Add Critbonus: ATK Bonus " << heroAtkValues[heroDatabaseId - 1]);
        actPtr->attackDiff += heroAtkValues[heroDatabaseId - 1];
    }
}

// Dem Helden mit der gegebenen Datenbank-ID wird die Crit-Atk genommen wenn er welche hat.
void ResetCritBonus(int heroDatabaseId)
{
    if(heroAtkValues[heroDatabaseId - 1 ] > 0)
    {

        RPG::Actor *actPtr = RPG::actors[heroDatabaseId];
        actPtr->attackDiff -= heroAtkValues[heroDatabaseId - 1 ];
        heroAtkValues[heroDatabaseId - 1] = 0;

        LOGINFO("Hero " << heroDatabaseId << " Reset ATK Bonus");
    }
}

bool GetAtkStatus(int databaseId)
{
    return heroAtkValues[databaseId - 1 ] > 0 ? true : false;
}

// Passiert wenn das Spiel resettet wurde im Testmodus.
// Unterschied zwischen OnResetGame und OnSceneChange:
// in OnResetGame wird nur das Kritbonus-Flag resettet, das reduzieren der Attack-Werte passiert durch den Spielreset von selbst.
void OnResetGame()
{
    // Rücksetzen der Flags
    for(int iActors = 0; iActors < numberOfActors; iActors++)
    {
        heroAtkValues[iActors] = 0;
    }
}

// Aufgerufen bei Szenenwechsel zum Kampf oder vom Kampf weg. In dem Fall alle Kritboni entfernen und Animationen abbrechen
void OnSceneChange()
{
    for(int iActors = 1; iActors <= numberOfActors; iActors++)
    {
        ResetCritBonus(iActors);
    }
}

void Load()
{
    // Anzahl Helden in der Datenbank
    numberOfActors = RPG::actors.count();
    heroAtkValues = new int[numberOfActors + 1]; // Allocate n ints and save ptr in a.
    for (int i = 0; i <= numberOfActors; i++)
    {
        heroAtkValues[i] = 0;    // Initialize all elements to zero.
    }
}

void Unload()
{
    if(numberOfActors > 0)
    {
        delete [] heroAtkValues;  // When done, free memory pointed to by a.
        heroAtkValues = NULL;     // Clear a to prevent using invalid memory reference.
    }
}
}
