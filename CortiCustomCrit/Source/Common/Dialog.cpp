/* Enthält nicht-makerspezifische Hilfsfunktionen.

Benötigt:
#include <sstream>
#include <algorithm>
#include <fstream>  */

namespace Dialog
{
void Show( int value, std::string caption )
{
    std::stringstream strea;
    strea.clear();
    strea << value;
    MessageBox ( NULL, strea.str().c_str(),  caption.c_str(),  MB_OK | MB_ICONWARNING );
}

void Show ( std::string text, std::string caption )
{
    MessageBox ( NULL, text.c_str(),  caption.c_str() ,  MB_OK | MB_ICONWARNING );
}
}
