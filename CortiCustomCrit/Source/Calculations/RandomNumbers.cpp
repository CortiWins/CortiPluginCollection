namespace RandomNumbers
{
const int RNDSIZE = 100;

//! Contains the numbers from 1 to 100 in random order.
int randomNumbersHeros[RNDSIZE];
int randomNumbersHerosIndex = RNDSIZE;

int randomNumbersMonsters[RNDSIZE];
int randomNumbersMonstersIndex = RNDSIZE;

//! Fills the array which takes exactly 100 numbers with numbers from 1 to 100 and shuffles them around randomly.
void ResetDeck ( int* array)
{

    for ( int i = 0; i < RNDSIZE ; i++ )
    {
        array[i] = i + 1;
    }

    for ( int i = 0; i < RNDSIZE ; i++ )
    {
        int randomIndex = rand() % RNDSIZE;
        int temp = array[i];
        array[i] = array[randomIndex];
        array[randomIndex] = temp;
    }
}

//! Gets a random number between 1 and 100 from the pre-calculated deck.
int GetRandomNumberHeroFromDeck()
{
    if ( randomNumbersHerosIndex >= RNDSIZE )
    {
        randomNumbersHerosIndex = 0;
        ResetDeck (randomNumbersHeros );

        std::stringstream strea;
        strea.clear();

        for ( int i = 0; i < RNDSIZE ; i++ )
        {
            strea << randomNumbersHeros[i] << ", ";
        }
        LOGINFO ( "CreateNewNumbers.Heroes" );
        LOGINFO ( strea.str() );
    }

    int value = randomNumbersHeros[randomNumbersHerosIndex];
    randomNumbersHerosIndex++;
    return value;
}

//! Gets a random number between 1 and 100 from the pre-calculated deck.
int GetRandomNumberMonsterFromDeck()
{
    if ( randomNumbersMonstersIndex >= RNDSIZE )
    {
        randomNumbersMonstersIndex = 0;
        ResetDeck (randomNumbersMonsters );

        std::stringstream strea;
        strea.clear();

        for ( int i = 0; i < RNDSIZE ; i++ )
        {
            strea << randomNumbersMonsters[i] << ", ";
        }
        LOGINFO ( "CreateNewNumbers.Monsters" );
        LOGINFO ( strea.str() );
    }

    int value = randomNumbersMonsters[randomNumbersMonstersIndex];
    randomNumbersMonstersIndex++;
    return value;
}

//! Gets a random number between 1 and 100.
int GetCppRandomRoll ()
{
    return ( rand() % 100 ) + 1;
}

//! Gets a random number between 1 and 100 with the RPG-Maker function.
int GetRpgMakerRandomRoll ()
{
    return RPG::getDiceRoll(100);
}

void InitializeRandomSeed()
{
    srand(time(null));  // Initialize random number generator.
}
}
