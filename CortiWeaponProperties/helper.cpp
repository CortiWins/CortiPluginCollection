/*
Enthält nicht-makerspezifische Hilfsfunktionen.
*/
#include <sstream> // For std::stringstream

namespace Helper
{
// Locals made statics
int i, j;   // needed for the loops                                                            // BubbleSort(), BubbleSortDoubleArray()
int tmp;    // needed for swapping values between two variables          // BubbleSort(), BubbleSortDoubleArray()
int tmpSynch;   // needed for swapping values between two variables // BubbleSortDoubleArray

void BubbleSort ( int arrayToSort[], int sizeOfArray, bool ascendingOrder )
{
    if ( sizeOfArray <= 1 ) return;   // check if the array has no elements or has 1 element
    // in that case there is no need of sorting

    i = 1;  // initializing the variable i
    do// the start of a do/while loop
    {
        for ( j = sizeOfArray - 1; j >= i; --j ) // for loop that goes backwards and compares
        {
            if ( ascendingOrder )
            {
                if ( arrayToSort[j - 1] < arrayToSort[j] ) // if the condition is met then swap
                {
                    tmp = arrayToSort[j - 1];
                    arrayToSort[j - 1] = arrayToSort[j];
                    arrayToSort[j] = tmp;
                }
            }
            else
            {
                if ( arrayToSort[j - 1] > arrayToSort[j] ) // if the condition is met then swap
                {
                    tmp = arrayToSort[j - 1];
                    arrayToSort[j - 1] = arrayToSort[j];
                    arrayToSort[j] = tmp;
                }
            }
        }

    }
    while ( ++i < sizeOfArray );
}

void BubbleSortDoubleArray ( int arrayToSortBy[], int  arrayToSynch[], int sizeOfArray, bool ascendingOrder )
{
    if ( sizeOfArray <= 1 ) return;  // check if the array has no elements or has 1 element
    // in that case there is no need of sorting

    i = 1;  // initializing the variable i
    do// the start of a do/while loop
    {
        for ( j = sizeOfArray - 1; j >= i; --j ) // for loop that goes backwards and compares
        {
            if ( ascendingOrder )
            {
                if ( arrayToSortBy[j - 1] < arrayToSortBy[j] ) // if the condition is met then swap
                {
                    tmp = arrayToSortBy[j - 1];
                    arrayToSortBy[j - 1] = arrayToSortBy[j];
                    arrayToSortBy[j] = tmp;

                    tmpSynch = arrayToSynch[j - 1];
                    arrayToSynch[j - 1] = arrayToSynch[j];
                    arrayToSynch[j] = tmpSynch;
                }
            }
            else
            {
                if ( arrayToSortBy[j - 1] > arrayToSortBy[j] ) // if the condition is met then swap
                {
                    tmp = arrayToSortBy[j - 1];
                    arrayToSortBy[j - 1] = arrayToSortBy[j];
                    arrayToSortBy[j] = tmp;

                    tmpSynch = arrayToSynch[j - 1];
                    arrayToSynch[j - 1] = arrayToSynch[j];
                    arrayToSynch[j] = tmpSynch;
                }
            }
        }

    }
    while ( ++i < sizeOfArray );
}


void ShowInfoBox( int value, std::string str )
{

    std::stringstream strea;
    strea.clear();
    strea << value;

    MessageBox ( NULL, strea.str().c_str(),  str.c_str(),  MB_OK | MB_ICONWARNING );
}


void ShowInfoBoxChar ( int value, char *caption )
{
    std::stringstream strea;
    strea.clear();
    strea << value;
    MessageBox ( NULL, strea.str().c_str(),  caption,  MB_OK | MB_ICONWARNING );
}

void ShowInfoBox ( char *value, char *caption )
{
    MessageBox ( NULL, value,  caption,  MB_OK | MB_ICONWARNING );
}

void ShowInfoBox ( char *value, std::string str )
{
    char * writable = new char[str.size() + 1];
    std::copy ( str.begin(), str.end(), writable );
    writable[str.size()] = '\0'; // don't forget the terminating 0

    MessageBox ( NULL, value,  writable ,  MB_OK | MB_ICONWARNING );

    // don't forget to free the string after finished using it
    delete[] writable;
}

void ShowInfoBoxString ( std::string value, std::string str )
{
    char * writable = new char[str.size() + 1];
    std::copy ( str.begin(), str.end(), writable );
    writable[str.size()] = '\0'; // don't forget the terminating 0

    char * writableValue = new char[value.size() + 1];
    std::copy ( value.begin(), value.end(), writableValue );
    writableValue[value.size()] = '\0'; // don't forget the terminating 0

    MessageBox ( NULL, writableValue,  writable ,  MB_OK | MB_ICONWARNING );

    // don't forget to free the string after finished using it
    delete[] writable;
    delete[] writableValue;
}

void ShowInfoBox ( LPCWSTR value, LPCWSTR caption )
{
    MessageBoxW ( NULL, value,  caption,  MB_OK | MB_ICONWARNING );
}

// Transformiert einen String in eine kleinegeschriebene Variante.
std::string MakeLowerCase(std::string mixedCase)
{
    // benötigt <algorithm>
    std::transform(mixedCase.begin(), mixedCase.end(), mixedCase.begin(), ::tolower);
    return mixedCase;
}

bool FileExist(std::string filename)
{
    // benötigt #include <fstream>
    std::ifstream ifile(filename.c_str()); // Try to open file for reading
    return (bool)ifile; // Casted to bool here, so true if ifile != null, i.e. it exists
}

RPG::Image* imgPtr = NULL;
void ShowDebugNumber(int x, int y, int num)
{
    if(imgPtr == NULL)
    {
        if(FileExist("D:\\Daten\\Privat\\Project1\\DynRessource\\DebugNumbers.png"))
        {
            imgPtr = RPG::Image::create();
            imgPtr->useMaskColor = true;
            imgPtr->alpha = 255;
            imgPtr->loadFromFile("D:\\Daten\\Privat\\Project1\\DynRessource\\DebugNumbers.png", false);
        }
    }

    if(imgPtr != NULL)
    {
        RPG::screen->canvas->draw(  // oben links
            x,          // 0 - Referenz, Kante Monster - Links
            y,          // 0 - Referenz, Kante Monster - Oben
            imgPtr,
            0,
            num*16,
            16,
            16);
    }
}

void FreeHelperRessource()
{
if(imgPtr != NULL)
    {
        RPG::Image::destroy(imgPtr);
    }
}

void InitRandomSeed()
{
    SYSTEMTIME st;
    GetSystemTime(&st);
    srand(st.wMilliseconds);  // Initialize random number generator.
}

int GetRandomNumber ( int min, int max )
{
    // Zahl 0 bis...irgendwas generieren
    int randomNumber = (rand() % ( max - min + 1 )) + min;
    /*
            // Example min 3, max 7 : ergibt mögliche Werte 3,4,5,6,7 -> 5 Werte
            // ModValue = 7 - 3 = 4, es sollten aber 5 Werte werden, also +1
            int modValue = ( max - min ) + 1;
            // Hieraus gibt sich dann ein Wert von 0 bis 4
            int randomModulized = randomNumber % modValue;
            // Adidert man Min(3) zu (0...4) ergibt das (3...7)
            int returnrandom = randomModulized + min;
            */

    return randomNumber;
}

bool lastBit = false;
bool GetRandomBit ()
{
    // Zahl 0 bis...irgendwas generieren
    int randomNumber = rand() % 3; // Results in ... 0,1,2
    if(randomNumber==1)
    {
        lastBit = true;
        return true;
    }
    else if(randomNumber==2)
    {
        lastBit = false;
        return false;
    }
    else
    {
        lastBit = !lastBit;
        return lastBit;
    }

}

int GetNumberOfDigits ( int zahl )
{
    if ( zahl > 9999999 )
    {
        return 8;
    }
    else if ( zahl > 999999 )
    {
        return 7;
    }
    else if ( zahl > 99999 )
    {
        return 6;
    }
    else if ( zahl > 9999 )
    {
        return 5;
    }
    else if ( zahl > 999 )
    {
        return 4;
    }
    else if ( zahl > 99 )
    {
        return 3;
    }
    else if ( zahl > 9 )
    {
        return 2;
    }
    else
    {
        return 1;
    }
}
}
