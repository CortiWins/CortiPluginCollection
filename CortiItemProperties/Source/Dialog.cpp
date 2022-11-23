/* Enthält nicht-makerspezifische Hilfsfunktionen.

Benötigt:
#include <sstream>
#include <algorithm>
#include <fstream>  */

namespace Dialog
{

void ShowInfoBox( int value, std::string str )
{
    std::stringstream strea;
    strea.clear();
    strea << value;
    MessageBox ( NULL, strea.str().c_str(),  str.c_str(),  MB_OK | MB_ICONWARNING );
}

void ShowInfoBox ( std::string value, std::string str )
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

}
