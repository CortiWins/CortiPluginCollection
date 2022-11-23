// Kapselt Daten für die Akteure
namespace CT
{
    // Anzahl Monster
    const unsigned int NUM_MONSTERS = 8;
    // Anzahl Runden über die Thread gespeichert wird.
    const unsigned int NUM_THREADROUNDS = 21;

    unsigned int threadLevel[NUM_MONSTERS];


    // map<int,*int[]>rofl;

    void ResetFields()
    {
        int rofl[44];

        int* laster = new int[NUM_THREADROUNDS];

        delete[] laster;

    }

}
