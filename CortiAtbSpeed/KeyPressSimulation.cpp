namespace KeyPressSimu
{
// Dieses Feature aktiviert?
bool useSystem = false ;
// ID des Switches, mit dem das KeyPress-Feature temporär deaktiviert werden kann.
int deadSwitch = 0;

// DeadSwitch Prüfung aktiv
bool checkDeadSwitch = false;

//! Handel des Fensters des Spieles, Fenstername konstant gesetzt in "SendKeyState"
HWND _gameWindow; // FindWindow aufgerufen in "LoadMaterial"()

//! Zuletzt gesendeter KeyCode, wird resettet (0) wenn die taste losgelassen wird.
int virtualKeyCode = 0;

/*! \brief Schickt das Kommando eine Taste zu drücken oder loszulassen.
@param keyCode Der Keycode der zu drückenden/loszulassenden Taste
@param keyUp Loslassen (true) oder runterdrücken (false) .
@note Mögliche Keycodes: http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731%28v=vs.85%29.aspx  */
void SendKeyState(int keyCode, bool keyUp)
{
    // Prüfen, ob Fenster beim Ressourcen laden gefunden wurde.
    if( _gameWindow)
    {
        // Struktur für Konfiguration des zu sendenden KeyCodes
        // The type of the input event. Can be Keyboard, Mouse, Hardware
        INPUT InputData;
        // Rückgabewert des Sendevorgangs, ungenutzt
        int iEvents;
        // RPG_RT-Fenster in den Vordergrund holen, damit es die Tastendrücke empfängt
        SetForegroundWindow(_gameWindow);
        // Wenn Keyboard -> ki.Substrutur parametrieren
        InputData.type = INPUT_KEYBOARD;
        // Tastencode ( Mögliche Codes: http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731%28v=vs.85%29.aspx )
        InputData.ki.wVk = keyCode;
        InputData.ki.wScan = 0; // Unicodeeinstellungsmöglichkeit, brauche ich nicht.
        InputData.ki.dwFlags  = keyUp ? KEYEVENTF_KEYUP : 0; // Unterscheidung ob Loslassen oder Runterdrücken
        InputData.ki.time = time(NULL);
        InputData.ki.dwExtraInfo = GetMessageExtraInfo();

        // Senden des simulierten Tastendrucks
        iEvents = SendInput(
                      (UINT)1,                   // The number of structures in the pInputs array.
                      &InputData,            // An array of INPUT structures. Each structure represents an event to be inserted into the keyboard or mouse input stream.
                      sizeof(InputData)   // The size, in bytes, of an INPUT structure.
                      // Für Array[]-Variante
                      //InputData,           // An array of INPUT structures. Each structure represents an event to be inserted into the keyboard or mouse input stream.
                      //sizeof(*InputData) // The size, in bytes, of an INPUT structure.
                  );
    }
}

//! Drücken einer Taste und merken des Tastendrucks. Kein Senden möglich wenn bereits eine andere Taste gedrückt.
void SendKey(int keyCode)
{
    if(virtualKeyCode!=0)
    {
        return;
    }

    SendKeyState(keyCode, false);
    virtualKeyCode = keyCode;
}

//! Loslassen der zuletzt gedrückten Taste.
void ReleaseKey()
{
    // Prüfung ob was gedrückt war an aufrufender Stelle
    SendKeyState(virtualKeyCode, true);
    virtualKeyCode = 0;
}

/* Material Managers  */
void GetWindowOnInit()
{
    char* rpgrt = (char*)"RPG_RT";
    char* rpgrtin = (char*)"RPG_RT.ini";
    std::map<std::string, std::string> configMap = RPG::loadConfiguration(rpgrt,rpgrtin);
     //std::map<std::string, std::string> configMap = RPG::loadConfiguration("RPG_RT","RPG_RT.ini");
     // Helper::ShowInfoBox( configMap.size(),"Confmapsize");
    // Suchen des Fensters des Makerspieles um simulierte Keys zu senden.
    _gameWindow = FindWindow(0, configMap["GameTitle"].c_str());
    // Helper::ShowInfoBoxString(configMap["GameTitle"],"ThisWindow..?");
    if(!_gameWindow)
    {
        Helper::ShowInfoBoxString("FindWindow failed. Makerfenster umbenannt? Sollte \"Untitled\" sein.","DynRPG MenuAccess Error");
        useSystem = false;
    }
}
}
